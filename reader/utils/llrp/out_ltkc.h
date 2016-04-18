
/*
 * Generated file - DO NOT EDIT
 *
 * This is the header file for the LLRP Tool Kit (LTK)
 * C++ (aka cpp) implementation. It is generated into a .inc file
 * that is included by a platform specific .h header file.
 * That .h file takes care of prerequisites needed by this file.
 */




/*
 * Message classes - forward decls
 */

struct LLRP_SCUSTOM_MESSAGE;
typedef struct LLRP_SCUSTOM_MESSAGE
    LLRP_tSCUSTOM_MESSAGE;

struct LLRP_SErrorAck;
typedef struct LLRP_SErrorAck
    LLRP_tSErrorAck;

struct LLRP_SKeepalive;
typedef struct LLRP_SKeepalive
    LLRP_tSKeepalive;

struct LLRP_SKeepaliveAck;
typedef struct LLRP_SKeepaliveAck
    LLRP_tSKeepaliveAck;

struct LLRP_SDisconnect;
typedef struct LLRP_SDisconnect
    LLRP_tSDisconnect;

struct LLRP_SDisconnectAck;
typedef struct LLRP_SDisconnectAck
    LLRP_tSDisconnectAck;

struct LLRP_SDeviceEventNotification;
typedef struct LLRP_SDeviceEventNotification
    LLRP_tSDeviceEventNotification;

struct LLRP_SGetDeviceCapabilities;
typedef struct LLRP_SGetDeviceCapabilities
    LLRP_tSGetDeviceCapabilities;

struct LLRP_SGetDeviceCapabilitiesAck;
typedef struct LLRP_SGetDeviceCapabilitiesAck
    LLRP_tSGetDeviceCapabilitiesAck;

struct LLRP_SAddSelectSpec;
typedef struct LLRP_SAddSelectSpec
    LLRP_tSAddSelectSpec;

struct LLRP_SAddSelectSpecAck;
typedef struct LLRP_SAddSelectSpecAck
    LLRP_tSAddSelectSpecAck;

struct LLRP_SDeleteSelectSpec;
typedef struct LLRP_SDeleteSelectSpec
    LLRP_tSDeleteSelectSpec;

struct LLRP_SDeleteSelectSpecAck;
typedef struct LLRP_SDeleteSelectSpecAck
    LLRP_tSDeleteSelectSpecAck;

struct LLRP_SStartSelectSpec;
typedef struct LLRP_SStartSelectSpec
    LLRP_tSStartSelectSpec;

struct LLRP_SStartSelectSpecAck;
typedef struct LLRP_SStartSelectSpecAck
    LLRP_tSStartSelectSpecAck;

struct LLRP_SStopSelectSpec;
typedef struct LLRP_SStopSelectSpec
    LLRP_tSStopSelectSpec;

struct LLRP_SStopSelectSpecAck;
typedef struct LLRP_SStopSelectSpecAck
    LLRP_tSStopSelectSpecAck;

struct LLRP_SEnableSelectSpec;
typedef struct LLRP_SEnableSelectSpec
    LLRP_tSEnableSelectSpec;

struct LLRP_SEnableSelectSpecAck;
typedef struct LLRP_SEnableSelectSpecAck
    LLRP_tSEnableSelectSpecAck;

struct LLRP_SDisableSelectSpec;
typedef struct LLRP_SDisableSelectSpec
    LLRP_tSDisableSelectSpec;

struct LLRP_SDisableSelectSpecAck;
typedef struct LLRP_SDisableSelectSpecAck
    LLRP_tSDisableSelectSpecAck;

struct LLRP_SGetSelectSpec;
typedef struct LLRP_SGetSelectSpec
    LLRP_tSGetSelectSpec;

struct LLRP_SGetSelectSpecAck;
typedef struct LLRP_SGetSelectSpecAck
    LLRP_tSGetSelectSpecAck;

struct LLRP_SAddAccessSpec;
typedef struct LLRP_SAddAccessSpec
    LLRP_tSAddAccessSpec;

struct LLRP_SAddAccessSpecAck;
typedef struct LLRP_SAddAccessSpecAck
    LLRP_tSAddAccessSpecAck;

struct LLRP_SDelectAccessSpec;
typedef struct LLRP_SDelectAccessSpec
    LLRP_tSDelectAccessSpec;

struct LLRP_SDelectAccessSpecAck;
typedef struct LLRP_SDelectAccessSpecAck
    LLRP_tSDelectAccessSpecAck;

struct LLRP_SEnableAccessSpec;
typedef struct LLRP_SEnableAccessSpec
    LLRP_tSEnableAccessSpec;

struct LLRP_SEnableAccessSpecAck;
typedef struct LLRP_SEnableAccessSpecAck
    LLRP_tSEnableAccessSpecAck;

struct LLRP_SDiableAccessSpec;
typedef struct LLRP_SDiableAccessSpec
    LLRP_tSDiableAccessSpec;

struct LLRP_SDiableAccessSpecAck;
typedef struct LLRP_SDiableAccessSpecAck
    LLRP_tSDiableAccessSpecAck;

struct LLRP_SGetAccessSpec;
typedef struct LLRP_SGetAccessSpec
    LLRP_tSGetAccessSpec;

struct LLRP_SGetAccessSpecAck;
typedef struct LLRP_SGetAccessSpecAck
    LLRP_tSGetAccessSpecAck;

struct LLRP_STagSelectAccessReport;
typedef struct LLRP_STagSelectAccessReport
    LLRP_tSTagSelectAccessReport;

struct LLRP_SClientRequestOp;
typedef struct LLRP_SClientRequestOp
    LLRP_tSClientRequestOp;

struct LLRP_SClientRequestOpAck;
typedef struct LLRP_SClientRequestOpAck
    LLRP_tSClientRequestOpAck;

struct LLRP_SDeviceBinding;
typedef struct LLRP_SDeviceBinding
    LLRP_tSDeviceBinding;

struct LLRP_SDeviceBindingAck;
typedef struct LLRP_SDeviceBindingAck
    LLRP_tSDeviceBindingAck;

struct LLRP_SDeviceCertificateConfig;
typedef struct LLRP_SDeviceCertificateConfig
    LLRP_tSDeviceCertificateConfig;

struct LLRP_SDeviceCertificateConfigAck;
typedef struct LLRP_SDeviceCertificateConfigAck
    LLRP_tSDeviceCertificateConfigAck;

struct LLRP_SUploadTagLog;
typedef struct LLRP_SUploadTagLog
    LLRP_tSUploadTagLog;

struct LLRP_SUploadTagLogAck;
typedef struct LLRP_SUploadTagLogAck
    LLRP_tSUploadTagLogAck;

struct LLRP_SClearTagLog;
typedef struct LLRP_SClearTagLog
    LLRP_tSClearTagLog;

struct LLRP_SClearTagLogAck;
typedef struct LLRP_SClearTagLogAck
    LLRP_tSClearTagLogAck;

struct LLRP_SUploadDeviceLog;
typedef struct LLRP_SUploadDeviceLog
    LLRP_tSUploadDeviceLog;

struct LLRP_SUploadDeviceLogAck;
typedef struct LLRP_SUploadDeviceLogAck
    LLRP_tSUploadDeviceLogAck;

struct LLRP_SClearDeviceLog;
typedef struct LLRP_SClearDeviceLog
    LLRP_tSClearDeviceLog;

struct LLRP_SClearDeviceLogAck;
typedef struct LLRP_SClearDeviceLogAck
    LLRP_tSClearDeviceLogAck;

struct LLRP_SGetDeviceConfig;
typedef struct LLRP_SGetDeviceConfig
    LLRP_tSGetDeviceConfig;

struct LLRP_SGetDeviceConfigAck;
typedef struct LLRP_SGetDeviceConfigAck
    LLRP_tSGetDeviceConfigAck;

struct LLRP_SSetDeviceConfig;
typedef struct LLRP_SSetDeviceConfig
    LLRP_tSSetDeviceConfig;

struct LLRP_SSetDeviceConfigAck;
typedef struct LLRP_SSetDeviceConfigAck
    LLRP_tSSetDeviceConfigAck;

struct LLRP_SGetVersion;
typedef struct LLRP_SGetVersion
    LLRP_tSGetVersion;

struct LLRP_SGetVersionAck;
typedef struct LLRP_SGetVersionAck
    LLRP_tSGetVersionAck;

struct LLRP_SSetVersion;
typedef struct LLRP_SSetVersion
    LLRP_tSSetVersion;

struct LLRP_SSetVersionAck;
typedef struct LLRP_SSetVersionAck
    LLRP_tSSetVersionAck;

struct LLRP_SActiveVersion;
typedef struct LLRP_SActiveVersion
    LLRP_tSActiveVersion;

struct LLRP_SActiveVersionAck;
typedef struct LLRP_SActiveVersionAck
    LLRP_tSActiveVersionAck;

struct LLRP_SUnActiveVersion;
typedef struct LLRP_SUnActiveVersion
    LLRP_tSUnActiveVersion;

struct LLRP_SUnActiveVersionAck;
typedef struct LLRP_SUnActiveVersionAck
    LLRP_tSUnActiveVersionAck;

struct LLRP_SAlarmReport;
typedef struct LLRP_SAlarmReport
    LLRP_tSAlarmReport;

struct LLRP_SAlarmRestore;
typedef struct LLRP_SAlarmRestore
    LLRP_tSAlarmRestore;

struct LLRP_SAlarmDelete;
typedef struct LLRP_SAlarmDelete
    LLRP_tSAlarmDelete;

struct LLRP_SAlarmSync;
typedef struct LLRP_SAlarmSync
    LLRP_tSAlarmSync;

struct LLRP_SDiagnosticTest;
typedef struct LLRP_SDiagnosticTest
    LLRP_tSDiagnosticTest;

struct LLRP_SDiagnosticTestAck;
typedef struct LLRP_SDiagnosticTestAck
    LLRP_tSDiagnosticTestAck;

struct LLRP_SResetDevice;
typedef struct LLRP_SResetDevice
    LLRP_tSResetDevice;

struct LLRP_SResetDeviceAck;
typedef struct LLRP_SResetDeviceAck
    LLRP_tSResetDeviceAck;


/* Custom messages */


/*
 * Parameter classes - forward decls
 */

struct LLRP_SCustom;
typedef struct LLRP_SCustom
    LLRP_tSCustom;

struct LLRP_SStatus;
typedef struct LLRP_SStatus
    LLRP_tSStatus;

struct LLRP_SUTCTimestamp;
typedef struct LLRP_SUTCTimestamp
    LLRP_tSUTCTimestamp;

struct LLRP_SGPIEvent;
typedef struct LLRP_SGPIEvent
    LLRP_tSGPIEvent;

struct LLRP_SSelectSpecEvent;
typedef struct LLRP_SSelectSpecEvent
    LLRP_tSSelectSpecEvent;

struct LLRP_SAntennaSpecEvent;
typedef struct LLRP_SAntennaSpecEvent
    LLRP_tSAntennaSpecEvent;

struct LLRP_SAntennaStatusEvent;
typedef struct LLRP_SAntennaStatusEvent
    LLRP_tSAntennaStatusEvent;

struct LLRP_SConnectionAttemptEvent;
typedef struct LLRP_SConnectionAttemptEvent
    LLRP_tSConnectionAttemptEvent;

struct LLRP_SGeneralCapabilities;
typedef struct LLRP_SGeneralCapabilities
    LLRP_tSGeneralCapabilities;

struct LLRP_SGPIOCapabilities;
typedef struct LLRP_SGPIOCapabilities
    LLRP_tSGPIOCapabilities;

struct LLRP_SCommunicationCapabilities;
typedef struct LLRP_SCommunicationCapabilities
    LLRP_tSCommunicationCapabilities;

struct LLRP_SSupportRS232;
typedef struct LLRP_SSupportRS232
    LLRP_tSSupportRS232;

struct LLRP_SSerialAttribute;
typedef struct LLRP_SSerialAttribute
    LLRP_tSSerialAttribute;

struct LLRP_SSupportRS485;
typedef struct LLRP_SSupportRS485
    LLRP_tSSupportRS485;

struct LLRP_SSpecCapabilities;
typedef struct LLRP_SSpecCapabilities
    LLRP_tSSpecCapabilities;

struct LLRP_SRfCapabilities;
typedef struct LLRP_SRfCapabilities
    LLRP_tSRfCapabilities;

struct LLRP_STransmitPowerLevelTable;
typedef struct LLRP_STransmitPowerLevelTable
    LLRP_tSTransmitPowerLevelTable;

struct LLRP_SFrequencyInformation;
typedef struct LLRP_SFrequencyInformation
    LLRP_tSFrequencyInformation;

struct LLRP_SFrequencyTable;
typedef struct LLRP_SFrequencyTable
    LLRP_tSFrequencyTable;

struct LLRP_SForDataRateTable;
typedef struct LLRP_SForDataRateTable
    LLRP_tSForDataRateTable;

struct LLRP_SRevDataRateTable;
typedef struct LLRP_SRevDataRateTable
    LLRP_tSRevDataRateTable;

struct LLRP_SForModulationTable;
typedef struct LLRP_SForModulationTable
    LLRP_tSForModulationTable;

struct LLRP_SRevDataEncodingTable;
typedef struct LLRP_SRevDataEncodingTable
    LLRP_tSRevDataEncodingTable;

struct LLRP_SModuleDepthTable;
typedef struct LLRP_SModuleDepthTable
    LLRP_tSModuleDepthTable;

struct LLRP_SAirProtocolCapabilities;
typedef struct LLRP_SAirProtocolCapabilities
    LLRP_tSAirProtocolCapabilities;

struct LLRP_SPerAntennaAirProtocol;
typedef struct LLRP_SPerAntennaAirProtocol
    LLRP_tSPerAntennaAirProtocol;

struct LLRP_SHbProtocolCapabilities;
typedef struct LLRP_SHbProtocolCapabilities
    LLRP_tSHbProtocolCapabilities;

struct LLRP_SSelectSpec;
typedef struct LLRP_SSelectSpec
    LLRP_tSSelectSpec;

struct LLRP_SSelectSpecStartTrigger;
typedef struct LLRP_SSelectSpecStartTrigger
    LLRP_tSSelectSpecStartTrigger;

struct LLRP_SPeriodicTriggerValue;
typedef struct LLRP_SPeriodicTriggerValue
    LLRP_tSPeriodicTriggerValue;

struct LLRP_SGPITrigger;
typedef struct LLRP_SGPITrigger
    LLRP_tSGPITrigger;

struct LLRP_SSelectSpecStopTrigger;
typedef struct LLRP_SSelectSpecStopTrigger
    LLRP_tSSelectSpecStopTrigger;

struct LLRP_SAntennaSpec;
typedef struct LLRP_SAntennaSpec
    LLRP_tSAntennaSpec;

struct LLRP_SAntennaSpecStopTrigger;
typedef struct LLRP_SAntennaSpecStopTrigger
    LLRP_tSAntennaSpecStopTrigger;

struct LLRP_STagObservationTrigger;
typedef struct LLRP_STagObservationTrigger
    LLRP_tSTagObservationTrigger;

struct LLRP_SRfSpec;
typedef struct LLRP_SRfSpec
    LLRP_tSRfSpec;

struct LLRP_SMemoryBank;
typedef struct LLRP_SMemoryBank
    LLRP_tSMemoryBank;

struct LLRP_SSelectReportSpec;
typedef struct LLRP_SSelectReportSpec
    LLRP_tSSelectReportSpec;

struct LLRP_SReportDestination;
typedef struct LLRP_SReportDestination
    LLRP_tSReportDestination;

struct LLRP_SAccessSpec;
typedef struct LLRP_SAccessSpec
    LLRP_tSAccessSpec;

struct LLRP_SAccessSpecStopTrigger;
typedef struct LLRP_SAccessSpecStopTrigger
    LLRP_tSAccessSpecStopTrigger;

struct LLRP_SAccessCommand;
typedef struct LLRP_SAccessCommand
    LLRP_tSAccessCommand;

struct LLRP_SHbMatchSpec;
typedef struct LLRP_SHbMatchSpec
    LLRP_tSHbMatchSpec;

struct LLRP_SHbTargetTag;
typedef struct LLRP_SHbTargetTag
    LLRP_tSHbTargetTag;

struct LLRP_SHbReadSpec;
typedef struct LLRP_SHbReadSpec
    LLRP_tSHbReadSpec;

struct LLRP_SClientRequestSpec;
typedef struct LLRP_SClientRequestSpec
    LLRP_tSClientRequestSpec;

struct LLRP_SAccessReportSpec;
typedef struct LLRP_SAccessReportSpec
    LLRP_tSAccessReportSpec;

struct LLRP_SHbWriteSpec;
typedef struct LLRP_SHbWriteSpec
    LLRP_tSHbWriteSpec;

struct LLRP_SHbPrivateWriteSpec;
typedef struct LLRP_SHbPrivateWriteSpec
    LLRP_tSHbPrivateWriteSpec;

struct LLRP_STagReportData;
typedef struct LLRP_STagReportData
    LLRP_tSTagReportData;

struct LLRP_SSelectSpecID;
typedef struct LLRP_SSelectSpecID
    LLRP_tSSelectSpecID;

struct LLRP_SSpecIndex;
typedef struct LLRP_SSpecIndex
    LLRP_tSSpecIndex;

struct LLRP_SRfSpecID;
typedef struct LLRP_SRfSpecID
    LLRP_tSRfSpecID;

struct LLRP_SAntennaID;
typedef struct LLRP_SAntennaID
    LLRP_tSAntennaID;

struct LLRP_SPeakRSSI;
typedef struct LLRP_SPeakRSSI
    LLRP_tSPeakRSSI;

struct LLRP_SFirstSeenTimestampUTC;
typedef struct LLRP_SFirstSeenTimestampUTC
    LLRP_tSFirstSeenTimestampUTC;

struct LLRP_SLastSeenTimestampUTC;
typedef struct LLRP_SLastSeenTimestampUTC
    LLRP_tSLastSeenTimestampUTC;

struct LLRP_STagSeenCount;
typedef struct LLRP_STagSeenCount
    LLRP_tSTagSeenCount;

struct LLRP_SAccessSpecID;
typedef struct LLRP_SAccessSpecID
    LLRP_tSAccessSpecID;

struct LLRP_SSelectSpecResult;
typedef struct LLRP_SSelectSpecResult
    LLRP_tSSelectSpecResult;

struct LLRP_SHbReadSpecResult;
typedef struct LLRP_SHbReadSpecResult
    LLRP_tSHbReadSpecResult;

struct LLRP_SClientRequestSpecResult;
typedef struct LLRP_SClientRequestSpecResult
    LLRP_tSClientRequestSpecResult;

struct LLRP_SHbWriteSpecResult;
typedef struct LLRP_SHbWriteSpecResult
    LLRP_tSHbWriteSpecResult;

struct LLRP_SHbPrivateWriteSpecResult;
typedef struct LLRP_SHbPrivateWriteSpecResult
    LLRP_tSHbPrivateWriteSpecResult;

struct LLRP_SClientRequestAck;
typedef struct LLRP_SClientRequestAck
    LLRP_tSClientRequestAck;

struct LLRP_STagLog;
typedef struct LLRP_STagLog
    LLRP_tSTagLog;

struct LLRP_SStartLogTimestamp;
typedef struct LLRP_SStartLogTimestamp
    LLRP_tSStartLogTimestamp;

struct LLRP_SEndLogTimestamp;
typedef struct LLRP_SEndLogTimestamp
    LLRP_tSEndLogTimestamp;

struct LLRP_SDeviceLog;
typedef struct LLRP_SDeviceLog
    LLRP_tSDeviceLog;

struct LLRP_SDeviceEventNotificationSpec;
typedef struct LLRP_SDeviceEventNotificationSpec
    LLRP_tSDeviceEventNotificationSpec;

struct LLRP_SEventNotificationState;
typedef struct LLRP_SEventNotificationState
    LLRP_tSEventNotificationState;

struct LLRP_SAntennaProperties;
typedef struct LLRP_SAntennaProperties
    LLRP_tSAntennaProperties;

struct LLRP_SAntennaConfiguration;
typedef struct LLRP_SAntennaConfiguration
    LLRP_tSAntennaConfiguration;

struct LLRP_SModuleDepth;
typedef struct LLRP_SModuleDepth
    LLRP_tSModuleDepth;

struct LLRP_SIdentification;
typedef struct LLRP_SIdentification
    LLRP_tSIdentification;

struct LLRP_SAlarmConfiguration;
typedef struct LLRP_SAlarmConfiguration
    LLRP_tSAlarmConfiguration;

struct LLRP_SAlarmThreshod;
typedef struct LLRP_SAlarmThreshod
    LLRP_tSAlarmThreshod;

struct LLRP_SCommunicationConfiguration;
typedef struct LLRP_SCommunicationConfiguration
    LLRP_tSCommunicationConfiguration;

struct LLRP_SCommLinkConfiguration;
typedef struct LLRP_SCommLinkConfiguration
    LLRP_tSCommLinkConfiguration;

struct LLRP_SKeepaliveSpec;
typedef struct LLRP_SKeepaliveSpec
    LLRP_tSKeepaliveSpec;

struct LLRP_STcpLinkConfiguration;
typedef struct LLRP_STcpLinkConfiguration
    LLRP_tSTcpLinkConfiguration;

struct LLRP_SClientModeConfiguration;
typedef struct LLRP_SClientModeConfiguration
    LLRP_tSClientModeConfiguration;

struct LLRP_SIPAddress;
typedef struct LLRP_SIPAddress
    LLRP_tSIPAddress;

struct LLRP_SServerModeConfiguration;
typedef struct LLRP_SServerModeConfiguration
    LLRP_tSServerModeConfiguration;

struct LLRP_SSerialLinkConfiguration;
typedef struct LLRP_SSerialLinkConfiguration
    LLRP_tSSerialLinkConfiguration;

struct LLRP_SHttpLinkConfiguration;
typedef struct LLRP_SHttpLinkConfiguration
    LLRP_tSHttpLinkConfiguration;

struct LLRP_SEthernetIpv4Configuration;
typedef struct LLRP_SEthernetIpv4Configuration
    LLRP_tSEthernetIpv4Configuration;

struct LLRP_SEthernetIpv6Configuration;
typedef struct LLRP_SEthernetIpv6Configuration
    LLRP_tSEthernetIpv6Configuration;

struct LLRP_SNTPConfiguration;
typedef struct LLRP_SNTPConfiguration
    LLRP_tSNTPConfiguration;

struct LLRP_SSerialPortConfiguration;
typedef struct LLRP_SSerialPortConfiguration
    LLRP_tSSerialPortConfiguration;

struct LLRP_SLocationConfiguration;
typedef struct LLRP_SLocationConfiguration
    LLRP_tSLocationConfiguration;

struct LLRP_SGpsLocation;
typedef struct LLRP_SGpsLocation
    LLRP_tSGpsLocation;

struct LLRP_SBdsLocation;
typedef struct LLRP_SBdsLocation
    LLRP_tSBdsLocation;

struct LLRP_SSecurityModuleConfiguration;
typedef struct LLRP_SSecurityModuleConfiguration
    LLRP_tSSecurityModuleConfiguration;

struct LLRP_SVersionInfo;
typedef struct LLRP_SVersionInfo
    LLRP_tSVersionInfo;

struct LLRP_SVersionDownload;
typedef struct LLRP_SVersionDownload
    LLRP_tSVersionDownload;

struct LLRP_SAlarmReportInfo;
typedef struct LLRP_SAlarmReportInfo
    LLRP_tSAlarmReportInfo;

struct LLRP_SAlarmRestoreInfo;
typedef struct LLRP_SAlarmRestoreInfo
    LLRP_tSAlarmRestoreInfo;

struct LLRP_SAlarmSyncInfo;
typedef struct LLRP_SAlarmSyncInfo
    LLRP_tSAlarmSyncInfo;

struct LLRP_SDiagnosticTestItem;
typedef struct LLRP_SDiagnosticTestItem
    LLRP_tSDiagnosticTestItem;

struct LLRP_SDiagnosticTestResultItem;
typedef struct LLRP_SDiagnosticTestResultItem
    LLRP_tSDiagnosticTestResultItem;

struct LLRP_SDiagnosticTestResultAntennaConnected;
typedef struct LLRP_SDiagnosticTestResultAntennaConnected
    LLRP_tSDiagnosticTestResultAntennaConnected;

struct LLRP_SDiagnosticTestResultAntennaVSWR;
typedef struct LLRP_SDiagnosticTestResultAntennaVSWR
    LLRP_tSDiagnosticTestResultAntennaVSWR;


/* Custom parameters */


/*
 * Vendor descriptor declarations.
 */


/*
 * Namespace descriptor declarations.
 */

extern const LLRP_tSNamespaceDescriptor
LLRP_nsdescllrp;


/*
 * Enumeration definitions and declarations of
 * enumeration string tables.
 */


enum LLRP_EStatusCode
{

    LLRP_StatusCode_M_Success = 0,
    LLRP_StatusCode_M_ReaderExcessTemperature = 1,
    LLRP_StatusCode_M_ReaderLowTemperature = 2,
    LLRP_StatusCode_M_TemperatureSensorBroken = 3,
    LLRP_StatusCode_M_HighCPUUtility = 4,
    LLRP_StatusCode_M_HighMemoryUtility = 5,
    LLRP_StatusCode_M_NTPUpdateException = 6,
    LLRP_StatusCode_M_PSAMBroken = 7,
    LLRP_StatusCode_M_PLLBroken = 8,
    LLRP_StatusCode_M_SecurityExcessTemperature = 16777217,
    LLRP_StatusCode_M_SecurityLowPower = 16777218,
};

typedef enum LLRP_EStatusCode
    LLRP_tEStatusCode;

extern const LLRP_tSEnumTableEntry
LLRP_estStatusCode[];


enum LLRP_EConnectionStatus
{

    LLRP_ConnectionStatus_Success = 0,
    LLRP_ConnectionStatus_Failed_A_Reader_Initiated_Connection_Already_Exists = 1,
    LLRP_ConnectionStatus_Failed_A_Client_Initiated_Connection_Already_Exists = 2,
    LLRP_ConnectionStatus_Failed_Reason_Other_Than_A_Connection_Already_Exists = 3,
};

typedef enum LLRP_EConnectionStatus
    LLRP_tEConnectionStatus;

extern const LLRP_tSEnumTableEntry
LLRP_estConnectionStatus[];


enum LLRP_ECapabilitiesRequestedData
{

    LLRP_CapabilitiesRequestedData_All = 0,
    LLRP_CapabilitiesRequestedData_GeneralCapabilities = 1,
    LLRP_CapabilitiesRequestedData_CommunicationCapabilities = 2,
    LLRP_CapabilitiesRequestedData_SpecCapabilities = 3,
    LLRP_CapabilitiesRequestedData_RfCapabilities = 4,
    LLRP_CapabilitiesRequestedData_AirProtocolCapabilities = 5,
};

typedef enum LLRP_ECapabilitiesRequestedData
    LLRP_tECapabilitiesRequestedData;

extern const LLRP_tSEnumTableEntry
LLRP_estCapabilitiesRequestedData[];


enum LLRP_EDataEncodingType
{

    LLRP_DataEncodingType_FMO = 0,
    LLRP_DataEncodingType_Miller = 1,
    LLRP_DataEncodingType_Miller4 = 2,
    LLRP_DataEncodingType_Miller8 = 3,
};

typedef enum LLRP_EDataEncodingType
    LLRP_tEDataEncodingType;

extern const LLRP_tSEnumTableEntry
LLRP_estDataEncodingType[];


enum LLRP_ESelectSpecState
{

    LLRP_SelectSpecState_Disabled = 0,
    LLRP_SelectSpecState_Inactive = 1,
    LLRP_SelectSpecState_Active = 2,
};

typedef enum LLRP_ESelectSpecState
    LLRP_tESelectSpecState;

extern const LLRP_tSEnumTableEntry
LLRP_estSelectSpecState[];


enum LLRP_ESelectSpecStartTriggerType
{

    LLRP_SelectSpecStartTriggerType_Null = 0,
    LLRP_SelectSpecStartTriggerType_Immediate = 1,
    LLRP_SelectSpecStartTriggerType_Periodic = 2,
    LLRP_SelectSpecStartTriggerType_GPI = 3,
};

typedef enum LLRP_ESelectSpecStartTriggerType
    LLRP_tESelectSpecStartTriggerType;

extern const LLRP_tSEnumTableEntry
LLRP_estSelectSpecStartTriggerType[];


enum LLRP_ESelectSpecStopTriggerType
{

    LLRP_SelectSpecStopTriggerType_Null = 0,
    LLRP_SelectSpecStopTriggerType_Duration = 1,
    LLRP_SelectSpecStopTriggerType_GPI = 2,
};

typedef enum LLRP_ESelectSpecStopTriggerType
    LLRP_tESelectSpecStopTriggerType;

extern const LLRP_tSEnumTableEntry
LLRP_estSelectSpecStopTriggerType[];


enum LLRP_EAntennaSpecStopTriggerType
{

    LLRP_AntennaSpecStopTriggerType_Null = 0,
    LLRP_AntennaSpecStopTriggerType_Duration = 1,
    LLRP_AntennaSpecStopTriggerType_GPI_With_Timeout = 2,
    LLRP_AntennaSpecStopTriggerType_Tag_Observation = 3,
};

typedef enum LLRP_EAntennaSpecStopTriggerType
    LLRP_tEAntennaSpecStopTriggerType;

extern const LLRP_tSEnumTableEntry
LLRP_estAntennaSpecStopTriggerType[];


enum LLRP_ETagObservationTriggerType
{

    LLRP_TagObservationTriggerType_Upon_Seeing_N_Tags_Or_Timeout = 0,
    LLRP_TagObservationTriggerType_Upon_Seeing_No_More_New_Tags_For_Tms_Or_Timeout = 1,
    LLRP_TagObservationTriggerType_N_Attempts_To_See_All_Tags_In_FOV_Or_Timeout = 2,
};

typedef enum LLRP_ETagObservationTriggerType
    LLRP_tETagObservationTriggerType;

extern const LLRP_tSEnumTableEntry
LLRP_estTagObservationTriggerType[];


enum LLRP_ERfSelectType
{

    LLRP_RfSelectType_Check = 0,
    LLRP_RfSelectType_Read = 1,
};

typedef enum LLRP_ERfSelectType
    LLRP_tERfSelectType;

extern const LLRP_tSEnumTableEntry
LLRP_estRfSelectType[];


enum LLRP_ESelectReportTrigger
{

    LLRP_SelectReportTrigger_None = 0,
    LLRP_SelectReportTrigger_Upon_N_Tags_Or_End_Of_RfSpec = 1,
    LLRP_SelectReportTrigger_Upon_N_Tags_Or_End_Of_SelectSpec = 2,
    LLRP_SelectReportTrigger_Do_Not_Generate_Report = 3,
};

typedef enum LLRP_ESelectReportTrigger
    LLRP_tESelectReportTrigger;

extern const LLRP_tSEnumTableEntry
LLRP_estSelectReportTrigger[];


enum LLRP_EAccessSpecState
{

    LLRP_AccessSpecState_Disabled = 0,
    LLRP_AccessSpecState_Active = 1,
};

typedef enum LLRP_EAccessSpecState
    LLRP_tEAccessSpecState;

extern const LLRP_tSEnumTableEntry
LLRP_estAccessSpecState[];


enum LLRP_EAccessSpecStopTriggerType
{

    LLRP_AccessSpecStopTriggerType_Null = 0,
    LLRP_AccessSpecStopTriggerType_Operation_Count = 1,
};

typedef enum LLRP_EAccessSpecStopTriggerType
    LLRP_tEAccessSpecStopTriggerType;

extern const LLRP_tSEnumTableEntry
LLRP_estAccessSpecStopTriggerType[];


enum LLRP_EMemoryBankID
{

    LLRP_MemoryBankID_User_0 = 0,
    LLRP_MemoryBankID_User_1 = 1,
    LLRP_MemoryBankID_User_2 = 2,
    LLRP_MemoryBankID_User_3 = 3,
    LLRP_MemoryBankID_User_4 = 4,
    LLRP_MemoryBankID_User_5 = 5,
};

typedef enum LLRP_EMemoryBankID
    LLRP_tEMemoryBankID;

extern const LLRP_tSEnumTableEntry
LLRP_estMemoryBankID[];


enum LLRP_EAccessReportTriggerType
{

    LLRP_AccessReportTriggerType_Whenever_ROReport_Is_Generated = 0,
    LLRP_AccessReportTriggerType_End_Of_AccessSpec = 1,
};

typedef enum LLRP_EAccessReportTriggerType
    LLRP_tEAccessReportTriggerType;

extern const LLRP_tSEnumTableEntry
LLRP_estAccessReportTriggerType[];


enum LLRP_ELogType
{

    LLRP_LogType_Device_Fault = 0,
    LLRP_LogType_Recorvery_Fault = 1,
    LLRP_LogType_Run_Log = 2,
};

typedef enum LLRP_ELogType
    LLRP_tELogType;

extern const LLRP_tSEnumTableEntry
LLRP_estLogType[];


enum LLRP_EConfigRequestedData
{

    LLRP_ConfigRequestedData_All = 0,
    LLRP_ConfigRequestedData_Identification = 1,
    LLRP_ConfigRequestedData_DeviceEventNotificationSpec = 2,
    LLRP_ConfigRequestedData_AlarmConfiguration = 3,
    LLRP_ConfigRequestedData_AntennaProperties = 4,
    LLRP_ConfigRequestedData_AntennaConfiguration = 5,
    LLRP_ConfigRequestedData_ModuleDepth = 6,
    LLRP_ConfigRequestedData_SelectReportSpec = 7,
    LLRP_ConfigRequestedData_AccessReportSpec = 8,
    LLRP_ConfigRequestedData_CommunicationConfiguration = 9,
    LLRP_ConfigRequestedData_LocationConfiguration = 10,
    LLRP_ConfigRequestedData_SecurityModuleConfiguration = 11,
};

typedef enum LLRP_EConfigRequestedData
    LLRP_tEConfigRequestedData;

extern const LLRP_tSEnumTableEntry
LLRP_estConfigRequestedData[];


enum LLRP_ENotificationEventType
{

    LLRP_NotificationEventType_GPI = 0,
    LLRP_NotificationEventType_TagSelectSpec = 1,
    LLRP_NotificationEventType_AntennaSpec = 2,
    LLRP_NotificationEventType_AntennaState = 3,
};

typedef enum LLRP_ENotificationEventType
    LLRP_tENotificationEventType;

extern const LLRP_tSEnumTableEntry
LLRP_estNotificationEventType[];


enum LLRP_ENotificationState
{

    LLRP_NotificationState_NotNotification = 0,
    LLRP_NotificationState_Notification = 1,
};

typedef enum LLRP_ENotificationState
    LLRP_tENotificationState;

extern const LLRP_tSEnumTableEntry
LLRP_estNotificationState[];


enum LLRP_ELinkType
{

    LLRP_LinkType_TCP = 0,
    LLRP_LinkType_RS232 = 1,
    LLRP_LinkType_RS485 = 2,
    LLRP_LinkType_HTTP = 3,
};

typedef enum LLRP_ELinkType
    LLRP_tELinkType;

extern const LLRP_tSEnumTableEntry
LLRP_estLinkType[];


enum LLRP_ECommMode
{

    LLRP_CommMode_ClientMode = 0,
    LLRP_CommMode_ServerMode = 1,
    LLRP_CommMode_MixMode = 2,
};

typedef enum LLRP_ECommMode
    LLRP_tECommMode;

extern const LLRP_tSEnumTableEntry
LLRP_estCommMode[];


enum LLRP_EIPVersion
{

    LLRP_IPVersion_IPV4 = 0,
    LLRP_IPVersion_IPV6 = 1,
};

typedef enum LLRP_EIPVersion
    LLRP_tEIPVersion;

extern const LLRP_tSEnumTableEntry
LLRP_estIPVersion[];


enum LLRP_ELocationType
{

    LLRP_LocationType_GPS = 0,
    LLRP_LocationType_BDS = 1,
};

typedef enum LLRP_ELocationType
    LLRP_tELocationType;

extern const LLRP_tSEnumTableEntry
LLRP_estLocationType[];


enum LLRP_EVerType
{

    LLRP_VerType_ReadBoot = 0,
    LLRP_VerType_ReadSystem = 1,
    LLRP_VerType_SecurityModuleSystem = 2,
    LLRP_VerType_SecurityChipSystem = 3,
    LLRP_VerType_RadioModule = 4,
};

typedef enum LLRP_EVerType
    LLRP_tEVerType;

extern const LLRP_tSEnumTableEntry
LLRP_estVerType[];


enum LLRP_EUsedOrSpare
{

    LLRP_UsedOrSpare_Main = 0,
    LLRP_UsedOrSpare_Backup = 1,
};

typedef enum LLRP_EUsedOrSpare
    LLRP_tEUsedOrSpare;

extern const LLRP_tSEnumTableEntry
LLRP_estUsedOrSpare[];


enum LLRP_ESetUse
{

    LLRP_SetUse_HasActived = 0,
    LLRP_SetUse_NotActive = 1,
};

typedef enum LLRP_ESetUse
    LLRP_tESetUse;

extern const LLRP_tSEnumTableEntry
LLRP_estSetUse[];


enum LLRP_EHasRun
{

    LLRP_HasRun_HasRuned = 0,
    LLRP_HasRun_NeverRun = 1,
};

typedef enum LLRP_EHasRun
    LLRP_tEHasRun;

extern const LLRP_tSEnumTableEntry
LLRP_estHasRun[];


enum LLRP_ECanRun
{

    LLRP_CanRun_CanRun = 0,
    LLRP_CanRun_CanNotRun = 1,
};

typedef enum LLRP_ECanRun
    LLRP_tECanRun;

extern const LLRP_tSEnumTableEntry
LLRP_estCanRun[];


enum LLRP_EServerType
{

    LLRP_ServerType_Ftp = 0,
    LLRP_ServerType_Tftp = 1,
};

typedef enum LLRP_EServerType
    LLRP_tEServerType;

extern const LLRP_tSEnumTableEntry
LLRP_estServerType[];


enum LLRP_EAlarmReportLevel
{

    LLRP_AlarmReportLevel_Lethal = 0,
    LLRP_AlarmReportLevel_Serious = 1,
    LLRP_AlarmReportLevel_Commonly = 2,
    LLRP_AlarmReportLevel_Little = 3,
    LLRP_AlarmReportLevel_Notify = 4,
};

typedef enum LLRP_EAlarmReportLevel
    LLRP_tEAlarmReportLevel;

extern const LLRP_tSEnumTableEntry
LLRP_estAlarmReportLevel[];


  
struct LLRP_SCUSTOM_MESSAGE
{
    LLRP_tSMessage hdr;
  
    llrp_u32_t VendorIdentifier;

    llrp_u8_t MessageSubtype;

    llrp_bytesToEnd_t Data;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdCUSTOM_MESSAGE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdCUSTOM_MESSAGE[];

extern LLRP_tSCUSTOM_MESSAGE *
LLRP_CUSTOM_MESSAGE_construct (void);

extern void
LLRP_CUSTOM_MESSAGE_destruct (
 LLRP_tSCUSTOM_MESSAGE * pThis);

extern void
LLRP_CUSTOM_MESSAGE_decodeFields (
 LLRP_tSCUSTOM_MESSAGE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_CUSTOM_MESSAGE_assimilateSubParameters (
 LLRP_tSCUSTOM_MESSAGE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_CUSTOM_MESSAGE_encode (
  const LLRP_tSCUSTOM_MESSAGE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdCUSTOM_MESSAGE_VendorIdentifier;

extern llrp_u32_t
LLRP_CUSTOM_MESSAGE_getVendorIdentifier (
  LLRP_tSCUSTOM_MESSAGE *pThis);

extern LLRP_tResultCode
LLRP_CUSTOM_MESSAGE_setVendorIdentifier (
  LLRP_tSCUSTOM_MESSAGE *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCUSTOM_MESSAGE_MessageSubtype;

extern llrp_u8_t
LLRP_CUSTOM_MESSAGE_getMessageSubtype (
  LLRP_tSCUSTOM_MESSAGE *pThis);

extern LLRP_tResultCode
LLRP_CUSTOM_MESSAGE_setMessageSubtype (
  LLRP_tSCUSTOM_MESSAGE *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCUSTOM_MESSAGE_Data;

extern llrp_bytesToEnd_t
LLRP_CUSTOM_MESSAGE_getData (
  LLRP_tSCUSTOM_MESSAGE *pThis);

extern LLRP_tResultCode
LLRP_CUSTOM_MESSAGE_setData (
  LLRP_tSCUSTOM_MESSAGE *pThis,
  llrp_bytesToEnd_t Value);

  


  
struct LLRP_SErrorAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdErrorAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdErrorAck[];

extern LLRP_tSErrorAck *
LLRP_ErrorAck_construct (void);

extern void
LLRP_ErrorAck_destruct (
 LLRP_tSErrorAck * pThis);

extern void
LLRP_ErrorAck_decodeFields (
 LLRP_tSErrorAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ErrorAck_assimilateSubParameters (
 LLRP_tSErrorAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ErrorAck_encode (
  const LLRP_tSErrorAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_ErrorAck_getStatus (
  LLRP_tSErrorAck *pThis);

extern LLRP_tResultCode
LLRP_ErrorAck_setStatus (
  LLRP_tSErrorAck *pThis,
  LLRP_tSStatus *pValue);



  
struct LLRP_SKeepalive
{
    LLRP_tSMessage hdr;
  
  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdKeepalive;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdKeepalive[];

extern LLRP_tSKeepalive *
LLRP_Keepalive_construct (void);

extern void
LLRP_Keepalive_destruct (
 LLRP_tSKeepalive * pThis);

extern void
LLRP_Keepalive_decodeFields (
 LLRP_tSKeepalive * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_Keepalive_assimilateSubParameters (
 LLRP_tSKeepalive * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_Keepalive_encode (
  const LLRP_tSKeepalive *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  


  
struct LLRP_SKeepaliveAck
{
    LLRP_tSMessage hdr;
  
  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdKeepaliveAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdKeepaliveAck[];

extern LLRP_tSKeepaliveAck *
LLRP_KeepaliveAck_construct (void);

extern void
LLRP_KeepaliveAck_destruct (
 LLRP_tSKeepaliveAck * pThis);

extern void
LLRP_KeepaliveAck_decodeFields (
 LLRP_tSKeepaliveAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_KeepaliveAck_assimilateSubParameters (
 LLRP_tSKeepaliveAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_KeepaliveAck_encode (
  const LLRP_tSKeepaliveAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  


  
struct LLRP_SDisconnect
{
    LLRP_tSMessage hdr;
  
  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdDisconnect;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDisconnect[];

extern LLRP_tSDisconnect *
LLRP_Disconnect_construct (void);

extern void
LLRP_Disconnect_destruct (
 LLRP_tSDisconnect * pThis);

extern void
LLRP_Disconnect_decodeFields (
 LLRP_tSDisconnect * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_Disconnect_assimilateSubParameters (
 LLRP_tSDisconnect * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_Disconnect_encode (
  const LLRP_tSDisconnect *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  


  
struct LLRP_SDisconnectAck
{
    LLRP_tSMessage hdr;
  
  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdDisconnectAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDisconnectAck[];

extern LLRP_tSDisconnectAck *
LLRP_DisconnectAck_construct (void);

extern void
LLRP_DisconnectAck_destruct (
 LLRP_tSDisconnectAck * pThis);

extern void
LLRP_DisconnectAck_decodeFields (
 LLRP_tSDisconnectAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DisconnectAck_assimilateSubParameters (
 LLRP_tSDisconnectAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DisconnectAck_encode (
  const LLRP_tSDisconnectAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  


  
struct LLRP_SDeviceEventNotification
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSUTCTimestamp * pUTCTimestamp;

    LLRP_tSGPIEvent * pGPIEvent;

    LLRP_tSSelectSpecEvent * pSelectSpecEvent;

    LLRP_tSAntennaSpecEvent * pAntennaSpecEvent;

    LLRP_tSAntennaStatusEvent * pAntennaStatusEvent;

    LLRP_tSConnectionAttemptEvent * pConnectionAttemptEvent;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdDeviceEventNotification;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDeviceEventNotification[];

extern LLRP_tSDeviceEventNotification *
LLRP_DeviceEventNotification_construct (void);

extern void
LLRP_DeviceEventNotification_destruct (
 LLRP_tSDeviceEventNotification * pThis);

extern void
LLRP_DeviceEventNotification_decodeFields (
 LLRP_tSDeviceEventNotification * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DeviceEventNotification_assimilateSubParameters (
 LLRP_tSDeviceEventNotification * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DeviceEventNotification_encode (
  const LLRP_tSDeviceEventNotification *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSUTCTimestamp *
LLRP_DeviceEventNotification_getUTCTimestamp (
  LLRP_tSDeviceEventNotification *pThis);

extern LLRP_tResultCode
LLRP_DeviceEventNotification_setUTCTimestamp (
  LLRP_tSDeviceEventNotification *pThis,
  LLRP_tSUTCTimestamp *pValue);

extern LLRP_tSGPIEvent *
LLRP_DeviceEventNotification_getGPIEvent (
  LLRP_tSDeviceEventNotification *pThis);

extern LLRP_tResultCode
LLRP_DeviceEventNotification_setGPIEvent (
  LLRP_tSDeviceEventNotification *pThis,
  LLRP_tSGPIEvent *pValue);

extern LLRP_tSSelectSpecEvent *
LLRP_DeviceEventNotification_getSelectSpecEvent (
  LLRP_tSDeviceEventNotification *pThis);

extern LLRP_tResultCode
LLRP_DeviceEventNotification_setSelectSpecEvent (
  LLRP_tSDeviceEventNotification *pThis,
  LLRP_tSSelectSpecEvent *pValue);

extern LLRP_tSAntennaSpecEvent *
LLRP_DeviceEventNotification_getAntennaSpecEvent (
  LLRP_tSDeviceEventNotification *pThis);

extern LLRP_tResultCode
LLRP_DeviceEventNotification_setAntennaSpecEvent (
  LLRP_tSDeviceEventNotification *pThis,
  LLRP_tSAntennaSpecEvent *pValue);

extern LLRP_tSAntennaStatusEvent *
LLRP_DeviceEventNotification_getAntennaStatusEvent (
  LLRP_tSDeviceEventNotification *pThis);

extern LLRP_tResultCode
LLRP_DeviceEventNotification_setAntennaStatusEvent (
  LLRP_tSDeviceEventNotification *pThis,
  LLRP_tSAntennaStatusEvent *pValue);

extern LLRP_tSConnectionAttemptEvent *
LLRP_DeviceEventNotification_getConnectionAttemptEvent (
  LLRP_tSDeviceEventNotification *pThis);

extern LLRP_tResultCode
LLRP_DeviceEventNotification_setConnectionAttemptEvent (
  LLRP_tSDeviceEventNotification *pThis,
  LLRP_tSConnectionAttemptEvent *pValue);



  
struct LLRP_SGetDeviceCapabilities
{
    LLRP_tSMessage hdr;
  
    LLRP_tECapabilitiesRequestedData eRequestedData;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdGetDeviceCapabilities;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGetDeviceCapabilities[];

extern LLRP_tSGetDeviceCapabilities *
LLRP_GetDeviceCapabilities_construct (void);

extern void
LLRP_GetDeviceCapabilities_destruct (
 LLRP_tSGetDeviceCapabilities * pThis);

extern void
LLRP_GetDeviceCapabilities_decodeFields (
 LLRP_tSGetDeviceCapabilities * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GetDeviceCapabilities_assimilateSubParameters (
 LLRP_tSGetDeviceCapabilities * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GetDeviceCapabilities_encode (
  const LLRP_tSGetDeviceCapabilities *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGetDeviceCapabilities_RequestedData;

extern LLRP_tECapabilitiesRequestedData
LLRP_GetDeviceCapabilities_getRequestedData (
  LLRP_tSGetDeviceCapabilities *pThis);

extern LLRP_tResultCode
LLRP_GetDeviceCapabilities_setRequestedData (
  LLRP_tSGetDeviceCapabilities *pThis,
  LLRP_tECapabilitiesRequestedData Value);

  


  
struct LLRP_SGetDeviceCapabilitiesAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

    LLRP_tSGeneralCapabilities * pGeneralCapabilities;

    LLRP_tSCommunicationCapabilities * pCommunicationCapabilities;

    LLRP_tSSpecCapabilities * pSpecCapabilities;

    LLRP_tSRfCapabilities * pRfCapabilities;

    LLRP_tSAirProtocolCapabilities * pAirProtocolCapabilities;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdGetDeviceCapabilitiesAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGetDeviceCapabilitiesAck[];

extern LLRP_tSGetDeviceCapabilitiesAck *
LLRP_GetDeviceCapabilitiesAck_construct (void);

extern void
LLRP_GetDeviceCapabilitiesAck_destruct (
 LLRP_tSGetDeviceCapabilitiesAck * pThis);

extern void
LLRP_GetDeviceCapabilitiesAck_decodeFields (
 LLRP_tSGetDeviceCapabilitiesAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GetDeviceCapabilitiesAck_assimilateSubParameters (
 LLRP_tSGetDeviceCapabilitiesAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GetDeviceCapabilitiesAck_encode (
  const LLRP_tSGetDeviceCapabilitiesAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_GetDeviceCapabilitiesAck_getStatus (
  LLRP_tSGetDeviceCapabilitiesAck *pThis);

extern LLRP_tResultCode
LLRP_GetDeviceCapabilitiesAck_setStatus (
  LLRP_tSGetDeviceCapabilitiesAck *pThis,
  LLRP_tSStatus *pValue);

extern LLRP_tSGeneralCapabilities *
LLRP_GetDeviceCapabilitiesAck_getGeneralCapabilities (
  LLRP_tSGetDeviceCapabilitiesAck *pThis);

extern LLRP_tResultCode
LLRP_GetDeviceCapabilitiesAck_setGeneralCapabilities (
  LLRP_tSGetDeviceCapabilitiesAck *pThis,
  LLRP_tSGeneralCapabilities *pValue);

extern LLRP_tSCommunicationCapabilities *
LLRP_GetDeviceCapabilitiesAck_getCommunicationCapabilities (
  LLRP_tSGetDeviceCapabilitiesAck *pThis);

extern LLRP_tResultCode
LLRP_GetDeviceCapabilitiesAck_setCommunicationCapabilities (
  LLRP_tSGetDeviceCapabilitiesAck *pThis,
  LLRP_tSCommunicationCapabilities *pValue);

extern LLRP_tSSpecCapabilities *
LLRP_GetDeviceCapabilitiesAck_getSpecCapabilities (
  LLRP_tSGetDeviceCapabilitiesAck *pThis);

extern LLRP_tResultCode
LLRP_GetDeviceCapabilitiesAck_setSpecCapabilities (
  LLRP_tSGetDeviceCapabilitiesAck *pThis,
  LLRP_tSSpecCapabilities *pValue);

extern LLRP_tSRfCapabilities *
LLRP_GetDeviceCapabilitiesAck_getRfCapabilities (
  LLRP_tSGetDeviceCapabilitiesAck *pThis);

extern LLRP_tResultCode
LLRP_GetDeviceCapabilitiesAck_setRfCapabilities (
  LLRP_tSGetDeviceCapabilitiesAck *pThis,
  LLRP_tSRfCapabilities *pValue);

extern LLRP_tSAirProtocolCapabilities *
LLRP_GetDeviceCapabilitiesAck_getAirProtocolCapabilities (
  LLRP_tSGetDeviceCapabilitiesAck *pThis);

extern LLRP_tResultCode
LLRP_GetDeviceCapabilitiesAck_setAirProtocolCapabilities (
  LLRP_tSGetDeviceCapabilitiesAck *pThis,
  LLRP_tSAirProtocolCapabilities *pValue);



  
struct LLRP_SAddSelectSpec
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSSelectSpec * pSelectSpec;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdAddSelectSpec;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAddSelectSpec[];

extern LLRP_tSAddSelectSpec *
LLRP_AddSelectSpec_construct (void);

extern void
LLRP_AddSelectSpec_destruct (
 LLRP_tSAddSelectSpec * pThis);

extern void
LLRP_AddSelectSpec_decodeFields (
 LLRP_tSAddSelectSpec * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AddSelectSpec_assimilateSubParameters (
 LLRP_tSAddSelectSpec * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AddSelectSpec_encode (
  const LLRP_tSAddSelectSpec *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSSelectSpec *
LLRP_AddSelectSpec_getSelectSpec (
  LLRP_tSAddSelectSpec *pThis);

extern LLRP_tResultCode
LLRP_AddSelectSpec_setSelectSpec (
  LLRP_tSAddSelectSpec *pThis,
  LLRP_tSSelectSpec *pValue);



  
struct LLRP_SAddSelectSpecAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdAddSelectSpecAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAddSelectSpecAck[];

extern LLRP_tSAddSelectSpecAck *
LLRP_AddSelectSpecAck_construct (void);

extern void
LLRP_AddSelectSpecAck_destruct (
 LLRP_tSAddSelectSpecAck * pThis);

extern void
LLRP_AddSelectSpecAck_decodeFields (
 LLRP_tSAddSelectSpecAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AddSelectSpecAck_assimilateSubParameters (
 LLRP_tSAddSelectSpecAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AddSelectSpecAck_encode (
  const LLRP_tSAddSelectSpecAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_AddSelectSpecAck_getStatus (
  LLRP_tSAddSelectSpecAck *pThis);

extern LLRP_tResultCode
LLRP_AddSelectSpecAck_setStatus (
  LLRP_tSAddSelectSpecAck *pThis,
  LLRP_tSStatus *pValue);



  
struct LLRP_SDeleteSelectSpec
{
    LLRP_tSMessage hdr;
  
    llrp_u32_t SelectSpecID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdDeleteSelectSpec;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDeleteSelectSpec[];

extern LLRP_tSDeleteSelectSpec *
LLRP_DeleteSelectSpec_construct (void);

extern void
LLRP_DeleteSelectSpec_destruct (
 LLRP_tSDeleteSelectSpec * pThis);

extern void
LLRP_DeleteSelectSpec_decodeFields (
 LLRP_tSDeleteSelectSpec * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DeleteSelectSpec_assimilateSubParameters (
 LLRP_tSDeleteSelectSpec * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DeleteSelectSpec_encode (
  const LLRP_tSDeleteSelectSpec *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdDeleteSelectSpec_SelectSpecID;

extern llrp_u32_t
LLRP_DeleteSelectSpec_getSelectSpecID (
  LLRP_tSDeleteSelectSpec *pThis);

extern LLRP_tResultCode
LLRP_DeleteSelectSpec_setSelectSpecID (
  LLRP_tSDeleteSelectSpec *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SDeleteSelectSpecAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdDeleteSelectSpecAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDeleteSelectSpecAck[];

extern LLRP_tSDeleteSelectSpecAck *
LLRP_DeleteSelectSpecAck_construct (void);

extern void
LLRP_DeleteSelectSpecAck_destruct (
 LLRP_tSDeleteSelectSpecAck * pThis);

extern void
LLRP_DeleteSelectSpecAck_decodeFields (
 LLRP_tSDeleteSelectSpecAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DeleteSelectSpecAck_assimilateSubParameters (
 LLRP_tSDeleteSelectSpecAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DeleteSelectSpecAck_encode (
  const LLRP_tSDeleteSelectSpecAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_DeleteSelectSpecAck_getStatus (
  LLRP_tSDeleteSelectSpecAck *pThis);

extern LLRP_tResultCode
LLRP_DeleteSelectSpecAck_setStatus (
  LLRP_tSDeleteSelectSpecAck *pThis,
  LLRP_tSStatus *pValue);



  
struct LLRP_SStartSelectSpec
{
    LLRP_tSMessage hdr;
  
    llrp_u32_t SelectSpecID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdStartSelectSpec;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdStartSelectSpec[];

extern LLRP_tSStartSelectSpec *
LLRP_StartSelectSpec_construct (void);

extern void
LLRP_StartSelectSpec_destruct (
 LLRP_tSStartSelectSpec * pThis);

extern void
LLRP_StartSelectSpec_decodeFields (
 LLRP_tSStartSelectSpec * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_StartSelectSpec_assimilateSubParameters (
 LLRP_tSStartSelectSpec * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_StartSelectSpec_encode (
  const LLRP_tSStartSelectSpec *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdStartSelectSpec_SelectSpecID;

extern llrp_u32_t
LLRP_StartSelectSpec_getSelectSpecID (
  LLRP_tSStartSelectSpec *pThis);

extern LLRP_tResultCode
LLRP_StartSelectSpec_setSelectSpecID (
  LLRP_tSStartSelectSpec *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SStartSelectSpecAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdStartSelectSpecAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdStartSelectSpecAck[];

extern LLRP_tSStartSelectSpecAck *
LLRP_StartSelectSpecAck_construct (void);

extern void
LLRP_StartSelectSpecAck_destruct (
 LLRP_tSStartSelectSpecAck * pThis);

extern void
LLRP_StartSelectSpecAck_decodeFields (
 LLRP_tSStartSelectSpecAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_StartSelectSpecAck_assimilateSubParameters (
 LLRP_tSStartSelectSpecAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_StartSelectSpecAck_encode (
  const LLRP_tSStartSelectSpecAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_StartSelectSpecAck_getStatus (
  LLRP_tSStartSelectSpecAck *pThis);

extern LLRP_tResultCode
LLRP_StartSelectSpecAck_setStatus (
  LLRP_tSStartSelectSpecAck *pThis,
  LLRP_tSStatus *pValue);



  
struct LLRP_SStopSelectSpec
{
    LLRP_tSMessage hdr;
  
    llrp_u32_t SelectSpecID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdStopSelectSpec;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdStopSelectSpec[];

extern LLRP_tSStopSelectSpec *
LLRP_StopSelectSpec_construct (void);

extern void
LLRP_StopSelectSpec_destruct (
 LLRP_tSStopSelectSpec * pThis);

extern void
LLRP_StopSelectSpec_decodeFields (
 LLRP_tSStopSelectSpec * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_StopSelectSpec_assimilateSubParameters (
 LLRP_tSStopSelectSpec * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_StopSelectSpec_encode (
  const LLRP_tSStopSelectSpec *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdStopSelectSpec_SelectSpecID;

extern llrp_u32_t
LLRP_StopSelectSpec_getSelectSpecID (
  LLRP_tSStopSelectSpec *pThis);

extern LLRP_tResultCode
LLRP_StopSelectSpec_setSelectSpecID (
  LLRP_tSStopSelectSpec *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SStopSelectSpecAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdStopSelectSpecAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdStopSelectSpecAck[];

extern LLRP_tSStopSelectSpecAck *
LLRP_StopSelectSpecAck_construct (void);

extern void
LLRP_StopSelectSpecAck_destruct (
 LLRP_tSStopSelectSpecAck * pThis);

extern void
LLRP_StopSelectSpecAck_decodeFields (
 LLRP_tSStopSelectSpecAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_StopSelectSpecAck_assimilateSubParameters (
 LLRP_tSStopSelectSpecAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_StopSelectSpecAck_encode (
  const LLRP_tSStopSelectSpecAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_StopSelectSpecAck_getStatus (
  LLRP_tSStopSelectSpecAck *pThis);

extern LLRP_tResultCode
LLRP_StopSelectSpecAck_setStatus (
  LLRP_tSStopSelectSpecAck *pThis,
  LLRP_tSStatus *pValue);



  
struct LLRP_SEnableSelectSpec
{
    LLRP_tSMessage hdr;
  
    llrp_u32_t SelectSpecID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdEnableSelectSpec;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdEnableSelectSpec[];

extern LLRP_tSEnableSelectSpec *
LLRP_EnableSelectSpec_construct (void);

extern void
LLRP_EnableSelectSpec_destruct (
 LLRP_tSEnableSelectSpec * pThis);

extern void
LLRP_EnableSelectSpec_decodeFields (
 LLRP_tSEnableSelectSpec * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_EnableSelectSpec_assimilateSubParameters (
 LLRP_tSEnableSelectSpec * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_EnableSelectSpec_encode (
  const LLRP_tSEnableSelectSpec *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdEnableSelectSpec_SelectSpecID;

extern llrp_u32_t
LLRP_EnableSelectSpec_getSelectSpecID (
  LLRP_tSEnableSelectSpec *pThis);

extern LLRP_tResultCode
LLRP_EnableSelectSpec_setSelectSpecID (
  LLRP_tSEnableSelectSpec *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SEnableSelectSpecAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdEnableSelectSpecAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdEnableSelectSpecAck[];

extern LLRP_tSEnableSelectSpecAck *
LLRP_EnableSelectSpecAck_construct (void);

extern void
LLRP_EnableSelectSpecAck_destruct (
 LLRP_tSEnableSelectSpecAck * pThis);

extern void
LLRP_EnableSelectSpecAck_decodeFields (
 LLRP_tSEnableSelectSpecAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_EnableSelectSpecAck_assimilateSubParameters (
 LLRP_tSEnableSelectSpecAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_EnableSelectSpecAck_encode (
  const LLRP_tSEnableSelectSpecAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_EnableSelectSpecAck_getStatus (
  LLRP_tSEnableSelectSpecAck *pThis);

extern LLRP_tResultCode
LLRP_EnableSelectSpecAck_setStatus (
  LLRP_tSEnableSelectSpecAck *pThis,
  LLRP_tSStatus *pValue);



  
struct LLRP_SDisableSelectSpec
{
    LLRP_tSMessage hdr;
  
    llrp_u32_t SelectSpecID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdDisableSelectSpec;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDisableSelectSpec[];

extern LLRP_tSDisableSelectSpec *
LLRP_DisableSelectSpec_construct (void);

extern void
LLRP_DisableSelectSpec_destruct (
 LLRP_tSDisableSelectSpec * pThis);

extern void
LLRP_DisableSelectSpec_decodeFields (
 LLRP_tSDisableSelectSpec * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DisableSelectSpec_assimilateSubParameters (
 LLRP_tSDisableSelectSpec * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DisableSelectSpec_encode (
  const LLRP_tSDisableSelectSpec *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdDisableSelectSpec_SelectSpecID;

extern llrp_u32_t
LLRP_DisableSelectSpec_getSelectSpecID (
  LLRP_tSDisableSelectSpec *pThis);

extern LLRP_tResultCode
LLRP_DisableSelectSpec_setSelectSpecID (
  LLRP_tSDisableSelectSpec *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SDisableSelectSpecAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdDisableSelectSpecAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDisableSelectSpecAck[];

extern LLRP_tSDisableSelectSpecAck *
LLRP_DisableSelectSpecAck_construct (void);

extern void
LLRP_DisableSelectSpecAck_destruct (
 LLRP_tSDisableSelectSpecAck * pThis);

extern void
LLRP_DisableSelectSpecAck_decodeFields (
 LLRP_tSDisableSelectSpecAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DisableSelectSpecAck_assimilateSubParameters (
 LLRP_tSDisableSelectSpecAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DisableSelectSpecAck_encode (
  const LLRP_tSDisableSelectSpecAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_DisableSelectSpecAck_getStatus (
  LLRP_tSDisableSelectSpecAck *pThis);

extern LLRP_tResultCode
LLRP_DisableSelectSpecAck_setStatus (
  LLRP_tSDisableSelectSpecAck *pThis,
  LLRP_tSStatus *pValue);



  
struct LLRP_SGetSelectSpec
{
    LLRP_tSMessage hdr;
  
  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdGetSelectSpec;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGetSelectSpec[];

extern LLRP_tSGetSelectSpec *
LLRP_GetSelectSpec_construct (void);

extern void
LLRP_GetSelectSpec_destruct (
 LLRP_tSGetSelectSpec * pThis);

extern void
LLRP_GetSelectSpec_decodeFields (
 LLRP_tSGetSelectSpec * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GetSelectSpec_assimilateSubParameters (
 LLRP_tSGetSelectSpec * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GetSelectSpec_encode (
  const LLRP_tSGetSelectSpec *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  


  
struct LLRP_SGetSelectSpecAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

    LLRP_tSSelectSpec * listSelectSpec;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdGetSelectSpecAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGetSelectSpecAck[];

extern LLRP_tSGetSelectSpecAck *
LLRP_GetSelectSpecAck_construct (void);

extern void
LLRP_GetSelectSpecAck_destruct (
 LLRP_tSGetSelectSpecAck * pThis);

extern void
LLRP_GetSelectSpecAck_decodeFields (
 LLRP_tSGetSelectSpecAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GetSelectSpecAck_assimilateSubParameters (
 LLRP_tSGetSelectSpecAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GetSelectSpecAck_encode (
  const LLRP_tSGetSelectSpecAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_GetSelectSpecAck_getStatus (
  LLRP_tSGetSelectSpecAck *pThis);

extern LLRP_tResultCode
LLRP_GetSelectSpecAck_setStatus (
  LLRP_tSGetSelectSpecAck *pThis,
  LLRP_tSStatus *pValue);

extern LLRP_tSSelectSpec *
LLRP_GetSelectSpecAck_beginSelectSpec (
  LLRP_tSGetSelectSpecAck *pThis);

extern LLRP_tSSelectSpec *
LLRP_GetSelectSpecAck_nextSelectSpec (
  LLRP_tSSelectSpec *pCurrent);

extern void
LLRP_GetSelectSpecAck_clearSelectSpec (
  LLRP_tSGetSelectSpecAck *pThis);

extern int
LLRP_GetSelectSpecAck_countSelectSpec (
  LLRP_tSGetSelectSpecAck *pThis);

extern LLRP_tResultCode
LLRP_GetSelectSpecAck_addSelectSpec (
  LLRP_tSGetSelectSpecAck *pThis,
  LLRP_tSSelectSpec *pValue);




  
struct LLRP_SAddAccessSpec
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSAccessSpec * pAccessSpec;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdAddAccessSpec;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAddAccessSpec[];

extern LLRP_tSAddAccessSpec *
LLRP_AddAccessSpec_construct (void);

extern void
LLRP_AddAccessSpec_destruct (
 LLRP_tSAddAccessSpec * pThis);

extern void
LLRP_AddAccessSpec_decodeFields (
 LLRP_tSAddAccessSpec * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AddAccessSpec_assimilateSubParameters (
 LLRP_tSAddAccessSpec * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AddAccessSpec_encode (
  const LLRP_tSAddAccessSpec *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSAccessSpec *
LLRP_AddAccessSpec_getAccessSpec (
  LLRP_tSAddAccessSpec *pThis);

extern LLRP_tResultCode
LLRP_AddAccessSpec_setAccessSpec (
  LLRP_tSAddAccessSpec *pThis,
  LLRP_tSAccessSpec *pValue);



  
struct LLRP_SAddAccessSpecAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdAddAccessSpecAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAddAccessSpecAck[];

extern LLRP_tSAddAccessSpecAck *
LLRP_AddAccessSpecAck_construct (void);

extern void
LLRP_AddAccessSpecAck_destruct (
 LLRP_tSAddAccessSpecAck * pThis);

extern void
LLRP_AddAccessSpecAck_decodeFields (
 LLRP_tSAddAccessSpecAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AddAccessSpecAck_assimilateSubParameters (
 LLRP_tSAddAccessSpecAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AddAccessSpecAck_encode (
  const LLRP_tSAddAccessSpecAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_AddAccessSpecAck_getStatus (
  LLRP_tSAddAccessSpecAck *pThis);

extern LLRP_tResultCode
LLRP_AddAccessSpecAck_setStatus (
  LLRP_tSAddAccessSpecAck *pThis,
  LLRP_tSStatus *pValue);



  
struct LLRP_SDelectAccessSpec
{
    LLRP_tSMessage hdr;
  
    llrp_u32_t AccessSpecID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdDelectAccessSpec;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDelectAccessSpec[];

extern LLRP_tSDelectAccessSpec *
LLRP_DelectAccessSpec_construct (void);

extern void
LLRP_DelectAccessSpec_destruct (
 LLRP_tSDelectAccessSpec * pThis);

extern void
LLRP_DelectAccessSpec_decodeFields (
 LLRP_tSDelectAccessSpec * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DelectAccessSpec_assimilateSubParameters (
 LLRP_tSDelectAccessSpec * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DelectAccessSpec_encode (
  const LLRP_tSDelectAccessSpec *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdDelectAccessSpec_AccessSpecID;

extern llrp_u32_t
LLRP_DelectAccessSpec_getAccessSpecID (
  LLRP_tSDelectAccessSpec *pThis);

extern LLRP_tResultCode
LLRP_DelectAccessSpec_setAccessSpecID (
  LLRP_tSDelectAccessSpec *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SDelectAccessSpecAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdDelectAccessSpecAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDelectAccessSpecAck[];

extern LLRP_tSDelectAccessSpecAck *
LLRP_DelectAccessSpecAck_construct (void);

extern void
LLRP_DelectAccessSpecAck_destruct (
 LLRP_tSDelectAccessSpecAck * pThis);

extern void
LLRP_DelectAccessSpecAck_decodeFields (
 LLRP_tSDelectAccessSpecAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DelectAccessSpecAck_assimilateSubParameters (
 LLRP_tSDelectAccessSpecAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DelectAccessSpecAck_encode (
  const LLRP_tSDelectAccessSpecAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_DelectAccessSpecAck_getStatus (
  LLRP_tSDelectAccessSpecAck *pThis);

extern LLRP_tResultCode
LLRP_DelectAccessSpecAck_setStatus (
  LLRP_tSDelectAccessSpecAck *pThis,
  LLRP_tSStatus *pValue);



  
struct LLRP_SEnableAccessSpec
{
    LLRP_tSMessage hdr;
  
    llrp_u32_t AccessSpecID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdEnableAccessSpec;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdEnableAccessSpec[];

extern LLRP_tSEnableAccessSpec *
LLRP_EnableAccessSpec_construct (void);

extern void
LLRP_EnableAccessSpec_destruct (
 LLRP_tSEnableAccessSpec * pThis);

extern void
LLRP_EnableAccessSpec_decodeFields (
 LLRP_tSEnableAccessSpec * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_EnableAccessSpec_assimilateSubParameters (
 LLRP_tSEnableAccessSpec * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_EnableAccessSpec_encode (
  const LLRP_tSEnableAccessSpec *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdEnableAccessSpec_AccessSpecID;

extern llrp_u32_t
LLRP_EnableAccessSpec_getAccessSpecID (
  LLRP_tSEnableAccessSpec *pThis);

extern LLRP_tResultCode
LLRP_EnableAccessSpec_setAccessSpecID (
  LLRP_tSEnableAccessSpec *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SEnableAccessSpecAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdEnableAccessSpecAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdEnableAccessSpecAck[];

extern LLRP_tSEnableAccessSpecAck *
LLRP_EnableAccessSpecAck_construct (void);

extern void
LLRP_EnableAccessSpecAck_destruct (
 LLRP_tSEnableAccessSpecAck * pThis);

extern void
LLRP_EnableAccessSpecAck_decodeFields (
 LLRP_tSEnableAccessSpecAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_EnableAccessSpecAck_assimilateSubParameters (
 LLRP_tSEnableAccessSpecAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_EnableAccessSpecAck_encode (
  const LLRP_tSEnableAccessSpecAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_EnableAccessSpecAck_getStatus (
  LLRP_tSEnableAccessSpecAck *pThis);

extern LLRP_tResultCode
LLRP_EnableAccessSpecAck_setStatus (
  LLRP_tSEnableAccessSpecAck *pThis,
  LLRP_tSStatus *pValue);



  
struct LLRP_SDiableAccessSpec
{
    LLRP_tSMessage hdr;
  
    llrp_u32_t AccessSpecID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdDiableAccessSpec;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDiableAccessSpec[];

extern LLRP_tSDiableAccessSpec *
LLRP_DiableAccessSpec_construct (void);

extern void
LLRP_DiableAccessSpec_destruct (
 LLRP_tSDiableAccessSpec * pThis);

extern void
LLRP_DiableAccessSpec_decodeFields (
 LLRP_tSDiableAccessSpec * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DiableAccessSpec_assimilateSubParameters (
 LLRP_tSDiableAccessSpec * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DiableAccessSpec_encode (
  const LLRP_tSDiableAccessSpec *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdDiableAccessSpec_AccessSpecID;

extern llrp_u32_t
LLRP_DiableAccessSpec_getAccessSpecID (
  LLRP_tSDiableAccessSpec *pThis);

extern LLRP_tResultCode
LLRP_DiableAccessSpec_setAccessSpecID (
  LLRP_tSDiableAccessSpec *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SDiableAccessSpecAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdDiableAccessSpecAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDiableAccessSpecAck[];

extern LLRP_tSDiableAccessSpecAck *
LLRP_DiableAccessSpecAck_construct (void);

extern void
LLRP_DiableAccessSpecAck_destruct (
 LLRP_tSDiableAccessSpecAck * pThis);

extern void
LLRP_DiableAccessSpecAck_decodeFields (
 LLRP_tSDiableAccessSpecAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DiableAccessSpecAck_assimilateSubParameters (
 LLRP_tSDiableAccessSpecAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DiableAccessSpecAck_encode (
  const LLRP_tSDiableAccessSpecAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_DiableAccessSpecAck_getStatus (
  LLRP_tSDiableAccessSpecAck *pThis);

extern LLRP_tResultCode
LLRP_DiableAccessSpecAck_setStatus (
  LLRP_tSDiableAccessSpecAck *pThis,
  LLRP_tSStatus *pValue);



  
struct LLRP_SGetAccessSpec
{
    LLRP_tSMessage hdr;
  
  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdGetAccessSpec;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGetAccessSpec[];

extern LLRP_tSGetAccessSpec *
LLRP_GetAccessSpec_construct (void);

extern void
LLRP_GetAccessSpec_destruct (
 LLRP_tSGetAccessSpec * pThis);

extern void
LLRP_GetAccessSpec_decodeFields (
 LLRP_tSGetAccessSpec * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GetAccessSpec_assimilateSubParameters (
 LLRP_tSGetAccessSpec * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GetAccessSpec_encode (
  const LLRP_tSGetAccessSpec *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  


  
struct LLRP_SGetAccessSpecAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

    LLRP_tSAccessSpec * listAccessSpec;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdGetAccessSpecAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGetAccessSpecAck[];

extern LLRP_tSGetAccessSpecAck *
LLRP_GetAccessSpecAck_construct (void);

extern void
LLRP_GetAccessSpecAck_destruct (
 LLRP_tSGetAccessSpecAck * pThis);

extern void
LLRP_GetAccessSpecAck_decodeFields (
 LLRP_tSGetAccessSpecAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GetAccessSpecAck_assimilateSubParameters (
 LLRP_tSGetAccessSpecAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GetAccessSpecAck_encode (
  const LLRP_tSGetAccessSpecAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_GetAccessSpecAck_getStatus (
  LLRP_tSGetAccessSpecAck *pThis);

extern LLRP_tResultCode
LLRP_GetAccessSpecAck_setStatus (
  LLRP_tSGetAccessSpecAck *pThis,
  LLRP_tSStatus *pValue);

extern LLRP_tSAccessSpec *
LLRP_GetAccessSpecAck_beginAccessSpec (
  LLRP_tSGetAccessSpecAck *pThis);

extern LLRP_tSAccessSpec *
LLRP_GetAccessSpecAck_nextAccessSpec (
  LLRP_tSAccessSpec *pCurrent);

extern void
LLRP_GetAccessSpecAck_clearAccessSpec (
  LLRP_tSGetAccessSpecAck *pThis);

extern int
LLRP_GetAccessSpecAck_countAccessSpec (
  LLRP_tSGetAccessSpecAck *pThis);

extern LLRP_tResultCode
LLRP_GetAccessSpecAck_addAccessSpec (
  LLRP_tSGetAccessSpecAck *pThis,
  LLRP_tSAccessSpec *pValue);




  
struct LLRP_STagSelectAccessReport
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSTagReportData * listTagReportData;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdTagSelectAccessReport;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdTagSelectAccessReport[];

extern LLRP_tSTagSelectAccessReport *
LLRP_TagSelectAccessReport_construct (void);

extern void
LLRP_TagSelectAccessReport_destruct (
 LLRP_tSTagSelectAccessReport * pThis);

extern void
LLRP_TagSelectAccessReport_decodeFields (
 LLRP_tSTagSelectAccessReport * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_TagSelectAccessReport_assimilateSubParameters (
 LLRP_tSTagSelectAccessReport * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_TagSelectAccessReport_encode (
  const LLRP_tSTagSelectAccessReport *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSTagReportData *
LLRP_TagSelectAccessReport_beginTagReportData (
  LLRP_tSTagSelectAccessReport *pThis);

extern LLRP_tSTagReportData *
LLRP_TagSelectAccessReport_nextTagReportData (
  LLRP_tSTagReportData *pCurrent);

extern void
LLRP_TagSelectAccessReport_clearTagReportData (
  LLRP_tSTagSelectAccessReport *pThis);

extern int
LLRP_TagSelectAccessReport_countTagReportData (
  LLRP_tSTagSelectAccessReport *pThis);

extern LLRP_tResultCode
LLRP_TagSelectAccessReport_addTagReportData (
  LLRP_tSTagSelectAccessReport *pThis,
  LLRP_tSTagReportData *pValue);




  
struct LLRP_SClientRequestOp
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSTagReportData * pTagReportData;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdClientRequestOp;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdClientRequestOp[];

extern LLRP_tSClientRequestOp *
LLRP_ClientRequestOp_construct (void);

extern void
LLRP_ClientRequestOp_destruct (
 LLRP_tSClientRequestOp * pThis);

extern void
LLRP_ClientRequestOp_decodeFields (
 LLRP_tSClientRequestOp * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ClientRequestOp_assimilateSubParameters (
 LLRP_tSClientRequestOp * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ClientRequestOp_encode (
  const LLRP_tSClientRequestOp *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSTagReportData *
LLRP_ClientRequestOp_getTagReportData (
  LLRP_tSClientRequestOp *pThis);

extern LLRP_tResultCode
LLRP_ClientRequestOp_setTagReportData (
  LLRP_tSClientRequestOp *pThis,
  LLRP_tSTagReportData *pValue);



  
struct LLRP_SClientRequestOpAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSClientRequestAck * pClientRequestAck;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdClientRequestOpAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdClientRequestOpAck[];

extern LLRP_tSClientRequestOpAck *
LLRP_ClientRequestOpAck_construct (void);

extern void
LLRP_ClientRequestOpAck_destruct (
 LLRP_tSClientRequestOpAck * pThis);

extern void
LLRP_ClientRequestOpAck_decodeFields (
 LLRP_tSClientRequestOpAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ClientRequestOpAck_assimilateSubParameters (
 LLRP_tSClientRequestOpAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ClientRequestOpAck_encode (
  const LLRP_tSClientRequestOpAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSClientRequestAck *
LLRP_ClientRequestOpAck_getClientRequestAck (
  LLRP_tSClientRequestOpAck *pThis);

extern LLRP_tResultCode
LLRP_ClientRequestOpAck_setClientRequestAck (
  LLRP_tSClientRequestOpAck *pThis,
  LLRP_tSClientRequestAck *pValue);



  
struct LLRP_SDeviceBinding
{
    LLRP_tSMessage hdr;
  
    llrp_u8_t BindingType;

    llrp_u8v_t BindingData;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdDeviceBinding;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDeviceBinding[];

extern LLRP_tSDeviceBinding *
LLRP_DeviceBinding_construct (void);

extern void
LLRP_DeviceBinding_destruct (
 LLRP_tSDeviceBinding * pThis);

extern void
LLRP_DeviceBinding_decodeFields (
 LLRP_tSDeviceBinding * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DeviceBinding_assimilateSubParameters (
 LLRP_tSDeviceBinding * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DeviceBinding_encode (
  const LLRP_tSDeviceBinding *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdDeviceBinding_BindingType;

extern llrp_u8_t
LLRP_DeviceBinding_getBindingType (
  LLRP_tSDeviceBinding *pThis);

extern LLRP_tResultCode
LLRP_DeviceBinding_setBindingType (
  LLRP_tSDeviceBinding *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdDeviceBinding_BindingData;

extern llrp_u8v_t
LLRP_DeviceBinding_getBindingData (
  LLRP_tSDeviceBinding *pThis);

extern LLRP_tResultCode
LLRP_DeviceBinding_setBindingData (
  LLRP_tSDeviceBinding *pThis,
  llrp_u8v_t Value);

  


  
struct LLRP_SDeviceBindingAck
{
    LLRP_tSMessage hdr;
  
    llrp_u8v_t BindingResultData;

  
    LLRP_tSStatus * pStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdDeviceBindingAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDeviceBindingAck[];

extern LLRP_tSDeviceBindingAck *
LLRP_DeviceBindingAck_construct (void);

extern void
LLRP_DeviceBindingAck_destruct (
 LLRP_tSDeviceBindingAck * pThis);

extern void
LLRP_DeviceBindingAck_decodeFields (
 LLRP_tSDeviceBindingAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DeviceBindingAck_assimilateSubParameters (
 LLRP_tSDeviceBindingAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DeviceBindingAck_encode (
  const LLRP_tSDeviceBindingAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdDeviceBindingAck_BindingResultData;

extern llrp_u8v_t
LLRP_DeviceBindingAck_getBindingResultData (
  LLRP_tSDeviceBindingAck *pThis);

extern LLRP_tResultCode
LLRP_DeviceBindingAck_setBindingResultData (
  LLRP_tSDeviceBindingAck *pThis,
  llrp_u8v_t Value);

  
extern LLRP_tSStatus *
LLRP_DeviceBindingAck_getStatus (
  LLRP_tSDeviceBindingAck *pThis);

extern LLRP_tResultCode
LLRP_DeviceBindingAck_setStatus (
  LLRP_tSDeviceBindingAck *pThis,
  LLRP_tSStatus *pValue);



  
struct LLRP_SDeviceCertificateConfig
{
    LLRP_tSMessage hdr;
  
    llrp_u8v_t CertificateData;

    llrp_u8v_t UserData;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdDeviceCertificateConfig;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDeviceCertificateConfig[];

extern LLRP_tSDeviceCertificateConfig *
LLRP_DeviceCertificateConfig_construct (void);

extern void
LLRP_DeviceCertificateConfig_destruct (
 LLRP_tSDeviceCertificateConfig * pThis);

extern void
LLRP_DeviceCertificateConfig_decodeFields (
 LLRP_tSDeviceCertificateConfig * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DeviceCertificateConfig_assimilateSubParameters (
 LLRP_tSDeviceCertificateConfig * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DeviceCertificateConfig_encode (
  const LLRP_tSDeviceCertificateConfig *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdDeviceCertificateConfig_CertificateData;

extern llrp_u8v_t
LLRP_DeviceCertificateConfig_getCertificateData (
  LLRP_tSDeviceCertificateConfig *pThis);

extern LLRP_tResultCode
LLRP_DeviceCertificateConfig_setCertificateData (
  LLRP_tSDeviceCertificateConfig *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdDeviceCertificateConfig_UserData;

extern llrp_u8v_t
LLRP_DeviceCertificateConfig_getUserData (
  LLRP_tSDeviceCertificateConfig *pThis);

extern LLRP_tResultCode
LLRP_DeviceCertificateConfig_setUserData (
  LLRP_tSDeviceCertificateConfig *pThis,
  llrp_u8v_t Value);

  


  
struct LLRP_SDeviceCertificateConfigAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdDeviceCertificateConfigAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDeviceCertificateConfigAck[];

extern LLRP_tSDeviceCertificateConfigAck *
LLRP_DeviceCertificateConfigAck_construct (void);

extern void
LLRP_DeviceCertificateConfigAck_destruct (
 LLRP_tSDeviceCertificateConfigAck * pThis);

extern void
LLRP_DeviceCertificateConfigAck_decodeFields (
 LLRP_tSDeviceCertificateConfigAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DeviceCertificateConfigAck_assimilateSubParameters (
 LLRP_tSDeviceCertificateConfigAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DeviceCertificateConfigAck_encode (
  const LLRP_tSDeviceCertificateConfigAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_DeviceCertificateConfigAck_getStatus (
  LLRP_tSDeviceCertificateConfigAck *pThis);

extern LLRP_tResultCode
LLRP_DeviceCertificateConfigAck_setStatus (
  LLRP_tSDeviceCertificateConfigAck *pThis,
  LLRP_tSStatus *pValue);



  
struct LLRP_SUploadTagLog
{
    LLRP_tSMessage hdr;
  
    llrp_u8_t UploadType;

    llrp_u32_t UploadCount;

    llrp_u64_t StartLogSequence;

  
    LLRP_tSStartLogTimestamp * pStartLogTimestamp;

    LLRP_tSEndLogTimestamp * pEndLogTimestamp;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdUploadTagLog;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdUploadTagLog[];

extern LLRP_tSUploadTagLog *
LLRP_UploadTagLog_construct (void);

extern void
LLRP_UploadTagLog_destruct (
 LLRP_tSUploadTagLog * pThis);

extern void
LLRP_UploadTagLog_decodeFields (
 LLRP_tSUploadTagLog * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_UploadTagLog_assimilateSubParameters (
 LLRP_tSUploadTagLog * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_UploadTagLog_encode (
  const LLRP_tSUploadTagLog *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdUploadTagLog_UploadType;

extern llrp_u8_t
LLRP_UploadTagLog_getUploadType (
  LLRP_tSUploadTagLog *pThis);

extern LLRP_tResultCode
LLRP_UploadTagLog_setUploadType (
  LLRP_tSUploadTagLog *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdUploadTagLog_UploadCount;

extern llrp_u32_t
LLRP_UploadTagLog_getUploadCount (
  LLRP_tSUploadTagLog *pThis);

extern LLRP_tResultCode
LLRP_UploadTagLog_setUploadCount (
  LLRP_tSUploadTagLog *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdUploadTagLog_StartLogSequence;

extern llrp_u64_t
LLRP_UploadTagLog_getStartLogSequence (
  LLRP_tSUploadTagLog *pThis);

extern LLRP_tResultCode
LLRP_UploadTagLog_setStartLogSequence (
  LLRP_tSUploadTagLog *pThis,
  llrp_u64_t Value);

  
extern LLRP_tSStartLogTimestamp *
LLRP_UploadTagLog_getStartLogTimestamp (
  LLRP_tSUploadTagLog *pThis);

extern LLRP_tResultCode
LLRP_UploadTagLog_setStartLogTimestamp (
  LLRP_tSUploadTagLog *pThis,
  LLRP_tSStartLogTimestamp *pValue);

extern LLRP_tSEndLogTimestamp *
LLRP_UploadTagLog_getEndLogTimestamp (
  LLRP_tSUploadTagLog *pThis);

extern LLRP_tResultCode
LLRP_UploadTagLog_setEndLogTimestamp (
  LLRP_tSUploadTagLog *pThis,
  LLRP_tSEndLogTimestamp *pValue);



  
struct LLRP_SUploadTagLogAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

    LLRP_tSTagLog * listTagLog;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdUploadTagLogAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdUploadTagLogAck[];

extern LLRP_tSUploadTagLogAck *
LLRP_UploadTagLogAck_construct (void);

extern void
LLRP_UploadTagLogAck_destruct (
 LLRP_tSUploadTagLogAck * pThis);

extern void
LLRP_UploadTagLogAck_decodeFields (
 LLRP_tSUploadTagLogAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_UploadTagLogAck_assimilateSubParameters (
 LLRP_tSUploadTagLogAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_UploadTagLogAck_encode (
  const LLRP_tSUploadTagLogAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_UploadTagLogAck_getStatus (
  LLRP_tSUploadTagLogAck *pThis);

extern LLRP_tResultCode
LLRP_UploadTagLogAck_setStatus (
  LLRP_tSUploadTagLogAck *pThis,
  LLRP_tSStatus *pValue);

extern LLRP_tSTagLog *
LLRP_UploadTagLogAck_beginTagLog (
  LLRP_tSUploadTagLogAck *pThis);

extern LLRP_tSTagLog *
LLRP_UploadTagLogAck_nextTagLog (
  LLRP_tSTagLog *pCurrent);

extern void
LLRP_UploadTagLogAck_clearTagLog (
  LLRP_tSUploadTagLogAck *pThis);

extern int
LLRP_UploadTagLogAck_countTagLog (
  LLRP_tSUploadTagLogAck *pThis);

extern LLRP_tResultCode
LLRP_UploadTagLogAck_addTagLog (
  LLRP_tSUploadTagLogAck *pThis,
  LLRP_tSTagLog *pValue);




  
struct LLRP_SClearTagLog
{
    LLRP_tSMessage hdr;
  
  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdClearTagLog;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdClearTagLog[];

extern LLRP_tSClearTagLog *
LLRP_ClearTagLog_construct (void);

extern void
LLRP_ClearTagLog_destruct (
 LLRP_tSClearTagLog * pThis);

extern void
LLRP_ClearTagLog_decodeFields (
 LLRP_tSClearTagLog * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ClearTagLog_assimilateSubParameters (
 LLRP_tSClearTagLog * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ClearTagLog_encode (
  const LLRP_tSClearTagLog *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  


  
struct LLRP_SClearTagLogAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdClearTagLogAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdClearTagLogAck[];

extern LLRP_tSClearTagLogAck *
LLRP_ClearTagLogAck_construct (void);

extern void
LLRP_ClearTagLogAck_destruct (
 LLRP_tSClearTagLogAck * pThis);

extern void
LLRP_ClearTagLogAck_decodeFields (
 LLRP_tSClearTagLogAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ClearTagLogAck_assimilateSubParameters (
 LLRP_tSClearTagLogAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ClearTagLogAck_encode (
  const LLRP_tSClearTagLogAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_ClearTagLogAck_getStatus (
  LLRP_tSClearTagLogAck *pThis);

extern LLRP_tResultCode
LLRP_ClearTagLogAck_setStatus (
  LLRP_tSClearTagLogAck *pThis,
  LLRP_tSStatus *pValue);



  
struct LLRP_SUploadDeviceLog
{
    LLRP_tSMessage hdr;
  
    llrp_u8_t UploadType;

    llrp_u32_t UploadCount;

    llrp_u64_t StartLogSequence;

  
    LLRP_tSStartLogTimestamp * pStartLogTimestamp;

    LLRP_tSEndLogTimestamp * pEndLogTimestamp;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdUploadDeviceLog;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdUploadDeviceLog[];

extern LLRP_tSUploadDeviceLog *
LLRP_UploadDeviceLog_construct (void);

extern void
LLRP_UploadDeviceLog_destruct (
 LLRP_tSUploadDeviceLog * pThis);

extern void
LLRP_UploadDeviceLog_decodeFields (
 LLRP_tSUploadDeviceLog * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_UploadDeviceLog_assimilateSubParameters (
 LLRP_tSUploadDeviceLog * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_UploadDeviceLog_encode (
  const LLRP_tSUploadDeviceLog *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdUploadDeviceLog_UploadType;

extern llrp_u8_t
LLRP_UploadDeviceLog_getUploadType (
  LLRP_tSUploadDeviceLog *pThis);

extern LLRP_tResultCode
LLRP_UploadDeviceLog_setUploadType (
  LLRP_tSUploadDeviceLog *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdUploadDeviceLog_UploadCount;

extern llrp_u32_t
LLRP_UploadDeviceLog_getUploadCount (
  LLRP_tSUploadDeviceLog *pThis);

extern LLRP_tResultCode
LLRP_UploadDeviceLog_setUploadCount (
  LLRP_tSUploadDeviceLog *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdUploadDeviceLog_StartLogSequence;

extern llrp_u64_t
LLRP_UploadDeviceLog_getStartLogSequence (
  LLRP_tSUploadDeviceLog *pThis);

extern LLRP_tResultCode
LLRP_UploadDeviceLog_setStartLogSequence (
  LLRP_tSUploadDeviceLog *pThis,
  llrp_u64_t Value);

  
extern LLRP_tSStartLogTimestamp *
LLRP_UploadDeviceLog_getStartLogTimestamp (
  LLRP_tSUploadDeviceLog *pThis);

extern LLRP_tResultCode
LLRP_UploadDeviceLog_setStartLogTimestamp (
  LLRP_tSUploadDeviceLog *pThis,
  LLRP_tSStartLogTimestamp *pValue);

extern LLRP_tSEndLogTimestamp *
LLRP_UploadDeviceLog_getEndLogTimestamp (
  LLRP_tSUploadDeviceLog *pThis);

extern LLRP_tResultCode
LLRP_UploadDeviceLog_setEndLogTimestamp (
  LLRP_tSUploadDeviceLog *pThis,
  LLRP_tSEndLogTimestamp *pValue);



  
struct LLRP_SUploadDeviceLogAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

    LLRP_tSDeviceLog * listDeviceLog;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdUploadDeviceLogAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdUploadDeviceLogAck[];

extern LLRP_tSUploadDeviceLogAck *
LLRP_UploadDeviceLogAck_construct (void);

extern void
LLRP_UploadDeviceLogAck_destruct (
 LLRP_tSUploadDeviceLogAck * pThis);

extern void
LLRP_UploadDeviceLogAck_decodeFields (
 LLRP_tSUploadDeviceLogAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_UploadDeviceLogAck_assimilateSubParameters (
 LLRP_tSUploadDeviceLogAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_UploadDeviceLogAck_encode (
  const LLRP_tSUploadDeviceLogAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_UploadDeviceLogAck_getStatus (
  LLRP_tSUploadDeviceLogAck *pThis);

extern LLRP_tResultCode
LLRP_UploadDeviceLogAck_setStatus (
  LLRP_tSUploadDeviceLogAck *pThis,
  LLRP_tSStatus *pValue);

extern LLRP_tSDeviceLog *
LLRP_UploadDeviceLogAck_beginDeviceLog (
  LLRP_tSUploadDeviceLogAck *pThis);

extern LLRP_tSDeviceLog *
LLRP_UploadDeviceLogAck_nextDeviceLog (
  LLRP_tSDeviceLog *pCurrent);

extern void
LLRP_UploadDeviceLogAck_clearDeviceLog (
  LLRP_tSUploadDeviceLogAck *pThis);

extern int
LLRP_UploadDeviceLogAck_countDeviceLog (
  LLRP_tSUploadDeviceLogAck *pThis);

extern LLRP_tResultCode
LLRP_UploadDeviceLogAck_addDeviceLog (
  LLRP_tSUploadDeviceLogAck *pThis,
  LLRP_tSDeviceLog *pValue);




  
struct LLRP_SClearDeviceLog
{
    LLRP_tSMessage hdr;
  
  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdClearDeviceLog;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdClearDeviceLog[];

extern LLRP_tSClearDeviceLog *
LLRP_ClearDeviceLog_construct (void);

extern void
LLRP_ClearDeviceLog_destruct (
 LLRP_tSClearDeviceLog * pThis);

extern void
LLRP_ClearDeviceLog_decodeFields (
 LLRP_tSClearDeviceLog * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ClearDeviceLog_assimilateSubParameters (
 LLRP_tSClearDeviceLog * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ClearDeviceLog_encode (
  const LLRP_tSClearDeviceLog *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  


  
struct LLRP_SClearDeviceLogAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdClearDeviceLogAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdClearDeviceLogAck[];

extern LLRP_tSClearDeviceLogAck *
LLRP_ClearDeviceLogAck_construct (void);

extern void
LLRP_ClearDeviceLogAck_destruct (
 LLRP_tSClearDeviceLogAck * pThis);

extern void
LLRP_ClearDeviceLogAck_decodeFields (
 LLRP_tSClearDeviceLogAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ClearDeviceLogAck_assimilateSubParameters (
 LLRP_tSClearDeviceLogAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ClearDeviceLogAck_encode (
  const LLRP_tSClearDeviceLogAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_ClearDeviceLogAck_getStatus (
  LLRP_tSClearDeviceLogAck *pThis);

extern LLRP_tResultCode
LLRP_ClearDeviceLogAck_setStatus (
  LLRP_tSClearDeviceLogAck *pThis,
  LLRP_tSStatus *pValue);



  
struct LLRP_SGetDeviceConfig
{
    LLRP_tSMessage hdr;
  
    LLRP_tEConfigRequestedData eRequestedData;

    llrp_u8_t AntennalID;

  
    LLRP_tSSecurityModuleConfiguration * pSecurityModuleConfiguration;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdGetDeviceConfig;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGetDeviceConfig[];

extern LLRP_tSGetDeviceConfig *
LLRP_GetDeviceConfig_construct (void);

extern void
LLRP_GetDeviceConfig_destruct (
 LLRP_tSGetDeviceConfig * pThis);

extern void
LLRP_GetDeviceConfig_decodeFields (
 LLRP_tSGetDeviceConfig * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GetDeviceConfig_assimilateSubParameters (
 LLRP_tSGetDeviceConfig * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GetDeviceConfig_encode (
  const LLRP_tSGetDeviceConfig *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGetDeviceConfig_RequestedData;

extern LLRP_tEConfigRequestedData
LLRP_GetDeviceConfig_getRequestedData (
  LLRP_tSGetDeviceConfig *pThis);

extern LLRP_tResultCode
LLRP_GetDeviceConfig_setRequestedData (
  LLRP_tSGetDeviceConfig *pThis,
  LLRP_tEConfigRequestedData Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGetDeviceConfig_AntennalID;

extern llrp_u8_t
LLRP_GetDeviceConfig_getAntennalID (
  LLRP_tSGetDeviceConfig *pThis);

extern LLRP_tResultCode
LLRP_GetDeviceConfig_setAntennalID (
  LLRP_tSGetDeviceConfig *pThis,
  llrp_u8_t Value);

  
extern LLRP_tSSecurityModuleConfiguration *
LLRP_GetDeviceConfig_getSecurityModuleConfiguration (
  LLRP_tSGetDeviceConfig *pThis);

extern LLRP_tResultCode
LLRP_GetDeviceConfig_setSecurityModuleConfiguration (
  LLRP_tSGetDeviceConfig *pThis,
  LLRP_tSSecurityModuleConfiguration *pValue);



  
struct LLRP_SGetDeviceConfigAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

    LLRP_tSIdentification * pIdentification;

    LLRP_tSDeviceEventNotificationSpec * pDeviceEventNotificationSpec;

    LLRP_tSAlarmConfiguration * pAlarmConfiguration;

    LLRP_tSAntennaProperties * listAntennaProperties;

    LLRP_tSAntennaConfiguration * listAntennaConfiguration;

    LLRP_tSModuleDepth * pModuleDepth;

    LLRP_tSSelectReportSpec * pSelectReportSpec;

    LLRP_tSAccessReportSpec * pAccessReportSpec;

    LLRP_tSCommunicationConfiguration * pCommunicationConfiguration;

    LLRP_tSLocationConfiguration * pLocationConfiguration;

    LLRP_tSSecurityModuleConfiguration * pSecurityModuleConfiguration;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdGetDeviceConfigAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGetDeviceConfigAck[];

extern LLRP_tSGetDeviceConfigAck *
LLRP_GetDeviceConfigAck_construct (void);

extern void
LLRP_GetDeviceConfigAck_destruct (
 LLRP_tSGetDeviceConfigAck * pThis);

extern void
LLRP_GetDeviceConfigAck_decodeFields (
 LLRP_tSGetDeviceConfigAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GetDeviceConfigAck_assimilateSubParameters (
 LLRP_tSGetDeviceConfigAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GetDeviceConfigAck_encode (
  const LLRP_tSGetDeviceConfigAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_GetDeviceConfigAck_getStatus (
  LLRP_tSGetDeviceConfigAck *pThis);

extern LLRP_tResultCode
LLRP_GetDeviceConfigAck_setStatus (
  LLRP_tSGetDeviceConfigAck *pThis,
  LLRP_tSStatus *pValue);

extern LLRP_tSIdentification *
LLRP_GetDeviceConfigAck_getIdentification (
  LLRP_tSGetDeviceConfigAck *pThis);

extern LLRP_tResultCode
LLRP_GetDeviceConfigAck_setIdentification (
  LLRP_tSGetDeviceConfigAck *pThis,
  LLRP_tSIdentification *pValue);

extern LLRP_tSDeviceEventNotificationSpec *
LLRP_GetDeviceConfigAck_getDeviceEventNotificationSpec (
  LLRP_tSGetDeviceConfigAck *pThis);

extern LLRP_tResultCode
LLRP_GetDeviceConfigAck_setDeviceEventNotificationSpec (
  LLRP_tSGetDeviceConfigAck *pThis,
  LLRP_tSDeviceEventNotificationSpec *pValue);

extern LLRP_tSAlarmConfiguration *
LLRP_GetDeviceConfigAck_getAlarmConfiguration (
  LLRP_tSGetDeviceConfigAck *pThis);

extern LLRP_tResultCode
LLRP_GetDeviceConfigAck_setAlarmConfiguration (
  LLRP_tSGetDeviceConfigAck *pThis,
  LLRP_tSAlarmConfiguration *pValue);

extern LLRP_tSAntennaProperties *
LLRP_GetDeviceConfigAck_beginAntennaProperties (
  LLRP_tSGetDeviceConfigAck *pThis);

extern LLRP_tSAntennaProperties *
LLRP_GetDeviceConfigAck_nextAntennaProperties (
  LLRP_tSAntennaProperties *pCurrent);

extern void
LLRP_GetDeviceConfigAck_clearAntennaProperties (
  LLRP_tSGetDeviceConfigAck *pThis);

extern int
LLRP_GetDeviceConfigAck_countAntennaProperties (
  LLRP_tSGetDeviceConfigAck *pThis);

extern LLRP_tResultCode
LLRP_GetDeviceConfigAck_addAntennaProperties (
  LLRP_tSGetDeviceConfigAck *pThis,
  LLRP_tSAntennaProperties *pValue);


extern LLRP_tSAntennaConfiguration *
LLRP_GetDeviceConfigAck_beginAntennaConfiguration (
  LLRP_tSGetDeviceConfigAck *pThis);

extern LLRP_tSAntennaConfiguration *
LLRP_GetDeviceConfigAck_nextAntennaConfiguration (
  LLRP_tSAntennaConfiguration *pCurrent);

extern void
LLRP_GetDeviceConfigAck_clearAntennaConfiguration (
  LLRP_tSGetDeviceConfigAck *pThis);

extern int
LLRP_GetDeviceConfigAck_countAntennaConfiguration (
  LLRP_tSGetDeviceConfigAck *pThis);

extern LLRP_tResultCode
LLRP_GetDeviceConfigAck_addAntennaConfiguration (
  LLRP_tSGetDeviceConfigAck *pThis,
  LLRP_tSAntennaConfiguration *pValue);


extern LLRP_tSModuleDepth *
LLRP_GetDeviceConfigAck_getModuleDepth (
  LLRP_tSGetDeviceConfigAck *pThis);

extern LLRP_tResultCode
LLRP_GetDeviceConfigAck_setModuleDepth (
  LLRP_tSGetDeviceConfigAck *pThis,
  LLRP_tSModuleDepth *pValue);

extern LLRP_tSSelectReportSpec *
LLRP_GetDeviceConfigAck_getSelectReportSpec (
  LLRP_tSGetDeviceConfigAck *pThis);

extern LLRP_tResultCode
LLRP_GetDeviceConfigAck_setSelectReportSpec (
  LLRP_tSGetDeviceConfigAck *pThis,
  LLRP_tSSelectReportSpec *pValue);

extern LLRP_tSAccessReportSpec *
LLRP_GetDeviceConfigAck_getAccessReportSpec (
  LLRP_tSGetDeviceConfigAck *pThis);

extern LLRP_tResultCode
LLRP_GetDeviceConfigAck_setAccessReportSpec (
  LLRP_tSGetDeviceConfigAck *pThis,
  LLRP_tSAccessReportSpec *pValue);

extern LLRP_tSCommunicationConfiguration *
LLRP_GetDeviceConfigAck_getCommunicationConfiguration (
  LLRP_tSGetDeviceConfigAck *pThis);

extern LLRP_tResultCode
LLRP_GetDeviceConfigAck_setCommunicationConfiguration (
  LLRP_tSGetDeviceConfigAck *pThis,
  LLRP_tSCommunicationConfiguration *pValue);

extern LLRP_tSLocationConfiguration *
LLRP_GetDeviceConfigAck_getLocationConfiguration (
  LLRP_tSGetDeviceConfigAck *pThis);

extern LLRP_tResultCode
LLRP_GetDeviceConfigAck_setLocationConfiguration (
  LLRP_tSGetDeviceConfigAck *pThis,
  LLRP_tSLocationConfiguration *pValue);

extern LLRP_tSSecurityModuleConfiguration *
LLRP_GetDeviceConfigAck_getSecurityModuleConfiguration (
  LLRP_tSGetDeviceConfigAck *pThis);

extern LLRP_tResultCode
LLRP_GetDeviceConfigAck_setSecurityModuleConfiguration (
  LLRP_tSGetDeviceConfigAck *pThis,
  LLRP_tSSecurityModuleConfiguration *pValue);



  
struct LLRP_SSetDeviceConfig
{
    LLRP_tSMessage hdr;
  
    llrp_u1_t ResetToFactoryDefault;

  
    LLRP_tSIdentification * pIdentification;

    LLRP_tSDeviceEventNotificationSpec * pDeviceEventNotificationSpec;

    LLRP_tSAlarmConfiguration * pAlarmConfiguration;

    LLRP_tSAntennaConfiguration * listAntennaConfiguration;

    LLRP_tSModuleDepth * pModuleDepth;

    LLRP_tSSelectReportSpec * pSelectReportSpec;

    LLRP_tSAccessReportSpec * pAccessReportSpec;

    LLRP_tSCommunicationConfiguration * pCommunicationConfiguration;

    LLRP_tSLocationConfiguration * pLocationConfiguration;

    LLRP_tSSecurityModuleConfiguration * pSecurityModuleConfiguration;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSetDeviceConfig;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSetDeviceConfig[];

extern LLRP_tSSetDeviceConfig *
LLRP_SetDeviceConfig_construct (void);

extern void
LLRP_SetDeviceConfig_destruct (
 LLRP_tSSetDeviceConfig * pThis);

extern void
LLRP_SetDeviceConfig_decodeFields (
 LLRP_tSSetDeviceConfig * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SetDeviceConfig_assimilateSubParameters (
 LLRP_tSSetDeviceConfig * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SetDeviceConfig_encode (
  const LLRP_tSSetDeviceConfig *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSetDeviceConfig_ResetToFactoryDefault;

extern llrp_u1_t
LLRP_SetDeviceConfig_getResetToFactoryDefault (
  LLRP_tSSetDeviceConfig *pThis);

extern LLRP_tResultCode
LLRP_SetDeviceConfig_setResetToFactoryDefault (
  LLRP_tSSetDeviceConfig *pThis,
  llrp_u1_t Value);

  
extern LLRP_tSIdentification *
LLRP_SetDeviceConfig_getIdentification (
  LLRP_tSSetDeviceConfig *pThis);

extern LLRP_tResultCode
LLRP_SetDeviceConfig_setIdentification (
  LLRP_tSSetDeviceConfig *pThis,
  LLRP_tSIdentification *pValue);

extern LLRP_tSDeviceEventNotificationSpec *
LLRP_SetDeviceConfig_getDeviceEventNotificationSpec (
  LLRP_tSSetDeviceConfig *pThis);

extern LLRP_tResultCode
LLRP_SetDeviceConfig_setDeviceEventNotificationSpec (
  LLRP_tSSetDeviceConfig *pThis,
  LLRP_tSDeviceEventNotificationSpec *pValue);

extern LLRP_tSAlarmConfiguration *
LLRP_SetDeviceConfig_getAlarmConfiguration (
  LLRP_tSSetDeviceConfig *pThis);

extern LLRP_tResultCode
LLRP_SetDeviceConfig_setAlarmConfiguration (
  LLRP_tSSetDeviceConfig *pThis,
  LLRP_tSAlarmConfiguration *pValue);

extern LLRP_tSAntennaConfiguration *
LLRP_SetDeviceConfig_beginAntennaConfiguration (
  LLRP_tSSetDeviceConfig *pThis);

extern LLRP_tSAntennaConfiguration *
LLRP_SetDeviceConfig_nextAntennaConfiguration (
  LLRP_tSAntennaConfiguration *pCurrent);

extern void
LLRP_SetDeviceConfig_clearAntennaConfiguration (
  LLRP_tSSetDeviceConfig *pThis);

extern int
LLRP_SetDeviceConfig_countAntennaConfiguration (
  LLRP_tSSetDeviceConfig *pThis);

extern LLRP_tResultCode
LLRP_SetDeviceConfig_addAntennaConfiguration (
  LLRP_tSSetDeviceConfig *pThis,
  LLRP_tSAntennaConfiguration *pValue);


extern LLRP_tSModuleDepth *
LLRP_SetDeviceConfig_getModuleDepth (
  LLRP_tSSetDeviceConfig *pThis);

extern LLRP_tResultCode
LLRP_SetDeviceConfig_setModuleDepth (
  LLRP_tSSetDeviceConfig *pThis,
  LLRP_tSModuleDepth *pValue);

extern LLRP_tSSelectReportSpec *
LLRP_SetDeviceConfig_getSelectReportSpec (
  LLRP_tSSetDeviceConfig *pThis);

extern LLRP_tResultCode
LLRP_SetDeviceConfig_setSelectReportSpec (
  LLRP_tSSetDeviceConfig *pThis,
  LLRP_tSSelectReportSpec *pValue);

extern LLRP_tSAccessReportSpec *
LLRP_SetDeviceConfig_getAccessReportSpec (
  LLRP_tSSetDeviceConfig *pThis);

extern LLRP_tResultCode
LLRP_SetDeviceConfig_setAccessReportSpec (
  LLRP_tSSetDeviceConfig *pThis,
  LLRP_tSAccessReportSpec *pValue);

extern LLRP_tSCommunicationConfiguration *
LLRP_SetDeviceConfig_getCommunicationConfiguration (
  LLRP_tSSetDeviceConfig *pThis);

extern LLRP_tResultCode
LLRP_SetDeviceConfig_setCommunicationConfiguration (
  LLRP_tSSetDeviceConfig *pThis,
  LLRP_tSCommunicationConfiguration *pValue);

extern LLRP_tSLocationConfiguration *
LLRP_SetDeviceConfig_getLocationConfiguration (
  LLRP_tSSetDeviceConfig *pThis);

extern LLRP_tResultCode
LLRP_SetDeviceConfig_setLocationConfiguration (
  LLRP_tSSetDeviceConfig *pThis,
  LLRP_tSLocationConfiguration *pValue);

extern LLRP_tSSecurityModuleConfiguration *
LLRP_SetDeviceConfig_getSecurityModuleConfiguration (
  LLRP_tSSetDeviceConfig *pThis);

extern LLRP_tResultCode
LLRP_SetDeviceConfig_setSecurityModuleConfiguration (
  LLRP_tSSetDeviceConfig *pThis,
  LLRP_tSSecurityModuleConfiguration *pValue);



  
struct LLRP_SSetDeviceConfigAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSetDeviceConfigAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSetDeviceConfigAck[];

extern LLRP_tSSetDeviceConfigAck *
LLRP_SetDeviceConfigAck_construct (void);

extern void
LLRP_SetDeviceConfigAck_destruct (
 LLRP_tSSetDeviceConfigAck * pThis);

extern void
LLRP_SetDeviceConfigAck_decodeFields (
 LLRP_tSSetDeviceConfigAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SetDeviceConfigAck_assimilateSubParameters (
 LLRP_tSSetDeviceConfigAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SetDeviceConfigAck_encode (
  const LLRP_tSSetDeviceConfigAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_SetDeviceConfigAck_getStatus (
  LLRP_tSSetDeviceConfigAck *pThis);

extern LLRP_tResultCode
LLRP_SetDeviceConfigAck_setStatus (
  LLRP_tSSetDeviceConfigAck *pThis,
  LLRP_tSStatus *pValue);



  
struct LLRP_SGetVersion
{
    LLRP_tSMessage hdr;
  
    LLRP_tEVerType eVerType;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdGetVersion;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGetVersion[];

extern LLRP_tSGetVersion *
LLRP_GetVersion_construct (void);

extern void
LLRP_GetVersion_destruct (
 LLRP_tSGetVersion * pThis);

extern void
LLRP_GetVersion_decodeFields (
 LLRP_tSGetVersion * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GetVersion_assimilateSubParameters (
 LLRP_tSGetVersion * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GetVersion_encode (
  const LLRP_tSGetVersion *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGetVersion_VerType;

extern LLRP_tEVerType
LLRP_GetVersion_getVerType (
  LLRP_tSGetVersion *pThis);

extern LLRP_tResultCode
LLRP_GetVersion_setVerType (
  LLRP_tSGetVersion *pThis,
  LLRP_tEVerType Value);

  


  
struct LLRP_SGetVersionAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

    LLRP_tSVersionInfo * listVersionInfo;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdGetVersionAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGetVersionAck[];

extern LLRP_tSGetVersionAck *
LLRP_GetVersionAck_construct (void);

extern void
LLRP_GetVersionAck_destruct (
 LLRP_tSGetVersionAck * pThis);

extern void
LLRP_GetVersionAck_decodeFields (
 LLRP_tSGetVersionAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GetVersionAck_assimilateSubParameters (
 LLRP_tSGetVersionAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GetVersionAck_encode (
  const LLRP_tSGetVersionAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_GetVersionAck_getStatus (
  LLRP_tSGetVersionAck *pThis);

extern LLRP_tResultCode
LLRP_GetVersionAck_setStatus (
  LLRP_tSGetVersionAck *pThis,
  LLRP_tSStatus *pValue);

extern LLRP_tSVersionInfo *
LLRP_GetVersionAck_beginVersionInfo (
  LLRP_tSGetVersionAck *pThis);

extern LLRP_tSVersionInfo *
LLRP_GetVersionAck_nextVersionInfo (
  LLRP_tSVersionInfo *pCurrent);

extern void
LLRP_GetVersionAck_clearVersionInfo (
  LLRP_tSGetVersionAck *pThis);

extern int
LLRP_GetVersionAck_countVersionInfo (
  LLRP_tSGetVersionAck *pThis);

extern LLRP_tResultCode
LLRP_GetVersionAck_addVersionInfo (
  LLRP_tSGetVersionAck *pThis,
  LLRP_tSVersionInfo *pValue);




  
struct LLRP_SSetVersion
{
    LLRP_tSMessage hdr;
  
    LLRP_tEVerType eVerType;

  
    LLRP_tSVersionDownload * pVersionDownload;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSetVersion;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSetVersion[];

extern LLRP_tSSetVersion *
LLRP_SetVersion_construct (void);

extern void
LLRP_SetVersion_destruct (
 LLRP_tSSetVersion * pThis);

extern void
LLRP_SetVersion_decodeFields (
 LLRP_tSSetVersion * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SetVersion_assimilateSubParameters (
 LLRP_tSSetVersion * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SetVersion_encode (
  const LLRP_tSSetVersion *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSetVersion_VerType;

extern LLRP_tEVerType
LLRP_SetVersion_getVerType (
  LLRP_tSSetVersion *pThis);

extern LLRP_tResultCode
LLRP_SetVersion_setVerType (
  LLRP_tSSetVersion *pThis,
  LLRP_tEVerType Value);

  
extern LLRP_tSVersionDownload *
LLRP_SetVersion_getVersionDownload (
  LLRP_tSSetVersion *pThis);

extern LLRP_tResultCode
LLRP_SetVersion_setVersionDownload (
  LLRP_tSSetVersion *pThis,
  LLRP_tSVersionDownload *pValue);



  
struct LLRP_SSetVersionAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSetVersionAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSetVersionAck[];

extern LLRP_tSSetVersionAck *
LLRP_SetVersionAck_construct (void);

extern void
LLRP_SetVersionAck_destruct (
 LLRP_tSSetVersionAck * pThis);

extern void
LLRP_SetVersionAck_decodeFields (
 LLRP_tSSetVersionAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SetVersionAck_assimilateSubParameters (
 LLRP_tSSetVersionAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SetVersionAck_encode (
  const LLRP_tSSetVersionAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_SetVersionAck_getStatus (
  LLRP_tSSetVersionAck *pThis);

extern LLRP_tResultCode
LLRP_SetVersionAck_setStatus (
  LLRP_tSSetVersionAck *pThis,
  LLRP_tSStatus *pValue);



  
struct LLRP_SActiveVersion
{
    LLRP_tSMessage hdr;
  
    LLRP_tEVerType eVerType;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdActiveVersion;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdActiveVersion[];

extern LLRP_tSActiveVersion *
LLRP_ActiveVersion_construct (void);

extern void
LLRP_ActiveVersion_destruct (
 LLRP_tSActiveVersion * pThis);

extern void
LLRP_ActiveVersion_decodeFields (
 LLRP_tSActiveVersion * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ActiveVersion_assimilateSubParameters (
 LLRP_tSActiveVersion * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ActiveVersion_encode (
  const LLRP_tSActiveVersion *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdActiveVersion_VerType;

extern LLRP_tEVerType
LLRP_ActiveVersion_getVerType (
  LLRP_tSActiveVersion *pThis);

extern LLRP_tResultCode
LLRP_ActiveVersion_setVerType (
  LLRP_tSActiveVersion *pThis,
  LLRP_tEVerType Value);

  


  
struct LLRP_SActiveVersionAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdActiveVersionAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdActiveVersionAck[];

extern LLRP_tSActiveVersionAck *
LLRP_ActiveVersionAck_construct (void);

extern void
LLRP_ActiveVersionAck_destruct (
 LLRP_tSActiveVersionAck * pThis);

extern void
LLRP_ActiveVersionAck_decodeFields (
 LLRP_tSActiveVersionAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ActiveVersionAck_assimilateSubParameters (
 LLRP_tSActiveVersionAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ActiveVersionAck_encode (
  const LLRP_tSActiveVersionAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_ActiveVersionAck_getStatus (
  LLRP_tSActiveVersionAck *pThis);

extern LLRP_tResultCode
LLRP_ActiveVersionAck_setStatus (
  LLRP_tSActiveVersionAck *pThis,
  LLRP_tSStatus *pValue);



  
struct LLRP_SUnActiveVersion
{
    LLRP_tSMessage hdr;
  
    LLRP_tEVerType eVerType;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdUnActiveVersion;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdUnActiveVersion[];

extern LLRP_tSUnActiveVersion *
LLRP_UnActiveVersion_construct (void);

extern void
LLRP_UnActiveVersion_destruct (
 LLRP_tSUnActiveVersion * pThis);

extern void
LLRP_UnActiveVersion_decodeFields (
 LLRP_tSUnActiveVersion * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_UnActiveVersion_assimilateSubParameters (
 LLRP_tSUnActiveVersion * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_UnActiveVersion_encode (
  const LLRP_tSUnActiveVersion *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdUnActiveVersion_VerType;

extern LLRP_tEVerType
LLRP_UnActiveVersion_getVerType (
  LLRP_tSUnActiveVersion *pThis);

extern LLRP_tResultCode
LLRP_UnActiveVersion_setVerType (
  LLRP_tSUnActiveVersion *pThis,
  LLRP_tEVerType Value);

  


  
struct LLRP_SUnActiveVersionAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdUnActiveVersionAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdUnActiveVersionAck[];

extern LLRP_tSUnActiveVersionAck *
LLRP_UnActiveVersionAck_construct (void);

extern void
LLRP_UnActiveVersionAck_destruct (
 LLRP_tSUnActiveVersionAck * pThis);

extern void
LLRP_UnActiveVersionAck_decodeFields (
 LLRP_tSUnActiveVersionAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_UnActiveVersionAck_assimilateSubParameters (
 LLRP_tSUnActiveVersionAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_UnActiveVersionAck_encode (
  const LLRP_tSUnActiveVersionAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_UnActiveVersionAck_getStatus (
  LLRP_tSUnActiveVersionAck *pThis);

extern LLRP_tResultCode
LLRP_UnActiveVersionAck_setStatus (
  LLRP_tSUnActiveVersionAck *pThis,
  LLRP_tSStatus *pValue);



  
struct LLRP_SAlarmReport
{
    LLRP_tSMessage hdr;
  
    llrp_u32_t AlarmID;

  
    LLRP_tSAlarmReportInfo * pAlarmReportInfo;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdAlarmReport;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAlarmReport[];

extern LLRP_tSAlarmReport *
LLRP_AlarmReport_construct (void);

extern void
LLRP_AlarmReport_destruct (
 LLRP_tSAlarmReport * pThis);

extern void
LLRP_AlarmReport_decodeFields (
 LLRP_tSAlarmReport * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AlarmReport_assimilateSubParameters (
 LLRP_tSAlarmReport * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AlarmReport_encode (
  const LLRP_tSAlarmReport *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmReport_AlarmID;

extern llrp_u32_t
LLRP_AlarmReport_getAlarmID (
  LLRP_tSAlarmReport *pThis);

extern LLRP_tResultCode
LLRP_AlarmReport_setAlarmID (
  LLRP_tSAlarmReport *pThis,
  llrp_u32_t Value);

  
extern LLRP_tSAlarmReportInfo *
LLRP_AlarmReport_getAlarmReportInfo (
  LLRP_tSAlarmReport *pThis);

extern LLRP_tResultCode
LLRP_AlarmReport_setAlarmReportInfo (
  LLRP_tSAlarmReport *pThis,
  LLRP_tSAlarmReportInfo *pValue);



  
struct LLRP_SAlarmRestore
{
    LLRP_tSMessage hdr;
  
    llrp_u32_t AlarmID;

  
    LLRP_tSAlarmRestoreInfo * pAlarmRestoreInfo;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdAlarmRestore;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAlarmRestore[];

extern LLRP_tSAlarmRestore *
LLRP_AlarmRestore_construct (void);

extern void
LLRP_AlarmRestore_destruct (
 LLRP_tSAlarmRestore * pThis);

extern void
LLRP_AlarmRestore_decodeFields (
 LLRP_tSAlarmRestore * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AlarmRestore_assimilateSubParameters (
 LLRP_tSAlarmRestore * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AlarmRestore_encode (
  const LLRP_tSAlarmRestore *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmRestore_AlarmID;

extern llrp_u32_t
LLRP_AlarmRestore_getAlarmID (
  LLRP_tSAlarmRestore *pThis);

extern LLRP_tResultCode
LLRP_AlarmRestore_setAlarmID (
  LLRP_tSAlarmRestore *pThis,
  llrp_u32_t Value);

  
extern LLRP_tSAlarmRestoreInfo *
LLRP_AlarmRestore_getAlarmRestoreInfo (
  LLRP_tSAlarmRestore *pThis);

extern LLRP_tResultCode
LLRP_AlarmRestore_setAlarmRestoreInfo (
  LLRP_tSAlarmRestore *pThis,
  LLRP_tSAlarmRestoreInfo *pValue);



  
struct LLRP_SAlarmDelete
{
    LLRP_tSMessage hdr;
  
    llrp_u32_t AlarmID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdAlarmDelete;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAlarmDelete[];

extern LLRP_tSAlarmDelete *
LLRP_AlarmDelete_construct (void);

extern void
LLRP_AlarmDelete_destruct (
 LLRP_tSAlarmDelete * pThis);

extern void
LLRP_AlarmDelete_decodeFields (
 LLRP_tSAlarmDelete * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AlarmDelete_assimilateSubParameters (
 LLRP_tSAlarmDelete * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AlarmDelete_encode (
  const LLRP_tSAlarmDelete *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmDelete_AlarmID;

extern llrp_u32_t
LLRP_AlarmDelete_getAlarmID (
  LLRP_tSAlarmDelete *pThis);

extern LLRP_tResultCode
LLRP_AlarmDelete_setAlarmID (
  LLRP_tSAlarmDelete *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SAlarmSync
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSAlarmSyncInfo * pAlarmSyncInfo;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdAlarmSync;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAlarmSync[];

extern LLRP_tSAlarmSync *
LLRP_AlarmSync_construct (void);

extern void
LLRP_AlarmSync_destruct (
 LLRP_tSAlarmSync * pThis);

extern void
LLRP_AlarmSync_decodeFields (
 LLRP_tSAlarmSync * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AlarmSync_assimilateSubParameters (
 LLRP_tSAlarmSync * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AlarmSync_encode (
  const LLRP_tSAlarmSync *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSAlarmSyncInfo *
LLRP_AlarmSync_getAlarmSyncInfo (
  LLRP_tSAlarmSync *pThis);

extern LLRP_tResultCode
LLRP_AlarmSync_setAlarmSyncInfo (
  LLRP_tSAlarmSync *pThis,
  LLRP_tSAlarmSyncInfo *pValue);



  
struct LLRP_SDiagnosticTest
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSDiagnosticTestItem * listDiagnosticTestItem;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdDiagnosticTest;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDiagnosticTest[];

extern LLRP_tSDiagnosticTest *
LLRP_DiagnosticTest_construct (void);

extern void
LLRP_DiagnosticTest_destruct (
 LLRP_tSDiagnosticTest * pThis);

extern void
LLRP_DiagnosticTest_decodeFields (
 LLRP_tSDiagnosticTest * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DiagnosticTest_assimilateSubParameters (
 LLRP_tSDiagnosticTest * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DiagnosticTest_encode (
  const LLRP_tSDiagnosticTest *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSDiagnosticTestItem *
LLRP_DiagnosticTest_beginDiagnosticTestItem (
  LLRP_tSDiagnosticTest *pThis);

extern LLRP_tSDiagnosticTestItem *
LLRP_DiagnosticTest_nextDiagnosticTestItem (
  LLRP_tSDiagnosticTestItem *pCurrent);

extern void
LLRP_DiagnosticTest_clearDiagnosticTestItem (
  LLRP_tSDiagnosticTest *pThis);

extern int
LLRP_DiagnosticTest_countDiagnosticTestItem (
  LLRP_tSDiagnosticTest *pThis);

extern LLRP_tResultCode
LLRP_DiagnosticTest_addDiagnosticTestItem (
  LLRP_tSDiagnosticTest *pThis,
  LLRP_tSDiagnosticTestItem *pValue);




  
struct LLRP_SDiagnosticTestAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

    LLRP_tSDiagnosticTestResultItem * listDiagnosticTestResultItem;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdDiagnosticTestAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDiagnosticTestAck[];

extern LLRP_tSDiagnosticTestAck *
LLRP_DiagnosticTestAck_construct (void);

extern void
LLRP_DiagnosticTestAck_destruct (
 LLRP_tSDiagnosticTestAck * pThis);

extern void
LLRP_DiagnosticTestAck_decodeFields (
 LLRP_tSDiagnosticTestAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DiagnosticTestAck_assimilateSubParameters (
 LLRP_tSDiagnosticTestAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DiagnosticTestAck_encode (
  const LLRP_tSDiagnosticTestAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_DiagnosticTestAck_getStatus (
  LLRP_tSDiagnosticTestAck *pThis);

extern LLRP_tResultCode
LLRP_DiagnosticTestAck_setStatus (
  LLRP_tSDiagnosticTestAck *pThis,
  LLRP_tSStatus *pValue);

extern LLRP_tSDiagnosticTestResultItem *
LLRP_DiagnosticTestAck_beginDiagnosticTestResultItem (
  LLRP_tSDiagnosticTestAck *pThis);

extern LLRP_tSDiagnosticTestResultItem *
LLRP_DiagnosticTestAck_nextDiagnosticTestResultItem (
  LLRP_tSDiagnosticTestResultItem *pCurrent);

extern void
LLRP_DiagnosticTestAck_clearDiagnosticTestResultItem (
  LLRP_tSDiagnosticTestAck *pThis);

extern int
LLRP_DiagnosticTestAck_countDiagnosticTestResultItem (
  LLRP_tSDiagnosticTestAck *pThis);

extern LLRP_tResultCode
LLRP_DiagnosticTestAck_addDiagnosticTestResultItem (
  LLRP_tSDiagnosticTestAck *pThis,
  LLRP_tSDiagnosticTestResultItem *pValue);




  
struct LLRP_SResetDevice
{
    LLRP_tSMessage hdr;
  
  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdResetDevice;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdResetDevice[];

extern LLRP_tSResetDevice *
LLRP_ResetDevice_construct (void);

extern void
LLRP_ResetDevice_destruct (
 LLRP_tSResetDevice * pThis);

extern void
LLRP_ResetDevice_decodeFields (
 LLRP_tSResetDevice * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ResetDevice_assimilateSubParameters (
 LLRP_tSResetDevice * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ResetDevice_encode (
  const LLRP_tSResetDevice *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  


  
struct LLRP_SResetDeviceAck
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSStatus * pStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdResetDeviceAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdResetDeviceAck[];

extern LLRP_tSResetDeviceAck *
LLRP_ResetDeviceAck_construct (void);

extern void
LLRP_ResetDeviceAck_destruct (
 LLRP_tSResetDeviceAck * pThis);

extern void
LLRP_ResetDeviceAck_decodeFields (
 LLRP_tSResetDeviceAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ResetDeviceAck_assimilateSubParameters (
 LLRP_tSResetDeviceAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ResetDeviceAck_encode (
  const LLRP_tSResetDeviceAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSStatus *
LLRP_ResetDeviceAck_getStatus (
  LLRP_tSResetDeviceAck *pThis);

extern LLRP_tResultCode
LLRP_ResetDeviceAck_setStatus (
  LLRP_tSResetDeviceAck *pThis,
  LLRP_tSStatus *pValue);



  
struct LLRP_SCustom
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t VendorIdentifier;

    llrp_u32_t ParameterSubtype;

    llrp_bytesToEnd_t Data;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdCustom;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdCustom[];

extern LLRP_tSCustom *
LLRP_Custom_construct (void);

extern void
LLRP_Custom_destruct (
 LLRP_tSCustom * pThis);

extern void
LLRP_Custom_decodeFields (
 LLRP_tSCustom * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_Custom_assimilateSubParameters (
 LLRP_tSCustom * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_Custom_encode (
  const LLRP_tSCustom *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdCustom_VendorIdentifier;

extern llrp_u32_t
LLRP_Custom_getVendorIdentifier (
  LLRP_tSCustom *pThis);

extern LLRP_tResultCode
LLRP_Custom_setVendorIdentifier (
  LLRP_tSCustom *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCustom_ParameterSubtype;

extern llrp_u32_t
LLRP_Custom_getParameterSubtype (
  LLRP_tSCustom *pThis);

extern LLRP_tResultCode
LLRP_Custom_setParameterSubtype (
  LLRP_tSCustom *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCustom_Data;

extern llrp_bytesToEnd_t
LLRP_Custom_getData (
  LLRP_tSCustom *pThis);

extern LLRP_tResultCode
LLRP_Custom_setData (
  LLRP_tSCustom *pThis,
  llrp_bytesToEnd_t Value);

  


  
struct LLRP_SStatus
{
    LLRP_tSParameter hdr;
  
    LLRP_tEStatusCode eStatusCode;

    llrp_utf8v_t ErrorDescription;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdStatus;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdStatus[];

extern LLRP_tSStatus *
LLRP_Status_construct (void);

extern void
LLRP_Status_destruct (
 LLRP_tSStatus * pThis);

extern void
LLRP_Status_decodeFields (
 LLRP_tSStatus * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_Status_assimilateSubParameters (
 LLRP_tSStatus * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_Status_encode (
  const LLRP_tSStatus *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdStatus_StatusCode;

extern LLRP_tEStatusCode
LLRP_Status_getStatusCode (
  LLRP_tSStatus *pThis);

extern LLRP_tResultCode
LLRP_Status_setStatusCode (
  LLRP_tSStatus *pThis,
  LLRP_tEStatusCode Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdStatus_ErrorDescription;

extern llrp_utf8v_t
LLRP_Status_getErrorDescription (
  LLRP_tSStatus *pThis);

extern LLRP_tResultCode
LLRP_Status_setErrorDescription (
  LLRP_tSStatus *pThis,
  llrp_utf8v_t Value);

  


  
struct LLRP_SUTCTimestamp
{
    LLRP_tSParameter hdr;
  
    llrp_u64_t Microseconds;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdUTCTimestamp;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdUTCTimestamp[];

extern LLRP_tSUTCTimestamp *
LLRP_UTCTimestamp_construct (void);

extern void
LLRP_UTCTimestamp_destruct (
 LLRP_tSUTCTimestamp * pThis);

extern void
LLRP_UTCTimestamp_decodeFields (
 LLRP_tSUTCTimestamp * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_UTCTimestamp_assimilateSubParameters (
 LLRP_tSUTCTimestamp * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_UTCTimestamp_encode (
  const LLRP_tSUTCTimestamp *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdUTCTimestamp_Microseconds;

extern llrp_u64_t
LLRP_UTCTimestamp_getMicroseconds (
  LLRP_tSUTCTimestamp *pThis);

extern LLRP_tResultCode
LLRP_UTCTimestamp_setMicroseconds (
  LLRP_tSUTCTimestamp *pThis,
  llrp_u64_t Value);

  


  
struct LLRP_SGPIEvent
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t GPIPortNumber;

    llrp_u1_t GPIEvent;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdGPIEvent;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGPIEvent[];

extern LLRP_tSGPIEvent *
LLRP_GPIEvent_construct (void);

extern void
LLRP_GPIEvent_destruct (
 LLRP_tSGPIEvent * pThis);

extern void
LLRP_GPIEvent_decodeFields (
 LLRP_tSGPIEvent * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GPIEvent_assimilateSubParameters (
 LLRP_tSGPIEvent * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GPIEvent_encode (
  const LLRP_tSGPIEvent *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGPIEvent_GPIPortNumber;

extern llrp_u8_t
LLRP_GPIEvent_getGPIPortNumber (
  LLRP_tSGPIEvent *pThis);

extern LLRP_tResultCode
LLRP_GPIEvent_setGPIPortNumber (
  LLRP_tSGPIEvent *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGPIEvent_GPIEvent;

extern llrp_u1_t
LLRP_GPIEvent_getGPIEvent (
  LLRP_tSGPIEvent *pThis);

extern LLRP_tResultCode
LLRP_GPIEvent_setGPIEvent (
  LLRP_tSGPIEvent *pThis,
  llrp_u1_t Value);

  


  
struct LLRP_SSelectSpecEvent
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t EventType;

    llrp_u32_t SelectSpecID;

    llrp_u32_t PreemptingSelectSpecID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSelectSpecEvent;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSelectSpecEvent[];

extern LLRP_tSSelectSpecEvent *
LLRP_SelectSpecEvent_construct (void);

extern void
LLRP_SelectSpecEvent_destruct (
 LLRP_tSSelectSpecEvent * pThis);

extern void
LLRP_SelectSpecEvent_decodeFields (
 LLRP_tSSelectSpecEvent * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SelectSpecEvent_assimilateSubParameters (
 LLRP_tSSelectSpecEvent * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SelectSpecEvent_encode (
  const LLRP_tSSelectSpecEvent *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSelectSpecEvent_EventType;

extern llrp_u8_t
LLRP_SelectSpecEvent_getEventType (
  LLRP_tSSelectSpecEvent *pThis);

extern LLRP_tResultCode
LLRP_SelectSpecEvent_setEventType (
  LLRP_tSSelectSpecEvent *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSelectSpecEvent_SelectSpecID;

extern llrp_u32_t
LLRP_SelectSpecEvent_getSelectSpecID (
  LLRP_tSSelectSpecEvent *pThis);

extern LLRP_tResultCode
LLRP_SelectSpecEvent_setSelectSpecID (
  LLRP_tSSelectSpecEvent *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSelectSpecEvent_PreemptingSelectSpecID;

extern llrp_u32_t
LLRP_SelectSpecEvent_getPreemptingSelectSpecID (
  LLRP_tSSelectSpecEvent *pThis);

extern LLRP_tResultCode
LLRP_SelectSpecEvent_setPreemptingSelectSpecID (
  LLRP_tSSelectSpecEvent *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SAntennaSpecEvent
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t EventType;

    llrp_u32_t SelectSpecID;

    llrp_u16_t SpecIndex;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdAntennaSpecEvent;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAntennaSpecEvent[];

extern LLRP_tSAntennaSpecEvent *
LLRP_AntennaSpecEvent_construct (void);

extern void
LLRP_AntennaSpecEvent_destruct (
 LLRP_tSAntennaSpecEvent * pThis);

extern void
LLRP_AntennaSpecEvent_decodeFields (
 LLRP_tSAntennaSpecEvent * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AntennaSpecEvent_assimilateSubParameters (
 LLRP_tSAntennaSpecEvent * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AntennaSpecEvent_encode (
  const LLRP_tSAntennaSpecEvent *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAntennaSpecEvent_EventType;

extern llrp_u8_t
LLRP_AntennaSpecEvent_getEventType (
  LLRP_tSAntennaSpecEvent *pThis);

extern LLRP_tResultCode
LLRP_AntennaSpecEvent_setEventType (
  LLRP_tSAntennaSpecEvent *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAntennaSpecEvent_SelectSpecID;

extern llrp_u32_t
LLRP_AntennaSpecEvent_getSelectSpecID (
  LLRP_tSAntennaSpecEvent *pThis);

extern LLRP_tResultCode
LLRP_AntennaSpecEvent_setSelectSpecID (
  LLRP_tSAntennaSpecEvent *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAntennaSpecEvent_SpecIndex;

extern llrp_u16_t
LLRP_AntennaSpecEvent_getSpecIndex (
  LLRP_tSAntennaSpecEvent *pThis);

extern LLRP_tResultCode
LLRP_AntennaSpecEvent_setSpecIndex (
  LLRP_tSAntennaSpecEvent *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SAntennaStatusEvent
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t EventType;

    llrp_u8_t AntennaID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdAntennaStatusEvent;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAntennaStatusEvent[];

extern LLRP_tSAntennaStatusEvent *
LLRP_AntennaStatusEvent_construct (void);

extern void
LLRP_AntennaStatusEvent_destruct (
 LLRP_tSAntennaStatusEvent * pThis);

extern void
LLRP_AntennaStatusEvent_decodeFields (
 LLRP_tSAntennaStatusEvent * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AntennaStatusEvent_assimilateSubParameters (
 LLRP_tSAntennaStatusEvent * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AntennaStatusEvent_encode (
  const LLRP_tSAntennaStatusEvent *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAntennaStatusEvent_EventType;

extern llrp_u8_t
LLRP_AntennaStatusEvent_getEventType (
  LLRP_tSAntennaStatusEvent *pThis);

extern LLRP_tResultCode
LLRP_AntennaStatusEvent_setEventType (
  LLRP_tSAntennaStatusEvent *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAntennaStatusEvent_AntennaID;

extern llrp_u8_t
LLRP_AntennaStatusEvent_getAntennaID (
  LLRP_tSAntennaStatusEvent *pThis);

extern LLRP_tResultCode
LLRP_AntennaStatusEvent_setAntennaID (
  LLRP_tSAntennaStatusEvent *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SConnectionAttemptEvent
{
    LLRP_tSParameter hdr;
  
    LLRP_tEConnectionStatus eConnectionStatus;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdConnectionAttemptEvent;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdConnectionAttemptEvent[];

extern LLRP_tSConnectionAttemptEvent *
LLRP_ConnectionAttemptEvent_construct (void);

extern void
LLRP_ConnectionAttemptEvent_destruct (
 LLRP_tSConnectionAttemptEvent * pThis);

extern void
LLRP_ConnectionAttemptEvent_decodeFields (
 LLRP_tSConnectionAttemptEvent * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ConnectionAttemptEvent_assimilateSubParameters (
 LLRP_tSConnectionAttemptEvent * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ConnectionAttemptEvent_encode (
  const LLRP_tSConnectionAttemptEvent *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdConnectionAttemptEvent_ConnectionStatus;

extern LLRP_tEConnectionStatus
LLRP_ConnectionAttemptEvent_getConnectionStatus (
  LLRP_tSConnectionAttemptEvent *pThis);

extern LLRP_tResultCode
LLRP_ConnectionAttemptEvent_setConnectionStatus (
  LLRP_tSConnectionAttemptEvent *pThis,
  LLRP_tEConnectionStatus Value);

  


  
struct LLRP_SGeneralCapabilities
{
    LLRP_tSParameter hdr;
  
    llrp_utf8v_t DeviceManufacturerName;

    llrp_u8v_t DeviceSN;

    llrp_u16_t DeviceModel;

    llrp_u16_t DeviceSpecification;

    llrp_u8_t MaxNumberOfAntennaSupported;

    llrp_u1_t HasUTCClockCapability;

    llrp_u1_t HasLocationCapability;

  
    LLRP_tSGPIOCapabilities * pGPIOCapabilities;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdGeneralCapabilities;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGeneralCapabilities[];

extern LLRP_tSGeneralCapabilities *
LLRP_GeneralCapabilities_construct (void);

extern void
LLRP_GeneralCapabilities_destruct (
 LLRP_tSGeneralCapabilities * pThis);

extern void
LLRP_GeneralCapabilities_decodeFields (
 LLRP_tSGeneralCapabilities * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GeneralCapabilities_assimilateSubParameters (
 LLRP_tSGeneralCapabilities * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GeneralCapabilities_encode (
  const LLRP_tSGeneralCapabilities *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGeneralCapabilities_DeviceManufacturerName;

extern llrp_utf8v_t
LLRP_GeneralCapabilities_getDeviceManufacturerName (
  LLRP_tSGeneralCapabilities *pThis);

extern LLRP_tResultCode
LLRP_GeneralCapabilities_setDeviceManufacturerName (
  LLRP_tSGeneralCapabilities *pThis,
  llrp_utf8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGeneralCapabilities_DeviceSN;

extern llrp_u8v_t
LLRP_GeneralCapabilities_getDeviceSN (
  LLRP_tSGeneralCapabilities *pThis);

extern LLRP_tResultCode
LLRP_GeneralCapabilities_setDeviceSN (
  LLRP_tSGeneralCapabilities *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGeneralCapabilities_DeviceModel;

extern llrp_u16_t
LLRP_GeneralCapabilities_getDeviceModel (
  LLRP_tSGeneralCapabilities *pThis);

extern LLRP_tResultCode
LLRP_GeneralCapabilities_setDeviceModel (
  LLRP_tSGeneralCapabilities *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGeneralCapabilities_DeviceSpecification;

extern llrp_u16_t
LLRP_GeneralCapabilities_getDeviceSpecification (
  LLRP_tSGeneralCapabilities *pThis);

extern LLRP_tResultCode
LLRP_GeneralCapabilities_setDeviceSpecification (
  LLRP_tSGeneralCapabilities *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGeneralCapabilities_MaxNumberOfAntennaSupported;

extern llrp_u8_t
LLRP_GeneralCapabilities_getMaxNumberOfAntennaSupported (
  LLRP_tSGeneralCapabilities *pThis);

extern LLRP_tResultCode
LLRP_GeneralCapabilities_setMaxNumberOfAntennaSupported (
  LLRP_tSGeneralCapabilities *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGeneralCapabilities_HasUTCClockCapability;

extern llrp_u1_t
LLRP_GeneralCapabilities_getHasUTCClockCapability (
  LLRP_tSGeneralCapabilities *pThis);

extern LLRP_tResultCode
LLRP_GeneralCapabilities_setHasUTCClockCapability (
  LLRP_tSGeneralCapabilities *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGeneralCapabilities_HasLocationCapability;

extern llrp_u1_t
LLRP_GeneralCapabilities_getHasLocationCapability (
  LLRP_tSGeneralCapabilities *pThis);

extern LLRP_tResultCode
LLRP_GeneralCapabilities_setHasLocationCapability (
  LLRP_tSGeneralCapabilities *pThis,
  llrp_u1_t Value);

  
extern LLRP_tSGPIOCapabilities *
LLRP_GeneralCapabilities_getGPIOCapabilities (
  LLRP_tSGeneralCapabilities *pThis);

extern LLRP_tResultCode
LLRP_GeneralCapabilities_setGPIOCapabilities (
  LLRP_tSGeneralCapabilities *pThis,
  LLRP_tSGPIOCapabilities *pValue);



  
struct LLRP_SGPIOCapabilities
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t NumGPIs;

    llrp_u8_t NumGPOs;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdGPIOCapabilities;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGPIOCapabilities[];

extern LLRP_tSGPIOCapabilities *
LLRP_GPIOCapabilities_construct (void);

extern void
LLRP_GPIOCapabilities_destruct (
 LLRP_tSGPIOCapabilities * pThis);

extern void
LLRP_GPIOCapabilities_decodeFields (
 LLRP_tSGPIOCapabilities * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GPIOCapabilities_assimilateSubParameters (
 LLRP_tSGPIOCapabilities * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GPIOCapabilities_encode (
  const LLRP_tSGPIOCapabilities *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGPIOCapabilities_NumGPIs;

extern llrp_u8_t
LLRP_GPIOCapabilities_getNumGPIs (
  LLRP_tSGPIOCapabilities *pThis);

extern LLRP_tResultCode
LLRP_GPIOCapabilities_setNumGPIs (
  LLRP_tSGPIOCapabilities *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGPIOCapabilities_NumGPOs;

extern llrp_u8_t
LLRP_GPIOCapabilities_getNumGPOs (
  LLRP_tSGPIOCapabilities *pThis);

extern LLRP_tResultCode
LLRP_GPIOCapabilities_setNumGPOs (
  LLRP_tSGPIOCapabilities *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SCommunicationCapabilities
{
    LLRP_tSParameter hdr;
  
    llrp_u1_t SupportEthernet;

    llrp_u1_t SupportWIFI;

    llrp_u1_t SupportMobil;

    llrp_u1_t SupportUSB;

    llrp_u1_t SupportHttpLink;

    llrp_u1_t SupportIPV6;

    llrp_u1_t SupportSSL;

    llrp_u8_t SupportRcpLinkNum;

  
    LLRP_tSSupportRS232 * pSupportRS232;

    LLRP_tSSupportRS485 * pSupportRS485;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdCommunicationCapabilities;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdCommunicationCapabilities[];

extern LLRP_tSCommunicationCapabilities *
LLRP_CommunicationCapabilities_construct (void);

extern void
LLRP_CommunicationCapabilities_destruct (
 LLRP_tSCommunicationCapabilities * pThis);

extern void
LLRP_CommunicationCapabilities_decodeFields (
 LLRP_tSCommunicationCapabilities * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_CommunicationCapabilities_assimilateSubParameters (
 LLRP_tSCommunicationCapabilities * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_CommunicationCapabilities_encode (
  const LLRP_tSCommunicationCapabilities *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdCommunicationCapabilities_SupportEthernet;

extern llrp_u1_t
LLRP_CommunicationCapabilities_getSupportEthernet (
  LLRP_tSCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_CommunicationCapabilities_setSupportEthernet (
  LLRP_tSCommunicationCapabilities *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCommunicationCapabilities_SupportWIFI;

extern llrp_u1_t
LLRP_CommunicationCapabilities_getSupportWIFI (
  LLRP_tSCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_CommunicationCapabilities_setSupportWIFI (
  LLRP_tSCommunicationCapabilities *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCommunicationCapabilities_SupportMobil;

extern llrp_u1_t
LLRP_CommunicationCapabilities_getSupportMobil (
  LLRP_tSCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_CommunicationCapabilities_setSupportMobil (
  LLRP_tSCommunicationCapabilities *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCommunicationCapabilities_SupportUSB;

extern llrp_u1_t
LLRP_CommunicationCapabilities_getSupportUSB (
  LLRP_tSCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_CommunicationCapabilities_setSupportUSB (
  LLRP_tSCommunicationCapabilities *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCommunicationCapabilities_SupportHttpLink;

extern llrp_u1_t
LLRP_CommunicationCapabilities_getSupportHttpLink (
  LLRP_tSCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_CommunicationCapabilities_setSupportHttpLink (
  LLRP_tSCommunicationCapabilities *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCommunicationCapabilities_SupportIPV6;

extern llrp_u1_t
LLRP_CommunicationCapabilities_getSupportIPV6 (
  LLRP_tSCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_CommunicationCapabilities_setSupportIPV6 (
  LLRP_tSCommunicationCapabilities *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCommunicationCapabilities_SupportSSL;

extern llrp_u1_t
LLRP_CommunicationCapabilities_getSupportSSL (
  LLRP_tSCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_CommunicationCapabilities_setSupportSSL (
  LLRP_tSCommunicationCapabilities *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCommunicationCapabilities_SupportRcpLinkNum;

extern llrp_u8_t
LLRP_CommunicationCapabilities_getSupportRcpLinkNum (
  LLRP_tSCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_CommunicationCapabilities_setSupportRcpLinkNum (
  LLRP_tSCommunicationCapabilities *pThis,
  llrp_u8_t Value);

  
extern LLRP_tSSupportRS232 *
LLRP_CommunicationCapabilities_getSupportRS232 (
  LLRP_tSCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_CommunicationCapabilities_setSupportRS232 (
  LLRP_tSCommunicationCapabilities *pThis,
  LLRP_tSSupportRS232 *pValue);

extern LLRP_tSSupportRS485 *
LLRP_CommunicationCapabilities_getSupportRS485 (
  LLRP_tSCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_CommunicationCapabilities_setSupportRS485 (
  LLRP_tSCommunicationCapabilities *pThis,
  LLRP_tSSupportRS485 *pValue);



  
struct LLRP_SSupportRS232
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t PortNum;

  
    LLRP_tSSerialAttribute * listSerialAttribute;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSupportRS232;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSupportRS232[];

extern LLRP_tSSupportRS232 *
LLRP_SupportRS232_construct (void);

extern void
LLRP_SupportRS232_destruct (
 LLRP_tSSupportRS232 * pThis);

extern void
LLRP_SupportRS232_decodeFields (
 LLRP_tSSupportRS232 * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SupportRS232_assimilateSubParameters (
 LLRP_tSSupportRS232 * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SupportRS232_encode (
  const LLRP_tSSupportRS232 *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSupportRS232_PortNum;

extern llrp_u8_t
LLRP_SupportRS232_getPortNum (
  LLRP_tSSupportRS232 *pThis);

extern LLRP_tResultCode
LLRP_SupportRS232_setPortNum (
  LLRP_tSSupportRS232 *pThis,
  llrp_u8_t Value);

  
extern LLRP_tSSerialAttribute *
LLRP_SupportRS232_beginSerialAttribute (
  LLRP_tSSupportRS232 *pThis);

extern LLRP_tSSerialAttribute *
LLRP_SupportRS232_nextSerialAttribute (
  LLRP_tSSerialAttribute *pCurrent);

extern void
LLRP_SupportRS232_clearSerialAttribute (
  LLRP_tSSupportRS232 *pThis);

extern int
LLRP_SupportRS232_countSerialAttribute (
  LLRP_tSSupportRS232 *pThis);

extern LLRP_tResultCode
LLRP_SupportRS232_addSerialAttribute (
  LLRP_tSSupportRS232 *pThis,
  LLRP_tSSerialAttribute *pValue);




  
struct LLRP_SSerialAttribute
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t Index;

    llrp_u32_t BaudRate;

    llrp_u8_t DataBit;

    llrp_u8_t StopBit;

    llrp_u8_t Parity;

    llrp_u8_t FlowControl;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSerialAttribute;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSerialAttribute[];

extern LLRP_tSSerialAttribute *
LLRP_SerialAttribute_construct (void);

extern void
LLRP_SerialAttribute_destruct (
 LLRP_tSSerialAttribute * pThis);

extern void
LLRP_SerialAttribute_decodeFields (
 LLRP_tSSerialAttribute * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SerialAttribute_assimilateSubParameters (
 LLRP_tSSerialAttribute * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SerialAttribute_encode (
  const LLRP_tSSerialAttribute *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSerialAttribute_Index;

extern llrp_u16_t
LLRP_SerialAttribute_getIndex (
  LLRP_tSSerialAttribute *pThis);

extern LLRP_tResultCode
LLRP_SerialAttribute_setIndex (
  LLRP_tSSerialAttribute *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSerialAttribute_BaudRate;

extern llrp_u32_t
LLRP_SerialAttribute_getBaudRate (
  LLRP_tSSerialAttribute *pThis);

extern LLRP_tResultCode
LLRP_SerialAttribute_setBaudRate (
  LLRP_tSSerialAttribute *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSerialAttribute_DataBit;

extern llrp_u8_t
LLRP_SerialAttribute_getDataBit (
  LLRP_tSSerialAttribute *pThis);

extern LLRP_tResultCode
LLRP_SerialAttribute_setDataBit (
  LLRP_tSSerialAttribute *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSerialAttribute_StopBit;

extern llrp_u8_t
LLRP_SerialAttribute_getStopBit (
  LLRP_tSSerialAttribute *pThis);

extern LLRP_tResultCode
LLRP_SerialAttribute_setStopBit (
  LLRP_tSSerialAttribute *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSerialAttribute_Parity;

extern llrp_u8_t
LLRP_SerialAttribute_getParity (
  LLRP_tSSerialAttribute *pThis);

extern LLRP_tResultCode
LLRP_SerialAttribute_setParity (
  LLRP_tSSerialAttribute *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSerialAttribute_FlowControl;

extern llrp_u8_t
LLRP_SerialAttribute_getFlowControl (
  LLRP_tSSerialAttribute *pThis);

extern LLRP_tResultCode
LLRP_SerialAttribute_setFlowControl (
  LLRP_tSSerialAttribute *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SSupportRS485
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t PortNum;

  
    LLRP_tSSerialAttribute * listSerialAttribute;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSupportRS485;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSupportRS485[];

extern LLRP_tSSupportRS485 *
LLRP_SupportRS485_construct (void);

extern void
LLRP_SupportRS485_destruct (
 LLRP_tSSupportRS485 * pThis);

extern void
LLRP_SupportRS485_decodeFields (
 LLRP_tSSupportRS485 * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SupportRS485_assimilateSubParameters (
 LLRP_tSSupportRS485 * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SupportRS485_encode (
  const LLRP_tSSupportRS485 *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSupportRS485_PortNum;

extern llrp_u8_t
LLRP_SupportRS485_getPortNum (
  LLRP_tSSupportRS485 *pThis);

extern LLRP_tResultCode
LLRP_SupportRS485_setPortNum (
  LLRP_tSSupportRS485 *pThis,
  llrp_u8_t Value);

  
extern LLRP_tSSerialAttribute *
LLRP_SupportRS485_beginSerialAttribute (
  LLRP_tSSupportRS485 *pThis);

extern LLRP_tSSerialAttribute *
LLRP_SupportRS485_nextSerialAttribute (
  LLRP_tSSerialAttribute *pCurrent);

extern void
LLRP_SupportRS485_clearSerialAttribute (
  LLRP_tSSupportRS485 *pThis);

extern int
LLRP_SupportRS485_countSerialAttribute (
  LLRP_tSSupportRS485 *pThis);

extern LLRP_tResultCode
LLRP_SupportRS485_addSerialAttribute (
  LLRP_tSSupportRS485 *pThis,
  LLRP_tSSerialAttribute *pValue);




  
struct LLRP_SSpecCapabilities
{
    LLRP_tSParameter hdr;
  
    llrp_u1_t SupportClientRequestOpSpec;

    llrp_u1_t SupportEventAndReportHolding;

    llrp_u16_t ClientRequestOpSpecTimeout;

    llrp_u8_t MaxPriorityLevelSupported;

    llrp_u8_t MaxNumSelectSpec;

    llrp_u8_t MaxNumAntennaSpecsPerSelectSpec;

    llrp_u8_t MaxNumRfSpecsPerAntennaSpec;

    llrp_u8_t MaxNumAccessSpecs;

    llrp_u8_t MaxNumOperationSpecsPerAccessSpec;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSpecCapabilities;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSpecCapabilities[];

extern LLRP_tSSpecCapabilities *
LLRP_SpecCapabilities_construct (void);

extern void
LLRP_SpecCapabilities_destruct (
 LLRP_tSSpecCapabilities * pThis);

extern void
LLRP_SpecCapabilities_decodeFields (
 LLRP_tSSpecCapabilities * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SpecCapabilities_assimilateSubParameters (
 LLRP_tSSpecCapabilities * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SpecCapabilities_encode (
  const LLRP_tSSpecCapabilities *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSpecCapabilities_SupportClientRequestOpSpec;

extern llrp_u1_t
LLRP_SpecCapabilities_getSupportClientRequestOpSpec (
  LLRP_tSSpecCapabilities *pThis);

extern LLRP_tResultCode
LLRP_SpecCapabilities_setSupportClientRequestOpSpec (
  LLRP_tSSpecCapabilities *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSpecCapabilities_SupportEventAndReportHolding;

extern llrp_u1_t
LLRP_SpecCapabilities_getSupportEventAndReportHolding (
  LLRP_tSSpecCapabilities *pThis);

extern LLRP_tResultCode
LLRP_SpecCapabilities_setSupportEventAndReportHolding (
  LLRP_tSSpecCapabilities *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSpecCapabilities_ClientRequestOpSpecTimeout;

extern llrp_u16_t
LLRP_SpecCapabilities_getClientRequestOpSpecTimeout (
  LLRP_tSSpecCapabilities *pThis);

extern LLRP_tResultCode
LLRP_SpecCapabilities_setClientRequestOpSpecTimeout (
  LLRP_tSSpecCapabilities *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSpecCapabilities_MaxPriorityLevelSupported;

extern llrp_u8_t
LLRP_SpecCapabilities_getMaxPriorityLevelSupported (
  LLRP_tSSpecCapabilities *pThis);

extern LLRP_tResultCode
LLRP_SpecCapabilities_setMaxPriorityLevelSupported (
  LLRP_tSSpecCapabilities *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSpecCapabilities_MaxNumSelectSpec;

extern llrp_u8_t
LLRP_SpecCapabilities_getMaxNumSelectSpec (
  LLRP_tSSpecCapabilities *pThis);

extern LLRP_tResultCode
LLRP_SpecCapabilities_setMaxNumSelectSpec (
  LLRP_tSSpecCapabilities *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSpecCapabilities_MaxNumAntennaSpecsPerSelectSpec;

extern llrp_u8_t
LLRP_SpecCapabilities_getMaxNumAntennaSpecsPerSelectSpec (
  LLRP_tSSpecCapabilities *pThis);

extern LLRP_tResultCode
LLRP_SpecCapabilities_setMaxNumAntennaSpecsPerSelectSpec (
  LLRP_tSSpecCapabilities *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSpecCapabilities_MaxNumRfSpecsPerAntennaSpec;

extern llrp_u8_t
LLRP_SpecCapabilities_getMaxNumRfSpecsPerAntennaSpec (
  LLRP_tSSpecCapabilities *pThis);

extern LLRP_tResultCode
LLRP_SpecCapabilities_setMaxNumRfSpecsPerAntennaSpec (
  LLRP_tSSpecCapabilities *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSpecCapabilities_MaxNumAccessSpecs;

extern llrp_u8_t
LLRP_SpecCapabilities_getMaxNumAccessSpecs (
  LLRP_tSSpecCapabilities *pThis);

extern LLRP_tResultCode
LLRP_SpecCapabilities_setMaxNumAccessSpecs (
  LLRP_tSSpecCapabilities *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSpecCapabilities_MaxNumOperationSpecsPerAccessSpec;

extern llrp_u8_t
LLRP_SpecCapabilities_getMaxNumOperationSpecsPerAccessSpec (
  LLRP_tSSpecCapabilities *pThis);

extern LLRP_tResultCode
LLRP_SpecCapabilities_setMaxNumOperationSpecsPerAccessSpec (
  LLRP_tSSpecCapabilities *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SRfCapabilities
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t CountryCode;

    llrp_u16_t CommunicationsStandard;

  
    LLRP_tSTransmitPowerLevelTable * listTransmitPowerLevelTable;

    LLRP_tSFrequencyInformation * pFrequencyInformation;

    LLRP_tSForDataRateTable * listForDataRateTable;

    LLRP_tSRevDataRateTable * listRevDataRateTable;

    LLRP_tSForModulationTable * listForModulationTable;

    LLRP_tSRevDataEncodingTable * listRevDataEncodingTable;

    LLRP_tSModuleDepthTable * listModuleDepthTable;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdRfCapabilities;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRfCapabilities[];

extern LLRP_tSRfCapabilities *
LLRP_RfCapabilities_construct (void);

extern void
LLRP_RfCapabilities_destruct (
 LLRP_tSRfCapabilities * pThis);

extern void
LLRP_RfCapabilities_decodeFields (
 LLRP_tSRfCapabilities * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RfCapabilities_assimilateSubParameters (
 LLRP_tSRfCapabilities * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RfCapabilities_encode (
  const LLRP_tSRfCapabilities *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdRfCapabilities_CountryCode;

extern llrp_u16_t
LLRP_RfCapabilities_getCountryCode (
  LLRP_tSRfCapabilities *pThis);

extern LLRP_tResultCode
LLRP_RfCapabilities_setCountryCode (
  LLRP_tSRfCapabilities *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRfCapabilities_CommunicationsStandard;

extern llrp_u16_t
LLRP_RfCapabilities_getCommunicationsStandard (
  LLRP_tSRfCapabilities *pThis);

extern LLRP_tResultCode
LLRP_RfCapabilities_setCommunicationsStandard (
  LLRP_tSRfCapabilities *pThis,
  llrp_u16_t Value);

  
extern LLRP_tSTransmitPowerLevelTable *
LLRP_RfCapabilities_beginTransmitPowerLevelTable (
  LLRP_tSRfCapabilities *pThis);

extern LLRP_tSTransmitPowerLevelTable *
LLRP_RfCapabilities_nextTransmitPowerLevelTable (
  LLRP_tSTransmitPowerLevelTable *pCurrent);

extern void
LLRP_RfCapabilities_clearTransmitPowerLevelTable (
  LLRP_tSRfCapabilities *pThis);

extern int
LLRP_RfCapabilities_countTransmitPowerLevelTable (
  LLRP_tSRfCapabilities *pThis);

extern LLRP_tResultCode
LLRP_RfCapabilities_addTransmitPowerLevelTable (
  LLRP_tSRfCapabilities *pThis,
  LLRP_tSTransmitPowerLevelTable *pValue);


extern LLRP_tSFrequencyInformation *
LLRP_RfCapabilities_getFrequencyInformation (
  LLRP_tSRfCapabilities *pThis);

extern LLRP_tResultCode
LLRP_RfCapabilities_setFrequencyInformation (
  LLRP_tSRfCapabilities *pThis,
  LLRP_tSFrequencyInformation *pValue);

extern LLRP_tSForDataRateTable *
LLRP_RfCapabilities_beginForDataRateTable (
  LLRP_tSRfCapabilities *pThis);

extern LLRP_tSForDataRateTable *
LLRP_RfCapabilities_nextForDataRateTable (
  LLRP_tSForDataRateTable *pCurrent);

extern void
LLRP_RfCapabilities_clearForDataRateTable (
  LLRP_tSRfCapabilities *pThis);

extern int
LLRP_RfCapabilities_countForDataRateTable (
  LLRP_tSRfCapabilities *pThis);

extern LLRP_tResultCode
LLRP_RfCapabilities_addForDataRateTable (
  LLRP_tSRfCapabilities *pThis,
  LLRP_tSForDataRateTable *pValue);


extern LLRP_tSRevDataRateTable *
LLRP_RfCapabilities_beginRevDataRateTable (
  LLRP_tSRfCapabilities *pThis);

extern LLRP_tSRevDataRateTable *
LLRP_RfCapabilities_nextRevDataRateTable (
  LLRP_tSRevDataRateTable *pCurrent);

extern void
LLRP_RfCapabilities_clearRevDataRateTable (
  LLRP_tSRfCapabilities *pThis);

extern int
LLRP_RfCapabilities_countRevDataRateTable (
  LLRP_tSRfCapabilities *pThis);

extern LLRP_tResultCode
LLRP_RfCapabilities_addRevDataRateTable (
  LLRP_tSRfCapabilities *pThis,
  LLRP_tSRevDataRateTable *pValue);


extern LLRP_tSForModulationTable *
LLRP_RfCapabilities_beginForModulationTable (
  LLRP_tSRfCapabilities *pThis);

extern LLRP_tSForModulationTable *
LLRP_RfCapabilities_nextForModulationTable (
  LLRP_tSForModulationTable *pCurrent);

extern void
LLRP_RfCapabilities_clearForModulationTable (
  LLRP_tSRfCapabilities *pThis);

extern int
LLRP_RfCapabilities_countForModulationTable (
  LLRP_tSRfCapabilities *pThis);

extern LLRP_tResultCode
LLRP_RfCapabilities_addForModulationTable (
  LLRP_tSRfCapabilities *pThis,
  LLRP_tSForModulationTable *pValue);


extern LLRP_tSRevDataEncodingTable *
LLRP_RfCapabilities_beginRevDataEncodingTable (
  LLRP_tSRfCapabilities *pThis);

extern LLRP_tSRevDataEncodingTable *
LLRP_RfCapabilities_nextRevDataEncodingTable (
  LLRP_tSRevDataEncodingTable *pCurrent);

extern void
LLRP_RfCapabilities_clearRevDataEncodingTable (
  LLRP_tSRfCapabilities *pThis);

extern int
LLRP_RfCapabilities_countRevDataEncodingTable (
  LLRP_tSRfCapabilities *pThis);

extern LLRP_tResultCode
LLRP_RfCapabilities_addRevDataEncodingTable (
  LLRP_tSRfCapabilities *pThis,
  LLRP_tSRevDataEncodingTable *pValue);


extern LLRP_tSModuleDepthTable *
LLRP_RfCapabilities_beginModuleDepthTable (
  LLRP_tSRfCapabilities *pThis);

extern LLRP_tSModuleDepthTable *
LLRP_RfCapabilities_nextModuleDepthTable (
  LLRP_tSModuleDepthTable *pCurrent);

extern void
LLRP_RfCapabilities_clearModuleDepthTable (
  LLRP_tSRfCapabilities *pThis);

extern int
LLRP_RfCapabilities_countModuleDepthTable (
  LLRP_tSRfCapabilities *pThis);

extern LLRP_tResultCode
LLRP_RfCapabilities_addModuleDepthTable (
  LLRP_tSRfCapabilities *pThis,
  LLRP_tSModuleDepthTable *pValue);




  
struct LLRP_STransmitPowerLevelTable
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t Index;

    llrp_s16_t TransmitPowerValue;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdTransmitPowerLevelTable;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdTransmitPowerLevelTable[];

extern LLRP_tSTransmitPowerLevelTable *
LLRP_TransmitPowerLevelTable_construct (void);

extern void
LLRP_TransmitPowerLevelTable_destruct (
 LLRP_tSTransmitPowerLevelTable * pThis);

extern void
LLRP_TransmitPowerLevelTable_decodeFields (
 LLRP_tSTransmitPowerLevelTable * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_TransmitPowerLevelTable_assimilateSubParameters (
 LLRP_tSTransmitPowerLevelTable * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_TransmitPowerLevelTable_encode (
  const LLRP_tSTransmitPowerLevelTable *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdTransmitPowerLevelTable_Index;

extern llrp_u16_t
LLRP_TransmitPowerLevelTable_getIndex (
  LLRP_tSTransmitPowerLevelTable *pThis);

extern LLRP_tResultCode
LLRP_TransmitPowerLevelTable_setIndex (
  LLRP_tSTransmitPowerLevelTable *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTransmitPowerLevelTable_TransmitPowerValue;

extern llrp_s16_t
LLRP_TransmitPowerLevelTable_getTransmitPowerValue (
  LLRP_tSTransmitPowerLevelTable *pThis);

extern LLRP_tResultCode
LLRP_TransmitPowerLevelTable_setTransmitPowerValue (
  LLRP_tSTransmitPowerLevelTable *pThis,
  llrp_s16_t Value);

  


  
struct LLRP_SFrequencyInformation
{
    LLRP_tSParameter hdr;
  
    llrp_u1_t Hopping;

  
    LLRP_tSFrequencyTable * listFrequencyTable;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdFrequencyInformation;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdFrequencyInformation[];

extern LLRP_tSFrequencyInformation *
LLRP_FrequencyInformation_construct (void);

extern void
LLRP_FrequencyInformation_destruct (
 LLRP_tSFrequencyInformation * pThis);

extern void
LLRP_FrequencyInformation_decodeFields (
 LLRP_tSFrequencyInformation * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_FrequencyInformation_assimilateSubParameters (
 LLRP_tSFrequencyInformation * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_FrequencyInformation_encode (
  const LLRP_tSFrequencyInformation *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdFrequencyInformation_Hopping;

extern llrp_u1_t
LLRP_FrequencyInformation_getHopping (
  LLRP_tSFrequencyInformation *pThis);

extern LLRP_tResultCode
LLRP_FrequencyInformation_setHopping (
  LLRP_tSFrequencyInformation *pThis,
  llrp_u1_t Value);

  
extern LLRP_tSFrequencyTable *
LLRP_FrequencyInformation_beginFrequencyTable (
  LLRP_tSFrequencyInformation *pThis);

extern LLRP_tSFrequencyTable *
LLRP_FrequencyInformation_nextFrequencyTable (
  LLRP_tSFrequencyTable *pCurrent);

extern void
LLRP_FrequencyInformation_clearFrequencyTable (
  LLRP_tSFrequencyInformation *pThis);

extern int
LLRP_FrequencyInformation_countFrequencyTable (
  LLRP_tSFrequencyInformation *pThis);

extern LLRP_tResultCode
LLRP_FrequencyInformation_addFrequencyTable (
  LLRP_tSFrequencyInformation *pThis,
  LLRP_tSFrequencyTable *pValue);




  
struct LLRP_SFrequencyTable
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t Index;

    llrp_u64_t Frequency;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdFrequencyTable;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdFrequencyTable[];

extern LLRP_tSFrequencyTable *
LLRP_FrequencyTable_construct (void);

extern void
LLRP_FrequencyTable_destruct (
 LLRP_tSFrequencyTable * pThis);

extern void
LLRP_FrequencyTable_decodeFields (
 LLRP_tSFrequencyTable * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_FrequencyTable_assimilateSubParameters (
 LLRP_tSFrequencyTable * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_FrequencyTable_encode (
  const LLRP_tSFrequencyTable *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdFrequencyTable_Index;

extern llrp_u16_t
LLRP_FrequencyTable_getIndex (
  LLRP_tSFrequencyTable *pThis);

extern LLRP_tResultCode
LLRP_FrequencyTable_setIndex (
  LLRP_tSFrequencyTable *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdFrequencyTable_Frequency;

extern llrp_u64_t
LLRP_FrequencyTable_getFrequency (
  LLRP_tSFrequencyTable *pThis);

extern LLRP_tResultCode
LLRP_FrequencyTable_setFrequency (
  LLRP_tSFrequencyTable *pThis,
  llrp_u64_t Value);

  


  
struct LLRP_SForDataRateTable
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t Index;

    llrp_u32_t ForDataRate;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdForDataRateTable;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdForDataRateTable[];

extern LLRP_tSForDataRateTable *
LLRP_ForDataRateTable_construct (void);

extern void
LLRP_ForDataRateTable_destruct (
 LLRP_tSForDataRateTable * pThis);

extern void
LLRP_ForDataRateTable_decodeFields (
 LLRP_tSForDataRateTable * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ForDataRateTable_assimilateSubParameters (
 LLRP_tSForDataRateTable * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ForDataRateTable_encode (
  const LLRP_tSForDataRateTable *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdForDataRateTable_Index;

extern llrp_u16_t
LLRP_ForDataRateTable_getIndex (
  LLRP_tSForDataRateTable *pThis);

extern LLRP_tResultCode
LLRP_ForDataRateTable_setIndex (
  LLRP_tSForDataRateTable *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdForDataRateTable_ForDataRate;

extern llrp_u32_t
LLRP_ForDataRateTable_getForDataRate (
  LLRP_tSForDataRateTable *pThis);

extern LLRP_tResultCode
LLRP_ForDataRateTable_setForDataRate (
  LLRP_tSForDataRateTable *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SRevDataRateTable
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t Index;

    llrp_u32_t RevDataRate;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdRevDataRateTable;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRevDataRateTable[];

extern LLRP_tSRevDataRateTable *
LLRP_RevDataRateTable_construct (void);

extern void
LLRP_RevDataRateTable_destruct (
 LLRP_tSRevDataRateTable * pThis);

extern void
LLRP_RevDataRateTable_decodeFields (
 LLRP_tSRevDataRateTable * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RevDataRateTable_assimilateSubParameters (
 LLRP_tSRevDataRateTable * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RevDataRateTable_encode (
  const LLRP_tSRevDataRateTable *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdRevDataRateTable_Index;

extern llrp_u16_t
LLRP_RevDataRateTable_getIndex (
  LLRP_tSRevDataRateTable *pThis);

extern LLRP_tResultCode
LLRP_RevDataRateTable_setIndex (
  LLRP_tSRevDataRateTable *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRevDataRateTable_RevDataRate;

extern llrp_u32_t
LLRP_RevDataRateTable_getRevDataRate (
  LLRP_tSRevDataRateTable *pThis);

extern LLRP_tResultCode
LLRP_RevDataRateTable_setRevDataRate (
  LLRP_tSRevDataRateTable *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SForModulationTable
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t Index;

    llrp_u8_t ModulationType;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdForModulationTable;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdForModulationTable[];

extern LLRP_tSForModulationTable *
LLRP_ForModulationTable_construct (void);

extern void
LLRP_ForModulationTable_destruct (
 LLRP_tSForModulationTable * pThis);

extern void
LLRP_ForModulationTable_decodeFields (
 LLRP_tSForModulationTable * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ForModulationTable_assimilateSubParameters (
 LLRP_tSForModulationTable * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ForModulationTable_encode (
  const LLRP_tSForModulationTable *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdForModulationTable_Index;

extern llrp_u16_t
LLRP_ForModulationTable_getIndex (
  LLRP_tSForModulationTable *pThis);

extern LLRP_tResultCode
LLRP_ForModulationTable_setIndex (
  LLRP_tSForModulationTable *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdForModulationTable_ModulationType;

extern llrp_u8_t
LLRP_ForModulationTable_getModulationType (
  LLRP_tSForModulationTable *pThis);

extern LLRP_tResultCode
LLRP_ForModulationTable_setModulationType (
  LLRP_tSForModulationTable *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SRevDataEncodingTable
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t Index;

    LLRP_tEDataEncodingType eDataEncodingType;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdRevDataEncodingTable;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRevDataEncodingTable[];

extern LLRP_tSRevDataEncodingTable *
LLRP_RevDataEncodingTable_construct (void);

extern void
LLRP_RevDataEncodingTable_destruct (
 LLRP_tSRevDataEncodingTable * pThis);

extern void
LLRP_RevDataEncodingTable_decodeFields (
 LLRP_tSRevDataEncodingTable * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RevDataEncodingTable_assimilateSubParameters (
 LLRP_tSRevDataEncodingTable * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RevDataEncodingTable_encode (
  const LLRP_tSRevDataEncodingTable *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdRevDataEncodingTable_Index;

extern llrp_u16_t
LLRP_RevDataEncodingTable_getIndex (
  LLRP_tSRevDataEncodingTable *pThis);

extern LLRP_tResultCode
LLRP_RevDataEncodingTable_setIndex (
  LLRP_tSRevDataEncodingTable *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRevDataEncodingTable_DataEncodingType;

extern LLRP_tEDataEncodingType
LLRP_RevDataEncodingTable_getDataEncodingType (
  LLRP_tSRevDataEncodingTable *pThis);

extern LLRP_tResultCode
LLRP_RevDataEncodingTable_setDataEncodingType (
  LLRP_tSRevDataEncodingTable *pThis,
  LLRP_tEDataEncodingType Value);

  


  
struct LLRP_SModuleDepthTable
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t Index;

    llrp_u16_t ModuleDepthValue;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdModuleDepthTable;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdModuleDepthTable[];

extern LLRP_tSModuleDepthTable *
LLRP_ModuleDepthTable_construct (void);

extern void
LLRP_ModuleDepthTable_destruct (
 LLRP_tSModuleDepthTable * pThis);

extern void
LLRP_ModuleDepthTable_decodeFields (
 LLRP_tSModuleDepthTable * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ModuleDepthTable_assimilateSubParameters (
 LLRP_tSModuleDepthTable * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ModuleDepthTable_encode (
  const LLRP_tSModuleDepthTable *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdModuleDepthTable_Index;

extern llrp_u16_t
LLRP_ModuleDepthTable_getIndex (
  LLRP_tSModuleDepthTable *pThis);

extern LLRP_tResultCode
LLRP_ModuleDepthTable_setIndex (
  LLRP_tSModuleDepthTable *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdModuleDepthTable_ModuleDepthValue;

extern llrp_u16_t
LLRP_ModuleDepthTable_getModuleDepthValue (
  LLRP_tSModuleDepthTable *pThis);

extern LLRP_tResultCode
LLRP_ModuleDepthTable_setModuleDepthValue (
  LLRP_tSModuleDepthTable *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SAirProtocolCapabilities
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSPerAntennaAirProtocol * listPerAntennaAirProtocol;

    LLRP_tSParameter * listDeviceAirProtocolCapabilities;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdAirProtocolCapabilities;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAirProtocolCapabilities[];

extern LLRP_tSAirProtocolCapabilities *
LLRP_AirProtocolCapabilities_construct (void);

extern void
LLRP_AirProtocolCapabilities_destruct (
 LLRP_tSAirProtocolCapabilities * pThis);

extern void
LLRP_AirProtocolCapabilities_decodeFields (
 LLRP_tSAirProtocolCapabilities * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AirProtocolCapabilities_assimilateSubParameters (
 LLRP_tSAirProtocolCapabilities * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AirProtocolCapabilities_encode (
  const LLRP_tSAirProtocolCapabilities *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSPerAntennaAirProtocol *
LLRP_AirProtocolCapabilities_beginPerAntennaAirProtocol (
  LLRP_tSAirProtocolCapabilities *pThis);

extern LLRP_tSPerAntennaAirProtocol *
LLRP_AirProtocolCapabilities_nextPerAntennaAirProtocol (
  LLRP_tSPerAntennaAirProtocol *pCurrent);

extern void
LLRP_AirProtocolCapabilities_clearPerAntennaAirProtocol (
  LLRP_tSAirProtocolCapabilities *pThis);

extern int
LLRP_AirProtocolCapabilities_countPerAntennaAirProtocol (
  LLRP_tSAirProtocolCapabilities *pThis);

extern LLRP_tResultCode
LLRP_AirProtocolCapabilities_addPerAntennaAirProtocol (
  LLRP_tSAirProtocolCapabilities *pThis,
  LLRP_tSPerAntennaAirProtocol *pValue);


extern LLRP_tSParameter *
LLRP_AirProtocolCapabilities_beginDeviceAirProtocolCapabilities (
  LLRP_tSAirProtocolCapabilities *pThis);

extern LLRP_tSParameter *
LLRP_AirProtocolCapabilities_nextDeviceAirProtocolCapabilities (
  LLRP_tSParameter *pCurrent);

extern void
LLRP_AirProtocolCapabilities_clearDeviceAirProtocolCapabilities (
  LLRP_tSAirProtocolCapabilities *pThis);

extern int
LLRP_AirProtocolCapabilities_countDeviceAirProtocolCapabilities (
  LLRP_tSAirProtocolCapabilities *pThis);

extern LLRP_tResultCode
LLRP_AirProtocolCapabilities_addDeviceAirProtocolCapabilities (
  LLRP_tSAirProtocolCapabilities *pThis,
  LLRP_tSParameter *pValue);




  
struct LLRP_SPerAntennaAirProtocol
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t AntennaID;

    llrp_u8v_t ProtocolIDs;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdPerAntennaAirProtocol;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdPerAntennaAirProtocol[];

extern LLRP_tSPerAntennaAirProtocol *
LLRP_PerAntennaAirProtocol_construct (void);

extern void
LLRP_PerAntennaAirProtocol_destruct (
 LLRP_tSPerAntennaAirProtocol * pThis);

extern void
LLRP_PerAntennaAirProtocol_decodeFields (
 LLRP_tSPerAntennaAirProtocol * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_PerAntennaAirProtocol_assimilateSubParameters (
 LLRP_tSPerAntennaAirProtocol * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_PerAntennaAirProtocol_encode (
  const LLRP_tSPerAntennaAirProtocol *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdPerAntennaAirProtocol_AntennaID;

extern llrp_u8_t
LLRP_PerAntennaAirProtocol_getAntennaID (
  LLRP_tSPerAntennaAirProtocol *pThis);

extern LLRP_tResultCode
LLRP_PerAntennaAirProtocol_setAntennaID (
  LLRP_tSPerAntennaAirProtocol *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdPerAntennaAirProtocol_ProtocolIDs;

extern llrp_u8v_t
LLRP_PerAntennaAirProtocol_getProtocolIDs (
  LLRP_tSPerAntennaAirProtocol *pThis);

extern LLRP_tResultCode
LLRP_PerAntennaAirProtocol_setProtocolIDs (
  LLRP_tSPerAntennaAirProtocol *pThis,
  llrp_u8v_t Value);

  


  
struct LLRP_SHbProtocolCapabilities
{
    LLRP_tSParameter hdr;
  
    llrp_u1_t SupportQuery;

    llrp_u1_t SupportReadData;

    llrp_u1_t SupportWriteData;

    llrp_u1_t SupportWriteKey;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdHbProtocolCapabilities;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHbProtocolCapabilities[];

extern LLRP_tSHbProtocolCapabilities *
LLRP_HbProtocolCapabilities_construct (void);

extern void
LLRP_HbProtocolCapabilities_destruct (
 LLRP_tSHbProtocolCapabilities * pThis);

extern void
LLRP_HbProtocolCapabilities_decodeFields (
 LLRP_tSHbProtocolCapabilities * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HbProtocolCapabilities_assimilateSubParameters (
 LLRP_tSHbProtocolCapabilities * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HbProtocolCapabilities_encode (
  const LLRP_tSHbProtocolCapabilities *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdHbProtocolCapabilities_SupportQuery;

extern llrp_u1_t
LLRP_HbProtocolCapabilities_getSupportQuery (
  LLRP_tSHbProtocolCapabilities *pThis);

extern LLRP_tResultCode
LLRP_HbProtocolCapabilities_setSupportQuery (
  LLRP_tSHbProtocolCapabilities *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHbProtocolCapabilities_SupportReadData;

extern llrp_u1_t
LLRP_HbProtocolCapabilities_getSupportReadData (
  LLRP_tSHbProtocolCapabilities *pThis);

extern LLRP_tResultCode
LLRP_HbProtocolCapabilities_setSupportReadData (
  LLRP_tSHbProtocolCapabilities *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHbProtocolCapabilities_SupportWriteData;

extern llrp_u1_t
LLRP_HbProtocolCapabilities_getSupportWriteData (
  LLRP_tSHbProtocolCapabilities *pThis);

extern LLRP_tResultCode
LLRP_HbProtocolCapabilities_setSupportWriteData (
  LLRP_tSHbProtocolCapabilities *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHbProtocolCapabilities_SupportWriteKey;

extern llrp_u1_t
LLRP_HbProtocolCapabilities_getSupportWriteKey (
  LLRP_tSHbProtocolCapabilities *pThis);

extern LLRP_tResultCode
LLRP_HbProtocolCapabilities_setSupportWriteKey (
  LLRP_tSHbProtocolCapabilities *pThis,
  llrp_u1_t Value);

  


  
struct LLRP_SSelectSpec
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t SelectSpecID;

    llrp_u8_t Priority;

    LLRP_tESelectSpecState eCurrentState;

    llrp_u1_t Persistence;

  
    LLRP_tSSelectSpecStartTrigger * pSelectSpecStartTrigger;

    LLRP_tSSelectSpecStopTrigger * pSelectSpecStopTrigger;

    LLRP_tSParameter * listSpecParameter;

    LLRP_tSSelectReportSpec * pSelectReportSpec;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSelectSpec;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSelectSpec[];

extern LLRP_tSSelectSpec *
LLRP_SelectSpec_construct (void);

extern void
LLRP_SelectSpec_destruct (
 LLRP_tSSelectSpec * pThis);

extern void
LLRP_SelectSpec_decodeFields (
 LLRP_tSSelectSpec * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SelectSpec_assimilateSubParameters (
 LLRP_tSSelectSpec * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SelectSpec_encode (
  const LLRP_tSSelectSpec *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSelectSpec_SelectSpecID;

extern llrp_u32_t
LLRP_SelectSpec_getSelectSpecID (
  LLRP_tSSelectSpec *pThis);

extern LLRP_tResultCode
LLRP_SelectSpec_setSelectSpecID (
  LLRP_tSSelectSpec *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSelectSpec_Priority;

extern llrp_u8_t
LLRP_SelectSpec_getPriority (
  LLRP_tSSelectSpec *pThis);

extern LLRP_tResultCode
LLRP_SelectSpec_setPriority (
  LLRP_tSSelectSpec *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSelectSpec_CurrentState;

extern LLRP_tESelectSpecState
LLRP_SelectSpec_getCurrentState (
  LLRP_tSSelectSpec *pThis);

extern LLRP_tResultCode
LLRP_SelectSpec_setCurrentState (
  LLRP_tSSelectSpec *pThis,
  LLRP_tESelectSpecState Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSelectSpec_Persistence;

extern llrp_u1_t
LLRP_SelectSpec_getPersistence (
  LLRP_tSSelectSpec *pThis);

extern LLRP_tResultCode
LLRP_SelectSpec_setPersistence (
  LLRP_tSSelectSpec *pThis,
  llrp_u1_t Value);

  
extern LLRP_tSSelectSpecStartTrigger *
LLRP_SelectSpec_getSelectSpecStartTrigger (
  LLRP_tSSelectSpec *pThis);

extern LLRP_tResultCode
LLRP_SelectSpec_setSelectSpecStartTrigger (
  LLRP_tSSelectSpec *pThis,
  LLRP_tSSelectSpecStartTrigger *pValue);

extern LLRP_tSSelectSpecStopTrigger *
LLRP_SelectSpec_getSelectSpecStopTrigger (
  LLRP_tSSelectSpec *pThis);

extern LLRP_tResultCode
LLRP_SelectSpec_setSelectSpecStopTrigger (
  LLRP_tSSelectSpec *pThis,
  LLRP_tSSelectSpecStopTrigger *pValue);

extern LLRP_tSParameter *
LLRP_SelectSpec_beginSpecParameter (
  LLRP_tSSelectSpec *pThis);

extern LLRP_tSParameter *
LLRP_SelectSpec_nextSpecParameter (
  LLRP_tSParameter *pCurrent);

extern void
LLRP_SelectSpec_clearSpecParameter (
  LLRP_tSSelectSpec *pThis);

extern int
LLRP_SelectSpec_countSpecParameter (
  LLRP_tSSelectSpec *pThis);

extern LLRP_tResultCode
LLRP_SelectSpec_addSpecParameter (
  LLRP_tSSelectSpec *pThis,
  LLRP_tSParameter *pValue);


extern LLRP_tSSelectReportSpec *
LLRP_SelectSpec_getSelectReportSpec (
  LLRP_tSSelectSpec *pThis);

extern LLRP_tResultCode
LLRP_SelectSpec_setSelectReportSpec (
  LLRP_tSSelectSpec *pThis,
  LLRP_tSSelectReportSpec *pValue);



  
struct LLRP_SSelectSpecStartTrigger
{
    LLRP_tSParameter hdr;
  
    LLRP_tESelectSpecStartTriggerType eSelectSpecStartTriggerType;

  
    LLRP_tSPeriodicTriggerValue * pPeriodicTriggerValue;

    LLRP_tSGPITrigger * pGPITrigger;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSelectSpecStartTrigger;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSelectSpecStartTrigger[];

extern LLRP_tSSelectSpecStartTrigger *
LLRP_SelectSpecStartTrigger_construct (void);

extern void
LLRP_SelectSpecStartTrigger_destruct (
 LLRP_tSSelectSpecStartTrigger * pThis);

extern void
LLRP_SelectSpecStartTrigger_decodeFields (
 LLRP_tSSelectSpecStartTrigger * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SelectSpecStartTrigger_assimilateSubParameters (
 LLRP_tSSelectSpecStartTrigger * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SelectSpecStartTrigger_encode (
  const LLRP_tSSelectSpecStartTrigger *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSelectSpecStartTrigger_SelectSpecStartTriggerType;

extern LLRP_tESelectSpecStartTriggerType
LLRP_SelectSpecStartTrigger_getSelectSpecStartTriggerType (
  LLRP_tSSelectSpecStartTrigger *pThis);

extern LLRP_tResultCode
LLRP_SelectSpecStartTrigger_setSelectSpecStartTriggerType (
  LLRP_tSSelectSpecStartTrigger *pThis,
  LLRP_tESelectSpecStartTriggerType Value);

  
extern LLRP_tSPeriodicTriggerValue *
LLRP_SelectSpecStartTrigger_getPeriodicTriggerValue (
  LLRP_tSSelectSpecStartTrigger *pThis);

extern LLRP_tResultCode
LLRP_SelectSpecStartTrigger_setPeriodicTriggerValue (
  LLRP_tSSelectSpecStartTrigger *pThis,
  LLRP_tSPeriodicTriggerValue *pValue);

extern LLRP_tSGPITrigger *
LLRP_SelectSpecStartTrigger_getGPITrigger (
  LLRP_tSSelectSpecStartTrigger *pThis);

extern LLRP_tResultCode
LLRP_SelectSpecStartTrigger_setGPITrigger (
  LLRP_tSSelectSpecStartTrigger *pThis,
  LLRP_tSGPITrigger *pValue);



  
struct LLRP_SPeriodicTriggerValue
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t Offset;

    llrp_u32_t Period;

  
    LLRP_tSUTCTimestamp * pUTCTimestamp;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdPeriodicTriggerValue;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdPeriodicTriggerValue[];

extern LLRP_tSPeriodicTriggerValue *
LLRP_PeriodicTriggerValue_construct (void);

extern void
LLRP_PeriodicTriggerValue_destruct (
 LLRP_tSPeriodicTriggerValue * pThis);

extern void
LLRP_PeriodicTriggerValue_decodeFields (
 LLRP_tSPeriodicTriggerValue * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_PeriodicTriggerValue_assimilateSubParameters (
 LLRP_tSPeriodicTriggerValue * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_PeriodicTriggerValue_encode (
  const LLRP_tSPeriodicTriggerValue *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdPeriodicTriggerValue_Offset;

extern llrp_u32_t
LLRP_PeriodicTriggerValue_getOffset (
  LLRP_tSPeriodicTriggerValue *pThis);

extern LLRP_tResultCode
LLRP_PeriodicTriggerValue_setOffset (
  LLRP_tSPeriodicTriggerValue *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdPeriodicTriggerValue_Period;

extern llrp_u32_t
LLRP_PeriodicTriggerValue_getPeriod (
  LLRP_tSPeriodicTriggerValue *pThis);

extern LLRP_tResultCode
LLRP_PeriodicTriggerValue_setPeriod (
  LLRP_tSPeriodicTriggerValue *pThis,
  llrp_u32_t Value);

  
extern LLRP_tSUTCTimestamp *
LLRP_PeriodicTriggerValue_getUTCTimestamp (
  LLRP_tSPeriodicTriggerValue *pThis);

extern LLRP_tResultCode
LLRP_PeriodicTriggerValue_setUTCTimestamp (
  LLRP_tSPeriodicTriggerValue *pThis,
  LLRP_tSUTCTimestamp *pValue);



  
struct LLRP_SGPITrigger
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t GPIPortNum;

    llrp_u1_t GPIEvent;

    llrp_u32_t Timeout;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdGPITrigger;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGPITrigger[];

extern LLRP_tSGPITrigger *
LLRP_GPITrigger_construct (void);

extern void
LLRP_GPITrigger_destruct (
 LLRP_tSGPITrigger * pThis);

extern void
LLRP_GPITrigger_decodeFields (
 LLRP_tSGPITrigger * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GPITrigger_assimilateSubParameters (
 LLRP_tSGPITrigger * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GPITrigger_encode (
  const LLRP_tSGPITrigger *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGPITrigger_GPIPortNum;

extern llrp_u8_t
LLRP_GPITrigger_getGPIPortNum (
  LLRP_tSGPITrigger *pThis);

extern LLRP_tResultCode
LLRP_GPITrigger_setGPIPortNum (
  LLRP_tSGPITrigger *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGPITrigger_GPIEvent;

extern llrp_u1_t
LLRP_GPITrigger_getGPIEvent (
  LLRP_tSGPITrigger *pThis);

extern LLRP_tResultCode
LLRP_GPITrigger_setGPIEvent (
  LLRP_tSGPITrigger *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGPITrigger_Timeout;

extern llrp_u32_t
LLRP_GPITrigger_getTimeout (
  LLRP_tSGPITrigger *pThis);

extern LLRP_tResultCode
LLRP_GPITrigger_setTimeout (
  LLRP_tSGPITrigger *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SSelectSpecStopTrigger
{
    LLRP_tSParameter hdr;
  
    LLRP_tESelectSpecStopTriggerType eSelectSpecStopTriggerType;

    llrp_u32_t DurationValue;

  
    LLRP_tSGPITrigger * pGPITrigger;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSelectSpecStopTrigger;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSelectSpecStopTrigger[];

extern LLRP_tSSelectSpecStopTrigger *
LLRP_SelectSpecStopTrigger_construct (void);

extern void
LLRP_SelectSpecStopTrigger_destruct (
 LLRP_tSSelectSpecStopTrigger * pThis);

extern void
LLRP_SelectSpecStopTrigger_decodeFields (
 LLRP_tSSelectSpecStopTrigger * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SelectSpecStopTrigger_assimilateSubParameters (
 LLRP_tSSelectSpecStopTrigger * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SelectSpecStopTrigger_encode (
  const LLRP_tSSelectSpecStopTrigger *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSelectSpecStopTrigger_SelectSpecStopTriggerType;

extern LLRP_tESelectSpecStopTriggerType
LLRP_SelectSpecStopTrigger_getSelectSpecStopTriggerType (
  LLRP_tSSelectSpecStopTrigger *pThis);

extern LLRP_tResultCode
LLRP_SelectSpecStopTrigger_setSelectSpecStopTriggerType (
  LLRP_tSSelectSpecStopTrigger *pThis,
  LLRP_tESelectSpecStopTriggerType Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSelectSpecStopTrigger_DurationValue;

extern llrp_u32_t
LLRP_SelectSpecStopTrigger_getDurationValue (
  LLRP_tSSelectSpecStopTrigger *pThis);

extern LLRP_tResultCode
LLRP_SelectSpecStopTrigger_setDurationValue (
  LLRP_tSSelectSpecStopTrigger *pThis,
  llrp_u32_t Value);

  
extern LLRP_tSGPITrigger *
LLRP_SelectSpecStopTrigger_getGPITrigger (
  LLRP_tSSelectSpecStopTrigger *pThis);

extern LLRP_tResultCode
LLRP_SelectSpecStopTrigger_setGPITrigger (
  LLRP_tSSelectSpecStopTrigger *pThis,
  LLRP_tSGPITrigger *pValue);



  
struct LLRP_SAntennaSpec
{
    LLRP_tSParameter hdr;
  
    llrp_u8v_t AntennaIDs;

  
    LLRP_tSAntennaSpecStopTrigger * pAntennaSpecStopTrigger;

    LLRP_tSRfSpec * listRfSpec;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdAntennaSpec;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAntennaSpec[];

extern LLRP_tSAntennaSpec *
LLRP_AntennaSpec_construct (void);

extern void
LLRP_AntennaSpec_destruct (
 LLRP_tSAntennaSpec * pThis);

extern void
LLRP_AntennaSpec_decodeFields (
 LLRP_tSAntennaSpec * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AntennaSpec_assimilateSubParameters (
 LLRP_tSAntennaSpec * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AntennaSpec_encode (
  const LLRP_tSAntennaSpec *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAntennaSpec_AntennaIDs;

extern llrp_u8v_t
LLRP_AntennaSpec_getAntennaIDs (
  LLRP_tSAntennaSpec *pThis);

extern LLRP_tResultCode
LLRP_AntennaSpec_setAntennaIDs (
  LLRP_tSAntennaSpec *pThis,
  llrp_u8v_t Value);

  
extern LLRP_tSAntennaSpecStopTrigger *
LLRP_AntennaSpec_getAntennaSpecStopTrigger (
  LLRP_tSAntennaSpec *pThis);

extern LLRP_tResultCode
LLRP_AntennaSpec_setAntennaSpecStopTrigger (
  LLRP_tSAntennaSpec *pThis,
  LLRP_tSAntennaSpecStopTrigger *pValue);

extern LLRP_tSRfSpec *
LLRP_AntennaSpec_beginRfSpec (
  LLRP_tSAntennaSpec *pThis);

extern LLRP_tSRfSpec *
LLRP_AntennaSpec_nextRfSpec (
  LLRP_tSRfSpec *pCurrent);

extern void
LLRP_AntennaSpec_clearRfSpec (
  LLRP_tSAntennaSpec *pThis);

extern int
LLRP_AntennaSpec_countRfSpec (
  LLRP_tSAntennaSpec *pThis);

extern LLRP_tResultCode
LLRP_AntennaSpec_addRfSpec (
  LLRP_tSAntennaSpec *pThis,
  LLRP_tSRfSpec *pValue);




  
struct LLRP_SAntennaSpecStopTrigger
{
    LLRP_tSParameter hdr;
  
    LLRP_tEAntennaSpecStopTriggerType eAntennaSpecStopTriggerType;

    llrp_u32_t DurationValue;

  
    LLRP_tSGPITrigger * pGPITrigger;

    LLRP_tSTagObservationTrigger * pTagObservationTrigger;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdAntennaSpecStopTrigger;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAntennaSpecStopTrigger[];

extern LLRP_tSAntennaSpecStopTrigger *
LLRP_AntennaSpecStopTrigger_construct (void);

extern void
LLRP_AntennaSpecStopTrigger_destruct (
 LLRP_tSAntennaSpecStopTrigger * pThis);

extern void
LLRP_AntennaSpecStopTrigger_decodeFields (
 LLRP_tSAntennaSpecStopTrigger * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AntennaSpecStopTrigger_assimilateSubParameters (
 LLRP_tSAntennaSpecStopTrigger * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AntennaSpecStopTrigger_encode (
  const LLRP_tSAntennaSpecStopTrigger *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAntennaSpecStopTrigger_AntennaSpecStopTriggerType;

extern LLRP_tEAntennaSpecStopTriggerType
LLRP_AntennaSpecStopTrigger_getAntennaSpecStopTriggerType (
  LLRP_tSAntennaSpecStopTrigger *pThis);

extern LLRP_tResultCode
LLRP_AntennaSpecStopTrigger_setAntennaSpecStopTriggerType (
  LLRP_tSAntennaSpecStopTrigger *pThis,
  LLRP_tEAntennaSpecStopTriggerType Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAntennaSpecStopTrigger_DurationValue;

extern llrp_u32_t
LLRP_AntennaSpecStopTrigger_getDurationValue (
  LLRP_tSAntennaSpecStopTrigger *pThis);

extern LLRP_tResultCode
LLRP_AntennaSpecStopTrigger_setDurationValue (
  LLRP_tSAntennaSpecStopTrigger *pThis,
  llrp_u32_t Value);

  
extern LLRP_tSGPITrigger *
LLRP_AntennaSpecStopTrigger_getGPITrigger (
  LLRP_tSAntennaSpecStopTrigger *pThis);

extern LLRP_tResultCode
LLRP_AntennaSpecStopTrigger_setGPITrigger (
  LLRP_tSAntennaSpecStopTrigger *pThis,
  LLRP_tSGPITrigger *pValue);

extern LLRP_tSTagObservationTrigger *
LLRP_AntennaSpecStopTrigger_getTagObservationTrigger (
  LLRP_tSAntennaSpecStopTrigger *pThis);

extern LLRP_tResultCode
LLRP_AntennaSpecStopTrigger_setTagObservationTrigger (
  LLRP_tSAntennaSpecStopTrigger *pThis,
  LLRP_tSTagObservationTrigger *pValue);



  
struct LLRP_STagObservationTrigger
{
    LLRP_tSParameter hdr;
  
    LLRP_tETagObservationTriggerType eTriggerType;

    llrp_u16_t NumberOfTags;

    llrp_u16_t NumberOfAttempts;

    llrp_u16_t TValue;

    llrp_u32_t Timeout;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdTagObservationTrigger;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdTagObservationTrigger[];

extern LLRP_tSTagObservationTrigger *
LLRP_TagObservationTrigger_construct (void);

extern void
LLRP_TagObservationTrigger_destruct (
 LLRP_tSTagObservationTrigger * pThis);

extern void
LLRP_TagObservationTrigger_decodeFields (
 LLRP_tSTagObservationTrigger * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_TagObservationTrigger_assimilateSubParameters (
 LLRP_tSTagObservationTrigger * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_TagObservationTrigger_encode (
  const LLRP_tSTagObservationTrigger *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdTagObservationTrigger_TriggerType;

extern LLRP_tETagObservationTriggerType
LLRP_TagObservationTrigger_getTriggerType (
  LLRP_tSTagObservationTrigger *pThis);

extern LLRP_tResultCode
LLRP_TagObservationTrigger_setTriggerType (
  LLRP_tSTagObservationTrigger *pThis,
  LLRP_tETagObservationTriggerType Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTagObservationTrigger_NumberOfTags;

extern llrp_u16_t
LLRP_TagObservationTrigger_getNumberOfTags (
  LLRP_tSTagObservationTrigger *pThis);

extern LLRP_tResultCode
LLRP_TagObservationTrigger_setNumberOfTags (
  LLRP_tSTagObservationTrigger *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTagObservationTrigger_NumberOfAttempts;

extern llrp_u16_t
LLRP_TagObservationTrigger_getNumberOfAttempts (
  LLRP_tSTagObservationTrigger *pThis);

extern LLRP_tResultCode
LLRP_TagObservationTrigger_setNumberOfAttempts (
  LLRP_tSTagObservationTrigger *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTagObservationTrigger_TValue;

extern llrp_u16_t
LLRP_TagObservationTrigger_getTValue (
  LLRP_tSTagObservationTrigger *pThis);

extern LLRP_tResultCode
LLRP_TagObservationTrigger_setTValue (
  LLRP_tSTagObservationTrigger *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTagObservationTrigger_Timeout;

extern llrp_u32_t
LLRP_TagObservationTrigger_getTimeout (
  LLRP_tSTagObservationTrigger *pThis);

extern LLRP_tResultCode
LLRP_TagObservationTrigger_setTimeout (
  LLRP_tSTagObservationTrigger *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SRfSpec
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t RfSpecID;

    llrp_u8_t ProtocolID;

    LLRP_tERfSelectType eSelectType;

  
    LLRP_tSMemoryBank * pMemoryBank;

    LLRP_tSAntennaConfiguration * listAntennaConfiguration;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdRfSpec;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRfSpec[];

extern LLRP_tSRfSpec *
LLRP_RfSpec_construct (void);

extern void
LLRP_RfSpec_destruct (
 LLRP_tSRfSpec * pThis);

extern void
LLRP_RfSpec_decodeFields (
 LLRP_tSRfSpec * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RfSpec_assimilateSubParameters (
 LLRP_tSRfSpec * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RfSpec_encode (
  const LLRP_tSRfSpec *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdRfSpec_RfSpecID;

extern llrp_u16_t
LLRP_RfSpec_getRfSpecID (
  LLRP_tSRfSpec *pThis);

extern LLRP_tResultCode
LLRP_RfSpec_setRfSpecID (
  LLRP_tSRfSpec *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRfSpec_ProtocolID;

extern llrp_u8_t
LLRP_RfSpec_getProtocolID (
  LLRP_tSRfSpec *pThis);

extern LLRP_tResultCode
LLRP_RfSpec_setProtocolID (
  LLRP_tSRfSpec *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRfSpec_SelectType;

extern LLRP_tERfSelectType
LLRP_RfSpec_getSelectType (
  LLRP_tSRfSpec *pThis);

extern LLRP_tResultCode
LLRP_RfSpec_setSelectType (
  LLRP_tSRfSpec *pThis,
  LLRP_tERfSelectType Value);

  
extern LLRP_tSMemoryBank *
LLRP_RfSpec_getMemoryBank (
  LLRP_tSRfSpec *pThis);

extern LLRP_tResultCode
LLRP_RfSpec_setMemoryBank (
  LLRP_tSRfSpec *pThis,
  LLRP_tSMemoryBank *pValue);

extern LLRP_tSAntennaConfiguration *
LLRP_RfSpec_beginAntennaConfiguration (
  LLRP_tSRfSpec *pThis);

extern LLRP_tSAntennaConfiguration *
LLRP_RfSpec_nextAntennaConfiguration (
  LLRP_tSAntennaConfiguration *pCurrent);

extern void
LLRP_RfSpec_clearAntennaConfiguration (
  LLRP_tSRfSpec *pThis);

extern int
LLRP_RfSpec_countAntennaConfiguration (
  LLRP_tSRfSpec *pThis);

extern LLRP_tResultCode
LLRP_RfSpec_addAntennaConfiguration (
  LLRP_tSRfSpec *pThis,
  LLRP_tSAntennaConfiguration *pValue);




  
struct LLRP_SMemoryBank
{
    LLRP_tSParameter hdr;
  
    LLRP_tEMemoryBankID eMemoryBankID;

    llrp_u16_t Pointer;

    llrp_u16_t Count;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdMemoryBank;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdMemoryBank[];

extern LLRP_tSMemoryBank *
LLRP_MemoryBank_construct (void);

extern void
LLRP_MemoryBank_destruct (
 LLRP_tSMemoryBank * pThis);

extern void
LLRP_MemoryBank_decodeFields (
 LLRP_tSMemoryBank * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_MemoryBank_assimilateSubParameters (
 LLRP_tSMemoryBank * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_MemoryBank_encode (
  const LLRP_tSMemoryBank *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdMemoryBank_MemoryBankID;

extern LLRP_tEMemoryBankID
LLRP_MemoryBank_getMemoryBankID (
  LLRP_tSMemoryBank *pThis);

extern LLRP_tResultCode
LLRP_MemoryBank_setMemoryBankID (
  LLRP_tSMemoryBank *pThis,
  LLRP_tEMemoryBankID Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdMemoryBank_Pointer;

extern llrp_u16_t
LLRP_MemoryBank_getPointer (
  LLRP_tSMemoryBank *pThis);

extern LLRP_tResultCode
LLRP_MemoryBank_setPointer (
  LLRP_tSMemoryBank *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdMemoryBank_Count;

extern llrp_u16_t
LLRP_MemoryBank_getCount (
  LLRP_tSMemoryBank *pThis);

extern LLRP_tResultCode
LLRP_MemoryBank_setCount (
  LLRP_tSMemoryBank *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SSelectReportSpec
{
    LLRP_tSParameter hdr;
  
    LLRP_tESelectReportTrigger eSelectReportTrigger;

    llrp_u16_t NValue;

    llrp_u1_t EnableSelectSpecID;

    llrp_u1_t EnableSpecIndex;

    llrp_u1_t EnableRfSpecID;

    llrp_u1_t EnableAntennaID;

    llrp_u1_t EnablePeakRSSI;

    llrp_u1_t EnableFirstSeenTimestamp;

    llrp_u1_t EnableLastSeenTimestamp;

    llrp_u1_t EnableTagSeenCount;

    llrp_u1_t EnableAccessSpecID;

  
    LLRP_tSReportDestination * pReportDestination;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSelectReportSpec;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSelectReportSpec[];

extern LLRP_tSSelectReportSpec *
LLRP_SelectReportSpec_construct (void);

extern void
LLRP_SelectReportSpec_destruct (
 LLRP_tSSelectReportSpec * pThis);

extern void
LLRP_SelectReportSpec_decodeFields (
 LLRP_tSSelectReportSpec * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SelectReportSpec_assimilateSubParameters (
 LLRP_tSSelectReportSpec * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SelectReportSpec_encode (
  const LLRP_tSSelectReportSpec *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSelectReportSpec_SelectReportTrigger;

extern LLRP_tESelectReportTrigger
LLRP_SelectReportSpec_getSelectReportTrigger (
  LLRP_tSSelectReportSpec *pThis);

extern LLRP_tResultCode
LLRP_SelectReportSpec_setSelectReportTrigger (
  LLRP_tSSelectReportSpec *pThis,
  LLRP_tESelectReportTrigger Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSelectReportSpec_NValue;

extern llrp_u16_t
LLRP_SelectReportSpec_getNValue (
  LLRP_tSSelectReportSpec *pThis);

extern LLRP_tResultCode
LLRP_SelectReportSpec_setNValue (
  LLRP_tSSelectReportSpec *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSelectReportSpec_EnableSelectSpecID;

extern llrp_u1_t
LLRP_SelectReportSpec_getEnableSelectSpecID (
  LLRP_tSSelectReportSpec *pThis);

extern LLRP_tResultCode
LLRP_SelectReportSpec_setEnableSelectSpecID (
  LLRP_tSSelectReportSpec *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSelectReportSpec_EnableSpecIndex;

extern llrp_u1_t
LLRP_SelectReportSpec_getEnableSpecIndex (
  LLRP_tSSelectReportSpec *pThis);

extern LLRP_tResultCode
LLRP_SelectReportSpec_setEnableSpecIndex (
  LLRP_tSSelectReportSpec *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSelectReportSpec_EnableRfSpecID;

extern llrp_u1_t
LLRP_SelectReportSpec_getEnableRfSpecID (
  LLRP_tSSelectReportSpec *pThis);

extern LLRP_tResultCode
LLRP_SelectReportSpec_setEnableRfSpecID (
  LLRP_tSSelectReportSpec *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSelectReportSpec_EnableAntennaID;

extern llrp_u1_t
LLRP_SelectReportSpec_getEnableAntennaID (
  LLRP_tSSelectReportSpec *pThis);

extern LLRP_tResultCode
LLRP_SelectReportSpec_setEnableAntennaID (
  LLRP_tSSelectReportSpec *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSelectReportSpec_EnablePeakRSSI;

extern llrp_u1_t
LLRP_SelectReportSpec_getEnablePeakRSSI (
  LLRP_tSSelectReportSpec *pThis);

extern LLRP_tResultCode
LLRP_SelectReportSpec_setEnablePeakRSSI (
  LLRP_tSSelectReportSpec *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSelectReportSpec_EnableFirstSeenTimestamp;

extern llrp_u1_t
LLRP_SelectReportSpec_getEnableFirstSeenTimestamp (
  LLRP_tSSelectReportSpec *pThis);

extern LLRP_tResultCode
LLRP_SelectReportSpec_setEnableFirstSeenTimestamp (
  LLRP_tSSelectReportSpec *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSelectReportSpec_EnableLastSeenTimestamp;

extern llrp_u1_t
LLRP_SelectReportSpec_getEnableLastSeenTimestamp (
  LLRP_tSSelectReportSpec *pThis);

extern LLRP_tResultCode
LLRP_SelectReportSpec_setEnableLastSeenTimestamp (
  LLRP_tSSelectReportSpec *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSelectReportSpec_EnableTagSeenCount;

extern llrp_u1_t
LLRP_SelectReportSpec_getEnableTagSeenCount (
  LLRP_tSSelectReportSpec *pThis);

extern LLRP_tResultCode
LLRP_SelectReportSpec_setEnableTagSeenCount (
  LLRP_tSSelectReportSpec *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSelectReportSpec_EnableAccessSpecID;

extern llrp_u1_t
LLRP_SelectReportSpec_getEnableAccessSpecID (
  LLRP_tSSelectReportSpec *pThis);

extern LLRP_tResultCode
LLRP_SelectReportSpec_setEnableAccessSpecID (
  LLRP_tSSelectReportSpec *pThis,
  llrp_u1_t Value);

  
extern LLRP_tSReportDestination *
LLRP_SelectReportSpec_getReportDestination (
  LLRP_tSSelectReportSpec *pThis);

extern LLRP_tResultCode
LLRP_SelectReportSpec_setReportDestination (
  LLRP_tSSelectReportSpec *pThis,
  LLRP_tSReportDestination *pValue);



  
struct LLRP_SReportDestination
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSCommLinkConfiguration * listCommLinkConfiguration;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdReportDestination;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdReportDestination[];

extern LLRP_tSReportDestination *
LLRP_ReportDestination_construct (void);

extern void
LLRP_ReportDestination_destruct (
 LLRP_tSReportDestination * pThis);

extern void
LLRP_ReportDestination_decodeFields (
 LLRP_tSReportDestination * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ReportDestination_assimilateSubParameters (
 LLRP_tSReportDestination * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ReportDestination_encode (
  const LLRP_tSReportDestination *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSCommLinkConfiguration *
LLRP_ReportDestination_beginCommLinkConfiguration (
  LLRP_tSReportDestination *pThis);

extern LLRP_tSCommLinkConfiguration *
LLRP_ReportDestination_nextCommLinkConfiguration (
  LLRP_tSCommLinkConfiguration *pCurrent);

extern void
LLRP_ReportDestination_clearCommLinkConfiguration (
  LLRP_tSReportDestination *pThis);

extern int
LLRP_ReportDestination_countCommLinkConfiguration (
  LLRP_tSReportDestination *pThis);

extern LLRP_tResultCode
LLRP_ReportDestination_addCommLinkConfiguration (
  LLRP_tSReportDestination *pThis,
  LLRP_tSCommLinkConfiguration *pValue);




  
struct LLRP_SAccessSpec
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t AccessSpecID;

    llrp_u32_t SelectSpecID;

    llrp_u8_t AntennaID;

    llrp_u8_t ProtocolID;

    LLRP_tEAccessSpecState eCurrentState;

    llrp_u1_t Persistence;

  
    LLRP_tSAccessSpecStopTrigger * pAccessSpecStopTrigger;

    LLRP_tSAccessCommand * pAccessCommand;

    LLRP_tSAccessReportSpec * pAccessReportSpec;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdAccessSpec;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAccessSpec[];

extern LLRP_tSAccessSpec *
LLRP_AccessSpec_construct (void);

extern void
LLRP_AccessSpec_destruct (
 LLRP_tSAccessSpec * pThis);

extern void
LLRP_AccessSpec_decodeFields (
 LLRP_tSAccessSpec * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AccessSpec_assimilateSubParameters (
 LLRP_tSAccessSpec * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AccessSpec_encode (
  const LLRP_tSAccessSpec *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAccessSpec_AccessSpecID;

extern llrp_u32_t
LLRP_AccessSpec_getAccessSpecID (
  LLRP_tSAccessSpec *pThis);

extern LLRP_tResultCode
LLRP_AccessSpec_setAccessSpecID (
  LLRP_tSAccessSpec *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAccessSpec_SelectSpecID;

extern llrp_u32_t
LLRP_AccessSpec_getSelectSpecID (
  LLRP_tSAccessSpec *pThis);

extern LLRP_tResultCode
LLRP_AccessSpec_setSelectSpecID (
  LLRP_tSAccessSpec *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAccessSpec_AntennaID;

extern llrp_u8_t
LLRP_AccessSpec_getAntennaID (
  LLRP_tSAccessSpec *pThis);

extern LLRP_tResultCode
LLRP_AccessSpec_setAntennaID (
  LLRP_tSAccessSpec *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAccessSpec_ProtocolID;

extern llrp_u8_t
LLRP_AccessSpec_getProtocolID (
  LLRP_tSAccessSpec *pThis);

extern LLRP_tResultCode
LLRP_AccessSpec_setProtocolID (
  LLRP_tSAccessSpec *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAccessSpec_CurrentState;

extern LLRP_tEAccessSpecState
LLRP_AccessSpec_getCurrentState (
  LLRP_tSAccessSpec *pThis);

extern LLRP_tResultCode
LLRP_AccessSpec_setCurrentState (
  LLRP_tSAccessSpec *pThis,
  LLRP_tEAccessSpecState Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAccessSpec_Persistence;

extern llrp_u1_t
LLRP_AccessSpec_getPersistence (
  LLRP_tSAccessSpec *pThis);

extern LLRP_tResultCode
LLRP_AccessSpec_setPersistence (
  LLRP_tSAccessSpec *pThis,
  llrp_u1_t Value);

  
extern LLRP_tSAccessSpecStopTrigger *
LLRP_AccessSpec_getAccessSpecStopTrigger (
  LLRP_tSAccessSpec *pThis);

extern LLRP_tResultCode
LLRP_AccessSpec_setAccessSpecStopTrigger (
  LLRP_tSAccessSpec *pThis,
  LLRP_tSAccessSpecStopTrigger *pValue);

extern LLRP_tSAccessCommand *
LLRP_AccessSpec_getAccessCommand (
  LLRP_tSAccessSpec *pThis);

extern LLRP_tResultCode
LLRP_AccessSpec_setAccessCommand (
  LLRP_tSAccessSpec *pThis,
  LLRP_tSAccessCommand *pValue);

extern LLRP_tSAccessReportSpec *
LLRP_AccessSpec_getAccessReportSpec (
  LLRP_tSAccessSpec *pThis);

extern LLRP_tResultCode
LLRP_AccessSpec_setAccessReportSpec (
  LLRP_tSAccessSpec *pThis,
  LLRP_tSAccessReportSpec *pValue);



  
struct LLRP_SAccessSpecStopTrigger
{
    LLRP_tSParameter hdr;
  
    LLRP_tEAccessSpecStopTriggerType eAccessSpecStopTrigger;

    llrp_u16_t OperationCountValue;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdAccessSpecStopTrigger;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAccessSpecStopTrigger[];

extern LLRP_tSAccessSpecStopTrigger *
LLRP_AccessSpecStopTrigger_construct (void);

extern void
LLRP_AccessSpecStopTrigger_destruct (
 LLRP_tSAccessSpecStopTrigger * pThis);

extern void
LLRP_AccessSpecStopTrigger_decodeFields (
 LLRP_tSAccessSpecStopTrigger * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AccessSpecStopTrigger_assimilateSubParameters (
 LLRP_tSAccessSpecStopTrigger * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AccessSpecStopTrigger_encode (
  const LLRP_tSAccessSpecStopTrigger *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAccessSpecStopTrigger_AccessSpecStopTrigger;

extern LLRP_tEAccessSpecStopTriggerType
LLRP_AccessSpecStopTrigger_getAccessSpecStopTrigger (
  LLRP_tSAccessSpecStopTrigger *pThis);

extern LLRP_tResultCode
LLRP_AccessSpecStopTrigger_setAccessSpecStopTrigger (
  LLRP_tSAccessSpecStopTrigger *pThis,
  LLRP_tEAccessSpecStopTriggerType Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAccessSpecStopTrigger_OperationCountValue;

extern llrp_u16_t
LLRP_AccessSpecStopTrigger_getOperationCountValue (
  LLRP_tSAccessSpecStopTrigger *pThis);

extern LLRP_tResultCode
LLRP_AccessSpecStopTrigger_setOperationCountValue (
  LLRP_tSAccessSpecStopTrigger *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SAccessCommand
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSParameter * pMatchSpec;

    LLRP_tSParameter * listOpSpec;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdAccessCommand;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAccessCommand[];

extern LLRP_tSAccessCommand *
LLRP_AccessCommand_construct (void);

extern void
LLRP_AccessCommand_destruct (
 LLRP_tSAccessCommand * pThis);

extern void
LLRP_AccessCommand_decodeFields (
 LLRP_tSAccessCommand * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AccessCommand_assimilateSubParameters (
 LLRP_tSAccessCommand * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AccessCommand_encode (
  const LLRP_tSAccessCommand *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSParameter *
LLRP_AccessCommand_getMatchSpec (
  LLRP_tSAccessCommand *pThis);

extern LLRP_tResultCode
LLRP_AccessCommand_setMatchSpec (
  LLRP_tSAccessCommand *pThis,
  LLRP_tSParameter *pValue);

extern LLRP_tSParameter *
LLRP_AccessCommand_beginOpSpec (
  LLRP_tSAccessCommand *pThis);

extern LLRP_tSParameter *
LLRP_AccessCommand_nextOpSpec (
  LLRP_tSParameter *pCurrent);

extern void
LLRP_AccessCommand_clearOpSpec (
  LLRP_tSAccessCommand *pThis);

extern int
LLRP_AccessCommand_countOpSpec (
  LLRP_tSAccessCommand *pThis);

extern LLRP_tResultCode
LLRP_AccessCommand_addOpSpec (
  LLRP_tSAccessCommand *pThis,
  LLRP_tSParameter *pValue);




  
struct LLRP_SHbMatchSpec
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSHbTargetTag * listHbTargetTag;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdHbMatchSpec;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHbMatchSpec[];

extern LLRP_tSHbMatchSpec *
LLRP_HbMatchSpec_construct (void);

extern void
LLRP_HbMatchSpec_destruct (
 LLRP_tSHbMatchSpec * pThis);

extern void
LLRP_HbMatchSpec_decodeFields (
 LLRP_tSHbMatchSpec * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HbMatchSpec_assimilateSubParameters (
 LLRP_tSHbMatchSpec * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HbMatchSpec_encode (
  const LLRP_tSHbMatchSpec *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSHbTargetTag *
LLRP_HbMatchSpec_beginHbTargetTag (
  LLRP_tSHbMatchSpec *pThis);

extern LLRP_tSHbTargetTag *
LLRP_HbMatchSpec_nextHbTargetTag (
  LLRP_tSHbTargetTag *pCurrent);

extern void
LLRP_HbMatchSpec_clearHbTargetTag (
  LLRP_tSHbMatchSpec *pThis);

extern int
LLRP_HbMatchSpec_countHbTargetTag (
  LLRP_tSHbMatchSpec *pThis);

extern LLRP_tResultCode
LLRP_HbMatchSpec_addHbTargetTag (
  LLRP_tSHbMatchSpec *pThis,
  LLRP_tSHbTargetTag *pValue);




  
struct LLRP_SHbTargetTag
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t MemoryType;

    llrp_u1_t MatchType;

    llrp_u16_t Pointer;

    llrp_u1v_t TagMask;

    llrp_u1v_t TagData;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdHbTargetTag;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHbTargetTag[];

extern LLRP_tSHbTargetTag *
LLRP_HbTargetTag_construct (void);

extern void
LLRP_HbTargetTag_destruct (
 LLRP_tSHbTargetTag * pThis);

extern void
LLRP_HbTargetTag_decodeFields (
 LLRP_tSHbTargetTag * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HbTargetTag_assimilateSubParameters (
 LLRP_tSHbTargetTag * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HbTargetTag_encode (
  const LLRP_tSHbTargetTag *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdHbTargetTag_MemoryType;

extern llrp_u8_t
LLRP_HbTargetTag_getMemoryType (
  LLRP_tSHbTargetTag *pThis);

extern LLRP_tResultCode
LLRP_HbTargetTag_setMemoryType (
  LLRP_tSHbTargetTag *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHbTargetTag_MatchType;

extern llrp_u1_t
LLRP_HbTargetTag_getMatchType (
  LLRP_tSHbTargetTag *pThis);

extern LLRP_tResultCode
LLRP_HbTargetTag_setMatchType (
  LLRP_tSHbTargetTag *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHbTargetTag_Pointer;

extern llrp_u16_t
LLRP_HbTargetTag_getPointer (
  LLRP_tSHbTargetTag *pThis);

extern LLRP_tResultCode
LLRP_HbTargetTag_setPointer (
  LLRP_tSHbTargetTag *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHbTargetTag_TagMask;

extern llrp_u1v_t
LLRP_HbTargetTag_getTagMask (
  LLRP_tSHbTargetTag *pThis);

extern LLRP_tResultCode
LLRP_HbTargetTag_setTagMask (
  LLRP_tSHbTargetTag *pThis,
  llrp_u1v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHbTargetTag_TagData;

extern llrp_u1v_t
LLRP_HbTargetTag_getTagData (
  LLRP_tSHbTargetTag *pThis);

extern LLRP_tResultCode
LLRP_HbTargetTag_setTagData (
  LLRP_tSHbTargetTag *pThis,
  llrp_u1v_t Value);

  


  
struct LLRP_SHbReadSpec
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t OpSpecID;

    LLRP_tEMemoryBankID eMemoryBankID;

    llrp_u16_t Pointer;

    llrp_u16_t Count;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdHbReadSpec;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHbReadSpec[];

extern LLRP_tSHbReadSpec *
LLRP_HbReadSpec_construct (void);

extern void
LLRP_HbReadSpec_destruct (
 LLRP_tSHbReadSpec * pThis);

extern void
LLRP_HbReadSpec_decodeFields (
 LLRP_tSHbReadSpec * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HbReadSpec_assimilateSubParameters (
 LLRP_tSHbReadSpec * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HbReadSpec_encode (
  const LLRP_tSHbReadSpec *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdHbReadSpec_OpSpecID;

extern llrp_u16_t
LLRP_HbReadSpec_getOpSpecID (
  LLRP_tSHbReadSpec *pThis);

extern LLRP_tResultCode
LLRP_HbReadSpec_setOpSpecID (
  LLRP_tSHbReadSpec *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHbReadSpec_MemoryBankID;

extern LLRP_tEMemoryBankID
LLRP_HbReadSpec_getMemoryBankID (
  LLRP_tSHbReadSpec *pThis);

extern LLRP_tResultCode
LLRP_HbReadSpec_setMemoryBankID (
  LLRP_tSHbReadSpec *pThis,
  LLRP_tEMemoryBankID Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHbReadSpec_Pointer;

extern llrp_u16_t
LLRP_HbReadSpec_getPointer (
  LLRP_tSHbReadSpec *pThis);

extern LLRP_tResultCode
LLRP_HbReadSpec_setPointer (
  LLRP_tSHbReadSpec *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHbReadSpec_Count;

extern llrp_u16_t
LLRP_HbReadSpec_getCount (
  LLRP_tSHbReadSpec *pThis);

extern LLRP_tResultCode
LLRP_HbReadSpec_setCount (
  LLRP_tSHbReadSpec *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SClientRequestSpec
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t OpSpecID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdClientRequestSpec;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdClientRequestSpec[];

extern LLRP_tSClientRequestSpec *
LLRP_ClientRequestSpec_construct (void);

extern void
LLRP_ClientRequestSpec_destruct (
 LLRP_tSClientRequestSpec * pThis);

extern void
LLRP_ClientRequestSpec_decodeFields (
 LLRP_tSClientRequestSpec * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ClientRequestSpec_assimilateSubParameters (
 LLRP_tSClientRequestSpec * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ClientRequestSpec_encode (
  const LLRP_tSClientRequestSpec *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdClientRequestSpec_OpSpecID;

extern llrp_u16_t
LLRP_ClientRequestSpec_getOpSpecID (
  LLRP_tSClientRequestSpec *pThis);

extern LLRP_tResultCode
LLRP_ClientRequestSpec_setOpSpecID (
  LLRP_tSClientRequestSpec *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SAccessReportSpec
{
    LLRP_tSParameter hdr;
  
    LLRP_tEAccessReportTriggerType eAccessReportTrigger;

  
    LLRP_tSReportDestination * pReportDestination;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdAccessReportSpec;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAccessReportSpec[];

extern LLRP_tSAccessReportSpec *
LLRP_AccessReportSpec_construct (void);

extern void
LLRP_AccessReportSpec_destruct (
 LLRP_tSAccessReportSpec * pThis);

extern void
LLRP_AccessReportSpec_decodeFields (
 LLRP_tSAccessReportSpec * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AccessReportSpec_assimilateSubParameters (
 LLRP_tSAccessReportSpec * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AccessReportSpec_encode (
  const LLRP_tSAccessReportSpec *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAccessReportSpec_AccessReportTrigger;

extern LLRP_tEAccessReportTriggerType
LLRP_AccessReportSpec_getAccessReportTrigger (
  LLRP_tSAccessReportSpec *pThis);

extern LLRP_tResultCode
LLRP_AccessReportSpec_setAccessReportTrigger (
  LLRP_tSAccessReportSpec *pThis,
  LLRP_tEAccessReportTriggerType Value);

  
extern LLRP_tSReportDestination *
LLRP_AccessReportSpec_getReportDestination (
  LLRP_tSAccessReportSpec *pThis);

extern LLRP_tResultCode
LLRP_AccessReportSpec_setReportDestination (
  LLRP_tSAccessReportSpec *pThis,
  LLRP_tSReportDestination *pValue);



  
struct LLRP_SHbWriteSpec
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t OpSpecID;

    LLRP_tEMemoryBankID eMemoryBankID;

    llrp_u16_t Pointer;

    llrp_u16v_t Data;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdHbWriteSpec;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHbWriteSpec[];

extern LLRP_tSHbWriteSpec *
LLRP_HbWriteSpec_construct (void);

extern void
LLRP_HbWriteSpec_destruct (
 LLRP_tSHbWriteSpec * pThis);

extern void
LLRP_HbWriteSpec_decodeFields (
 LLRP_tSHbWriteSpec * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HbWriteSpec_assimilateSubParameters (
 LLRP_tSHbWriteSpec * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HbWriteSpec_encode (
  const LLRP_tSHbWriteSpec *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdHbWriteSpec_OpSpecID;

extern llrp_u16_t
LLRP_HbWriteSpec_getOpSpecID (
  LLRP_tSHbWriteSpec *pThis);

extern LLRP_tResultCode
LLRP_HbWriteSpec_setOpSpecID (
  LLRP_tSHbWriteSpec *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHbWriteSpec_MemoryBankID;

extern LLRP_tEMemoryBankID
LLRP_HbWriteSpec_getMemoryBankID (
  LLRP_tSHbWriteSpec *pThis);

extern LLRP_tResultCode
LLRP_HbWriteSpec_setMemoryBankID (
  LLRP_tSHbWriteSpec *pThis,
  LLRP_tEMemoryBankID Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHbWriteSpec_Pointer;

extern llrp_u16_t
LLRP_HbWriteSpec_getPointer (
  LLRP_tSHbWriteSpec *pThis);

extern LLRP_tResultCode
LLRP_HbWriteSpec_setPointer (
  LLRP_tSHbWriteSpec *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHbWriteSpec_Data;

extern llrp_u16v_t
LLRP_HbWriteSpec_getData (
  LLRP_tSHbWriteSpec *pThis);

extern LLRP_tResultCode
LLRP_HbWriteSpec_setData (
  LLRP_tSHbWriteSpec *pThis,
  llrp_u16v_t Value);

  


  
struct LLRP_SHbPrivateWriteSpec
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t OpSpecID;

    llrp_u8_t WriteType;

    llrp_u16v_t Data;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdHbPrivateWriteSpec;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHbPrivateWriteSpec[];

extern LLRP_tSHbPrivateWriteSpec *
LLRP_HbPrivateWriteSpec_construct (void);

extern void
LLRP_HbPrivateWriteSpec_destruct (
 LLRP_tSHbPrivateWriteSpec * pThis);

extern void
LLRP_HbPrivateWriteSpec_decodeFields (
 LLRP_tSHbPrivateWriteSpec * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HbPrivateWriteSpec_assimilateSubParameters (
 LLRP_tSHbPrivateWriteSpec * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HbPrivateWriteSpec_encode (
  const LLRP_tSHbPrivateWriteSpec *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdHbPrivateWriteSpec_OpSpecID;

extern llrp_u16_t
LLRP_HbPrivateWriteSpec_getOpSpecID (
  LLRP_tSHbPrivateWriteSpec *pThis);

extern LLRP_tResultCode
LLRP_HbPrivateWriteSpec_setOpSpecID (
  LLRP_tSHbPrivateWriteSpec *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHbPrivateWriteSpec_WriteType;

extern llrp_u8_t
LLRP_HbPrivateWriteSpec_getWriteType (
  LLRP_tSHbPrivateWriteSpec *pThis);

extern LLRP_tResultCode
LLRP_HbPrivateWriteSpec_setWriteType (
  LLRP_tSHbPrivateWriteSpec *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHbPrivateWriteSpec_Data;

extern llrp_u16v_t
LLRP_HbPrivateWriteSpec_getData (
  LLRP_tSHbPrivateWriteSpec *pThis);

extern LLRP_tResultCode
LLRP_HbPrivateWriteSpec_setData (
  LLRP_tSHbPrivateWriteSpec *pThis,
  llrp_u16v_t Value);

  


  
struct LLRP_STagReportData
{
    LLRP_tSParameter hdr;
  
    llrp_u8v_t TID;

  
    LLRP_tSSelectSpecID * pSelectSpecID;

    LLRP_tSSpecIndex * pSpecIndex;

    LLRP_tSRfSpecID * pRfSpecID;

    LLRP_tSAntennaID * pAntennaID;

    LLRP_tSPeakRSSI * pPeakRSSI;

    LLRP_tSFirstSeenTimestampUTC * pFirstSeenTimestampUTC;

    LLRP_tSLastSeenTimestampUTC * pLastSeenTimestampUTC;

    LLRP_tSTagSeenCount * pTagSeenCount;

    LLRP_tSAccessSpecID * pAccessSpecID;

    LLRP_tSSelectSpecResult * pSelectSpecResult;

    LLRP_tSParameter * listAccessSpecResult;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdTagReportData;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdTagReportData[];

extern LLRP_tSTagReportData *
LLRP_TagReportData_construct (void);

extern void
LLRP_TagReportData_destruct (
 LLRP_tSTagReportData * pThis);

extern void
LLRP_TagReportData_decodeFields (
 LLRP_tSTagReportData * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_TagReportData_assimilateSubParameters (
 LLRP_tSTagReportData * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_TagReportData_encode (
  const LLRP_tSTagReportData *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdTagReportData_TID;

extern llrp_u8v_t
LLRP_TagReportData_getTID (
  LLRP_tSTagReportData *pThis);

extern LLRP_tResultCode
LLRP_TagReportData_setTID (
  LLRP_tSTagReportData *pThis,
  llrp_u8v_t Value);

  
extern LLRP_tSSelectSpecID *
LLRP_TagReportData_getSelectSpecID (
  LLRP_tSTagReportData *pThis);

extern LLRP_tResultCode
LLRP_TagReportData_setSelectSpecID (
  LLRP_tSTagReportData *pThis,
  LLRP_tSSelectSpecID *pValue);

extern LLRP_tSSpecIndex *
LLRP_TagReportData_getSpecIndex (
  LLRP_tSTagReportData *pThis);

extern LLRP_tResultCode
LLRP_TagReportData_setSpecIndex (
  LLRP_tSTagReportData *pThis,
  LLRP_tSSpecIndex *pValue);

extern LLRP_tSRfSpecID *
LLRP_TagReportData_getRfSpecID (
  LLRP_tSTagReportData *pThis);

extern LLRP_tResultCode
LLRP_TagReportData_setRfSpecID (
  LLRP_tSTagReportData *pThis,
  LLRP_tSRfSpecID *pValue);

extern LLRP_tSAntennaID *
LLRP_TagReportData_getAntennaID (
  LLRP_tSTagReportData *pThis);

extern LLRP_tResultCode
LLRP_TagReportData_setAntennaID (
  LLRP_tSTagReportData *pThis,
  LLRP_tSAntennaID *pValue);

extern LLRP_tSPeakRSSI *
LLRP_TagReportData_getPeakRSSI (
  LLRP_tSTagReportData *pThis);

extern LLRP_tResultCode
LLRP_TagReportData_setPeakRSSI (
  LLRP_tSTagReportData *pThis,
  LLRP_tSPeakRSSI *pValue);

extern LLRP_tSFirstSeenTimestampUTC *
LLRP_TagReportData_getFirstSeenTimestampUTC (
  LLRP_tSTagReportData *pThis);

extern LLRP_tResultCode
LLRP_TagReportData_setFirstSeenTimestampUTC (
  LLRP_tSTagReportData *pThis,
  LLRP_tSFirstSeenTimestampUTC *pValue);

extern LLRP_tSLastSeenTimestampUTC *
LLRP_TagReportData_getLastSeenTimestampUTC (
  LLRP_tSTagReportData *pThis);

extern LLRP_tResultCode
LLRP_TagReportData_setLastSeenTimestampUTC (
  LLRP_tSTagReportData *pThis,
  LLRP_tSLastSeenTimestampUTC *pValue);

extern LLRP_tSTagSeenCount *
LLRP_TagReportData_getTagSeenCount (
  LLRP_tSTagReportData *pThis);

extern LLRP_tResultCode
LLRP_TagReportData_setTagSeenCount (
  LLRP_tSTagReportData *pThis,
  LLRP_tSTagSeenCount *pValue);

extern LLRP_tSAccessSpecID *
LLRP_TagReportData_getAccessSpecID (
  LLRP_tSTagReportData *pThis);

extern LLRP_tResultCode
LLRP_TagReportData_setAccessSpecID (
  LLRP_tSTagReportData *pThis,
  LLRP_tSAccessSpecID *pValue);

extern LLRP_tSSelectSpecResult *
LLRP_TagReportData_getSelectSpecResult (
  LLRP_tSTagReportData *pThis);

extern LLRP_tResultCode
LLRP_TagReportData_setSelectSpecResult (
  LLRP_tSTagReportData *pThis,
  LLRP_tSSelectSpecResult *pValue);

extern LLRP_tSParameter *
LLRP_TagReportData_beginAccessSpecResult (
  LLRP_tSTagReportData *pThis);

extern LLRP_tSParameter *
LLRP_TagReportData_nextAccessSpecResult (
  LLRP_tSParameter *pCurrent);

extern void
LLRP_TagReportData_clearAccessSpecResult (
  LLRP_tSTagReportData *pThis);

extern int
LLRP_TagReportData_countAccessSpecResult (
  LLRP_tSTagReportData *pThis);

extern LLRP_tResultCode
LLRP_TagReportData_addAccessSpecResult (
  LLRP_tSTagReportData *pThis,
  LLRP_tSParameter *pValue);




  
struct LLRP_SSelectSpecID
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t SelectSpecID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSelectSpecID;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSelectSpecID[];

extern LLRP_tSSelectSpecID *
LLRP_SelectSpecID_construct (void);

extern void
LLRP_SelectSpecID_destruct (
 LLRP_tSSelectSpecID * pThis);

extern void
LLRP_SelectSpecID_decodeFields (
 LLRP_tSSelectSpecID * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SelectSpecID_assimilateSubParameters (
 LLRP_tSSelectSpecID * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SelectSpecID_encode (
  const LLRP_tSSelectSpecID *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSelectSpecID_SelectSpecID;

extern llrp_u32_t
LLRP_SelectSpecID_getSelectSpecID (
  LLRP_tSSelectSpecID *pThis);

extern LLRP_tResultCode
LLRP_SelectSpecID_setSelectSpecID (
  LLRP_tSSelectSpecID *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SSpecIndex
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t SpecIndex;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSpecIndex;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSpecIndex[];

extern LLRP_tSSpecIndex *
LLRP_SpecIndex_construct (void);

extern void
LLRP_SpecIndex_destruct (
 LLRP_tSSpecIndex * pThis);

extern void
LLRP_SpecIndex_decodeFields (
 LLRP_tSSpecIndex * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SpecIndex_assimilateSubParameters (
 LLRP_tSSpecIndex * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SpecIndex_encode (
  const LLRP_tSSpecIndex *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSpecIndex_SpecIndex;

extern llrp_u16_t
LLRP_SpecIndex_getSpecIndex (
  LLRP_tSSpecIndex *pThis);

extern LLRP_tResultCode
LLRP_SpecIndex_setSpecIndex (
  LLRP_tSSpecIndex *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SRfSpecID
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t RfSpecID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdRfSpecID;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRfSpecID[];

extern LLRP_tSRfSpecID *
LLRP_RfSpecID_construct (void);

extern void
LLRP_RfSpecID_destruct (
 LLRP_tSRfSpecID * pThis);

extern void
LLRP_RfSpecID_decodeFields (
 LLRP_tSRfSpecID * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RfSpecID_assimilateSubParameters (
 LLRP_tSRfSpecID * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RfSpecID_encode (
  const LLRP_tSRfSpecID *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdRfSpecID_RfSpecID;

extern llrp_u16_t
LLRP_RfSpecID_getRfSpecID (
  LLRP_tSRfSpecID *pThis);

extern LLRP_tResultCode
LLRP_RfSpecID_setRfSpecID (
  LLRP_tSRfSpecID *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SAntennaID
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t AntennaID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdAntennaID;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAntennaID[];

extern LLRP_tSAntennaID *
LLRP_AntennaID_construct (void);

extern void
LLRP_AntennaID_destruct (
 LLRP_tSAntennaID * pThis);

extern void
LLRP_AntennaID_decodeFields (
 LLRP_tSAntennaID * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AntennaID_assimilateSubParameters (
 LLRP_tSAntennaID * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AntennaID_encode (
  const LLRP_tSAntennaID *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAntennaID_AntennaID;

extern llrp_u8_t
LLRP_AntennaID_getAntennaID (
  LLRP_tSAntennaID *pThis);

extern LLRP_tResultCode
LLRP_AntennaID_setAntennaID (
  LLRP_tSAntennaID *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SPeakRSSI
{
    LLRP_tSParameter hdr;
  
    llrp_s8_t PeakRSSI;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdPeakRSSI;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdPeakRSSI[];

extern LLRP_tSPeakRSSI *
LLRP_PeakRSSI_construct (void);

extern void
LLRP_PeakRSSI_destruct (
 LLRP_tSPeakRSSI * pThis);

extern void
LLRP_PeakRSSI_decodeFields (
 LLRP_tSPeakRSSI * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_PeakRSSI_assimilateSubParameters (
 LLRP_tSPeakRSSI * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_PeakRSSI_encode (
  const LLRP_tSPeakRSSI *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdPeakRSSI_PeakRSSI;

extern llrp_s8_t
LLRP_PeakRSSI_getPeakRSSI (
  LLRP_tSPeakRSSI *pThis);

extern LLRP_tResultCode
LLRP_PeakRSSI_setPeakRSSI (
  LLRP_tSPeakRSSI *pThis,
  llrp_s8_t Value);

  


  
struct LLRP_SFirstSeenTimestampUTC
{
    LLRP_tSParameter hdr;
  
    llrp_u64_t Microseconds;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdFirstSeenTimestampUTC;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdFirstSeenTimestampUTC[];

extern LLRP_tSFirstSeenTimestampUTC *
LLRP_FirstSeenTimestampUTC_construct (void);

extern void
LLRP_FirstSeenTimestampUTC_destruct (
 LLRP_tSFirstSeenTimestampUTC * pThis);

extern void
LLRP_FirstSeenTimestampUTC_decodeFields (
 LLRP_tSFirstSeenTimestampUTC * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_FirstSeenTimestampUTC_assimilateSubParameters (
 LLRP_tSFirstSeenTimestampUTC * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_FirstSeenTimestampUTC_encode (
  const LLRP_tSFirstSeenTimestampUTC *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdFirstSeenTimestampUTC_Microseconds;

extern llrp_u64_t
LLRP_FirstSeenTimestampUTC_getMicroseconds (
  LLRP_tSFirstSeenTimestampUTC *pThis);

extern LLRP_tResultCode
LLRP_FirstSeenTimestampUTC_setMicroseconds (
  LLRP_tSFirstSeenTimestampUTC *pThis,
  llrp_u64_t Value);

  


  
struct LLRP_SLastSeenTimestampUTC
{
    LLRP_tSParameter hdr;
  
    llrp_u64_t Microseconds;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdLastSeenTimestampUTC;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdLastSeenTimestampUTC[];

extern LLRP_tSLastSeenTimestampUTC *
LLRP_LastSeenTimestampUTC_construct (void);

extern void
LLRP_LastSeenTimestampUTC_destruct (
 LLRP_tSLastSeenTimestampUTC * pThis);

extern void
LLRP_LastSeenTimestampUTC_decodeFields (
 LLRP_tSLastSeenTimestampUTC * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_LastSeenTimestampUTC_assimilateSubParameters (
 LLRP_tSLastSeenTimestampUTC * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_LastSeenTimestampUTC_encode (
  const LLRP_tSLastSeenTimestampUTC *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdLastSeenTimestampUTC_Microseconds;

extern llrp_u64_t
LLRP_LastSeenTimestampUTC_getMicroseconds (
  LLRP_tSLastSeenTimestampUTC *pThis);

extern LLRP_tResultCode
LLRP_LastSeenTimestampUTC_setMicroseconds (
  LLRP_tSLastSeenTimestampUTC *pThis,
  llrp_u64_t Value);

  


  
struct LLRP_STagSeenCount
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t TagCount;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdTagSeenCount;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdTagSeenCount[];

extern LLRP_tSTagSeenCount *
LLRP_TagSeenCount_construct (void);

extern void
LLRP_TagSeenCount_destruct (
 LLRP_tSTagSeenCount * pThis);

extern void
LLRP_TagSeenCount_decodeFields (
 LLRP_tSTagSeenCount * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_TagSeenCount_assimilateSubParameters (
 LLRP_tSTagSeenCount * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_TagSeenCount_encode (
  const LLRP_tSTagSeenCount *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdTagSeenCount_TagCount;

extern llrp_u16_t
LLRP_TagSeenCount_getTagCount (
  LLRP_tSTagSeenCount *pThis);

extern LLRP_tResultCode
LLRP_TagSeenCount_setTagCount (
  LLRP_tSTagSeenCount *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SAccessSpecID
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t AccessSpecID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdAccessSpecID;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAccessSpecID[];

extern LLRP_tSAccessSpecID *
LLRP_AccessSpecID_construct (void);

extern void
LLRP_AccessSpecID_destruct (
 LLRP_tSAccessSpecID * pThis);

extern void
LLRP_AccessSpecID_decodeFields (
 LLRP_tSAccessSpecID * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AccessSpecID_assimilateSubParameters (
 LLRP_tSAccessSpecID * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AccessSpecID_encode (
  const LLRP_tSAccessSpecID *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAccessSpecID_AccessSpecID;

extern llrp_u32_t
LLRP_AccessSpecID_getAccessSpecID (
  LLRP_tSAccessSpecID *pThis);

extern LLRP_tResultCode
LLRP_AccessSpecID_setAccessSpecID (
  LLRP_tSAccessSpecID *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SSelectSpecResult
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t Result;

    llrp_u16v_t TagData;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSelectSpecResult;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSelectSpecResult[];

extern LLRP_tSSelectSpecResult *
LLRP_SelectSpecResult_construct (void);

extern void
LLRP_SelectSpecResult_destruct (
 LLRP_tSSelectSpecResult * pThis);

extern void
LLRP_SelectSpecResult_decodeFields (
 LLRP_tSSelectSpecResult * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SelectSpecResult_assimilateSubParameters (
 LLRP_tSSelectSpecResult * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SelectSpecResult_encode (
  const LLRP_tSSelectSpecResult *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSelectSpecResult_Result;

extern llrp_u8_t
LLRP_SelectSpecResult_getResult (
  LLRP_tSSelectSpecResult *pThis);

extern LLRP_tResultCode
LLRP_SelectSpecResult_setResult (
  LLRP_tSSelectSpecResult *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSelectSpecResult_TagData;

extern llrp_u16v_t
LLRP_SelectSpecResult_getTagData (
  LLRP_tSSelectSpecResult *pThis);

extern LLRP_tResultCode
LLRP_SelectSpecResult_setTagData (
  LLRP_tSSelectSpecResult *pThis,
  llrp_u16v_t Value);

  


  
struct LLRP_SHbReadSpecResult
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t Result;

    llrp_u16_t OpSpecID;

    llrp_u16v_t ReadData;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdHbReadSpecResult;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHbReadSpecResult[];

extern LLRP_tSHbReadSpecResult *
LLRP_HbReadSpecResult_construct (void);

extern void
LLRP_HbReadSpecResult_destruct (
 LLRP_tSHbReadSpecResult * pThis);

extern void
LLRP_HbReadSpecResult_decodeFields (
 LLRP_tSHbReadSpecResult * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HbReadSpecResult_assimilateSubParameters (
 LLRP_tSHbReadSpecResult * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HbReadSpecResult_encode (
  const LLRP_tSHbReadSpecResult *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdHbReadSpecResult_Result;

extern llrp_u8_t
LLRP_HbReadSpecResult_getResult (
  LLRP_tSHbReadSpecResult *pThis);

extern LLRP_tResultCode
LLRP_HbReadSpecResult_setResult (
  LLRP_tSHbReadSpecResult *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHbReadSpecResult_OpSpecID;

extern llrp_u16_t
LLRP_HbReadSpecResult_getOpSpecID (
  LLRP_tSHbReadSpecResult *pThis);

extern LLRP_tResultCode
LLRP_HbReadSpecResult_setOpSpecID (
  LLRP_tSHbReadSpecResult *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHbReadSpecResult_ReadData;

extern llrp_u16v_t
LLRP_HbReadSpecResult_getReadData (
  LLRP_tSHbReadSpecResult *pThis);

extern LLRP_tResultCode
LLRP_HbReadSpecResult_setReadData (
  LLRP_tSHbReadSpecResult *pThis,
  llrp_u16v_t Value);

  


  
struct LLRP_SClientRequestSpecResult
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t OpSpecID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdClientRequestSpecResult;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdClientRequestSpecResult[];

extern LLRP_tSClientRequestSpecResult *
LLRP_ClientRequestSpecResult_construct (void);

extern void
LLRP_ClientRequestSpecResult_destruct (
 LLRP_tSClientRequestSpecResult * pThis);

extern void
LLRP_ClientRequestSpecResult_decodeFields (
 LLRP_tSClientRequestSpecResult * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ClientRequestSpecResult_assimilateSubParameters (
 LLRP_tSClientRequestSpecResult * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ClientRequestSpecResult_encode (
  const LLRP_tSClientRequestSpecResult *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdClientRequestSpecResult_OpSpecID;

extern llrp_u16_t
LLRP_ClientRequestSpecResult_getOpSpecID (
  LLRP_tSClientRequestSpecResult *pThis);

extern LLRP_tResultCode
LLRP_ClientRequestSpecResult_setOpSpecID (
  LLRP_tSClientRequestSpecResult *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SHbWriteSpecResult
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t Result;

    llrp_u8v_t ResultDescription;

    llrp_u16_t OpSpecID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdHbWriteSpecResult;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHbWriteSpecResult[];

extern LLRP_tSHbWriteSpecResult *
LLRP_HbWriteSpecResult_construct (void);

extern void
LLRP_HbWriteSpecResult_destruct (
 LLRP_tSHbWriteSpecResult * pThis);

extern void
LLRP_HbWriteSpecResult_decodeFields (
 LLRP_tSHbWriteSpecResult * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HbWriteSpecResult_assimilateSubParameters (
 LLRP_tSHbWriteSpecResult * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HbWriteSpecResult_encode (
  const LLRP_tSHbWriteSpecResult *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdHbWriteSpecResult_Result;

extern llrp_u8_t
LLRP_HbWriteSpecResult_getResult (
  LLRP_tSHbWriteSpecResult *pThis);

extern LLRP_tResultCode
LLRP_HbWriteSpecResult_setResult (
  LLRP_tSHbWriteSpecResult *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHbWriteSpecResult_ResultDescription;

extern llrp_u8v_t
LLRP_HbWriteSpecResult_getResultDescription (
  LLRP_tSHbWriteSpecResult *pThis);

extern LLRP_tResultCode
LLRP_HbWriteSpecResult_setResultDescription (
  LLRP_tSHbWriteSpecResult *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHbWriteSpecResult_OpSpecID;

extern llrp_u16_t
LLRP_HbWriteSpecResult_getOpSpecID (
  LLRP_tSHbWriteSpecResult *pThis);

extern LLRP_tResultCode
LLRP_HbWriteSpecResult_setOpSpecID (
  LLRP_tSHbWriteSpecResult *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SHbPrivateWriteSpecResult
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t Result;

    llrp_u8v_t ResultDescription;

    llrp_u16_t OpSpecID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdHbPrivateWriteSpecResult;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHbPrivateWriteSpecResult[];

extern LLRP_tSHbPrivateWriteSpecResult *
LLRP_HbPrivateWriteSpecResult_construct (void);

extern void
LLRP_HbPrivateWriteSpecResult_destruct (
 LLRP_tSHbPrivateWriteSpecResult * pThis);

extern void
LLRP_HbPrivateWriteSpecResult_decodeFields (
 LLRP_tSHbPrivateWriteSpecResult * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HbPrivateWriteSpecResult_assimilateSubParameters (
 LLRP_tSHbPrivateWriteSpecResult * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HbPrivateWriteSpecResult_encode (
  const LLRP_tSHbPrivateWriteSpecResult *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdHbPrivateWriteSpecResult_Result;

extern llrp_u8_t
LLRP_HbPrivateWriteSpecResult_getResult (
  LLRP_tSHbPrivateWriteSpecResult *pThis);

extern LLRP_tResultCode
LLRP_HbPrivateWriteSpecResult_setResult (
  LLRP_tSHbPrivateWriteSpecResult *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHbPrivateWriteSpecResult_ResultDescription;

extern llrp_u8v_t
LLRP_HbPrivateWriteSpecResult_getResultDescription (
  LLRP_tSHbPrivateWriteSpecResult *pThis);

extern LLRP_tResultCode
LLRP_HbPrivateWriteSpecResult_setResultDescription (
  LLRP_tSHbPrivateWriteSpecResult *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHbPrivateWriteSpecResult_OpSpecID;

extern llrp_u16_t
LLRP_HbPrivateWriteSpecResult_getOpSpecID (
  LLRP_tSHbPrivateWriteSpecResult *pThis);

extern LLRP_tResultCode
LLRP_HbPrivateWriteSpecResult_setOpSpecID (
  LLRP_tSHbPrivateWriteSpecResult *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SClientRequestAck
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t AccessSpecID;

    llrp_u8v_t TID;

  
    LLRP_tSParameter * listOpSpec;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdClientRequestAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdClientRequestAck[];

extern LLRP_tSClientRequestAck *
LLRP_ClientRequestAck_construct (void);

extern void
LLRP_ClientRequestAck_destruct (
 LLRP_tSClientRequestAck * pThis);

extern void
LLRP_ClientRequestAck_decodeFields (
 LLRP_tSClientRequestAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ClientRequestAck_assimilateSubParameters (
 LLRP_tSClientRequestAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ClientRequestAck_encode (
  const LLRP_tSClientRequestAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdClientRequestAck_AccessSpecID;

extern llrp_u32_t
LLRP_ClientRequestAck_getAccessSpecID (
  LLRP_tSClientRequestAck *pThis);

extern LLRP_tResultCode
LLRP_ClientRequestAck_setAccessSpecID (
  LLRP_tSClientRequestAck *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdClientRequestAck_TID;

extern llrp_u8v_t
LLRP_ClientRequestAck_getTID (
  LLRP_tSClientRequestAck *pThis);

extern LLRP_tResultCode
LLRP_ClientRequestAck_setTID (
  LLRP_tSClientRequestAck *pThis,
  llrp_u8v_t Value);

  
extern LLRP_tSParameter *
LLRP_ClientRequestAck_beginOpSpec (
  LLRP_tSClientRequestAck *pThis);

extern LLRP_tSParameter *
LLRP_ClientRequestAck_nextOpSpec (
  LLRP_tSParameter *pCurrent);

extern void
LLRP_ClientRequestAck_clearOpSpec (
  LLRP_tSClientRequestAck *pThis);

extern int
LLRP_ClientRequestAck_countOpSpec (
  LLRP_tSClientRequestAck *pThis);

extern LLRP_tResultCode
LLRP_ClientRequestAck_addOpSpec (
  LLRP_tSClientRequestAck *pThis,
  LLRP_tSParameter *pValue);




  
struct LLRP_STagLog
{
    LLRP_tSParameter hdr;
  
    llrp_u64_t LogSequence;

    llrp_u8v_t TID;

    llrp_u8v_t CardID;

    llrp_u32_t OpNum;

  
    LLRP_tSUTCTimestamp * pUTCTimestamp;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdTagLog;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdTagLog[];

extern LLRP_tSTagLog *
LLRP_TagLog_construct (void);

extern void
LLRP_TagLog_destruct (
 LLRP_tSTagLog * pThis);

extern void
LLRP_TagLog_decodeFields (
 LLRP_tSTagLog * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_TagLog_assimilateSubParameters (
 LLRP_tSTagLog * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_TagLog_encode (
  const LLRP_tSTagLog *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdTagLog_LogSequence;

extern llrp_u64_t
LLRP_TagLog_getLogSequence (
  LLRP_tSTagLog *pThis);

extern LLRP_tResultCode
LLRP_TagLog_setLogSequence (
  LLRP_tSTagLog *pThis,
  llrp_u64_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTagLog_TID;

extern llrp_u8v_t
LLRP_TagLog_getTID (
  LLRP_tSTagLog *pThis);

extern LLRP_tResultCode
LLRP_TagLog_setTID (
  LLRP_tSTagLog *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTagLog_CardID;

extern llrp_u8v_t
LLRP_TagLog_getCardID (
  LLRP_tSTagLog *pThis);

extern LLRP_tResultCode
LLRP_TagLog_setCardID (
  LLRP_tSTagLog *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTagLog_OpNum;

extern llrp_u32_t
LLRP_TagLog_getOpNum (
  LLRP_tSTagLog *pThis);

extern LLRP_tResultCode
LLRP_TagLog_setOpNum (
  LLRP_tSTagLog *pThis,
  llrp_u32_t Value);

  
extern LLRP_tSUTCTimestamp *
LLRP_TagLog_getUTCTimestamp (
  LLRP_tSTagLog *pThis);

extern LLRP_tResultCode
LLRP_TagLog_setUTCTimestamp (
  LLRP_tSTagLog *pThis,
  LLRP_tSUTCTimestamp *pValue);



  
struct LLRP_SStartLogTimestamp
{
    LLRP_tSParameter hdr;
  
    llrp_u64_t Microseconds;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdStartLogTimestamp;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdStartLogTimestamp[];

extern LLRP_tSStartLogTimestamp *
LLRP_StartLogTimestamp_construct (void);

extern void
LLRP_StartLogTimestamp_destruct (
 LLRP_tSStartLogTimestamp * pThis);

extern void
LLRP_StartLogTimestamp_decodeFields (
 LLRP_tSStartLogTimestamp * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_StartLogTimestamp_assimilateSubParameters (
 LLRP_tSStartLogTimestamp * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_StartLogTimestamp_encode (
  const LLRP_tSStartLogTimestamp *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdStartLogTimestamp_Microseconds;

extern llrp_u64_t
LLRP_StartLogTimestamp_getMicroseconds (
  LLRP_tSStartLogTimestamp *pThis);

extern LLRP_tResultCode
LLRP_StartLogTimestamp_setMicroseconds (
  LLRP_tSStartLogTimestamp *pThis,
  llrp_u64_t Value);

  


  
struct LLRP_SEndLogTimestamp
{
    LLRP_tSParameter hdr;
  
    llrp_u64_t Microseconds;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdEndLogTimestamp;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdEndLogTimestamp[];

extern LLRP_tSEndLogTimestamp *
LLRP_EndLogTimestamp_construct (void);

extern void
LLRP_EndLogTimestamp_destruct (
 LLRP_tSEndLogTimestamp * pThis);

extern void
LLRP_EndLogTimestamp_decodeFields (
 LLRP_tSEndLogTimestamp * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_EndLogTimestamp_assimilateSubParameters (
 LLRP_tSEndLogTimestamp * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_EndLogTimestamp_encode (
  const LLRP_tSEndLogTimestamp *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdEndLogTimestamp_Microseconds;

extern llrp_u64_t
LLRP_EndLogTimestamp_getMicroseconds (
  LLRP_tSEndLogTimestamp *pThis);

extern LLRP_tResultCode
LLRP_EndLogTimestamp_setMicroseconds (
  LLRP_tSEndLogTimestamp *pThis,
  llrp_u64_t Value);

  


  
struct LLRP_SDeviceLog
{
    LLRP_tSParameter hdr;
  
    llrp_u64_t LogSequence;

    LLRP_tELogType eLogType;

    llrp_u32_t LogCode;

    llrp_utf8v_t LogDescInfo;

  
    LLRP_tSUTCTimestamp * pUTCTimestamp;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdDeviceLog;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDeviceLog[];

extern LLRP_tSDeviceLog *
LLRP_DeviceLog_construct (void);

extern void
LLRP_DeviceLog_destruct (
 LLRP_tSDeviceLog * pThis);

extern void
LLRP_DeviceLog_decodeFields (
 LLRP_tSDeviceLog * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DeviceLog_assimilateSubParameters (
 LLRP_tSDeviceLog * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DeviceLog_encode (
  const LLRP_tSDeviceLog *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdDeviceLog_LogSequence;

extern llrp_u64_t
LLRP_DeviceLog_getLogSequence (
  LLRP_tSDeviceLog *pThis);

extern LLRP_tResultCode
LLRP_DeviceLog_setLogSequence (
  LLRP_tSDeviceLog *pThis,
  llrp_u64_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdDeviceLog_LogType;

extern LLRP_tELogType
LLRP_DeviceLog_getLogType (
  LLRP_tSDeviceLog *pThis);

extern LLRP_tResultCode
LLRP_DeviceLog_setLogType (
  LLRP_tSDeviceLog *pThis,
  LLRP_tELogType Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdDeviceLog_LogCode;

extern llrp_u32_t
LLRP_DeviceLog_getLogCode (
  LLRP_tSDeviceLog *pThis);

extern LLRP_tResultCode
LLRP_DeviceLog_setLogCode (
  LLRP_tSDeviceLog *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdDeviceLog_LogDescInfo;

extern llrp_utf8v_t
LLRP_DeviceLog_getLogDescInfo (
  LLRP_tSDeviceLog *pThis);

extern LLRP_tResultCode
LLRP_DeviceLog_setLogDescInfo (
  LLRP_tSDeviceLog *pThis,
  llrp_utf8v_t Value);

  
extern LLRP_tSUTCTimestamp *
LLRP_DeviceLog_getUTCTimestamp (
  LLRP_tSDeviceLog *pThis);

extern LLRP_tResultCode
LLRP_DeviceLog_setUTCTimestamp (
  LLRP_tSDeviceLog *pThis,
  LLRP_tSUTCTimestamp *pValue);



  
struct LLRP_SDeviceEventNotificationSpec
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSEventNotificationState * pEventNotificationState;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdDeviceEventNotificationSpec;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDeviceEventNotificationSpec[];

extern LLRP_tSDeviceEventNotificationSpec *
LLRP_DeviceEventNotificationSpec_construct (void);

extern void
LLRP_DeviceEventNotificationSpec_destruct (
 LLRP_tSDeviceEventNotificationSpec * pThis);

extern void
LLRP_DeviceEventNotificationSpec_decodeFields (
 LLRP_tSDeviceEventNotificationSpec * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DeviceEventNotificationSpec_assimilateSubParameters (
 LLRP_tSDeviceEventNotificationSpec * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DeviceEventNotificationSpec_encode (
  const LLRP_tSDeviceEventNotificationSpec *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSEventNotificationState *
LLRP_DeviceEventNotificationSpec_getEventNotificationState (
  LLRP_tSDeviceEventNotificationSpec *pThis);

extern LLRP_tResultCode
LLRP_DeviceEventNotificationSpec_setEventNotificationState (
  LLRP_tSDeviceEventNotificationSpec *pThis,
  LLRP_tSEventNotificationState *pValue);



  
struct LLRP_SEventNotificationState
{
    LLRP_tSParameter hdr;
  
    LLRP_tENotificationEventType eEventType;

    LLRP_tENotificationState eNotificationState;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdEventNotificationState;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdEventNotificationState[];

extern LLRP_tSEventNotificationState *
LLRP_EventNotificationState_construct (void);

extern void
LLRP_EventNotificationState_destruct (
 LLRP_tSEventNotificationState * pThis);

extern void
LLRP_EventNotificationState_decodeFields (
 LLRP_tSEventNotificationState * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_EventNotificationState_assimilateSubParameters (
 LLRP_tSEventNotificationState * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_EventNotificationState_encode (
  const LLRP_tSEventNotificationState *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdEventNotificationState_EventType;

extern LLRP_tENotificationEventType
LLRP_EventNotificationState_getEventType (
  LLRP_tSEventNotificationState *pThis);

extern LLRP_tResultCode
LLRP_EventNotificationState_setEventType (
  LLRP_tSEventNotificationState *pThis,
  LLRP_tENotificationEventType Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdEventNotificationState_NotificationState;

extern LLRP_tENotificationState
LLRP_EventNotificationState_getNotificationState (
  LLRP_tSEventNotificationState *pThis);

extern LLRP_tResultCode
LLRP_EventNotificationState_setNotificationState (
  LLRP_tSEventNotificationState *pThis,
  LLRP_tENotificationState Value);

  


  
struct LLRP_SAntennaProperties
{
    LLRP_tSParameter hdr;
  
    llrp_u1_t AntennaConnected;

    llrp_u8_t AntennaID;

    llrp_s16_t AntennaGain;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdAntennaProperties;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAntennaProperties[];

extern LLRP_tSAntennaProperties *
LLRP_AntennaProperties_construct (void);

extern void
LLRP_AntennaProperties_destruct (
 LLRP_tSAntennaProperties * pThis);

extern void
LLRP_AntennaProperties_decodeFields (
 LLRP_tSAntennaProperties * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AntennaProperties_assimilateSubParameters (
 LLRP_tSAntennaProperties * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AntennaProperties_encode (
  const LLRP_tSAntennaProperties *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAntennaProperties_AntennaConnected;

extern llrp_u1_t
LLRP_AntennaProperties_getAntennaConnected (
  LLRP_tSAntennaProperties *pThis);

extern LLRP_tResultCode
LLRP_AntennaProperties_setAntennaConnected (
  LLRP_tSAntennaProperties *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAntennaProperties_AntennaID;

extern llrp_u8_t
LLRP_AntennaProperties_getAntennaID (
  LLRP_tSAntennaProperties *pThis);

extern LLRP_tResultCode
LLRP_AntennaProperties_setAntennaID (
  LLRP_tSAntennaProperties *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAntennaProperties_AntennaGain;

extern llrp_s16_t
LLRP_AntennaProperties_getAntennaGain (
  LLRP_tSAntennaProperties *pThis);

extern LLRP_tResultCode
LLRP_AntennaProperties_setAntennaGain (
  LLRP_tSAntennaProperties *pThis,
  llrp_s16_t Value);

  


  
struct LLRP_SAntennaConfiguration
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t AntennaID;

    llrp_u16_t TransmitPowerIndex;

    llrp_u16v_t FrequencyIndexes;

    llrp_u16_t ForDataRateIndex;

    llrp_u16_t RevDataRateIndex;

    llrp_u16_t ForModulationIndex;

    llrp_u16_t RevDataEncodingIndex;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdAntennaConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAntennaConfiguration[];

extern LLRP_tSAntennaConfiguration *
LLRP_AntennaConfiguration_construct (void);

extern void
LLRP_AntennaConfiguration_destruct (
 LLRP_tSAntennaConfiguration * pThis);

extern void
LLRP_AntennaConfiguration_decodeFields (
 LLRP_tSAntennaConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AntennaConfiguration_assimilateSubParameters (
 LLRP_tSAntennaConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AntennaConfiguration_encode (
  const LLRP_tSAntennaConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAntennaConfiguration_AntennaID;

extern llrp_u8_t
LLRP_AntennaConfiguration_getAntennaID (
  LLRP_tSAntennaConfiguration *pThis);

extern LLRP_tResultCode
LLRP_AntennaConfiguration_setAntennaID (
  LLRP_tSAntennaConfiguration *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAntennaConfiguration_TransmitPowerIndex;

extern llrp_u16_t
LLRP_AntennaConfiguration_getTransmitPowerIndex (
  LLRP_tSAntennaConfiguration *pThis);

extern LLRP_tResultCode
LLRP_AntennaConfiguration_setTransmitPowerIndex (
  LLRP_tSAntennaConfiguration *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAntennaConfiguration_FrequencyIndexes;

extern llrp_u16v_t
LLRP_AntennaConfiguration_getFrequencyIndexes (
  LLRP_tSAntennaConfiguration *pThis);

extern LLRP_tResultCode
LLRP_AntennaConfiguration_setFrequencyIndexes (
  LLRP_tSAntennaConfiguration *pThis,
  llrp_u16v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAntennaConfiguration_ForDataRateIndex;

extern llrp_u16_t
LLRP_AntennaConfiguration_getForDataRateIndex (
  LLRP_tSAntennaConfiguration *pThis);

extern LLRP_tResultCode
LLRP_AntennaConfiguration_setForDataRateIndex (
  LLRP_tSAntennaConfiguration *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAntennaConfiguration_RevDataRateIndex;

extern llrp_u16_t
LLRP_AntennaConfiguration_getRevDataRateIndex (
  LLRP_tSAntennaConfiguration *pThis);

extern LLRP_tResultCode
LLRP_AntennaConfiguration_setRevDataRateIndex (
  LLRP_tSAntennaConfiguration *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAntennaConfiguration_ForModulationIndex;

extern llrp_u16_t
LLRP_AntennaConfiguration_getForModulationIndex (
  LLRP_tSAntennaConfiguration *pThis);

extern LLRP_tResultCode
LLRP_AntennaConfiguration_setForModulationIndex (
  LLRP_tSAntennaConfiguration *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAntennaConfiguration_RevDataEncodingIndex;

extern llrp_u16_t
LLRP_AntennaConfiguration_getRevDataEncodingIndex (
  LLRP_tSAntennaConfiguration *pThis);

extern LLRP_tResultCode
LLRP_AntennaConfiguration_setRevDataEncodingIndex (
  LLRP_tSAntennaConfiguration *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SModuleDepth
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t Index;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdModuleDepth;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdModuleDepth[];

extern LLRP_tSModuleDepth *
LLRP_ModuleDepth_construct (void);

extern void
LLRP_ModuleDepth_destruct (
 LLRP_tSModuleDepth * pThis);

extern void
LLRP_ModuleDepth_decodeFields (
 LLRP_tSModuleDepth * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ModuleDepth_assimilateSubParameters (
 LLRP_tSModuleDepth * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ModuleDepth_encode (
  const LLRP_tSModuleDepth *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdModuleDepth_Index;

extern llrp_u16_t
LLRP_ModuleDepth_getIndex (
  LLRP_tSModuleDepth *pThis);

extern LLRP_tResultCode
LLRP_ModuleDepth_setIndex (
  LLRP_tSModuleDepth *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SIdentification
{
    LLRP_tSParameter hdr;
  
    llrp_utf8v_t DeviceName;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdIdentification;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdIdentification[];

extern LLRP_tSIdentification *
LLRP_Identification_construct (void);

extern void
LLRP_Identification_destruct (
 LLRP_tSIdentification * pThis);

extern void
LLRP_Identification_decodeFields (
 LLRP_tSIdentification * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_Identification_assimilateSubParameters (
 LLRP_tSIdentification * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_Identification_encode (
  const LLRP_tSIdentification *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdIdentification_DeviceName;

extern llrp_utf8v_t
LLRP_Identification_getDeviceName (
  LLRP_tSIdentification *pThis);

extern LLRP_tResultCode
LLRP_Identification_setDeviceName (
  LLRP_tSIdentification *pThis,
  llrp_utf8v_t Value);

  


  
struct LLRP_SAlarmConfiguration
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t AlarmMask;

  
    LLRP_tSAlarmThreshod * pAlarmThreshod;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdAlarmConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAlarmConfiguration[];

extern LLRP_tSAlarmConfiguration *
LLRP_AlarmConfiguration_construct (void);

extern void
LLRP_AlarmConfiguration_destruct (
 LLRP_tSAlarmConfiguration * pThis);

extern void
LLRP_AlarmConfiguration_decodeFields (
 LLRP_tSAlarmConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AlarmConfiguration_assimilateSubParameters (
 LLRP_tSAlarmConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AlarmConfiguration_encode (
  const LLRP_tSAlarmConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmConfiguration_AlarmMask;

extern llrp_u8_t
LLRP_AlarmConfiguration_getAlarmMask (
  LLRP_tSAlarmConfiguration *pThis);

extern LLRP_tResultCode
LLRP_AlarmConfiguration_setAlarmMask (
  LLRP_tSAlarmConfiguration *pThis,
  llrp_u8_t Value);

  
extern LLRP_tSAlarmThreshod *
LLRP_AlarmConfiguration_getAlarmThreshod (
  LLRP_tSAlarmConfiguration *pThis);

extern LLRP_tResultCode
LLRP_AlarmConfiguration_setAlarmThreshod (
  LLRP_tSAlarmConfiguration *pThis,
  LLRP_tSAlarmThreshod *pValue);



  
struct LLRP_SAlarmThreshod
{
    LLRP_tSParameter hdr;
  
    llrp_s8_t TemperatureMaxValue;

    llrp_s8_t TemperatureMinValue;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdAlarmThreshod;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAlarmThreshod[];

extern LLRP_tSAlarmThreshod *
LLRP_AlarmThreshod_construct (void);

extern void
LLRP_AlarmThreshod_destruct (
 LLRP_tSAlarmThreshod * pThis);

extern void
LLRP_AlarmThreshod_decodeFields (
 LLRP_tSAlarmThreshod * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AlarmThreshod_assimilateSubParameters (
 LLRP_tSAlarmThreshod * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AlarmThreshod_encode (
  const LLRP_tSAlarmThreshod *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmThreshod_TemperatureMaxValue;

extern llrp_s8_t
LLRP_AlarmThreshod_getTemperatureMaxValue (
  LLRP_tSAlarmThreshod *pThis);

extern LLRP_tResultCode
LLRP_AlarmThreshod_setTemperatureMaxValue (
  LLRP_tSAlarmThreshod *pThis,
  llrp_s8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmThreshod_TemperatureMinValue;

extern llrp_s8_t
LLRP_AlarmThreshod_getTemperatureMinValue (
  LLRP_tSAlarmThreshod *pThis);

extern LLRP_tResultCode
LLRP_AlarmThreshod_setTemperatureMinValue (
  LLRP_tSAlarmThreshod *pThis,
  llrp_s8_t Value);

  


  
struct LLRP_SCommunicationConfiguration
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSCommLinkConfiguration * listCommLinkConfiguration;

    LLRP_tSParameter * listEthernetConfiguration;

    LLRP_tSSerialPortConfiguration * listSerialPortConfiguration;

    LLRP_tSNTPConfiguration * pNTPConfiguration;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdCommunicationConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdCommunicationConfiguration[];

extern LLRP_tSCommunicationConfiguration *
LLRP_CommunicationConfiguration_construct (void);

extern void
LLRP_CommunicationConfiguration_destruct (
 LLRP_tSCommunicationConfiguration * pThis);

extern void
LLRP_CommunicationConfiguration_decodeFields (
 LLRP_tSCommunicationConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_CommunicationConfiguration_assimilateSubParameters (
 LLRP_tSCommunicationConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_CommunicationConfiguration_encode (
  const LLRP_tSCommunicationConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSCommLinkConfiguration *
LLRP_CommunicationConfiguration_beginCommLinkConfiguration (
  LLRP_tSCommunicationConfiguration *pThis);

extern LLRP_tSCommLinkConfiguration *
LLRP_CommunicationConfiguration_nextCommLinkConfiguration (
  LLRP_tSCommLinkConfiguration *pCurrent);

extern void
LLRP_CommunicationConfiguration_clearCommLinkConfiguration (
  LLRP_tSCommunicationConfiguration *pThis);

extern int
LLRP_CommunicationConfiguration_countCommLinkConfiguration (
  LLRP_tSCommunicationConfiguration *pThis);

extern LLRP_tResultCode
LLRP_CommunicationConfiguration_addCommLinkConfiguration (
  LLRP_tSCommunicationConfiguration *pThis,
  LLRP_tSCommLinkConfiguration *pValue);


extern LLRP_tSParameter *
LLRP_CommunicationConfiguration_beginEthernetConfiguration (
  LLRP_tSCommunicationConfiguration *pThis);

extern LLRP_tSParameter *
LLRP_CommunicationConfiguration_nextEthernetConfiguration (
  LLRP_tSParameter *pCurrent);

extern void
LLRP_CommunicationConfiguration_clearEthernetConfiguration (
  LLRP_tSCommunicationConfiguration *pThis);

extern int
LLRP_CommunicationConfiguration_countEthernetConfiguration (
  LLRP_tSCommunicationConfiguration *pThis);

extern LLRP_tResultCode
LLRP_CommunicationConfiguration_addEthernetConfiguration (
  LLRP_tSCommunicationConfiguration *pThis,
  LLRP_tSParameter *pValue);


extern LLRP_tSSerialPortConfiguration *
LLRP_CommunicationConfiguration_beginSerialPortConfiguration (
  LLRP_tSCommunicationConfiguration *pThis);

extern LLRP_tSSerialPortConfiguration *
LLRP_CommunicationConfiguration_nextSerialPortConfiguration (
  LLRP_tSSerialPortConfiguration *pCurrent);

extern void
LLRP_CommunicationConfiguration_clearSerialPortConfiguration (
  LLRP_tSCommunicationConfiguration *pThis);

extern int
LLRP_CommunicationConfiguration_countSerialPortConfiguration (
  LLRP_tSCommunicationConfiguration *pThis);

extern LLRP_tResultCode
LLRP_CommunicationConfiguration_addSerialPortConfiguration (
  LLRP_tSCommunicationConfiguration *pThis,
  LLRP_tSSerialPortConfiguration *pValue);


extern LLRP_tSNTPConfiguration *
LLRP_CommunicationConfiguration_getNTPConfiguration (
  LLRP_tSCommunicationConfiguration *pThis);

extern LLRP_tResultCode
LLRP_CommunicationConfiguration_setNTPConfiguration (
  LLRP_tSCommunicationConfiguration *pThis,
  LLRP_tSNTPConfiguration *pValue);



  
struct LLRP_SCommLinkConfiguration
{
    LLRP_tSParameter hdr;
  
    LLRP_tELinkType eLinkType;

  
    LLRP_tSKeepaliveSpec * pKeepaliveSpec;

    LLRP_tSTcpLinkConfiguration * pTcpLinkConfiguration;

    LLRP_tSSerialLinkConfiguration * pSerialLinkConfiguration;

    LLRP_tSHttpLinkConfiguration * pHttpLinkConfiguration;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdCommLinkConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdCommLinkConfiguration[];

extern LLRP_tSCommLinkConfiguration *
LLRP_CommLinkConfiguration_construct (void);

extern void
LLRP_CommLinkConfiguration_destruct (
 LLRP_tSCommLinkConfiguration * pThis);

extern void
LLRP_CommLinkConfiguration_decodeFields (
 LLRP_tSCommLinkConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_CommLinkConfiguration_assimilateSubParameters (
 LLRP_tSCommLinkConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_CommLinkConfiguration_encode (
  const LLRP_tSCommLinkConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdCommLinkConfiguration_LinkType;

extern LLRP_tELinkType
LLRP_CommLinkConfiguration_getLinkType (
  LLRP_tSCommLinkConfiguration *pThis);

extern LLRP_tResultCode
LLRP_CommLinkConfiguration_setLinkType (
  LLRP_tSCommLinkConfiguration *pThis,
  LLRP_tELinkType Value);

  
extern LLRP_tSKeepaliveSpec *
LLRP_CommLinkConfiguration_getKeepaliveSpec (
  LLRP_tSCommLinkConfiguration *pThis);

extern LLRP_tResultCode
LLRP_CommLinkConfiguration_setKeepaliveSpec (
  LLRP_tSCommLinkConfiguration *pThis,
  LLRP_tSKeepaliveSpec *pValue);

extern LLRP_tSTcpLinkConfiguration *
LLRP_CommLinkConfiguration_getTcpLinkConfiguration (
  LLRP_tSCommLinkConfiguration *pThis);

extern LLRP_tResultCode
LLRP_CommLinkConfiguration_setTcpLinkConfiguration (
  LLRP_tSCommLinkConfiguration *pThis,
  LLRP_tSTcpLinkConfiguration *pValue);

extern LLRP_tSSerialLinkConfiguration *
LLRP_CommLinkConfiguration_getSerialLinkConfiguration (
  LLRP_tSCommLinkConfiguration *pThis);

extern LLRP_tResultCode
LLRP_CommLinkConfiguration_setSerialLinkConfiguration (
  LLRP_tSCommLinkConfiguration *pThis,
  LLRP_tSSerialLinkConfiguration *pValue);

extern LLRP_tSHttpLinkConfiguration *
LLRP_CommLinkConfiguration_getHttpLinkConfiguration (
  LLRP_tSCommLinkConfiguration *pThis);

extern LLRP_tResultCode
LLRP_CommLinkConfiguration_setHttpLinkConfiguration (
  LLRP_tSCommLinkConfiguration *pThis,
  LLRP_tSHttpLinkConfiguration *pValue);



  
struct LLRP_SKeepaliveSpec
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t KeepaliveTrigger;

    llrp_u32_t PeriodicTriggerValue;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdKeepaliveSpec;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdKeepaliveSpec[];

extern LLRP_tSKeepaliveSpec *
LLRP_KeepaliveSpec_construct (void);

extern void
LLRP_KeepaliveSpec_destruct (
 LLRP_tSKeepaliveSpec * pThis);

extern void
LLRP_KeepaliveSpec_decodeFields (
 LLRP_tSKeepaliveSpec * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_KeepaliveSpec_assimilateSubParameters (
 LLRP_tSKeepaliveSpec * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_KeepaliveSpec_encode (
  const LLRP_tSKeepaliveSpec *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdKeepaliveSpec_KeepaliveTrigger;

extern llrp_u8_t
LLRP_KeepaliveSpec_getKeepaliveTrigger (
  LLRP_tSKeepaliveSpec *pThis);

extern LLRP_tResultCode
LLRP_KeepaliveSpec_setKeepaliveTrigger (
  LLRP_tSKeepaliveSpec *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdKeepaliveSpec_PeriodicTriggerValue;

extern llrp_u32_t
LLRP_KeepaliveSpec_getPeriodicTriggerValue (
  LLRP_tSKeepaliveSpec *pThis);

extern LLRP_tResultCode
LLRP_KeepaliveSpec_setPeriodicTriggerValue (
  LLRP_tSKeepaliveSpec *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_STcpLinkConfiguration
{
    LLRP_tSParameter hdr;
  
    LLRP_tECommMode eCommMode;

    llrp_u1_t IsSSL;

  
    LLRP_tSClientModeConfiguration * pClientModeConfiguration;

    LLRP_tSServerModeConfiguration * pServerModeConfiguration;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdTcpLinkConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdTcpLinkConfiguration[];

extern LLRP_tSTcpLinkConfiguration *
LLRP_TcpLinkConfiguration_construct (void);

extern void
LLRP_TcpLinkConfiguration_destruct (
 LLRP_tSTcpLinkConfiguration * pThis);

extern void
LLRP_TcpLinkConfiguration_decodeFields (
 LLRP_tSTcpLinkConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_TcpLinkConfiguration_assimilateSubParameters (
 LLRP_tSTcpLinkConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_TcpLinkConfiguration_encode (
  const LLRP_tSTcpLinkConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdTcpLinkConfiguration_CommMode;

extern LLRP_tECommMode
LLRP_TcpLinkConfiguration_getCommMode (
  LLRP_tSTcpLinkConfiguration *pThis);

extern LLRP_tResultCode
LLRP_TcpLinkConfiguration_setCommMode (
  LLRP_tSTcpLinkConfiguration *pThis,
  LLRP_tECommMode Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTcpLinkConfiguration_IsSSL;

extern llrp_u1_t
LLRP_TcpLinkConfiguration_getIsSSL (
  LLRP_tSTcpLinkConfiguration *pThis);

extern LLRP_tResultCode
LLRP_TcpLinkConfiguration_setIsSSL (
  LLRP_tSTcpLinkConfiguration *pThis,
  llrp_u1_t Value);

  
extern LLRP_tSClientModeConfiguration *
LLRP_TcpLinkConfiguration_getClientModeConfiguration (
  LLRP_tSTcpLinkConfiguration *pThis);

extern LLRP_tResultCode
LLRP_TcpLinkConfiguration_setClientModeConfiguration (
  LLRP_tSTcpLinkConfiguration *pThis,
  LLRP_tSClientModeConfiguration *pValue);

extern LLRP_tSServerModeConfiguration *
LLRP_TcpLinkConfiguration_getServerModeConfiguration (
  LLRP_tSTcpLinkConfiguration *pThis);

extern LLRP_tResultCode
LLRP_TcpLinkConfiguration_setServerModeConfiguration (
  LLRP_tSTcpLinkConfiguration *pThis,
  LLRP_tSServerModeConfiguration *pValue);



  
struct LLRP_SClientModeConfiguration
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t Port;

  
    LLRP_tSIPAddress * pIPAddress;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdClientModeConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdClientModeConfiguration[];

extern LLRP_tSClientModeConfiguration *
LLRP_ClientModeConfiguration_construct (void);

extern void
LLRP_ClientModeConfiguration_destruct (
 LLRP_tSClientModeConfiguration * pThis);

extern void
LLRP_ClientModeConfiguration_decodeFields (
 LLRP_tSClientModeConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ClientModeConfiguration_assimilateSubParameters (
 LLRP_tSClientModeConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ClientModeConfiguration_encode (
  const LLRP_tSClientModeConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdClientModeConfiguration_Port;

extern llrp_u16_t
LLRP_ClientModeConfiguration_getPort (
  LLRP_tSClientModeConfiguration *pThis);

extern LLRP_tResultCode
LLRP_ClientModeConfiguration_setPort (
  LLRP_tSClientModeConfiguration *pThis,
  llrp_u16_t Value);

  
extern LLRP_tSIPAddress *
LLRP_ClientModeConfiguration_getIPAddress (
  LLRP_tSClientModeConfiguration *pThis);

extern LLRP_tResultCode
LLRP_ClientModeConfiguration_setIPAddress (
  LLRP_tSClientModeConfiguration *pThis,
  LLRP_tSIPAddress *pValue);



  
struct LLRP_SIPAddress
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t Version;

    llrp_u32v_t Address;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdIPAddress;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdIPAddress[];

extern LLRP_tSIPAddress *
LLRP_IPAddress_construct (void);

extern void
LLRP_IPAddress_destruct (
 LLRP_tSIPAddress * pThis);

extern void
LLRP_IPAddress_decodeFields (
 LLRP_tSIPAddress * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_IPAddress_assimilateSubParameters (
 LLRP_tSIPAddress * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_IPAddress_encode (
  const LLRP_tSIPAddress *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdIPAddress_Version;

extern llrp_u8_t
LLRP_IPAddress_getVersion (
  LLRP_tSIPAddress *pThis);

extern LLRP_tResultCode
LLRP_IPAddress_setVersion (
  LLRP_tSIPAddress *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdIPAddress_Address;

extern llrp_u32v_t
LLRP_IPAddress_getAddress (
  LLRP_tSIPAddress *pThis);

extern LLRP_tResultCode
LLRP_IPAddress_setAddress (
  LLRP_tSIPAddress *pThis,
  llrp_u32v_t Value);

  


  
struct LLRP_SServerModeConfiguration
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t Port;

  
    LLRP_tSIPAddress * pIPAddress;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdServerModeConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdServerModeConfiguration[];

extern LLRP_tSServerModeConfiguration *
LLRP_ServerModeConfiguration_construct (void);

extern void
LLRP_ServerModeConfiguration_destruct (
 LLRP_tSServerModeConfiguration * pThis);

extern void
LLRP_ServerModeConfiguration_decodeFields (
 LLRP_tSServerModeConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ServerModeConfiguration_assimilateSubParameters (
 LLRP_tSServerModeConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ServerModeConfiguration_encode (
  const LLRP_tSServerModeConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdServerModeConfiguration_Port;

extern llrp_u16_t
LLRP_ServerModeConfiguration_getPort (
  LLRP_tSServerModeConfiguration *pThis);

extern LLRP_tResultCode
LLRP_ServerModeConfiguration_setPort (
  LLRP_tSServerModeConfiguration *pThis,
  llrp_u16_t Value);

  
extern LLRP_tSIPAddress *
LLRP_ServerModeConfiguration_getIPAddress (
  LLRP_tSServerModeConfiguration *pThis);

extern LLRP_tResultCode
LLRP_ServerModeConfiguration_setIPAddress (
  LLRP_tSServerModeConfiguration *pThis,
  LLRP_tSIPAddress *pValue);



  
struct LLRP_SSerialLinkConfiguration
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t IfIndex;

    llrp_u8_t SrcAddress;

    llrp_u8_t DstAddress;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSerialLinkConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSerialLinkConfiguration[];

extern LLRP_tSSerialLinkConfiguration *
LLRP_SerialLinkConfiguration_construct (void);

extern void
LLRP_SerialLinkConfiguration_destruct (
 LLRP_tSSerialLinkConfiguration * pThis);

extern void
LLRP_SerialLinkConfiguration_decodeFields (
 LLRP_tSSerialLinkConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SerialLinkConfiguration_assimilateSubParameters (
 LLRP_tSSerialLinkConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SerialLinkConfiguration_encode (
  const LLRP_tSSerialLinkConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSerialLinkConfiguration_IfIndex;

extern llrp_u8_t
LLRP_SerialLinkConfiguration_getIfIndex (
  LLRP_tSSerialLinkConfiguration *pThis);

extern LLRP_tResultCode
LLRP_SerialLinkConfiguration_setIfIndex (
  LLRP_tSSerialLinkConfiguration *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSerialLinkConfiguration_SrcAddress;

extern llrp_u8_t
LLRP_SerialLinkConfiguration_getSrcAddress (
  LLRP_tSSerialLinkConfiguration *pThis);

extern LLRP_tResultCode
LLRP_SerialLinkConfiguration_setSrcAddress (
  LLRP_tSSerialLinkConfiguration *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSerialLinkConfiguration_DstAddress;

extern llrp_u8_t
LLRP_SerialLinkConfiguration_getDstAddress (
  LLRP_tSSerialLinkConfiguration *pThis);

extern LLRP_tResultCode
LLRP_SerialLinkConfiguration_setDstAddress (
  LLRP_tSSerialLinkConfiguration *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SHttpLinkConfiguration
{
    LLRP_tSParameter hdr;
  
    llrp_utf8v_t ServerUrl;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdHttpLinkConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHttpLinkConfiguration[];

extern LLRP_tSHttpLinkConfiguration *
LLRP_HttpLinkConfiguration_construct (void);

extern void
LLRP_HttpLinkConfiguration_destruct (
 LLRP_tSHttpLinkConfiguration * pThis);

extern void
LLRP_HttpLinkConfiguration_decodeFields (
 LLRP_tSHttpLinkConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HttpLinkConfiguration_assimilateSubParameters (
 LLRP_tSHttpLinkConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HttpLinkConfiguration_encode (
  const LLRP_tSHttpLinkConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdHttpLinkConfiguration_ServerUrl;

extern llrp_utf8v_t
LLRP_HttpLinkConfiguration_getServerUrl (
  LLRP_tSHttpLinkConfiguration *pThis);

extern LLRP_tResultCode
LLRP_HttpLinkConfiguration_setServerUrl (
  LLRP_tSHttpLinkConfiguration *pThis,
  llrp_utf8v_t Value);

  


  
struct LLRP_SEthernetIpv4Configuration
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t IfIndex;

    llrp_u32_t IPAddress;

    llrp_u32_t IPMask;

    llrp_u32_t GateWayAddr;

    llrp_u32_t DNSAddr;

    llrp_u1_t IsDHCP;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdEthernetIpv4Configuration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdEthernetIpv4Configuration[];

extern LLRP_tSEthernetIpv4Configuration *
LLRP_EthernetIpv4Configuration_construct (void);

extern void
LLRP_EthernetIpv4Configuration_destruct (
 LLRP_tSEthernetIpv4Configuration * pThis);

extern void
LLRP_EthernetIpv4Configuration_decodeFields (
 LLRP_tSEthernetIpv4Configuration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_EthernetIpv4Configuration_assimilateSubParameters (
 LLRP_tSEthernetIpv4Configuration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_EthernetIpv4Configuration_encode (
  const LLRP_tSEthernetIpv4Configuration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdEthernetIpv4Configuration_IfIndex;

extern llrp_u8_t
LLRP_EthernetIpv4Configuration_getIfIndex (
  LLRP_tSEthernetIpv4Configuration *pThis);

extern LLRP_tResultCode
LLRP_EthernetIpv4Configuration_setIfIndex (
  LLRP_tSEthernetIpv4Configuration *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdEthernetIpv4Configuration_IPAddress;

extern llrp_u32_t
LLRP_EthernetIpv4Configuration_getIPAddress (
  LLRP_tSEthernetIpv4Configuration *pThis);

extern LLRP_tResultCode
LLRP_EthernetIpv4Configuration_setIPAddress (
  LLRP_tSEthernetIpv4Configuration *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdEthernetIpv4Configuration_IPMask;

extern llrp_u32_t
LLRP_EthernetIpv4Configuration_getIPMask (
  LLRP_tSEthernetIpv4Configuration *pThis);

extern LLRP_tResultCode
LLRP_EthernetIpv4Configuration_setIPMask (
  LLRP_tSEthernetIpv4Configuration *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdEthernetIpv4Configuration_GateWayAddr;

extern llrp_u32_t
LLRP_EthernetIpv4Configuration_getGateWayAddr (
  LLRP_tSEthernetIpv4Configuration *pThis);

extern LLRP_tResultCode
LLRP_EthernetIpv4Configuration_setGateWayAddr (
  LLRP_tSEthernetIpv4Configuration *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdEthernetIpv4Configuration_DNSAddr;

extern llrp_u32_t
LLRP_EthernetIpv4Configuration_getDNSAddr (
  LLRP_tSEthernetIpv4Configuration *pThis);

extern LLRP_tResultCode
LLRP_EthernetIpv4Configuration_setDNSAddr (
  LLRP_tSEthernetIpv4Configuration *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdEthernetIpv4Configuration_IsDHCP;

extern llrp_u1_t
LLRP_EthernetIpv4Configuration_getIsDHCP (
  LLRP_tSEthernetIpv4Configuration *pThis);

extern LLRP_tResultCode
LLRP_EthernetIpv4Configuration_setIsDHCP (
  LLRP_tSEthernetIpv4Configuration *pThis,
  llrp_u1_t Value);

  


  
struct LLRP_SEthernetIpv6Configuration
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t IfIndex;

    llrp_u32v_t IPAddress;

    llrp_u8_t IPMask;

    llrp_u32v_t GateWayAddr;

    llrp_u32v_t DNSAddr;

    llrp_u1_t IsDHCP;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdEthernetIpv6Configuration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdEthernetIpv6Configuration[];

extern LLRP_tSEthernetIpv6Configuration *
LLRP_EthernetIpv6Configuration_construct (void);

extern void
LLRP_EthernetIpv6Configuration_destruct (
 LLRP_tSEthernetIpv6Configuration * pThis);

extern void
LLRP_EthernetIpv6Configuration_decodeFields (
 LLRP_tSEthernetIpv6Configuration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_EthernetIpv6Configuration_assimilateSubParameters (
 LLRP_tSEthernetIpv6Configuration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_EthernetIpv6Configuration_encode (
  const LLRP_tSEthernetIpv6Configuration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdEthernetIpv6Configuration_IfIndex;

extern llrp_u8_t
LLRP_EthernetIpv6Configuration_getIfIndex (
  LLRP_tSEthernetIpv6Configuration *pThis);

extern LLRP_tResultCode
LLRP_EthernetIpv6Configuration_setIfIndex (
  LLRP_tSEthernetIpv6Configuration *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdEthernetIpv6Configuration_IPAddress;

extern llrp_u32v_t
LLRP_EthernetIpv6Configuration_getIPAddress (
  LLRP_tSEthernetIpv6Configuration *pThis);

extern LLRP_tResultCode
LLRP_EthernetIpv6Configuration_setIPAddress (
  LLRP_tSEthernetIpv6Configuration *pThis,
  llrp_u32v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdEthernetIpv6Configuration_IPMask;

extern llrp_u8_t
LLRP_EthernetIpv6Configuration_getIPMask (
  LLRP_tSEthernetIpv6Configuration *pThis);

extern LLRP_tResultCode
LLRP_EthernetIpv6Configuration_setIPMask (
  LLRP_tSEthernetIpv6Configuration *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdEthernetIpv6Configuration_GateWayAddr;

extern llrp_u32v_t
LLRP_EthernetIpv6Configuration_getGateWayAddr (
  LLRP_tSEthernetIpv6Configuration *pThis);

extern LLRP_tResultCode
LLRP_EthernetIpv6Configuration_setGateWayAddr (
  LLRP_tSEthernetIpv6Configuration *pThis,
  llrp_u32v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdEthernetIpv6Configuration_DNSAddr;

extern llrp_u32v_t
LLRP_EthernetIpv6Configuration_getDNSAddr (
  LLRP_tSEthernetIpv6Configuration *pThis);

extern LLRP_tResultCode
LLRP_EthernetIpv6Configuration_setDNSAddr (
  LLRP_tSEthernetIpv6Configuration *pThis,
  llrp_u32v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdEthernetIpv6Configuration_IsDHCP;

extern llrp_u1_t
LLRP_EthernetIpv6Configuration_getIsDHCP (
  LLRP_tSEthernetIpv6Configuration *pThis);

extern LLRP_tResultCode
LLRP_EthernetIpv6Configuration_setIsDHCP (
  LLRP_tSEthernetIpv6Configuration *pThis,
  llrp_u1_t Value);

  


  
struct LLRP_SNTPConfiguration
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t NtpPeriodic;

  
    LLRP_tSIPAddress * listIPAddress;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdNTPConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdNTPConfiguration[];

extern LLRP_tSNTPConfiguration *
LLRP_NTPConfiguration_construct (void);

extern void
LLRP_NTPConfiguration_destruct (
 LLRP_tSNTPConfiguration * pThis);

extern void
LLRP_NTPConfiguration_decodeFields (
 LLRP_tSNTPConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_NTPConfiguration_assimilateSubParameters (
 LLRP_tSNTPConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_NTPConfiguration_encode (
  const LLRP_tSNTPConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdNTPConfiguration_NtpPeriodic;

extern llrp_u32_t
LLRP_NTPConfiguration_getNtpPeriodic (
  LLRP_tSNTPConfiguration *pThis);

extern LLRP_tResultCode
LLRP_NTPConfiguration_setNtpPeriodic (
  LLRP_tSNTPConfiguration *pThis,
  llrp_u32_t Value);

  
extern LLRP_tSIPAddress *
LLRP_NTPConfiguration_beginIPAddress (
  LLRP_tSNTPConfiguration *pThis);

extern LLRP_tSIPAddress *
LLRP_NTPConfiguration_nextIPAddress (
  LLRP_tSIPAddress *pCurrent);

extern void
LLRP_NTPConfiguration_clearIPAddress (
  LLRP_tSNTPConfiguration *pThis);

extern int
LLRP_NTPConfiguration_countIPAddress (
  LLRP_tSNTPConfiguration *pThis);

extern LLRP_tResultCode
LLRP_NTPConfiguration_addIPAddress (
  LLRP_tSNTPConfiguration *pThis,
  LLRP_tSIPAddress *pValue);




  
struct LLRP_SSerialPortConfiguration
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t IfIndex;

    llrp_u8_t AttributeIndex;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSerialPortConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSerialPortConfiguration[];

extern LLRP_tSSerialPortConfiguration *
LLRP_SerialPortConfiguration_construct (void);

extern void
LLRP_SerialPortConfiguration_destruct (
 LLRP_tSSerialPortConfiguration * pThis);

extern void
LLRP_SerialPortConfiguration_decodeFields (
 LLRP_tSSerialPortConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SerialPortConfiguration_assimilateSubParameters (
 LLRP_tSSerialPortConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SerialPortConfiguration_encode (
  const LLRP_tSSerialPortConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSerialPortConfiguration_IfIndex;

extern llrp_u8_t
LLRP_SerialPortConfiguration_getIfIndex (
  LLRP_tSSerialPortConfiguration *pThis);

extern LLRP_tResultCode
LLRP_SerialPortConfiguration_setIfIndex (
  LLRP_tSSerialPortConfiguration *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSerialPortConfiguration_AttributeIndex;

extern llrp_u8_t
LLRP_SerialPortConfiguration_getAttributeIndex (
  LLRP_tSSerialPortConfiguration *pThis);

extern LLRP_tResultCode
LLRP_SerialPortConfiguration_setAttributeIndex (
  LLRP_tSSerialPortConfiguration *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SLocationConfiguration
{
    LLRP_tSParameter hdr;
  
    LLRP_tELocationType eLocationType;

  
    LLRP_tSParameter * pLocationInfo;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdLocationConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdLocationConfiguration[];

extern LLRP_tSLocationConfiguration *
LLRP_LocationConfiguration_construct (void);

extern void
LLRP_LocationConfiguration_destruct (
 LLRP_tSLocationConfiguration * pThis);

extern void
LLRP_LocationConfiguration_decodeFields (
 LLRP_tSLocationConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_LocationConfiguration_assimilateSubParameters (
 LLRP_tSLocationConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_LocationConfiguration_encode (
  const LLRP_tSLocationConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdLocationConfiguration_LocationType;

extern LLRP_tELocationType
LLRP_LocationConfiguration_getLocationType (
  LLRP_tSLocationConfiguration *pThis);

extern LLRP_tResultCode
LLRP_LocationConfiguration_setLocationType (
  LLRP_tSLocationConfiguration *pThis,
  LLRP_tELocationType Value);

  
extern LLRP_tSParameter *
LLRP_LocationConfiguration_getLocationInfo (
  LLRP_tSLocationConfiguration *pThis);

extern LLRP_tResultCode
LLRP_LocationConfiguration_setLocationInfo (
  LLRP_tSLocationConfiguration *pThis,
  LLRP_tSParameter *pValue);



  
struct LLRP_SGpsLocation
{
    LLRP_tSParameter hdr;
  
    llrp_s32_t Longitude;

    llrp_s32_t Latitude;

    llrp_s32_t Altitude;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdGpsLocation;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGpsLocation[];

extern LLRP_tSGpsLocation *
LLRP_GpsLocation_construct (void);

extern void
LLRP_GpsLocation_destruct (
 LLRP_tSGpsLocation * pThis);

extern void
LLRP_GpsLocation_decodeFields (
 LLRP_tSGpsLocation * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GpsLocation_assimilateSubParameters (
 LLRP_tSGpsLocation * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GpsLocation_encode (
  const LLRP_tSGpsLocation *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGpsLocation_Longitude;

extern llrp_s32_t
LLRP_GpsLocation_getLongitude (
  LLRP_tSGpsLocation *pThis);

extern LLRP_tResultCode
LLRP_GpsLocation_setLongitude (
  LLRP_tSGpsLocation *pThis,
  llrp_s32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGpsLocation_Latitude;

extern llrp_s32_t
LLRP_GpsLocation_getLatitude (
  LLRP_tSGpsLocation *pThis);

extern LLRP_tResultCode
LLRP_GpsLocation_setLatitude (
  LLRP_tSGpsLocation *pThis,
  llrp_s32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGpsLocation_Altitude;

extern llrp_s32_t
LLRP_GpsLocation_getAltitude (
  LLRP_tSGpsLocation *pThis);

extern LLRP_tResultCode
LLRP_GpsLocation_setAltitude (
  LLRP_tSGpsLocation *pThis,
  llrp_s32_t Value);

  


  
struct LLRP_SBdsLocation
{
    LLRP_tSParameter hdr;
  
    llrp_s32_t Longitude;

    llrp_s32_t Latitude;

    llrp_s32_t Altitude;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdBdsLocation;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdBdsLocation[];

extern LLRP_tSBdsLocation *
LLRP_BdsLocation_construct (void);

extern void
LLRP_BdsLocation_destruct (
 LLRP_tSBdsLocation * pThis);

extern void
LLRP_BdsLocation_decodeFields (
 LLRP_tSBdsLocation * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_BdsLocation_assimilateSubParameters (
 LLRP_tSBdsLocation * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_BdsLocation_encode (
  const LLRP_tSBdsLocation *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdBdsLocation_Longitude;

extern llrp_s32_t
LLRP_BdsLocation_getLongitude (
  LLRP_tSBdsLocation *pThis);

extern LLRP_tResultCode
LLRP_BdsLocation_setLongitude (
  LLRP_tSBdsLocation *pThis,
  llrp_s32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdBdsLocation_Latitude;

extern llrp_s32_t
LLRP_BdsLocation_getLatitude (
  LLRP_tSBdsLocation *pThis);

extern LLRP_tResultCode
LLRP_BdsLocation_setLatitude (
  LLRP_tSBdsLocation *pThis,
  llrp_s32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdBdsLocation_Altitude;

extern llrp_s32_t
LLRP_BdsLocation_getAltitude (
  LLRP_tSBdsLocation *pThis);

extern LLRP_tResultCode
LLRP_BdsLocation_setAltitude (
  LLRP_tSBdsLocation *pThis,
  llrp_s32_t Value);

  


  
struct LLRP_SSecurityModuleConfiguration
{
    LLRP_tSParameter hdr;
  
    llrp_u8v_t ConfigData;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSecurityModuleConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSecurityModuleConfiguration[];

extern LLRP_tSSecurityModuleConfiguration *
LLRP_SecurityModuleConfiguration_construct (void);

extern void
LLRP_SecurityModuleConfiguration_destruct (
 LLRP_tSSecurityModuleConfiguration * pThis);

extern void
LLRP_SecurityModuleConfiguration_decodeFields (
 LLRP_tSSecurityModuleConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SecurityModuleConfiguration_assimilateSubParameters (
 LLRP_tSSecurityModuleConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SecurityModuleConfiguration_encode (
  const LLRP_tSSecurityModuleConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSecurityModuleConfiguration_ConfigData;

extern llrp_u8v_t
LLRP_SecurityModuleConfiguration_getConfigData (
  LLRP_tSSecurityModuleConfiguration *pThis);

extern LLRP_tResultCode
LLRP_SecurityModuleConfiguration_setConfigData (
  LLRP_tSSecurityModuleConfiguration *pThis,
  llrp_u8v_t Value);

  


  
struct LLRP_SVersionInfo
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t MaxVerInfo;

    llrp_u8_t MinVerInfo;

    llrp_u8_t SubVerInfo;

    llrp_u8_t BuildVerInfo;

    LLRP_tEUsedOrSpare eUsedOrSpare;

    LLRP_tESetUse eSetUse;

    LLRP_tEHasRun eHasRun;

    LLRP_tECanRun eCanRun;

    llrp_utf8v_t VerDescInfo;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdVersionInfo;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdVersionInfo[];

extern LLRP_tSVersionInfo *
LLRP_VersionInfo_construct (void);

extern void
LLRP_VersionInfo_destruct (
 LLRP_tSVersionInfo * pThis);

extern void
LLRP_VersionInfo_decodeFields (
 LLRP_tSVersionInfo * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_VersionInfo_assimilateSubParameters (
 LLRP_tSVersionInfo * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_VersionInfo_encode (
  const LLRP_tSVersionInfo *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdVersionInfo_MaxVerInfo;

extern llrp_u8_t
LLRP_VersionInfo_getMaxVerInfo (
  LLRP_tSVersionInfo *pThis);

extern LLRP_tResultCode
LLRP_VersionInfo_setMaxVerInfo (
  LLRP_tSVersionInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionInfo_MinVerInfo;

extern llrp_u8_t
LLRP_VersionInfo_getMinVerInfo (
  LLRP_tSVersionInfo *pThis);

extern LLRP_tResultCode
LLRP_VersionInfo_setMinVerInfo (
  LLRP_tSVersionInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionInfo_SubVerInfo;

extern llrp_u8_t
LLRP_VersionInfo_getSubVerInfo (
  LLRP_tSVersionInfo *pThis);

extern LLRP_tResultCode
LLRP_VersionInfo_setSubVerInfo (
  LLRP_tSVersionInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionInfo_BuildVerInfo;

extern llrp_u8_t
LLRP_VersionInfo_getBuildVerInfo (
  LLRP_tSVersionInfo *pThis);

extern LLRP_tResultCode
LLRP_VersionInfo_setBuildVerInfo (
  LLRP_tSVersionInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionInfo_UsedOrSpare;

extern LLRP_tEUsedOrSpare
LLRP_VersionInfo_getUsedOrSpare (
  LLRP_tSVersionInfo *pThis);

extern LLRP_tResultCode
LLRP_VersionInfo_setUsedOrSpare (
  LLRP_tSVersionInfo *pThis,
  LLRP_tEUsedOrSpare Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionInfo_SetUse;

extern LLRP_tESetUse
LLRP_VersionInfo_getSetUse (
  LLRP_tSVersionInfo *pThis);

extern LLRP_tResultCode
LLRP_VersionInfo_setSetUse (
  LLRP_tSVersionInfo *pThis,
  LLRP_tESetUse Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionInfo_HasRun;

extern LLRP_tEHasRun
LLRP_VersionInfo_getHasRun (
  LLRP_tSVersionInfo *pThis);

extern LLRP_tResultCode
LLRP_VersionInfo_setHasRun (
  LLRP_tSVersionInfo *pThis,
  LLRP_tEHasRun Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionInfo_CanRun;

extern LLRP_tECanRun
LLRP_VersionInfo_getCanRun (
  LLRP_tSVersionInfo *pThis);

extern LLRP_tResultCode
LLRP_VersionInfo_setCanRun (
  LLRP_tSVersionInfo *pThis,
  LLRP_tECanRun Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionInfo_VerDescInfo;

extern llrp_utf8v_t
LLRP_VersionInfo_getVerDescInfo (
  LLRP_tSVersionInfo *pThis);

extern LLRP_tResultCode
LLRP_VersionInfo_setVerDescInfo (
  LLRP_tSVersionInfo *pThis,
  llrp_utf8v_t Value);

  


  
struct LLRP_SVersionDownload
{
    LLRP_tSParameter hdr;
  
    LLRP_tEServerType eServerType;

    llrp_u8v_t Username;

    llrp_u8v_t UserPass;

    llrp_u8v_t VersionPath;

    llrp_u16_t ServerPort;

  
    LLRP_tSIPAddress * pIPAddress;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdVersionDownload;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdVersionDownload[];

extern LLRP_tSVersionDownload *
LLRP_VersionDownload_construct (void);

extern void
LLRP_VersionDownload_destruct (
 LLRP_tSVersionDownload * pThis);

extern void
LLRP_VersionDownload_decodeFields (
 LLRP_tSVersionDownload * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_VersionDownload_assimilateSubParameters (
 LLRP_tSVersionDownload * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_VersionDownload_encode (
  const LLRP_tSVersionDownload *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDownload_ServerType;

extern LLRP_tEServerType
LLRP_VersionDownload_getServerType (
  LLRP_tSVersionDownload *pThis);

extern LLRP_tResultCode
LLRP_VersionDownload_setServerType (
  LLRP_tSVersionDownload *pThis,
  LLRP_tEServerType Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDownload_Username;

extern llrp_u8v_t
LLRP_VersionDownload_getUsername (
  LLRP_tSVersionDownload *pThis);

extern LLRP_tResultCode
LLRP_VersionDownload_setUsername (
  LLRP_tSVersionDownload *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDownload_UserPass;

extern llrp_u8v_t
LLRP_VersionDownload_getUserPass (
  LLRP_tSVersionDownload *pThis);

extern LLRP_tResultCode
LLRP_VersionDownload_setUserPass (
  LLRP_tSVersionDownload *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDownload_VersionPath;

extern llrp_u8v_t
LLRP_VersionDownload_getVersionPath (
  LLRP_tSVersionDownload *pThis);

extern LLRP_tResultCode
LLRP_VersionDownload_setVersionPath (
  LLRP_tSVersionDownload *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDownload_ServerPort;

extern llrp_u16_t
LLRP_VersionDownload_getServerPort (
  LLRP_tSVersionDownload *pThis);

extern LLRP_tResultCode
LLRP_VersionDownload_setServerPort (
  LLRP_tSVersionDownload *pThis,
  llrp_u16_t Value);

  
extern LLRP_tSIPAddress *
LLRP_VersionDownload_getIPAddress (
  LLRP_tSVersionDownload *pThis);

extern LLRP_tResultCode
LLRP_VersionDownload_setIPAddress (
  LLRP_tSVersionDownload *pThis,
  LLRP_tSIPAddress *pValue);



  
struct LLRP_SAlarmReportInfo
{
    LLRP_tSParameter hdr;
  
    LLRP_tEStatusCode eAlarmReportCode;

    llrp_u32_t AlarmReportReason;

    LLRP_tEAlarmReportLevel eAlarmReportLevel;

    llrp_u32_t AlarmReportSeconds;

    llrp_utf8v_t AlarmReportDescription;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdAlarmReportInfo;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAlarmReportInfo[];

extern LLRP_tSAlarmReportInfo *
LLRP_AlarmReportInfo_construct (void);

extern void
LLRP_AlarmReportInfo_destruct (
 LLRP_tSAlarmReportInfo * pThis);

extern void
LLRP_AlarmReportInfo_decodeFields (
 LLRP_tSAlarmReportInfo * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AlarmReportInfo_assimilateSubParameters (
 LLRP_tSAlarmReportInfo * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AlarmReportInfo_encode (
  const LLRP_tSAlarmReportInfo *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmReportInfo_AlarmReportCode;

extern LLRP_tEStatusCode
LLRP_AlarmReportInfo_getAlarmReportCode (
  LLRP_tSAlarmReportInfo *pThis);

extern LLRP_tResultCode
LLRP_AlarmReportInfo_setAlarmReportCode (
  LLRP_tSAlarmReportInfo *pThis,
  LLRP_tEStatusCode Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmReportInfo_AlarmReportReason;

extern llrp_u32_t
LLRP_AlarmReportInfo_getAlarmReportReason (
  LLRP_tSAlarmReportInfo *pThis);

extern LLRP_tResultCode
LLRP_AlarmReportInfo_setAlarmReportReason (
  LLRP_tSAlarmReportInfo *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmReportInfo_AlarmReportLevel;

extern LLRP_tEAlarmReportLevel
LLRP_AlarmReportInfo_getAlarmReportLevel (
  LLRP_tSAlarmReportInfo *pThis);

extern LLRP_tResultCode
LLRP_AlarmReportInfo_setAlarmReportLevel (
  LLRP_tSAlarmReportInfo *pThis,
  LLRP_tEAlarmReportLevel Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmReportInfo_AlarmReportSeconds;

extern llrp_u32_t
LLRP_AlarmReportInfo_getAlarmReportSeconds (
  LLRP_tSAlarmReportInfo *pThis);

extern LLRP_tResultCode
LLRP_AlarmReportInfo_setAlarmReportSeconds (
  LLRP_tSAlarmReportInfo *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmReportInfo_AlarmReportDescription;

extern llrp_utf8v_t
LLRP_AlarmReportInfo_getAlarmReportDescription (
  LLRP_tSAlarmReportInfo *pThis);

extern LLRP_tResultCode
LLRP_AlarmReportInfo_setAlarmReportDescription (
  LLRP_tSAlarmReportInfo *pThis,
  llrp_utf8v_t Value);

  


  
struct LLRP_SAlarmRestoreInfo
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t AlarmRestoreType;

    llrp_u32_t AlarmRestoreSeconds;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdAlarmRestoreInfo;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAlarmRestoreInfo[];

extern LLRP_tSAlarmRestoreInfo *
LLRP_AlarmRestoreInfo_construct (void);

extern void
LLRP_AlarmRestoreInfo_destruct (
 LLRP_tSAlarmRestoreInfo * pThis);

extern void
LLRP_AlarmRestoreInfo_decodeFields (
 LLRP_tSAlarmRestoreInfo * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AlarmRestoreInfo_assimilateSubParameters (
 LLRP_tSAlarmRestoreInfo * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AlarmRestoreInfo_encode (
  const LLRP_tSAlarmRestoreInfo *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmRestoreInfo_AlarmRestoreType;

extern llrp_u8_t
LLRP_AlarmRestoreInfo_getAlarmRestoreType (
  LLRP_tSAlarmRestoreInfo *pThis);

extern LLRP_tResultCode
LLRP_AlarmRestoreInfo_setAlarmRestoreType (
  LLRP_tSAlarmRestoreInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmRestoreInfo_AlarmRestoreSeconds;

extern llrp_u32_t
LLRP_AlarmRestoreInfo_getAlarmRestoreSeconds (
  LLRP_tSAlarmRestoreInfo *pThis);

extern LLRP_tResultCode
LLRP_AlarmRestoreInfo_setAlarmRestoreSeconds (
  LLRP_tSAlarmRestoreInfo *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SAlarmSyncInfo
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t AlarmSyncSeq;

    llrp_u8_t AlarmSyncType;

    llrp_u16_t AlarmSyncPackageNo;

    llrp_u16_t AlarmSyncPackageNum;

    llrp_u32v_t AlarmIDs;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdAlarmSyncInfo;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAlarmSyncInfo[];

extern LLRP_tSAlarmSyncInfo *
LLRP_AlarmSyncInfo_construct (void);

extern void
LLRP_AlarmSyncInfo_destruct (
 LLRP_tSAlarmSyncInfo * pThis);

extern void
LLRP_AlarmSyncInfo_decodeFields (
 LLRP_tSAlarmSyncInfo * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AlarmSyncInfo_assimilateSubParameters (
 LLRP_tSAlarmSyncInfo * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AlarmSyncInfo_encode (
  const LLRP_tSAlarmSyncInfo *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmSyncInfo_AlarmSyncSeq;

extern llrp_u32_t
LLRP_AlarmSyncInfo_getAlarmSyncSeq (
  LLRP_tSAlarmSyncInfo *pThis);

extern LLRP_tResultCode
LLRP_AlarmSyncInfo_setAlarmSyncSeq (
  LLRP_tSAlarmSyncInfo *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmSyncInfo_AlarmSyncType;

extern llrp_u8_t
LLRP_AlarmSyncInfo_getAlarmSyncType (
  LLRP_tSAlarmSyncInfo *pThis);

extern LLRP_tResultCode
LLRP_AlarmSyncInfo_setAlarmSyncType (
  LLRP_tSAlarmSyncInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmSyncInfo_AlarmSyncPackageNo;

extern llrp_u16_t
LLRP_AlarmSyncInfo_getAlarmSyncPackageNo (
  LLRP_tSAlarmSyncInfo *pThis);

extern LLRP_tResultCode
LLRP_AlarmSyncInfo_setAlarmSyncPackageNo (
  LLRP_tSAlarmSyncInfo *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmSyncInfo_AlarmSyncPackageNum;

extern llrp_u16_t
LLRP_AlarmSyncInfo_getAlarmSyncPackageNum (
  LLRP_tSAlarmSyncInfo *pThis);

extern LLRP_tResultCode
LLRP_AlarmSyncInfo_setAlarmSyncPackageNum (
  LLRP_tSAlarmSyncInfo *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmSyncInfo_AlarmIDs;

extern llrp_u32v_t
LLRP_AlarmSyncInfo_getAlarmIDs (
  LLRP_tSAlarmSyncInfo *pThis);

extern LLRP_tResultCode
LLRP_AlarmSyncInfo_setAlarmIDs (
  LLRP_tSAlarmSyncInfo *pThis,
  llrp_u32v_t Value);

  


  
struct LLRP_SDiagnosticTestItem
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t DiagnosticTestID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdDiagnosticTestItem;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDiagnosticTestItem[];

extern LLRP_tSDiagnosticTestItem *
LLRP_DiagnosticTestItem_construct (void);

extern void
LLRP_DiagnosticTestItem_destruct (
 LLRP_tSDiagnosticTestItem * pThis);

extern void
LLRP_DiagnosticTestItem_decodeFields (
 LLRP_tSDiagnosticTestItem * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DiagnosticTestItem_assimilateSubParameters (
 LLRP_tSDiagnosticTestItem * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DiagnosticTestItem_encode (
  const LLRP_tSDiagnosticTestItem *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdDiagnosticTestItem_DiagnosticTestID;

extern llrp_u16_t
LLRP_DiagnosticTestItem_getDiagnosticTestID (
  LLRP_tSDiagnosticTestItem *pThis);

extern LLRP_tResultCode
LLRP_DiagnosticTestItem_setDiagnosticTestID (
  LLRP_tSDiagnosticTestItem *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SDiagnosticTestResultItem
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t DiagnosticTestID;

    llrp_u32_t DiagnosticTestResultCode;

  
    LLRP_tSParameter * pDiagnosticTestResultData;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdDiagnosticTestResultItem;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDiagnosticTestResultItem[];

extern LLRP_tSDiagnosticTestResultItem *
LLRP_DiagnosticTestResultItem_construct (void);

extern void
LLRP_DiagnosticTestResultItem_destruct (
 LLRP_tSDiagnosticTestResultItem * pThis);

extern void
LLRP_DiagnosticTestResultItem_decodeFields (
 LLRP_tSDiagnosticTestResultItem * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DiagnosticTestResultItem_assimilateSubParameters (
 LLRP_tSDiagnosticTestResultItem * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DiagnosticTestResultItem_encode (
  const LLRP_tSDiagnosticTestResultItem *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdDiagnosticTestResultItem_DiagnosticTestID;

extern llrp_u16_t
LLRP_DiagnosticTestResultItem_getDiagnosticTestID (
  LLRP_tSDiagnosticTestResultItem *pThis);

extern LLRP_tResultCode
LLRP_DiagnosticTestResultItem_setDiagnosticTestID (
  LLRP_tSDiagnosticTestResultItem *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdDiagnosticTestResultItem_DiagnosticTestResultCode;

extern llrp_u32_t
LLRP_DiagnosticTestResultItem_getDiagnosticTestResultCode (
  LLRP_tSDiagnosticTestResultItem *pThis);

extern LLRP_tResultCode
LLRP_DiagnosticTestResultItem_setDiagnosticTestResultCode (
  LLRP_tSDiagnosticTestResultItem *pThis,
  llrp_u32_t Value);

  
extern LLRP_tSParameter *
LLRP_DiagnosticTestResultItem_getDiagnosticTestResultData (
  LLRP_tSDiagnosticTestResultItem *pThis);

extern LLRP_tResultCode
LLRP_DiagnosticTestResultItem_setDiagnosticTestResultData (
  LLRP_tSDiagnosticTestResultItem *pThis,
  LLRP_tSParameter *pValue);



  
struct LLRP_SDiagnosticTestResultAntennaConnected
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t AntennaID;

    llrp_u1_t AntennaConnected;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdDiagnosticTestResultAntennaConnected;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDiagnosticTestResultAntennaConnected[];

extern LLRP_tSDiagnosticTestResultAntennaConnected *
LLRP_DiagnosticTestResultAntennaConnected_construct (void);

extern void
LLRP_DiagnosticTestResultAntennaConnected_destruct (
 LLRP_tSDiagnosticTestResultAntennaConnected * pThis);

extern void
LLRP_DiagnosticTestResultAntennaConnected_decodeFields (
 LLRP_tSDiagnosticTestResultAntennaConnected * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DiagnosticTestResultAntennaConnected_assimilateSubParameters (
 LLRP_tSDiagnosticTestResultAntennaConnected * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DiagnosticTestResultAntennaConnected_encode (
  const LLRP_tSDiagnosticTestResultAntennaConnected *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdDiagnosticTestResultAntennaConnected_AntennaID;

extern llrp_u8_t
LLRP_DiagnosticTestResultAntennaConnected_getAntennaID (
  LLRP_tSDiagnosticTestResultAntennaConnected *pThis);

extern LLRP_tResultCode
LLRP_DiagnosticTestResultAntennaConnected_setAntennaID (
  LLRP_tSDiagnosticTestResultAntennaConnected *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdDiagnosticTestResultAntennaConnected_AntennaConnected;

extern llrp_u1_t
LLRP_DiagnosticTestResultAntennaConnected_getAntennaConnected (
  LLRP_tSDiagnosticTestResultAntennaConnected *pThis);

extern LLRP_tResultCode
LLRP_DiagnosticTestResultAntennaConnected_setAntennaConnected (
  LLRP_tSDiagnosticTestResultAntennaConnected *pThis,
  llrp_u1_t Value);

  


  
struct LLRP_SDiagnosticTestResultAntennaVSWR
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t AntennaID;

    llrp_u16_t AntennaVSWR;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdDiagnosticTestResultAntennaVSWR;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDiagnosticTestResultAntennaVSWR[];

extern LLRP_tSDiagnosticTestResultAntennaVSWR *
LLRP_DiagnosticTestResultAntennaVSWR_construct (void);

extern void
LLRP_DiagnosticTestResultAntennaVSWR_destruct (
 LLRP_tSDiagnosticTestResultAntennaVSWR * pThis);

extern void
LLRP_DiagnosticTestResultAntennaVSWR_decodeFields (
 LLRP_tSDiagnosticTestResultAntennaVSWR * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DiagnosticTestResultAntennaVSWR_assimilateSubParameters (
 LLRP_tSDiagnosticTestResultAntennaVSWR * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DiagnosticTestResultAntennaVSWR_encode (
  const LLRP_tSDiagnosticTestResultAntennaVSWR *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdDiagnosticTestResultAntennaVSWR_AntennaID;

extern llrp_u8_t
LLRP_DiagnosticTestResultAntennaVSWR_getAntennaID (
  LLRP_tSDiagnosticTestResultAntennaVSWR *pThis);

extern LLRP_tResultCode
LLRP_DiagnosticTestResultAntennaVSWR_setAntennaID (
  LLRP_tSDiagnosticTestResultAntennaVSWR *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdDiagnosticTestResultAntennaVSWR_AntennaVSWR;

extern llrp_u16_t
LLRP_DiagnosticTestResultAntennaVSWR_getAntennaVSWR (
  LLRP_tSDiagnosticTestResultAntennaVSWR *pThis);

extern LLRP_tResultCode
LLRP_DiagnosticTestResultAntennaVSWR_setAntennaVSWR (
  LLRP_tSDiagnosticTestResultAntennaVSWR *pThis,
  llrp_u16_t Value);

  



extern llrp_bool_t
LLRP_DeviceAirProtocolCapabilities_isMember (
  LLRP_tSParameter *            pParameter);

extern const LLRP_tSTypeDescriptor
LLRP_tdDeviceAirProtocolCapabilities;


extern llrp_bool_t
LLRP_SpecParameter_isMember (
  LLRP_tSParameter *            pParameter);

extern const LLRP_tSTypeDescriptor
LLRP_tdSpecParameter;


extern llrp_bool_t
LLRP_MatchSpec_isMember (
  LLRP_tSParameter *            pParameter);

extern const LLRP_tSTypeDescriptor
LLRP_tdMatchSpec;


extern llrp_bool_t
LLRP_OpSpec_isMember (
  LLRP_tSParameter *            pParameter);

extern const LLRP_tSTypeDescriptor
LLRP_tdOpSpec;


extern llrp_bool_t
LLRP_AccessSpecResult_isMember (
  LLRP_tSParameter *            pParameter);

extern const LLRP_tSTypeDescriptor
LLRP_tdAccessSpecResult;


extern llrp_bool_t
LLRP_EthernetConfiguration_isMember (
  LLRP_tSParameter *            pParameter);

extern const LLRP_tSTypeDescriptor
LLRP_tdEthernetConfiguration;


extern llrp_bool_t
LLRP_LocationInfo_isMember (
  LLRP_tSParameter *            pParameter);

extern const LLRP_tSTypeDescriptor
LLRP_tdLocationInfo;


extern llrp_bool_t
LLRP_DiagnosticTestResultData_isMember (
  LLRP_tSParameter *            pParameter);

extern const LLRP_tSTypeDescriptor
LLRP_tdDiagnosticTestResultData;


void
LLRP_enrollCoreTypesIntoRegistry (
  LLRP_tSTypeRegistry *         pTypeRegistry);

