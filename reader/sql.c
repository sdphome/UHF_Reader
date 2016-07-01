
/*
 *   Author: Shao Depeng <dp.shao@gmail.com>
 *   Copyright 2016 Golden Sky Technology CO.,LTD
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <uhf.h>

#include <sqlite3.h>

static int sql_isspace(int x)
{
	if (x == ' ' || x == '\n' || x == '\f' || x == '\b' || x == '\r')
		return 1;
	else
		return 0;
}

static int sql_isdigit(int x)
{
	if (x <= '9' && x >= '0')
		return 1;
	else
		return 0;
}

static uint8_t sql_atou8(const char *nptr)
{
	while (sql_isspace((int)(uint8_t) * nptr))
		++nptr;

	return (uint8_t) * nptr;
}

static uint16_t sql_atou16(const char *nptr)
{
	int c;
	uint16_t total = 0;

	while (sql_isspace((int)(uint8_t) * nptr))
		++nptr;

	c = (int)(uint8_t) * nptr++;

	while (sql_isdigit(c)) {
		total = 10 * total + (c - '0');
		c = (uint8_t) * nptr++;
	}

	return total;
}

static uint32_t sql_atou32(const char *nptr)
{
	int c;
	uint32_t total = 0;

	while (sql_isspace((int)(uint8_t) * nptr))
		++nptr;

	c = (int)(uint8_t) * nptr++;

	while (sql_isdigit(c)) {
		total = 10 * total + (c - '0');
		c = (uint8_t) * nptr++;
	}

	return total;
}

static uint64_t sql_atou64(const char *nptr)
{
	int c;
	uint64_t total = 0;

/*
	while (sql_isspace((int)(uint8_t)*nptr))
		++nptr;
*/
	while (!sql_isdigit((int)(uint8_t) * nptr))
		++nptr;

	c = (int)(uint8_t) * nptr++;

	while (sql_isdigit(c)) {
		total = 10 * total + (c - '0');
		c = (uint8_t) * nptr++;
	}

	return total;
}

#if 0							/* unused */
static char *sql_u64toa(uint64_t n, char *nptr)
{
	char string[] = "0123456789";
	char *ptr = nptr;
	char temp;
	uint64_t denom = 0;
	uint64_t radix = 10;
	int count = -1;
	int i, j;

	while (n > radix) {
		denom = n % radix;
		n = n / radix;

		*ptr++ = string[denom];
		count++;
	}

	if (n) {
		*ptr++ = string[n];
		count++;
	}

	*ptr = '\0';

	j = count;

	for (i = 0; i < (count + 1) / 2; i++) {
		temp = nptr[i];
		nptr[i] = nptr[j];
		nptr[j--] = temp;
	}

	return nptr;
}
#endif

/* tag info */
int sql_create_tag_table(char *path)
{
	sqlite3 *db = NULL;
	int ret = NO_ERROR;
	char *sql = NULL;
	char *zErrMsg = NULL;

	ret = sqlite3_open(path, &db);
	if (ret != NO_ERROR) {
		printf("%s: can't open database: %s.\n", __func__, path);
		sqlite3_close(db);
		return -FAILED;
	}

	sql = "CREATE TABLE TAG(" "TID TEXT PRIMARY KEY NOT NULL,"	// TID
		"SSID INTEGER NOT NULL,"	// SelectSpecID
		"SI INTEGER NOT NULL,"	// SpecIndex
		"RFSID INTEGER NOT NULL,"	// RfSpecID
		"AID INTEGER NOT NULL,"	// AntennaID
		"FSTU INTEGER,"			// FirstSeenTimestampUTC
		"LSTU INTEGER,"			// LastSeenTimestampUTC
		"TSC INTEGER,"			// TagSeenCount
		"ASID INTEGER);";		// AccessSpecID

	ret = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
	if (ret != SQLITE_OK) {
		printf("SQL error: %s.\n", zErrMsg);
	} else
		printf("Table created successfully.\n");

	sqlite3_close(db);

	return ret;
}

