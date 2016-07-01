#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <libxml/parser.h>

#define NAME_SIZE_MAX 512
#define MAX_KEY_VALUE_PAIRS 20

#define BUFF_SIZE_255 255

#define CONFIG_XML_PATH "/home/c_dshao/work/xml2/"
#define CONFIG_XML "uhf.xml"

#define TRUE 0
#define FALSE 1

#define RETURN_ON_FALSE(expr)                         \
    if ((expr) == FALSE) {                            \
        printf("failed evaluated expression is FALSE.\n"); \
        return FALSE;                                 \
     }

#if !defined RETURN_ON_NULL
#define RETURN_ON_NULL(expr)\
    if ((expr) == NULL) {\
        printf("failed NULL pointer detected " #expr);\
        return FALSE;\
     }
#endif

#define RETURN_FALSE_IF(_cond, args...)                \
    if ((_cond)) {                                     \
        printf(" failed evaluated expression is FALSE: " #_cond " : " args); \
        return FALSE;                                           \
    }

#define MAX_KEY_SIZE 32

enum xmlValueType {
	XML_VALUE_STRING,
	XML_VALUE_INT8,
	XML_VALUE_UINT8,
	XML_VALUE_INT16,
	XML_VALUE_UINT16,
	XML_VALUE_UINT64,
	XML_VALUE_INT32,
	XML_VALUE_UINT32,
	XML_VALUE_FLOAT,
	XML_VALUE_MAX
};

struct xmlKeyValuePair {
	void *value;
	char key[MAX_KEY_SIZE];
	xmlElementType nodeType;
	enum xmlValueType value_type;
};

typedef struct {
	uint8_t log_level;
	char dev_link[NAME_SIZE_MAX];
	char fw_path[NAME_SIZE_MAX];
	uint8_t timeout;
	uint32_t heart_peri;
} radio_config_t;

typedef struct {
	uint8_t log_level;
	char dev_link[NAME_SIZE_MAX];
	char fw_path[NAME_SIZE_MAX];
	char auth_x509_path[NAME_SIZE_MAX];
	uint8_t timeout;
} security_config_t;

typedef struct {
	uint8_t log_level;
	char db_path[NAME_SIZE_MAX];
	uint8_t timeout;
	uint32_t heart_peri;
} upper_config_t;

typedef struct {
	char active_cert_path[NAME_SIZE_MAX];
	char user_info_path[NAME_SIZE_MAX];
	char bind_accept_path[NAME_SIZE_MAX];
	char uuid_path[NAME_SIZE_MAX];
	char uhf_trace_path[NAME_SIZE_MAX];

	radio_config_t radio;
	security_config_t security;
	upper_config_t upper;
} uhf_config_t;

struct xmlConfigInfo {
	xmlDocPtr docPtr;
	xmlNodePtr nodePtr;
	uhf_config_t *configPtr;
};

size_t strlcpy(char *destination, const char *source, const size_t size)
{
	if (0 < size) {
		snprintf(destination, size, "%s", source);
		/*
		 * Platforms that lack strlcpy() also tend to have
		 * a broken snprintf implementation that doesn't
		 * guarantee nul termination.
		 *
		 * XXX: the configure script should detect and reject those.
		 */
		destination[size - 1] = '\0';
	}
	return strlen(source);
}

int xml_util_unload_file(xmlDocPtr docPtr)
{
	xmlFreeDoc(docPtr);
}

int xml_util_load_file(char *file_name, xmlDocPtr * pDocPtr,
					   xmlNodePtr * pNodePtr, const char *nodeName)
{
	xmlDocPtr docPtr = NULL;
	xmlNodePtr rootPtr = NULL;
	xmlNodePtr cur = NULL;

	docPtr = xmlParseFile(file_name);
	if (!docPtr) {
		printf("xmlParseFile failed. please validate the xml: %s.\n", file_name);
		return -1;
	}

	rootPtr = xmlDocGetRootElement(docPtr);
	if (!rootPtr) {
		printf("xmlDocGetRootElement failed rootPtr NULL.\n");
		goto error;
	}

	printf("node_name = %s root_name = %s.\n", nodeName, rootPtr->name);

	if (xmlStrncmp(rootPtr->name, (const xmlChar *)nodeName, xmlStrlen(rootPtr->name))) {
		printf("nodeName :%s not found Invalid node: %s.\n", nodeName, rootPtr->name);
		goto error;
	}

	*pDocPtr = docPtr;
	*pNodePtr = rootPtr;

	return 0;

  error:
	xmlFreeDoc(docPtr);
	return -1;
}

uint32_t xml_util_get_num_nodes(xmlNodePtr pNodePtr, const char *nodeName)
{
	uint32_t i = 0;
	uint32_t child_count = 0;
	uint32_t num_nodes = 0;
	xmlNodePtr curPtr = NULL;

	if (!pNodePtr || !nodeName)
		return 0;
	if (!xmlStrncmp(pNodePtr->name, (const xmlChar *)nodeName, xmlStrlen(pNodePtr->name)))
		num_nodes++;
	for (curPtr = xmlFirstElementChild(pNodePtr); curPtr; curPtr = xmlNextElementSibling(curPtr)) {
		num_nodes += xml_util_get_num_nodes(curPtr, nodeName);
	}
	return num_nodes;
}

xmlNodePtr xml_util_get_node(xmlNodePtr pNodePtr, const char *nodeName, uint32_t node_index)
{
	uint32_t node_count = 0;
	xmlNodePtr curPtr = NULL;

	if (!xmlStrncmp(pNodePtr->name, (const xmlChar *)nodeName, xmlStrlen(pNodePtr->name))) {
		if (node_index == 0)
			return pNodePtr;
		else
			node_index--;
	}

	for (curPtr = xmlFirstElementChild(pNodePtr); curPtr; curPtr = xmlNextElementSibling(curPtr)) {
		node_count = xml_util_get_num_nodes(curPtr, nodeName);
		if (node_count > node_index)
			return xml_util_get_node(curPtr, nodeName, node_index);
		else
			node_index -= node_count;
	}
	return NULL;
}

static int xml_util_get_node_data(xmlDocPtr docPtr,
								  xmlNodePtr pNodePtr, const char *parentName,
								  struct xmlKeyValuePair *key_value_pair, uint16_t num_pairs,
								  uint8_t index)
{
	uint16_t i = 0;
	char *str = NULL;
	uint32_t size = 0;
	xmlNodePtr curPtr = NULL;

	RETURN_ON_NULL(key_value_pair);
	RETURN_ON_NULL(parentName);
	RETURN_ON_NULL(pNodePtr);
	RETURN_ON_NULL(docPtr);

	RETURN_FALSE_IF(!num_pairs);
	RETURN_FALSE_IF(num_pairs > MAX_KEY_VALUE_PAIRS, "pairs = %d", num_pairs);

	printf("num_pairs = %d\n", num_pairs);

	pNodePtr = xml_util_get_node(pNodePtr, parentName, index);
	RETURN_ON_NULL(pNodePtr);

	for (i = 0; i < num_pairs; i++) {

		/* Validate the destination pointer */
		RETURN_ON_NULL(key_value_pair[i].value);

		if (key_value_pair[i].nodeType == XML_ELEMENT_NODE) {

			/* Match the key from xml with the requested key list */
			for (curPtr = xmlFirstElementChild(pNodePtr);
				 curPtr
				 && xmlStrncmp(curPtr->name, (const xmlChar *)key_value_pair[i].key,
							   xmlStrlen(curPtr->name)); curPtr = xmlNextElementSibling(curPtr)) ;

			/* Check if we found a match */
			if (!curPtr) {
				printf("Tag %s not present in XML file\n", key_value_pair[i].key);
				continue;
			}

			/* Get the data pointer  */
			str = (char *)xmlNodeListGetString(docPtr, curPtr->xmlChildrenNode, 1);
		} else if (key_value_pair[i].nodeType == XML_ATTRIBUTE_NODE) {
			str = (char *)xmlGetProp(pNodePtr, (const xmlChar *)key_value_pair[i].key);
		} else {
			printf("Invalid nodeType = %d\n", key_value_pair[i].nodeType);
			return FALSE;
		}

		/* Check if data pointer is NULL */
		if (str == NULL) {
			printf("Empty node %s in XML file\n", key_value_pair[i].key);
			continue;
		}

		printf(" i = %d str = %s\n", i, str);

		/* Copy the string */
		switch (key_value_pair[i].value_type) {

		  case XML_VALUE_STRING:
			  strlcpy(key_value_pair[i].value, str, xmlStrlen((const xmlChar *)str) + 1);
			  break;
		  case XML_VALUE_INT8:
			  *((int8_t *) key_value_pair[i].value) = (int8_t) strtoll(str, NULL, 0);
			  break;
		  case XML_VALUE_UINT8:
			  *((uint8_t *) key_value_pair[i].value) = (uint8_t) strtoll(str, NULL, 0);
			  break;
		  case XML_VALUE_INT16:
			  *((int16_t *) key_value_pair[i].value) = (int16_t) strtoll(str, NULL, 0);
			  break;
		  case XML_VALUE_UINT16:
			  *((uint16_t *) key_value_pair[i].value) = (uint16_t) strtoll(str, NULL, 0);
			  break;
		  case XML_VALUE_UINT64:
			  *((uint64_t *) key_value_pair[i].value) = (uint64_t) strtoll(str, NULL, 0);
			  break;
		  case XML_VALUE_INT32:
			  *((int32_t *) key_value_pair[i].value) = (int32_t) strtoll(str, NULL, 0);
			  break;
		  case XML_VALUE_UINT32:
			  *((uint32_t *) key_value_pair[i].value) = (uint32_t) strtoll(str, NULL, 0);
			  break;
		  case XML_VALUE_FLOAT:
			  *((float *)key_value_pair[i].value) = atof(str);
			  break;
		  default:
			  printf(" Invalid value_type = %d.\n", key_value_pair[i].value_type);
			  return FALSE;
		}

		xmlFree(str);
	}

	return TRUE;
}

int xml_util_get_radio_config(struct xmlConfigInfo *pXmlConfig)
{
	xmlDocPtr docPtr = pXmlConfig->docPtr;
	xmlNodePtr nodePtr = pXmlConfig->nodePtr;
	uhf_config_t *configPtr = pXmlConfig->configPtr;
	uint32_t num_pairs = 0;
	struct xmlKeyValuePair key_value_pair[5];

	strlcpy(key_value_pair[num_pairs].key, "LogLevel", MAX_KEY_SIZE);
	key_value_pair[num_pairs].value = &configPtr->radio.log_level;
	key_value_pair[num_pairs].value_type = XML_VALUE_UINT8;
	key_value_pair[num_pairs].nodeType = XML_ELEMENT_NODE;
	num_pairs++;

	strlcpy(key_value_pair[num_pairs].key, "DevLink", MAX_KEY_SIZE);
	key_value_pair[num_pairs].value = &configPtr->radio.dev_link;
	key_value_pair[num_pairs].value_type = XML_VALUE_STRING;
	key_value_pair[num_pairs].nodeType = XML_ELEMENT_NODE;
	num_pairs++;

	strlcpy(key_value_pair[num_pairs].key, "FWPath", MAX_KEY_SIZE);
	key_value_pair[num_pairs].value = &configPtr->radio.fw_path;
	key_value_pair[num_pairs].value_type = XML_VALUE_STRING;
	key_value_pair[num_pairs].nodeType = XML_ELEMENT_NODE;
	num_pairs++;

	strlcpy(key_value_pair[num_pairs].key, "Timeout", MAX_KEY_SIZE);
	key_value_pair[num_pairs].value = &configPtr->radio.timeout;
	key_value_pair[num_pairs].value_type = XML_VALUE_UINT8;
	key_value_pair[num_pairs].nodeType = XML_ELEMENT_NODE;
	num_pairs++;

	strlcpy(key_value_pair[num_pairs].key, "HeartBeatPeri", MAX_KEY_SIZE);
	key_value_pair[num_pairs].value = &configPtr->radio.heart_peri;
	key_value_pair[num_pairs].value_type = XML_VALUE_UINT32;
	key_value_pair[num_pairs].nodeType = XML_ELEMENT_NODE;
	num_pairs++;

	RETURN_ON_FALSE(xml_util_get_node_data(docPtr, nodePtr, "Radio", key_value_pair, num_pairs, 0));

	printf("radio log level = %d.\n", configPtr->radio.log_level);
	printf("radio device link = %s.\n", configPtr->radio.dev_link);
	printf("radio firmware path = %s.\n", configPtr->radio.fw_path);
	printf("radio timeout = %d.\n", configPtr->radio.timeout);
	printf("radio heart_peri = %d.\n", configPtr->radio.heart_peri);

	return 0;
}

int xml_util_get_security_config(struct xmlConfigInfo *pXmlConfig)
{
	xmlDocPtr docPtr = pXmlConfig->docPtr;
	xmlNodePtr nodePtr = pXmlConfig->nodePtr;
	uhf_config_t *configPtr = pXmlConfig->configPtr;
	uint32_t num_pairs = 0;
	struct xmlKeyValuePair key_value_pair[5];

	strlcpy(key_value_pair[num_pairs].key, "LogLevel", MAX_KEY_SIZE);
	key_value_pair[num_pairs].value = &configPtr->security.log_level;
	key_value_pair[num_pairs].value_type = XML_VALUE_UINT8;
	key_value_pair[num_pairs].nodeType = XML_ELEMENT_NODE;
	num_pairs++;

	RETURN_ON_FALSE(xml_util_get_node_data
					(docPtr, nodePtr, "Security", key_value_pair, num_pairs, 0));

	printf("security log level = %d.\n", configPtr->security.log_level);

	return 0;
}

int xml_util_get_upper_config(struct xmlConfigInfo *pXmlConfig)
{
	xmlDocPtr docPtr = pXmlConfig->docPtr;
	xmlNodePtr nodePtr = pXmlConfig->nodePtr;
	uhf_config_t *configPtr = pXmlConfig->configPtr;
	uint32_t num_pairs = 0;
	struct xmlKeyValuePair key_value_pair[4];

	strlcpy(key_value_pair[num_pairs].key, "LogLevel", MAX_KEY_SIZE);
	key_value_pair[num_pairs].value = &configPtr->upper.log_level;
	key_value_pair[num_pairs].value_type = XML_VALUE_UINT8;
	key_value_pair[num_pairs].nodeType = XML_ELEMENT_NODE;
	num_pairs++;

	strlcpy(key_value_pair[num_pairs].key, "DBPath", MAX_KEY_SIZE);
	key_value_pair[num_pairs].value = &configPtr->upper.db_path;
	key_value_pair[num_pairs].value_type = XML_VALUE_STRING;
	key_value_pair[num_pairs].nodeType = XML_ELEMENT_NODE;
	num_pairs++;

	strlcpy(key_value_pair[num_pairs].key, "Timeout", MAX_KEY_SIZE);
	key_value_pair[num_pairs].value = &configPtr->upper.timeout;
	key_value_pair[num_pairs].value_type = XML_VALUE_UINT8;
	key_value_pair[num_pairs].nodeType = XML_ELEMENT_NODE;
	num_pairs++;

	strlcpy(key_value_pair[num_pairs].key, "HeartBeatPeri", MAX_KEY_SIZE);
	key_value_pair[num_pairs].value = &configPtr->upper.heart_peri;
	key_value_pair[num_pairs].value_type = XML_VALUE_UINT8;
	key_value_pair[num_pairs].nodeType = XML_ELEMENT_NODE;
	num_pairs++;

	RETURN_ON_FALSE(xml_util_get_node_data(docPtr, nodePtr, "Upper", key_value_pair, num_pairs, 0));

	printf("upper log level = %d.\n", configPtr->upper.log_level);

	return 0;
}

int xml_util_get_uhf_probe_config(struct xmlConfigInfo *pXmlConfig)
{
	uint32_t num_pairs = 0;
	xmlDocPtr docPtr = pXmlConfig->docPtr;
	xmlNodePtr nodePtr = pXmlConfig->nodePtr;
	uhf_config_t *configPtr = pXmlConfig->configPtr;
	struct xmlKeyValuePair key_value_pair[20];
	char positionStr[25];

	memset(configPtr, 0, sizeof(uhf_config_t));

	strlcpy(key_value_pair[num_pairs].key, "ActiveCertPath", MAX_KEY_SIZE);
	key_value_pair[num_pairs].value = configPtr->active_cert_path;
	key_value_pair[num_pairs].value_type = XML_VALUE_STRING;
	key_value_pair[num_pairs].nodeType = XML_ELEMENT_NODE;
	num_pairs++;

	strlcpy(key_value_pair[num_pairs].key, "UserInfoPath", MAX_KEY_SIZE);
	key_value_pair[num_pairs].value = configPtr->user_info_path;
	key_value_pair[num_pairs].value_type = XML_VALUE_STRING;
	key_value_pair[num_pairs].nodeType = XML_ELEMENT_NODE;
	num_pairs++;

	strlcpy(key_value_pair[num_pairs].key, "BindAcceptFile", MAX_KEY_SIZE);
	key_value_pair[num_pairs].value = configPtr->bind_accept_path;
	key_value_pair[num_pairs].value_type = XML_VALUE_STRING;
	key_value_pair[num_pairs].nodeType = XML_ELEMENT_NODE;
	num_pairs++;

	strlcpy(key_value_pair[num_pairs].key, "UUIDPath", MAX_KEY_SIZE);
	key_value_pair[num_pairs].value = configPtr->uuid_path;
	key_value_pair[num_pairs].value_type = XML_VALUE_STRING;
	key_value_pair[num_pairs].nodeType = XML_ELEMENT_NODE;
	num_pairs++;

	strlcpy(key_value_pair[num_pairs].key, "UHFTraceFile", MAX_KEY_SIZE);
	key_value_pair[num_pairs].value = configPtr->uhf_trace_path;
	key_value_pair[num_pairs].value_type = XML_VALUE_STRING;
	key_value_pair[num_pairs].nodeType = XML_ELEMENT_NODE;
	num_pairs++;

	RETURN_ON_FALSE(xml_util_get_node_data
					(docPtr, nodePtr, "UHFModuleConfig", key_value_pair, num_pairs, 0));

	printf("active_cert_path = %s.\n", configPtr->active_cert_path);
	printf("user_info_path = %s.\n", configPtr->user_info_path);
	printf("bind_accept_file = %s.\n", configPtr->bind_accept_path);
	printf("uuid_path = %s.\n", configPtr->uuid_path);
	printf("uhf_trace_path = %s.\n", configPtr->uhf_trace_path);

	xml_util_get_radio_config(pXmlConfig);
	xml_util_get_security_config(pXmlConfig);
	xml_util_get_upper_config(pXmlConfig);

	return TRUE;
}

int main()
{
	int ret = 0;
	char config_xml_name[255];
	xmlDocPtr docPtr = NULL;
	xmlNodePtr rootPtr = NULL;
	xmlNodePtr nodePtr = NULL;
	struct xmlConfigInfo xmlConfig;
	uhf_config_t uhf_cfg;

	snprintf(config_xml_name, BUFF_SIZE_255, "%s%s", CONFIG_XML_PATH, CONFIG_XML);

	printf("reading from file %s.\n", config_xml_name);

	ret = xml_util_load_file(config_xml_name, &docPtr, &rootPtr, "UHFConfigurationRoot");
	if (ret) {
		printf("xml_util_load_file failed.\n");
		return -1;
	}

	xmlConfig.docPtr = docPtr;
	xmlConfig.configPtr = &uhf_cfg;

	/* node_index is 0, nodePtr is rootPtr */
	nodePtr = xml_util_get_node(rootPtr, "UHFModuleConfig", 0);
	if (!nodePtr) {
		ret = -1;
		printf("can't get node..\n");
		goto XML_PROBE_EXIT;
	}
	xmlConfig.nodePtr = nodePtr;

	ret = xml_util_get_uhf_probe_config(&xmlConfig);

  XML_PROBE_EXIT:
	xml_util_unload_file(docPtr);

	return ret;
}
