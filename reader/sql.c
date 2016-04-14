#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
//#include <uhf.h>
#include "sqlite3.h"

#define NO_ERROR	0
#define FAILED		1
#define DB_PATH "/home/c_dshao/test.db"

typedef struct tag_info {
    uint64_t TID;                                 
    uint32_t SelectSpecID;                        
    uint16_t SpecIndex;
    uint16_t RfSpecID;                            
    uint8_t AntennalID;                           
    uint64_t FistSeenTimestampUTC;                
    uint64_t LastSeenTimestampUTC;                
    uint32_t AccessSpecID;
	uint16_t TagSeenCount;
	uint16_t LastSeenCount;                        
} tag_info_t;

typedef struct src_info {
	uint16_t id;
	uint8_t SelectReportTrigger;
	uint16_t NValue;
	uint16_t mask;
} src_info_t;

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

	sql = "CREATE TABLE TAG("
		  "TID INTEGER PRIMARY KEY NOT NULL,"	  	// TID
		  "SSID INTEGER NOT NULL,"					// SelectSpecID
		  "SI INTEGER NOT NULL,"					// SpecIndex
		  "RFSID INTEGER NOT NULL,"					// RfSpecID
		  "AID INTEGER NOT NULL,"					// AntennaID
		  "FSTU INTEGER,"							// FirstSeenTimestampUTC
		  "LSTU INTEGER,"							// LastSeenTimestampUTC
		  "TSC INTEGER,"							// TagSeenCount
		  "ASID INTEGER,";							// AccessSpecID
		  "LSC INTEGER);";							// LastSeenCount, it will fix in an thread to check

	ret = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
	if (ret != SQLITE_OK) {
		printf("SQL error: %s.\n", zErrMsg);
	} else
		printf("Table created successfully.\n");

	sqlite3_close(db);

	return ret;
}

int sql_insert_tag_info(char *path, tag_info_t *tag)
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
		sprintf(sql, "INSERT INTO TAG (TID, SSID, SI, RFSID, AID, FSTU, LSTU, TSC, ASID) "	\
					"VALUES (%llu, %lu, %u, %u, %u, %llu, 0, 1, %lu);",	\
					tag->TID, tag->SelectSpecID, tag->SpecIndex, tag->RfSpecID,	\
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

int sql_get_tag_info(char *path, tag_info_t *tag)
{

}

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

	sql = "CREATE TABLE SRC("
		  "ID INTEGER PRIMARY KEY NOT NULL,"	  	// TID
		  "SRT INTEGER NOT NULL,"					// SelectSpecID
		  "NV INTEGER NOT NULL,"					// SpecIndex
		  "MASK INTEGER NOT NULL);";				// RfSpecID

	ret = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
	if (ret != SQLITE_OK) {
		printf("SQL error: %s.\n", zErrMsg);
	} else
		printf("Table created successfully.\n");

	sqlite3_close(db);
}

int sql_insert_SRC_info(char *path, src_info_t *tag)
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
		sprintf(sql, "INSERT INTO TAG (TID, SSID, SI, RFSID, AID, FSTU, LSTU, TSC, ASID) "	\
					"VALUES (%llu, %lu, %u, %u, %u, %llu, 0, 1, %lu);",	\
					tag->TID, tag->SelectSpecID, tag->SpecIndex, tag->RfSpecID,	\
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

int main(int argc, char **argv)
{
	tag_info_t tag;

	tag.TID = 1234;
	tag.SelectSpecID = 5678;
	tag.SpecIndex = 90;
	tag.RfSpecID = 11;
	tag.AntennalID = 22;
	tag.FistSeenTimestampUTC = 33;
	tag.AccessSpecID = 234;

	sql_create_tag_table(DB_PATH);

	sql_insert_tag_info(DB_PATH, &tag);

	return 0;
}