int sql_insert_tag_info(char *path, tag_info_t * tag)
{
	int ret = NO_ERROR;
	sqlite3 *db = NULL;
	char sql[512];
	char *zErrMsg = NULL;
	char **dbResult;
	int nRow, nColumn;

	memset(sql, 0, 512);
	ret = sqlite3_open(path, &db);
	if (ret != NO_ERROR) {
		printf("%s: can't open database: %s.\n", __func__, path);
		sqlite3_close(db);
		return -FAILED;
	}

	memset(sql, 0, 512);
	sprintf(sql, "SELECT TSC FROM TAG WHERE TID = %llu;", tag->TID);
	ret = sqlite3_get_table(db, sql, &dbResult, &nRow, &nColumn, &zErrMsg);

	//printf("nRow=%d, nColumn=%d.\n", nRow, nColumn);
	if (nRow == 0) {
		memset(sql, 0, 512);
		sprintf(sql, "INSERT INTO TAG (TID, SSID, SI, RFSID, AID, FSTU, LSTU, TSC, ASID) "
				"VALUES (%lld, %u, %u, %u, %u, %llu, %llu, 1, %u);",
				tag->TID, tag->SelectSpecID, tag->SpecIndex, tag->RfSpecID,
				tag->AntennalID, tag->FirstSeenTimestampUTC, tag->LastSeenTimestampUTC,
				tag->AccessSpecID);
		ret = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
		if (ret != SQLITE_OK) {
			printf("SQL error: %s.\n", zErrMsg);
		}
	} else {
		uint16_t count = 0;

		count = atoi(dbResult[nColumn]);
		//printf("%s: tid: %llx, count = %d.\n", __func__, tag->TID, count);
		memset(sql, 0, 512);
		sprintf(sql, "UPDATE TAG set TSC = %u where TID = %llu;", count + 1, tag->TID);
		sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
		sprintf(sql, "UPDATE TAG set LSTU = %llu where TID = %llu;", tag->LastSeenTimestampUTC,
				tag->TID);
		sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
	}

	sqlite3_free_table(dbResult);
	sqlite3_close(db);
	return 0;
}

