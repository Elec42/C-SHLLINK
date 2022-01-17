/*
    This library provides an interface for the MS Shell Link Binary File Format in C [MS-SHLLINK](https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-shllink/16cb4ca1-9339-4d0c-a68d-bf1d6cc0f943)

    

    Author: Felix Kröhnert
    License: GNU GPL V3 (refer to LICENSE for more information)
*/

#ifndef _CSHLLINK_H_
#define _CSHLLINK_H_

    #include <inttypes.h>

    /*
        SHLLINK Header
    */
    struct _cshllink_header{
        uint32_t HeaderSize;
        uint64_t LinkCLSID;
        uint32_t LinkFlags;
        uint32_t FileAttributes;
        uint64_t CreationTime;
        uint64_t AccessTime;
        uint64_t WriteTime;
        uint32_t FileSize;
        uint32_t IconIndex;
        uint32_t ShowCommand;
        uint16_t HotKey;
        /*
            + 10 bytes NULL
        */
    };
    /*
        SHLLINK LinkTargetIDList
    */
        /*
            SHLLINK LinkTargetIDList - IDList (terminated with TerminalBlock (2 Bytes NULL))
        */
        struct _cshllink_lnktidl_idl{
            uint8_t idl_inum;
            uint8_t *idl;
        };
    struct _cshllink_lnktidl{
        /*
            List of IDList elements
        */
        uint16_t idl_size;
        struct _cshllink_lnktidl_idl cshllink_lnktidl_idl;
    };
    /*
        SHLLINK LinkInfo
    */
        /*
        SHLLINK LinkInfo - VolumeID
        */
        struct _cshllink_lnkinfo_volid{
            uint32_t VolumeIDSize;
            uint32_t DriveType;
            uint32_t DriveSerialNumber;
            uint32_t VolumeLabelOffset;
            uint32_t VolumeLabelOffsetUnicode;
            uint8_t *Data;
        };
        /*
        SHLLINK LinkInfo - CommonNetworkRelativeLink
        */
        struct _cshllink_lnkinfo_cnetrlnk{
            uint32_t CommonNetworkRelativeSize;
            uint32_t CommonNetworkRelativeLinkFlags;
            uint32_t NetNameOffset;
            uint32_t DeviceNameOffset;
            uint32_t NetworkProviderType;
            uint32_t NetNameOffsetUnicode;
            uint32_t DeviceNameOffsetUnicode;
            uint8_t *NetName;
            uint8_t *DeviceName;
            uint8_t *NetNameUnicode;
            uint8_t *DeviceNameUnicode;
        };
    struct _cshllink_lnkinfo{
        uint32_t LinkInfoSize;
        uint32_t LinkInfoHeaderSize;
        uint32_t LinkInfoFlags;
        uint32_t VolumeIDOffset;
        uint32_t LocalBasePathOffset;
        uint32_t CommonNetworkRelativeLinkOffset;
        uint32_t CommonPathSuffixOffset;
        uint32_t LocalBasePathOffsetUnicode;
        uint32_t CommonPathSuffixOffsetUnicode;
        struct _cshllink_lnkinfo_volid cshllink_lnkinfo_volid;
        uint8_t *LocalBasePath;
        struct _cshllink_lnkinfo_cnetrlnk cshllink_lnkinfo_cnetrlnk;
        uint8_t *CommonPathSuffix;
        uint8_t *LocalBasePathUnicode;
        uint8_t *CommonPathSuffixUnicode;
    };
    /*
        SHLLINK StringData
    */
        /*
            SHLLINK StringData - Data
        */
       struct _cshllink_strdata_def{
           uint16_t CountCharacters;
           uint8_t *String;
       };
    struct _cshllink_strdata{
        struct _cshllink_strdata_def NameString;
        struct _cshllink_strdata_def RelativePath;
        struct _cshllink_strdata_def WorkingDir;
        struct _cshllink_strdata_def CommandLineArguments;
        struct _cshllink_strdata_def IconLocation;
    };
    /*
        SHLLINK ExtraDataBlock (terminated with TerminalBlock (4 Bytes NULL))
    */
            /*
            SHLLINK ExtraDataBlock - BlockInfo
            */
            struct _cshllink_extdatablk_blk_info{
                uint32_t BlockSize;
                uint32_t BlockSignature;
            };
        /*
            SHLLINK ExtraDataBlock - ConsoleDataBlock
        */
        struct _cshllink_extdatablk_consdblk{
            struct _cshllink_extdatablk_blk_info info;
            uint16_t FillAttributes;
            uint16_t PopupFillAttributes;
            uint16_t ScreenBufferSizeX;
            uint16_t ScreenBufferSizeY;
            uint16_t WindowSizeX;
            uint16_t WindowSizeY;
            uint16_t WindowOriginX;
            uint16_t WindowOriginY;
            /*8 bytes unused data*/
            uint32_t FontSize;
            uint32_t FontFamily;
            uint32_t FontWeight;
            uint8_t FaceName[65];
            uint32_t CursorSize;
            uint32_t FullScreen;
            uint32_t QuickEdit;
            uint32_t InsertMode;
            uint32_t AutoPosition;
            uint32_t HistoryBufferSize;
            uint32_t NumberOfHistoryBuffers;
            uint32_t HistoryNoDup;
            uint32_t ColorTable[16];
        };
        /*
            SHLLINK ExtraDataBlock - ConsoleFEDataBlock
        */
        struct _cshllink_extdatablk_consfdblk{
            struct _cshllink_extdatablk_blk_info info;
            uint32_t CodePage;
        };
        /*
            SHLLINK ExtraDataBlock - DarwinDataBlock
        */
        struct _cshllink_extdatablk_darwdblk{
            struct _cshllink_extdatablk_blk_info info;
            uint8_t DarwinDataAnsi[260];
            uint8_t DarwinDataUnicode[520];
        };
        /*
            SHLLINK ExtraDataBlock - EnvironmentVariableDataBlock
        */
        struct _cshllink_extdatablk_envdblk{
            struct _cshllink_extdatablk_blk_info info;
            uint8_t TargetAnsi[260];
            uint8_t TargetUnicode[520];
        };
        /*
            SHLLINK ExtraDataBlock - IconEnvironmentDataBlock
        */
        struct _cshllink_extdatablk_icoenvdblk{
            struct _cshllink_extdatablk_blk_info info;
            uint8_t TargetAnsi[260];
            uint8_t TargetUnicode[520];
        };
        /*
            SHLLINK ExtraDataBlock - KnownFolderDataBlock
        */
        struct _cshllink_extdatablk_knownfdblk{
            struct _cshllink_extdatablk_blk_info info;
            uint8_t KnownFolderID[16];
            uint32_t Offset;
        };
        /*
            SHLLINK ExtraDataBlock - PropertyStoreDataBlock
        */
        struct _cshllink_extdatablk_propsdblk{
            struct _cshllink_extdatablk_blk_info info;
            uint8_t *PropertyStore;
        };
        /*
            SHLLINK ExtraDataBlock - ShimDataBlock
        */
        struct _cshllink_extdatablk_shimblk{
            struct _cshllink_extdatablk_blk_info info;
            uint8_t *LayerName;
        };
        /*
            SHLLINK ExtraDataBlock - SpecialFolderDataBlock
        */
        struct _cshllink_extdatablk_specfdblk{
            struct _cshllink_extdatablk_blk_info info;
            uint32_t SpecialFolderID;
            uint32_t Offset;
        };
        /*
            SHLLINK ExtraDataBlock - TrackerDataBlock
        */
        struct _cshllink_extdatablk_trackdblk{
            struct _cshllink_extdatablk_blk_info info;
            uint32_t Length;
            uint32_t Version;
            uint8_t MachineID[16];
            uint8_t Droid[32];
            uint8_t DroidBirth[32];
        };
        /*
            SHLLINK ExtraDataBlock - VistaAndAboveIDListDataBlock
        */
        struct _cshllink_extdatablk_viidldblk{
            struct _cshllink_extdatablk_blk_info info;
            struct _cshllink_lnktidl_idl cshllink_lnktidl_idl;
        };
    struct _cshllink_extdatablk{
        struct _cshllink_extdatablk_consdblk *ConsoleDataBlock;
        struct _cshllink_extdatablk_consfdblk *ConsoleFEDataBlock;
        struct _cshllink_extdatablk_darwdblk *DarwinDataBlock;
        struct _cshllink_extdatablk_envdblk *EnvironmentVariableDataBlock;
        struct _cshllink_extdatablk_icoenvdblk *IconEnvironmentDataBlock;
        struct _cshllink_extdatablk_knownfdblk *KnownFolderDataBlock;
        struct _cshllink_extdatablk_propsdblk *PropertyStoreDataBlock;
        struct _cshllink_extdatablk_shimblk *ShimDataBlock;
        struct _cshllink_extdatablk_specfdblk *SpecialFolderDataBlock;
        struct _cshllink_extdatablk_trackdblk *TrackerDataBlock;
        struct _cshllink_extdatablk_viidldblk *VistaAndAboveIDListDataBlock;
    };


    /*
        SHLLINK Structure
    */
    struct _cshllink {

        /*
            SHLLINK Header
        */
        struct _cshllink_header cshllink_header;
        /*
            SHLLINK LinkTargetIDList
        */
        struct _cshllink_lnktidl cshllink_lnktidl;
        /*
            SHLLINK LinkInfo
        */
        struct _cshllink_lnkinfo cshllink_lnkinfo;
        /*
        SHLLINK StringData
        */
        struct _cshllink_strdata cshllink_strdata;
        /*
        SHLLINK ExtraData
        */
        struct _cshllink_extdatablk cshllink_extdatablk;
    };

#endif