int sql_get_tag_info(char *path, tag_list_t ** list)
{
	int ret = NO_ERROR;
	sqlite3 *db = NULL;
	char sql[512];
	char *zErrMsg = NULL;
	char **dbResult;
	int nRow, nColumn;
	int i, index;
	tag_list_t *curr;
	tag_list_t *next;

	if (list == NULL) {
		printf("%s: list is null.\n", __func__);
		return -FAILED;
	}

	memset(sql, 0, 512);
	ret = sqlite3_open(path, &db);
	if (ret != NO_ERROR) {
		printf("%s: can't open database: %s.\n", __func__, path);
		goto out;
	}

	memset(sql, 0, 512);
	sprintf(sql, "SELECT * FROM TAG");
	ret = sqlite3_get_table(db, sql, &dbResult, &nRow, &nColumn, &zErrMsg);
	printf("nRow=%d, nColumn=%d.\n", nRow, nColumn);
	if (ret != SQLITE_OK) {
		printf("%s: sql get table failed.\n", __func__);
		goto out;
	}

	curr = (tag_list_t *) malloc(sizeof(tag_list_t));
	memset(curr, 0, sizeof(tag_list_t));
	curr->next = NULL;

	if (*list == NULL) {
		*list = curr;
	} else {
		next = *list;
		while (next->next != NULL)
			next = next->next;

		next->next = curr;
	}

	index = nColumn;
	for (i = 0; i < nRow; i++) {
		printf("%s: i = %d, nRow = %d., dbResult[%d]=%s\n", __func__, i, nRow, index,
			   dbResult[index]);
		curr->tag.TID = sql_atou64(dbResult[index++]);
		curr->tag.SelectSpecID = sql_atou32(dbResult[index++]);
		curr->tag.SpecIndex = sql_atou16(dbResult[index++]);
		curr->tag.RfSpecID = sql_atou16(dbResult[index++]);
		curr->tag.AntennalID = sql_atou8(dbResult[index++]);
		curr->tag.FirstSeenTimestampUTC = sql_atou64(dbResult[index++]);
		curr->tag.LastSeenTimestampUTC = sql_atou64(dbResult[index++]);
		curr->tag.TagSeenCount = sql_atou16(dbResult[index++]);
		curr->tag.AccessSpecID = sql_atou32(dbResult[index++]);

		next = curr;
		curr = (tag_list_t *) malloc(sizeof(tag_list_t));
		memset(curr, 0, sizeof(tag_list_t));
		curr->next = NULL;
		next->next = curr;
	}

	printf("%s: finish analysis db.\n", __func__);

	next->next = NULL;
	free(curr);

	if (nRow == 0)
		*list = NULL;

	memset(sql, 0, 512);
	sprintf(sql, "DELETE FROM TAG");
	ret = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
	if (ret != SQLITE_OK)
		printf("SQL error: %s.\n", zErrMsg);

  out:
	sqlite3_close(db);
	return ret;
}
#if 0
/* spec : TODO */
int sql_create_SRC_table(char *path)
{
	sqlite3 *db = NULL;
	int ret = NO_ERROR;
	char *sql = NULL;
	char *zErrMsg = NULL;

	ret = sqlite3_open(path, &db);
	if (ret != NO_ERROR) {
		printf("%s: can't open database: %s.\n", __func__, path);
		sqlite3_close(db);
		return -FAILED;
	}

	sql = "CREATE TABLE SRC(" "ID INTEGER PRIMARY KEY NOT NULL,"	// TID
		"SRT INTEGER NOT NULL,"	// SelectSpecID
		"NV INTEGER NOT NULL,"	// SpecIndex
		"MASK INTEGER NOT NULL);";	// RfSpecID

	ret = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
	if (ret != SQLITE_OK) {
		printf("SQL error: %s.\n", zErrMsg);
	} else
		printf("Table created successfully.\n");

	sqlite3_close(db);
}

int sql_insert_SRC_info(char *path, src_info_t * tag)
{
	int ret = NO_ERROR;
	sqlite3 *db = NULL;
	char sql[512];
	char *zErrMsg = NULL;
	char **dbResult;
	int nRow, nColumn;

	memset(sql, 0, 512);
	ret = sqlite3_open(path, &db);
	if (ret != NO_ERROR) {
		printf("%s: can't open database: %s.\n", __func__, path);
		sqlite3_close(db);
		return -FAILED;
	}

	memset(sql, 0, 512);
	sprintf(sql, "SELECT TSC FROM TAG WHERE TID = %llu;", tag->TID);
	ret = sqlite3_get_table(db, sql, &dbResult, &nRow, &nColumn, &zErrMsg);

	printf("nRow=%d, nColumn=%d.\n", nRow, nColumn);
	if (nRow == 0) {
		memset(sql, 0, 512);
		sprintf(sql, "INSERT INTO TAG (TID, SSID, SI, RFSID, AID, FSTU, LSTU, TSC, ASID) "
				"VALUES (%llu, %lu, %u, %u, %u, %llu, 0, 1, %lu);",
				tag->TID, tag->SelectSpecID, tag->SpecIndex, tag->RfSpecID,
				tag->AntennalID, tag->FistSeenTimestampUTC, tag->AccessSpecID);
		sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
	} else {
		uint16_t count = 0;

		count = *dbResult[nColumn] - '0';
		printf("count = %d.\n", count);
		memset(sql, 0, 512);
		sprintf(sql, "UPDATE TAG set TSC = %lu where TID = %llu;", count + 1, tag->TID);
		sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
	}

	sqlite3_free_table(dbResult);
	sqlite3_close(db);
	return 0;
}
#endif
