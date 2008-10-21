/* ------------------------------------------------------------------
 * Copyright (C) 2008 PacketVideo
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 * -------------------------------------------------------------------
 */
#ifndef PV_PLAYER_ENGINE_H_INCLUDED
#define PV_PLAYER_ENGINE_H_INCLUDED

#ifndef OSCL_BASE_H_INCLUDED
#include "oscl_base.h"
#endif

#ifndef OSCL_MEM_H_INCLUDED
#include "oscl_mem.h"
#endif

#ifndef OSCL_SCHEDULER_AO_H_INCLUDED
#include "oscl_scheduler_ao.h"
#endif

#ifndef OSCL_VECTOR_H_INCLUDED
#include "oscl_vector.h"
#endif

#ifndef OSCL_PRIQUEUE_H_INCLUDED
#include "oscl_priqueue.h"
#endif

#ifndef OSCL_CLOCK_H_INCLUDED
#include "oscl_clock.h"
#endif

#ifndef PV_ENGINE_TYPES_H_INCLUDED
#include "pv_engine_types.h"
#endif

#ifndef PV_PLAYER_DATASOURCE_H_INCLUDED
#include "pv_player_datasource.h"
#endif

#ifndef PV_PLAYER_DATASINK_H_INCLUDED
#include "pv_player_datasink.h"
#endif

#ifndef PV_PLAYER_INTERFACE_H_INCLUDED
#include "pv_player_interface.h"
#endif

#ifndef PV_ENGINE_OBSERVER_H_INCLUDED
#include "pv_engine_observer.h"
#endif

#ifndef PVMF_NODE_INTERFACE_H_INCLUDED
#include "pvmf_node_interface.h"
#endif

#ifndef PV_PLAYER_DATAPATH_H_INCLUDED
#include "pv_player_datapath.h"
#endif

#ifndef PV_PLAYER_NODE_REGISTRY_H_INCLUDED
#include "pv_player_node_registry.h"
#endif

#ifndef PVMF_META_DATA_TYPES_H_INCLUDED
#include "pvmf_meta_data_types.h"
#endif

#ifndef PVMF_META_DATA_EXTENSION_H_INCLUDED
#include "pvmf_meta_data_extension.h"
#endif

#ifndef PVMF_DATA_SOURCE_INIT_EXTENSION_H_INCLUDED
#include "pvmf_data_source_init_extension.h"
#endif

#ifndef PVMF_MEDIA_PRESENTATION_INFO_H_INCLUDED
#include "pvmf_media_presentation_info.h"
#endif

#ifndef OSCL_TIMER_H_INCLUDED
#include "oscl_timer.h"
#endif

#ifndef OSCL_MEM_MEMPOOL_H_INCLUDED
#include "oscl_mem_mempool.h"
#endif

#ifndef PVMI_CONFIG_AND_CAPABILITY_H_INCLUDED
#include "pvmi_config_and_capability.h"
#endif

#ifndef PV_PLAYER_LICENSE_ACQUISITION_INTERFACE_H_INCLUDED
#include "pv_player_license_acquisition_interface.h"
#endif

#ifndef PVMF_CPMPLUGIN_INTERFACE_H_INCLUDED
#include "pvmf_cpmplugin_interface.h"
#endif

#ifndef CPM_PLUGIN_REGISTRY_H
#include "cpm_plugin_registry.h"
#endif

#ifndef PVMF_DATA_SOURCE_PLAYBACK_CONTROL_H_INCLUDED
#include "pvmf_data_source_playback_control.h"
#endif

#ifndef PV_PLAYER_TRACK_SELECTION_INTERFACE_H_INCLUDED
#include "pv_player_track_selection_interface.h"
#endif


#ifdef HAS_OSCL_LIB_SUPPORT
#ifndef PV_PLAYER_REGISTRY_INTERFACE_H_INCLUDED
#include "pv_player_registry_interface.h"
#endif

#ifndef PVMF_NODE_SHARED_LIB_INTERFACE_H_INCLUDED
#include "pvmf_node_shared_lib_interface.h"
#endif
#endif

/**
 * PVPlayerEngineState enum
 *
 *  Enumeration of internal pvPlayer engine state.
 *
 **/
typedef enum
{
    PVP_ENGINE_STATE_IDLE = 1,
    PVP_ENGINE_STATE_INITIALIZING,
    PVP_ENGINE_STATE_INITIALIZED,
    PVP_ENGINE_STATE_PREPARING,
    PVP_ENGINE_STATE_PREPARED,
    PVP_ENGINE_STATE_STARTING,
    PVP_ENGINE_STATE_STARTED,
    PVP_ENGINE_STATE_AUTO_PAUSING,
    PVP_ENGINE_STATE_AUTO_PAUSED,
    PVP_ENGINE_STATE_AUTO_RESUMING,
    PVP_ENGINE_STATE_PAUSING,
    PVP_ENGINE_STATE_PAUSED,
    PVP_ENGINE_STATE_RESUMING,
    PVP_ENGINE_STATE_STOPPING,
    PVP_ENGINE_STATE_RESETTING,
    PVP_ENGINE_STATE_HANDLINGERROR,
    PVP_ENGINE_STATE_ERROR
} PVPlayerEngineState;


typedef union PVPlayerEngineCommandParamUnion
{
    bool  bool_value;
    float float_value;
    double double_value;
    uint8 uint8_value;
    int32 int32_value;
    uint32 uint32_value;
    PVPPlaybackPosition playbackpos_value;
    oscl_wchar* pWChar_value;
    char* pChar_value;
    uint8* pUint8_value;
    int32* pInt32_value;
    uint32* pUint32_value;
    int64* pInt64_value;
    uint64*  pUint64_value;
    PVPPlaybackPosition* pPlaybackpos_value;
    OsclAny* pOsclAny_value;
} _PVPlayerEngineCommandParamUnion;

/**
 * PVPlayerEngineCommand Class
 *
 * PVPlayerEngineCommand class is a data class to hold issued commands inside the player engine
 **/
class PVPlayerEngineCommand
{
    public:
        /**
         * The constructor for PVPlayerEngineCommand which allows the data values to be set.
         *
         * @param aCmdType The command type value for this command. The value is an engine-specific 32-bit value.
         * @param aCmdId The command ID assigned by the engine for this command.
         * @param aContextData The pointer to the passed-in context data for this command.
         *
         * @returns None
         **/
        PVPlayerEngineCommand(int32 aCmdType, PVCommandId aCmdId, OsclAny* aContextData = NULL,
                              Oscl_Vector<PVPlayerEngineCommandParamUnion, OsclMemAllocator>* aParamVector = NULL, bool aAPICommand = true) :
                iCmdType(aCmdType), iCmdId(aCmdId), iContextData(aContextData), iAPICommand(aAPICommand)
        {
            iParamVector.clear();
            if (aParamVector)
            {
                iParamVector = *aParamVector;
            }
        }

        /**
         * The copy constructor for PVPlayerEngineCommand. Used mainly for Oscl_Vector.
         *
         * @param aCmd The reference to the source PVPlayerEngineCommand to copy the data values from.
         *
         * @returns None
         **/
        PVPlayerEngineCommand(const PVPlayerEngineCommand& aCmd)
        {
            iCmdType = aCmd.iCmdType;
            iCmdId = aCmd.iCmdId;
            iContextData = aCmd.iContextData;
            iAPICommand = aCmd.iAPICommand;
            iParamVector = aCmd.iParamVector;
            iMimeType = aCmd.iMimeType;
            iUuid = aCmd.iUuid;
        }

        /**
         * This function returns the stored command type value.
         *
         * @returns The signed 32-bit command type value for this command.
         **/
        int32 GetCmdType()const
        {
            return iCmdType;
        }

        /**
         * This function returns the stored command ID value.
         *
         * @returns The PVCommandId value for this command.
         **/
        PVCommandId GetCmdId()const
        {
            return iCmdId;
        }

        /**
         * This function returns the stored context data pointer.
         *
         * @returns The pointer to the context data for this command
         **/
        OsclAny* GetContext()const
        {
            return iContextData;
        }

        /**
         * This function tells whether the command is an API command or not
         *
         * @returns true if API command, false if not.
         **/
        bool IsAPICommand()const
        {
            return iAPICommand;
        }

        /**
         * This function returns the command parameter from the specified index.
         * If the specified index is not available, empty parameter will be returned
         *
         * @param aIndex The index of the parameter to return
         *
         * @returns The stored parameter for this command
         **/
        PVPlayerEngineCommandParamUnion GetParam(uint32 aIndex)const
        {
            if (aIndex >= iParamVector.size())
            {
                PVPlayerEngineCommandParamUnion param;
                oscl_memset(&param, 0, sizeof(PVPlayerEngineCommandParamUnion));
                return param;
            }
            else
            {
                return iParamVector[aIndex];
            }
        }

        /**
         * This function returns Mime type parameter for this command
         *
         * @returns The Mime type parameter for this command
         */
        const PvmfMimeString& GetMimeType()const
        {
            return iMimeType;
        }

        /**
         * This function returns Uuid parameter for this command
         *
         * @returns The Uuid parameter for this command
         */
        PVUuid GetUuid()const
        {
            return iUuid;
        }

        /**
         * This function stores Mime type parameter of this command
         */
        void SetMimeType(const PvmfMimeString& aMimeType)
        {
            iMimeType = aMimeType;
        }

        /**
         * This function stores the Uuid parameter of this command
         */
        void SetUuid(const PVUuid& aUuid)
        {
            iUuid = aUuid;
        }

        /**
         * Equality operator, for use by OsclPriorityQueue.
         */
        bool operator==(const PVPlayerEngineCommand& aCmd) const
        {
            return iCmdId == aCmd.iCmdId;
        }

        int32 iCmdType;
        PVCommandId iCmdId;
        OsclAny* iContextData;
        bool iAPICommand;
        Oscl_Vector<PVPlayerEngineCommandParamUnion, OsclMemAllocator> iParamVector;
        OSCL_HeapString<OsclMemAllocator> iMimeType;
        PVUuid iUuid;
};

/**
 * PVPlayerEngineCommandType enum
 *
 *  Enumeration of types of commands that can be issued to the pvPlayer.
 *
 **/
typedef enum
{
    // Engine API commands
    PVP_ENGINE_COMMAND_GET_SDK_INFO = 1,
    PVP_ENGINE_COMMAND_GET_SDK_MODULE_INFO,
    PVP_ENGINE_COMMAND_SET_LOG_APPENDER,
    PVP_ENGINE_COMMAND_REMOVE_LOG_APPENDER,
    PVP_ENGINE_COMMAND_SET_LOG_LEVEL,
    PVP_ENGINE_COMMAND_GET_LOG_LEVEL,
    PVP_ENGINE_COMMAND_QUERY_UUID,
    PVP_ENGINE_COMMAND_QUERY_INTERFACE,
    PVP_ENGINE_COMMAND_CANCEL_ALL_COMMANDS,
    PVP_ENGINE_COMMAND_GET_PVPLAYER_STATE,
    PVP_ENGINE_COMMAND_ADD_DATA_SOURCE,
    PVP_ENGINE_COMMAND_INIT,
    PVP_ENGINE_COMMAND_GET_METADATA_KEY,
    PVP_ENGINE_COMMAND_GET_METADATA_VALUE,
    PVP_ENGINE_COMMAND_ADD_DATA_SINK,
    PVP_ENGINE_COMMAND_SET_PLAYBACK_RANGE,
    PVP_ENGINE_COMMAND_GET_PLAYBACK_RANGE,
    PVP_ENGINE_COMMAND_GET_CURRENT_POSITION,
    PVP_ENGINE_COMMAND_SET_PLAYBACK_RATE,
    PVP_ENGINE_COMMAND_GET_PLAYBACK_RATE,
    PVP_ENGINE_COMMAND_GET_PLAYBACK_MINMAX_RATE,
    PVP_ENGINE_COMMAND_PREPARE,
    PVP_ENGINE_COMMAND_START,
    PVP_ENGINE_COMMAND_PAUSE,
    PVP_ENGINE_COMMAND_RESUME,
    PVP_ENGINE_COMMAND_STOP,
    PVP_ENGINE_COMMAND_REMOVE_DATA_SINK,
    PVP_ENGINE_COMMAND_RESET,
    PVP_ENGINE_COMMAND_REMOVE_DATA_SOURCE,
    PVP_ENGINE_COMMAND_CAPCONFIG_SET_PARAMETERS,
    PVP_ENGINE_COMMAND_ACQUIRE_LICENSE_WCHAR,
    PVP_ENGINE_COMMAND_ACQUIRE_LICENSE_CHAR,
    PVP_ENGINE_COMMAND_CANCEL_ACQUIRE_LICENSE,
    // Internal engine commands
    PVP_ENGINE_COMMAND_PAUSE_DUE_TO_ENDTIME_REACHED,
    PVP_ENGINE_COMMAND_PAUSE_DUE_TO_ENDOFCLIP,
    PVP_ENGINE_COMMAND_PAUSE_DUE_TO_BUFFER_UNDERFLOW,
    PVP_ENGINE_COMMAND_RESUME_DUE_TO_BUFFER_DATAREADY,
    PVP_ENGINE_COMMAND_CANCEL_DUE_TO_ERROR,
    PVP_ENGINE_COMMAND_STOP_DUE_TO_ERROR,
    PVP_ENGINE_COMMAND_RESET_DUE_TO_ERROR,
    PVP_ENGINE_COMMAND_CLEANUP_DUE_TO_ERROR,
    PVP_ENGINE_COMMAND_DATAPATH_DELETE
} PVPlayerEngineCommandType;


/**
 * PVPlayerEngineCommandCompareLess Class
 *
 * PVPlayerEngineCommandCompareLess class is a utility class to allow the OSCL priority queue perform command priority comparison.
 * The class is meant to be used inside the player engine and not exposed to the interface layer or above.
 **/
class PVPlayerEngineCommandCompareLess
{
    public:
        /**
        * The algorithm used in OsclPriorityQueue needs a compare function
        * that returns true when A's priority is less than B's
        * @return true if A's priority is less than B's, else false
        */
        int compare(PVPlayerEngineCommand& a, PVPlayerEngineCommand& b) const
        {
            int a_pri = PVPlayerEngineCommandCompareLess::GetPriority(a);
            int b_pri = PVPlayerEngineCommandCompareLess::GetPriority(b);
            if (a_pri < b_pri)
            {
                // Higher priority
                return false;
            }
            else if (a_pri == b_pri)
            {
                // Same priority so look at the command ID to maintain FIFO
                return (a.GetCmdId() > b.GetCmdId());
            }
            else
            {
                // Lower priority
                return true;
            }
        }

        /**
        * Returns the priority of each command
        * @return A 0-based priority number. A lower number indicates higher priority.
        */
        static int GetPriority(PVPlayerEngineCommand& aCmd)
        {
            switch (aCmd.GetCmdType())
            {
                case PVP_ENGINE_COMMAND_GET_SDK_INFO:
                    return 5;
                case PVP_ENGINE_COMMAND_GET_SDK_MODULE_INFO:
                    return 5;
                case PVP_ENGINE_COMMAND_SET_LOG_APPENDER:
                    return 5;
                case PVP_ENGINE_COMMAND_REMOVE_LOG_APPENDER:
                    return 5;
                case PVP_ENGINE_COMMAND_SET_LOG_LEVEL:
                    return 5;
                case PVP_ENGINE_COMMAND_GET_LOG_LEVEL:
                    return 5;
                case PVP_ENGINE_COMMAND_QUERY_UUID:
                    return 5;
                case PVP_ENGINE_COMMAND_QUERY_INTERFACE:
                    return 5;
                case PVP_ENGINE_COMMAND_CANCEL_ALL_COMMANDS:
                    return 3;
                case PVP_ENGINE_COMMAND_GET_PVPLAYER_STATE:
                    return 5;
                case PVP_ENGINE_COMMAND_ADD_DATA_SOURCE:
                    return 5;
                case PVP_ENGINE_COMMAND_INIT:
                    return 5;
                case PVP_ENGINE_COMMAND_GET_METADATA_KEY:
                    return 5;
                case PVP_ENGINE_COMMAND_GET_METADATA_VALUE:
                    return 5;
                case PVP_ENGINE_COMMAND_ADD_DATA_SINK:
                    return 5;
                case PVP_ENGINE_COMMAND_SET_PLAYBACK_RANGE:
                    return 5;
                case PVP_ENGINE_COMMAND_GET_PLAYBACK_RANGE:
                    return 5;
                case PVP_ENGINE_COMMAND_GET_CURRENT_POSITION:
                    return 5;
                case PVP_ENGINE_COMMAND_SET_PLAYBACK_RATE:
                    return 5;
                case PVP_ENGINE_COMMAND_GET_PLAYBACK_RATE:
                    return 5;
                case PVP_ENGINE_COMMAND_GET_PLAYBACK_MINMAX_RATE:
                    return 5;
                case PVP_ENGINE_COMMAND_PREPARE:
                    return 5;
                case PVP_ENGINE_COMMAND_START:
                    return 5;
                case PVP_ENGINE_COMMAND_PAUSE:
                    return 5;
                case PVP_ENGINE_COMMAND_RESUME:
                    return 5;
                case PVP_ENGINE_COMMAND_STOP:
                    return 5;
                case PVP_ENGINE_COMMAND_REMOVE_DATA_SINK:
                    return 5;
                case PVP_ENGINE_COMMAND_RESET:
                    return 5;
                case PVP_ENGINE_COMMAND_REMOVE_DATA_SOURCE:
                    return 5;
                case PVP_ENGINE_COMMAND_CAPCONFIG_SET_PARAMETERS:
                    return 5;
                case PVP_ENGINE_COMMAND_ACQUIRE_LICENSE_WCHAR:
                    return 5;
                case PVP_ENGINE_COMMAND_ACQUIRE_LICENSE_CHAR:
                    return 5;
                case PVP_ENGINE_COMMAND_CANCEL_ACQUIRE_LICENSE:
                    return 3;

                case PVP_ENGINE_COMMAND_PAUSE_DUE_TO_ENDTIME_REACHED:
                    return 4;
                case PVP_ENGINE_COMMAND_PAUSE_DUE_TO_ENDOFCLIP:
                    return 4;
                case PVP_ENGINE_COMMAND_PAUSE_DUE_TO_BUFFER_UNDERFLOW:
                    return 5;
                case PVP_ENGINE_COMMAND_RESUME_DUE_TO_BUFFER_DATAREADY:
                    return 5;

                case PVP_ENGINE_COMMAND_CANCEL_DUE_TO_ERROR:
                    return 1;

                case PVP_ENGINE_COMMAND_STOP_DUE_TO_ERROR:
                    return 2;
                case PVP_ENGINE_COMMAND_RESET_DUE_TO_ERROR:
                    return 2;
                case PVP_ENGINE_COMMAND_CLEANUP_DUE_TO_ERROR:
                    return 2;
                case PVP_ENGINE_COMMAND_DATAPATH_DELETE:
                    return 1;
                default:
                    return 0;
            }
        }
};


// Structure to hold the key string info for
// player engine's capability-and-config
struct PVPlayerKeyStringData
{
    char iString[64];
    PvmiKvpType iType;
    PvmiKvpValueType iValueType;
};

// The number of characters to allocate for the key string
#define PVPLAYERCONFIG_KEYSTRING_SIZE 128



// Key string info at the base level ("x-pvmf/player/")
#define PVPLAYERCONFIG_BASE_NUMKEYS 14
const PVPlayerKeyStringData PVPlayerConfigBaseKeys[PVPLAYERCONFIG_BASE_NUMKEYS] =
{
    {"pbpos_units", PVMI_KVPTYPE_VALUE, PVMI_KVPVALTYPE_CHARPTR},
    {"pbpos_interval", PVMI_KVPTYPE_VALUE, PVMI_KVPVALTYPE_UINT32},
    {"endtimecheck_interval", PVMI_KVPTYPE_VALUE, PVMI_KVPVALTYPE_UINT32},
    {"seektosyncpoint", PVMI_KVPTYPE_VALUE, PVMI_KVPVALTYPE_BOOL},
    {"skiptorequestedpos", PVMI_KVPTYPE_VALUE, PVMI_KVPVALTYPE_BOOL},
    {"renderskipped", PVMI_KVPTYPE_VALUE, PVMI_KVPVALTYPE_BOOL},
    {"syncpointseekwindow", PVMI_KVPTYPE_VALUE, PVMI_KVPVALTYPE_UINT32},
    {"syncmargin_video", PVMI_KVPTYPE_VALUE, PVMI_KVPVALTYPE_RANGE_INT32},
    {"syncmargin_audio", PVMI_KVPTYPE_VALUE, PVMI_KVPVALTYPE_RANGE_INT32},
    {"syncmargin_text", PVMI_KVPTYPE_VALUE, PVMI_KVPVALTYPE_RANGE_INT32},
    {"nodecmd_timeout", PVMI_KVPTYPE_VALUE, PVMI_KVPVALTYPE_UINT32},
    {"nodedataqueuing_timeout", PVMI_KVPTYPE_VALUE, PVMI_KVPVALTYPE_UINT32},
    {"productinfo", PVMI_KVPTYPE_AGGREGATE, PVMI_KVPVALTYPE_KSV},
    {"pbpos_enable", PVMI_KVPTYPE_VALUE, PVMI_KVPVALTYPE_BOOL}
};

// Key string info at the productinfo level ("x-pvmf/player/productinfo/")
#define PVPLAYERCONFIG_PRODINFO_NUMKEYS 5
const PVPlayerKeyStringData PVPlayerConfigProdInfoKeys[PVPLAYERCONFIG_PRODINFO_NUMKEYS] =
{
    {"productname", PVMI_KVPTYPE_VALUE, PVMI_KVPVALTYPE_CHARPTR},
    {"partnumber", PVMI_KVPTYPE_VALUE, PVMI_KVPVALTYPE_CHARPTR},
    {"hardwareplatform", PVMI_KVPTYPE_VALUE, PVMI_KVPVALTYPE_CHARPTR},
    {"softwareplatform", PVMI_KVPTYPE_VALUE, PVMI_KVPVALTYPE_CHARPTR},
    {"device", PVMI_KVPTYPE_VALUE, PVMI_KVPVALTYPE_CHARPTR}
};


// Player engine's timebase with rate change capability
class PVPlayerTimebase : public OsclTimebase_Tickcount
{
    public:
        PVPlayerTimebase()
        {
            iRate = 100000;
            iRateChangeTBTime = 0;
            iRateChangeTCTime = 0;
        }

        ~PVPlayerTimebase()
        {
        }

        void GetCurrentTime64(uint64& aTime, OsclClock_TimeUnits aUnits, uint64& aTimebaseTime)
        {
            if (aUnits != OSCLCLOCK_USEC)
            {
                // This is player engine specific timebase so only microsec is supported
                aTime = 0;
                aTimebaseTime = 0;
                return;
            }

            // Retrieve the tickcount time
            uint64 tickcounttime = 0;
            OsclTimebase_Tickcount::GetCurrentTime64(tickcounttime, aUnits, aTimebaseTime);

            // Calculate the tickcount since last rate change
            uint64 timesincechange = tickcounttime - iRateChangeTCTime;

            if (iRate != 100000)
            {
                // Adjust according to rate
                // Rate change resolution is 0.1
                uint64 convnum = (uint32)(iRate / 10000);
                uint64 convden = 10;
                aTime = ((timesincechange * convnum) / convden);
            }
            else
            {
                aTime = timesincechange;
            }

            // Add the timebase since last rate change
            aTime = aTime + iRateChangeTBTime;
        }

        void SetRate(int32 aRate)
        {
            // Save the tickcount time when the rate changed
            GetCurrentTime64(iRateChangeTBTime, OSCLCLOCK_USEC, iRateChangeTCTime);
            // Change the rate
            iRate = aRate;
        }

        int32 GetRate()
        {
            return iRate;
        }

    private:
        int32 iRate; // In millipercent of "real-time"
        uint64 iRateChangeTBTime;  // This timebase's time when rate last changed
        uint64 iRateChangeTCTime;  // The tickcount's time when rate last changed
};


class PVMFNodeInterface;
class PVMFDataSourceInitializationExtensionInterface;
class PVMFTrackSelectionExtensionInterface;
class PvmfDataSourcePlaybackControlInterface;
class PvmfDataSourceDirectionControlInterface;
class PVMFTrackLevelInfoExtensionInterface;
class PvmfNodesSyncControlInterface;
class PvmfFileOutputNodeConfigInterface;
class PVMFErrorInfoMessageInterface;
class PVLogger;
class PVMFCPMPluginLicenseInterface;
class PVMFBasicErrorInfoMessage;
class PVPlayerWatchdogTimer;
class PVMFDataSourcePacketSourceInterface;
class PVPlayerDataSourcePacketSource;

typedef enum
{
    PVP_MEDIATYPE_VIDEO,
    PVP_MEDIATYPE_AUDIO,
    PVP_MEDIATYPE_TEXT,
    PVP_MEDIATYPE_UNKNOWN
} PVPlayerMediaType;

typedef enum
{
    PVP_NODETYPE_SOURCE,
    PVP_NODETYPE_SINK,
    PVP_NODETYPE_DECODER,
    PVP_NODETYPE_UNKNOWN
} PVPlayerNodeType;

class PVPlayerEngineDatapath
{
    public:
        PVPlayerEngineDatapath()
        {
            iMediaType = PVP_MEDIATYPE_UNKNOWN;
            iTrackInfo = NULL;
            iSrcFormat = PVMF_FORMAT_UNKNOWN;
            iTrackActive = false;
            iDataSink = NULL;
            iDatapath = NULL;
            iDecNode = NULL;
            iDecNodeSessionId = 0;
            iDecNodeCapConfigIF = NULL;
            iDecNodeMetadataExtIF = NULL;
            iSinkNode = NULL;
            iSinkNodeSessionId = 0;
            iSinkNodeFOConfigIF = NULL;
            iSinkNodeSyncCtrlIF = NULL;
            iSinkNodeCapConfigIF = NULL;
            iSinkNodeMetadataExtIF = NULL;
            iSinkFormat = PVMF_FORMAT_UNKNOWN;
            iNumPendingCmd = 0;
            iEndOfDataReceived = false;
        };

        PVPlayerEngineDatapath(const PVPlayerEngineDatapath& aSrc)
        {
            iMediaType = aSrc.iMediaType;
            iTrackInfo = aSrc.iTrackInfo;
            iSrcFormat = aSrc.iSrcFormat;
            iTrackActive = aSrc.iTrackActive;
            iDataSink = aSrc.iDataSink;
            iDatapath = aSrc.iDatapath;
            iDecNode = aSrc.iDecNode;
            iDecNodeSessionId = aSrc.iDecNodeSessionId;
            iDecNodeCapConfigIF = aSrc.iDecNodeCapConfigIF;
            iDecNodeMetadataExtIF = aSrc.iDecNodeMetadataExtIF;
            iSinkNode = aSrc.iSinkNode;
            iSinkNodeSessionId = aSrc.iSinkNodeSessionId;
            iSinkNodeFOConfigIF = aSrc.iSinkNodeFOConfigIF;
            iSinkNodeSyncCtrlIF = aSrc.iSinkNodeSyncCtrlIF;
            iSinkNodeCapConfigIF = aSrc.iSinkNodeCapConfigIF;
            iSinkNodeMetadataExtIF = aSrc.iSinkNodeMetadataExtIF;
            iSinkFormat = aSrc.iSinkFormat;
            iNumPendingCmd = aSrc.iNumPendingCmd;
            iEndOfDataReceived = aSrc.iEndOfDataReceived;
        };

        ~PVPlayerEngineDatapath()
        {
        };

        PVPlayerMediaType iMediaType;
        PVMFTrackInfo* iTrackInfo;
        PVMFFormatType iSrcFormat;
        bool iTrackActive;

        PVPlayerDataSink* iDataSink;
        PVPlayerDatapath* iDatapath;

        PVMFNodeInterface* iDecNode;
        PVMFSessionId iDecNodeSessionId;
        PvmiCapabilityAndConfig* iDecNodeCapConfigIF;
        PVMFMetadataExtensionInterface* iDecNodeMetadataExtIF;

        PVMFNodeInterface* iSinkNode;
        PVMFSessionId iSinkNodeSessionId;
        PvmfFileOutputNodeConfigInterface* iSinkNodeFOConfigIF;
        PvmfNodesSyncControlInterface* iSinkNodeSyncCtrlIF;
        PvmiCapabilityAndConfig* iSinkNodeCapConfigIF;
        PVMFMetadataExtensionInterface* iSinkNodeMetadataExtIF;
        PVMFFormatType iSinkFormat;

        uint32 iNumPendingCmd;
        bool iEndOfDataReceived;
};

struct PVPlayerEngineContext
{
    PVPlayerEngineDatapath* iEngineDatapath;
    PVMFNodeInterface* iNode;
    PVPlayerDatapath* iDatapath;
    PVCommandId iCmdId;
    OsclAny* iCmdContext;
    int32 iCmdType;
};


/**
 * Observer class for the inactivity timer AO
 */
class PVPlayerWatchdogTimerObserver
{
    public:
        virtual ~PVPlayerWatchdogTimerObserver() {}
        /**
         * A timer event, indicating that the inactivity timer has expired.
         */
        virtual void PVPlayerWatchdogTimerEvent() = 0;
};


class PVPlayerEngine : public OsclTimerObject,
            public PVPlayerInterface,
            public PvmiCapabilityAndConfig,
            public PVMFNodeCmdStatusObserver,
            public PVMFNodeInfoEventObserver,
            public PVMFNodeErrorEventObserver,
            public PVPlayerDatapathObserver,
            public OsclTimerObserver,
            public PVPlayerLicenseAcquisitionInterface,
            public PVMFCPMPluginCmdStatusObserver,
            public PVPlayerRecognizerRegistryObserver,
            public PVPlayerWatchdogTimerObserver,
            public PVPlayerTrackSelectionInterface
{
    public:
        static PVPlayerEngine* New(PVCommandStatusObserver *aCmdObserver,
                                   PVErrorEventObserver *aErrorObserver,
                                   PVInformationalEventObserver *aInfoObserver);
        ~PVPlayerEngine();

        // From PVPlayerInterface
        PVCommandId GetSDKInfo(PVSDKInfo &aSDKInfo, const OsclAny* aContextData = NULL);
        PVCommandId GetSDKModuleInfo(PVSDKModuleInfo &aSDKModuleInfo, const OsclAny* aContextData = NULL);
        PVCommandId SetLogAppender(const char* aTag, OsclSharedPtr<PVLoggerAppender>& aAppender, const OsclAny* aContextData = NULL);
        PVCommandId RemoveLogAppender(const char* aTag, OsclSharedPtr<PVLoggerAppender>& aAppender, const OsclAny* aContextData = NULL);
        PVCommandId SetLogLevel(const char* aTag, int32 aLevel, bool aSetSubtree = false, const OsclAny* aContextData = NULL);
        PVCommandId GetLogLevel(const char* aTag, PVLogLevelInfo& aLogInfo, const OsclAny* aContextData = NULL);
        PVCommandId QueryUUID(const PvmfMimeString& aMimeType, Oscl_Vector<PVUuid, OsclMemAllocator>& aUuids, bool aExactUuidsOnly = false, const OsclAny* aContextData = NULL);
        PVCommandId QueryInterface(const PVUuid& aUuid, PVInterface*& aInterfacePtr, const OsclAny* aContextData = NULL);
        PVCommandId CancelAllCommands(const OsclAny* aContextData = NULL);
        PVCommandId GetPVPlayerState(PVPlayerState& aState, const OsclAny* aContextData = NULL);
        PVMFStatus GetPVPlayerStateSync(PVPlayerState& aState);
        PVCommandId AddDataSource(PVPlayerDataSource& aDataSource, const OsclAny* aContextData = NULL);
        PVCommandId Init(const OsclAny* aContextData = NULL);
        PVCommandId GetMetadataKeys(PVPMetadataList& aKeyList, int32 aStartingIndex = 0, int32 aMaxEntries = -1, char* aQueryKey = NULL, const OsclAny* aContextData = NULL);
        PVCommandId GetMetadataValues(PVPMetadataList& aKeyList, int32 aStartingValueIndex, int32 aMaxValueEntries, int32& aNumAvailableValueEntries, Oscl_Vector<PvmiKvp, OsclMemAllocator>& aValueList, const OsclAny* aContextData = NULL);
        PVCommandId AddDataSink(PVPlayerDataSink& aDataSink, const OsclAny* aContextData = NULL);
        PVCommandId SetPlaybackRange(PVPPlaybackPosition aBeginPos, PVPPlaybackPosition aEndPos, bool aQueueRange, const OsclAny* aContextData = NULL);
        PVCommandId GetPlaybackRange(PVPPlaybackPosition &aBeginPos, PVPPlaybackPosition &aEndPos, bool aQueued, const OsclAny* aContextData = NULL);
        PVCommandId GetCurrentPosition(PVPPlaybackPosition &aPos, const OsclAny* aContextData = NULL);
        PVMFStatus GetCurrentPositionSync(PVPPlaybackPosition &aPos);
        PVCommandId SetPlaybackRate(int32 aRate, OsclTimebase* aTimebase = NULL, const OsclAny* aContextData = NULL);
        PVCommandId GetPlaybackRate(int32& aRate, OsclTimebase*& aTimebase, const OsclAny* aContextData = NULL);
        PVCommandId GetPlaybackMinMaxRate(int32& aMinRate, int32& aMaxRate, const OsclAny* aContextData = NULL);
        PVCommandId Prepare(const OsclAny* aContextData = NULL);
        PVCommandId Start(const OsclAny* aContextData = NULL);
        PVCommandId Pause(const OsclAny* aContextData = NULL);
        PVCommandId Resume(const OsclAny* aContextData = NULL);
        PVCommandId Stop(const OsclAny* aContextData = NULL);
        PVCommandId RemoveDataSink(PVPlayerDataSink& aDataSink, const OsclAny* aContextData = NULL);
        PVCommandId Reset(const OsclAny* aContextData = NULL);
        PVCommandId RemoveDataSource(PVPlayerDataSource& aDataSource, const OsclAny* aContextData = NULL);

        // From PvmiCapabilityAndConfig
        void setObserver(PvmiConfigAndCapabilityCmdObserver* aObserver);
        PVMFStatus getParametersSync(PvmiMIOSession aSession, PvmiKeyType aIdentifier, PvmiKvp*& aParameters, int& aNumParamElements, PvmiCapabilityContext aContext);
        PVMFStatus releaseParameters(PvmiMIOSession aSession, PvmiKvp* aParameters, int aNumElements);
        void createContext(PvmiMIOSession aSession, PvmiCapabilityContext& aContext);
        void setContextParameters(PvmiMIOSession aSession, PvmiCapabilityContext& aContext, PvmiKvp* aParameters, int aNumParamElements);
        void DeleteContext(PvmiMIOSession aSession, PvmiCapabilityContext& aContext);
        void setParametersSync(PvmiMIOSession aSession, PvmiKvp* aParameters, int aNumElements, PvmiKvp* &aRetKVP);
        PVMFCommandId setParametersAsync(PvmiMIOSession aSession, PvmiKvp* aParameters, int aNumElements, PvmiKvp*& aRetKVP, OsclAny* aContext = NULL);
        uint32 getCapabilityMetric(PvmiMIOSession aSession);
        PVMFStatus verifyParametersSync(PvmiMIOSession aSession, PvmiKvp* aParameters, int aNumElements);

        // From PVPlayerLicenseAcquisitionInterface
        PVCommandId AcquireLicense(OsclAny* aLicenseData, uint32 aDataSize, oscl_wchar* aContentName, int32 aTimeoutMsec, const OsclAny* aContextData = NULL);
        PVCommandId AcquireLicense(OsclAny* aLicenseData, uint32 aDataSize, char* aContentName, int32 aTimeoutMsec, const OsclAny* aContextData = NULL);
        PVCommandId CancelAcquireLicense(PVMFCommandId aCmdId, const OsclAny* aContextData = NULL);
        PVMFStatus GetLicenseStatus(PVMFCPMLicenseStatus& aStatus);

        //From PVPlayerTrackSelectionInterface
        PVMFStatus GetCompleteList(PVMFMediaPresentationInfo& aList);
        PVMFStatus ReleaseCompleteList(PVMFMediaPresentationInfo& aList);
        PVMFStatus GetPlayableList(PVMFMediaPresentationInfo& aList);
        PVMFStatus ReleasePlayableList(PVMFMediaPresentationInfo& aList);
        PVMFStatus GetSelectedList(PVMFMediaPresentationInfo& aList);
        PVMFStatus ReleaseSelectedList(PVMFMediaPresentationInfo& aList);
        PVMFStatus RegisterHelperObject(PVMFTrackSelectionHelper* aObject);

        // From PVInterface
        void addRef();
        void removeRef();
        bool queryInterface(const PVUuid& uuid, PVInterface*& iface);

        // From PVPlayerWatchdogTimerObserver
        void PVPlayerWatchdogTimerEvent();

#ifdef HAS_OSCL_LIB_SUPPORT
        // from PVPlayerRegistryInterface
        void PopulateNodeRegistry(const OSCL_String& aConfigFilePath);
        void PopulateRecognizerRegistry(const OSCL_String& aConfigFilePath);
        void PopulateAllRegistries(const OSCL_String& aConfigFilePath);

        // In future a config file path will be added as a parameter to the
        // following functions. The original design is to allow the ability
        // to load and unload multiple configuration files independently.
        void DepopulateNodeRegistry();
        void DepopulateRecognizerRegistry();
        void DepopulateAllRegistries();
#endif

    private:
        PVPlayerEngine();
        void Construct(PVCommandStatusObserver *aCmdObserver,
                       PVErrorEventObserver *aErrorObserver,
                       PVInformationalEventObserver *aInfoObserver);

        // From OsclTimerObject
        void Run();

        // Utility function to determine the type of node in the player datapath and of the datapath which it belongs to
        bool FindNodeTypeByNode(PVMFNodeInterface* aUnknownNode, PVPlayerNodeType& aNodeType, int32& aDatapathListIndex);

        // Utility function to find the datapath list index based on media type
        bool FindDatapathByMediaType(PVPlayerMediaType aMediaType, int32& aDatapathListIndex);

        // From PVMFNodeCmdStatusObserver
        void NodeCommandCompleted(const PVMFCmdResp& aResponse);

        // From PVMFNodeInfoEventObserver
        void HandleNodeInformationalEvent(const PVMFAsyncEvent& aEvent);

        // From PVMFNodeErrorEventObserver
        void HandleNodeErrorEvent(const PVMFAsyncEvent& aEvent);

        // From PVPlayerDatapathObserver
        void HandlePlayerDatapathEvent(int32 aDatapathEvent, PVMFStatus aEventStatus, OsclAny* aContext = NULL, PVMFCmdResp* aCmdResp = NULL);

        // From OsclTimerObserver
        void TimeoutOccurred(int32 timerID, int32 timeoutInfo);

        // From PVMFCPMPluginCmdStatusObserver
        void CPMPluginCommandCompleted(const PVMFCmdResp& aResponse);

        // From PVPlayerRecognizerRegistryObserver
        void RecognizeCompleted(PVMFFormatType aSourceFormatType, OsclAny* aContext);

        // Command and event queueing related functions
        PVCommandId AddCommandToQueue(int32 aCmdType, OsclAny* aContextData = NULL,
                                      Oscl_Vector<PVPlayerEngineCommandParamUnion, OsclMemAllocator>* aParamVector = NULL,
                                      const PVUuid* aUuid = NULL, bool aAPICommand = true);

        // start the playback clock once skip is completed by one of the tracks
        void StartPlaybackClock();

        // Functions for engine state handling
        void SetEngineState(PVPlayerEngineState aState);
        PVPlayerState GetPVPlayerState(void);

        // Keeps track of next available command ID
        PVCommandId iCommandId;

        // Current engine state
        PVPlayerEngineState iState;

        // Reference to observers
        PVCommandStatusObserver *iCmdStatusObserver;
        PVErrorEventObserver *iErrorEventObserver;
        PVInformationalEventObserver *iInfoEventObserver;

        PvmiConfigAndCapabilityCmdObserver *iCfgCapCmdObserver;

        // Retrieve current playback clock position
        void GetPlaybackClockPosition(PVPPlaybackPosition& aClockPos);

        // Utility functions to convert to/from milliseconds to other playback position units
        PVMFStatus ConvertToMillisec(PVPPlaybackPosition aPBPos, uint32& aTimeMS);
        PVMFStatus ConvertFromMillisec(uint32 aTimeMS, PVPPlaybackPosition& aPBPos);

        // OsclTimer for polling checks
        OsclTimer<OsclMemAllocator>* iPollingCheckTimer;

        // Command and event callback functions
        void EngineCommandCompleted(PVCommandId aId, OsclAny* aContext, PVMFStatus aStatus, PVInterface* aExtInterface = NULL,
                                    OsclAny* aEventData = NULL, int32 aEventDataSize = 0);
        void SendInformationalEvent(PVMFEventType aEventType, PVInterface* aExtInterface = NULL,
                                    OsclAny* aEventData = NULL, uint8* aLocalBuffer = NULL, uint32 aLocalBufferSize = 0);
        void SendErrorEvent(PVMFEventType aEventType, PVInterface* aExtInterface = NULL,
                            OsclAny* aEventData = NULL, uint8* aLocalBuffer = NULL, uint32 aLocalBufferSize = 0);

        // Queue for engine commands
        Oscl_Vector<PVPlayerEngineCommand, OsclMemAllocator> iCurrentCmd; // Vector of size 1 to hold the command being currently processed
        Oscl_Vector<PVPlayerEngineCommand, OsclMemAllocator> iCmdToCancel; // Vector of size 1 to hold the command being currently cancelled
        Oscl_Vector<PVPlayerEngineCommand, OsclMemAllocator> iCmdToDlaCancel; // Vector of size 1 to hold the command being currently cancelled
        OsclPriorityQueue<PVPlayerEngineCommand, OsclMemAllocator, Oscl_Vector<PVPlayerEngineCommand, OsclMemAllocator>, PVPlayerEngineCommandCompareLess> iPendingCmds; // Vector to hold the command that has been requested

        // Variables for completing engine commands in engine's AO
        bool iCommandCompleteInEngineAOPending;
        PVMFStatus iCommandCompleteInEngineAOCmdStatus;
        PVMFBasicErrorInfoMessage* iCommandCompleteInEngineAOErrMsg;

        // Command handling functions
        void DoCancelAllCommands(PVPlayerEngineCommand& aCmd);
        void DoCancelCommandBeingProcessed(void);
        void DoCancelPendingNodeDatapathCommand(void);
        void DoShutdownDueToCancel(void);
        void DoStopDueToCancel(void);
        void DoResetDueToCancel(void);
        void DoCleanupDueToCancel(void);
        void DoCancelAcquireLicense(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoGetSDKInfo(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoSetLogAppender(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoRemoveLogAppender(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoSetLogLevel(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoGetLogLevel(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoQueryUUID(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoQueryInterface(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoGetPVPlayerState(PVPlayerEngineCommand& aCmd, bool aSyncCmd = false);
        PVMFStatus DoAddDataSource(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoQuerySourceFormatType(PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoSetupSourceNode(PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus SetupDataSourceForUnknownURLAccess();
        PVMFStatus DoSourceNodeQueryTrackSelIF(PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoSourceNodeQueryInterfaceOptional(PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoAddDataSourceFailureComplete(void);
        PVMFStatus DoInitFailureComplete(void);
        PVMFStatus DoGetMetadataKey(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoGetMetadataValue(PVPlayerEngineCommand& aCmd);
        PVMFStatus AddToMetadataInterfaceList(PVMFMetadataExtensionInterface* aMetadataIF, PVMFSessionId aSessionId);
        PVMFStatus RemoveFromMetadataInterfaceList(PVMFMetadataExtensionInterface* aMetadataIF, PVMFSessionId aSessionId);
        PVMFStatus DoInit(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoSourceNodeInit(PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoSourceNodeGetDurationValue(PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoSourceNodeGetDlaData(PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoAcquireLicense(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoSourceNodeGetLicense(PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoCPMPluginSetUserAgentHeader(PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoCPMPluginGetLicense(PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoCPMPluginAcquireLicenseComplete(void);
        PVMFStatus DoAddDataSink(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoSetPlaybackRange(PVPlayerEngineCommand& aCmd);
        PVMFStatus UpdateCurrentEndPosition(PVPPlaybackPosition& aEndPos);
        PVMFStatus UpdateCurrentBeginPosition(PVPPlaybackPosition& aBeginPos, PVPlayerEngineCommand& aCmd);
        PVMFStatus DoChangePlaybackPosition(PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoSourceNodeSetDataSourcePositionDuringPlayback(PVMFTimestamp aTargetNPT, bool aSeekToSyncPoint, PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoSinkNodeSkipMediaDataDuringPlayback(PVCommandId aCmdId,
                OsclAny* aCmdContext,
                bool aSFR = false);
        PVMFStatus DoGetPlaybackRange(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoGetCurrentPosition(PVPlayerEngineCommand& aCmd, bool aSyncCmd = false);
        PVMFStatus DoSetPlaybackRate(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoGetPlaybackRate(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoGetPlaybackMinMaxRate(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoPrepare(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoSourceNodeTrackSelection(PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoTrackSelection(bool oPopulatePlayableListOnly, bool oUsePreferenceList);
        PVMFStatus DoSourceNodeTrackQuery(PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoSinkNodeInit(PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoSinkNodeReset(PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoQueryTrackInfo(PVPlayerEngineDatapath &aDatapath, PVMFTrackInfo* aTrack, PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoVerifyTrackInfo(PVPlayerEngineDatapath &aDatapath, PVMFTrackInfo* aTrack, PVMFStatus& aCheckcodec);
        PVMFStatus DoSourceNodePrepare(PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoSetupSinkNode(PVPlayerEngineDatapath &aDatapath, PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoSinkNodeQueryInterfaceOptional(PVPlayerEngineDatapath &aDatapath, PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoSetupDecNode(PVPlayerEngineDatapath &aDatapath, PVCommandId aCmdId, OsclAny* aCmdContext);
        bool IsDecNodeNeeded(PVMFFormatType& aSrcFormat, PVMFFormatType& aSinkFormat);
        PVMFStatus DoDecNodeQueryInterfaceOptional(PVPlayerEngineDatapath &aDatapath, PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoDatapathPrepare(PVPlayerEngineDatapath &aDatapath, PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoSourceNodeQueryDataSourcePosition(PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoSourceNodeSetDataSourcePosition(PVCommandId aCmdId, OsclAny* aCmdContext, PVMFTimestamp aTargetNPT, bool aSeekToSyncPoint);
        PVMFStatus DoSourceNodeSetDataSourceDirection(PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoSourceNodeStart(PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoDatapathStart(PVPlayerEngineDatapath &aDatapath, PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoSinkNodeSkipMediaData(PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoStart(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoPause(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoDatapathPause(PVPlayerEngineDatapath &aDatapath, PVCommandId aCmdId, OsclAny* aCmdContext, bool aSinkPaused);
        PVMFStatus DoSourceNodePause(PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoResume(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoStop(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoDatapathStop(PVPlayerEngineDatapath &aDatapath, PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoSourceNodeStop(PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoDatapathTeardown(PVPlayerEngineDatapath &aDatapath, PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoDatapathReset(PVPlayerEngineDatapath &aDatapath, PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoRemoveDataSink(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoReset(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoRemoveDataSource(PVPlayerEngineCommand& aCmd);
        PVMFStatus RemoveDataSourceSync(PVPlayerDataSource &aSrc);
        PVMFStatus DoSourceUnderflowAutoPause(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoSourceDataReadyAutoResume(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoSinkNodePause(PVPlayerEngineDatapath &aDatapath, PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoSinkNodeResume(PVPlayerEngineDatapath &aDatapath, PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoCancelDueToError(void);
        PVMFStatus DoStopDueToError(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoDatapathStopDueToError(PVPlayerEngineDatapath &aDatapath, PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoSourceNodeStopDueToError(PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoDatapathTeardownDueToError(PVPlayerEngineDatapath &aDatapath, PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoDatapathResetDueToError(PVPlayerEngineDatapath &aDatapath, PVCommandId aCmdId, OsclAny* aCmdContext);
        PVMFStatus DoResetDueToError(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoCleanupDueToError(PVPlayerEngineCommand& aCmd);
        PVMFStatus DoDatapathDelete(PVPlayerEngineCommand &aCmd);
        void DoRemoveAllSinks(void);
        void DoEngineDatapathTeardown(PVPlayerEngineDatapath& aDatapath);
        void DoEngineDatapathCleanup(PVPlayerEngineDatapath& aDatapath);
        void DoSourceNodeCleanup(void);

        PVMFStatus DoCapConfigGetParametersSync(PvmiKeyType aIdentifier, PvmiKvp*& aParameters, int& aNumParamElements, PvmiCapabilityContext aContext);
        PVMFStatus DoCapConfigReleaseParameters(PvmiKvp* aParameters, int aNumElements);
        PVMFStatus DoCapConfigSetParameters(PVPlayerEngineCommand& aCmd, bool aSyncCmd = false);
        PVMFStatus DoCapConfigVerifyParameters(PvmiKvp* aParameters, int aNumElements);
        PVMFStatus DoQueryNodeCapConfig(char* aKeySubString, Oscl_Vector<PvmiCapabilityAndConfig*, OsclMemAllocator>& aNodeCapConfigIF);
        PVMFStatus DoGetPlayerParameter(PvmiKvp*& aParameters, int& aNumParamElements, int32 aIndex, PvmiKvpAttr reqattr);
        PVMFStatus DoGetPlayerProductInfoParameter(PvmiKvp*& aParameters, int& aNumParamElements, int32 aIndex, PvmiKvpAttr reqattr);
        PVMFStatus DoVerifyAndSetPlayerParameter(PvmiKvp& aParameter, bool aSetParam);
        PVMFStatus DoVerifyAndSetPlayerProductInfoParameter(PvmiKvp& aParameter, bool aSetParam);
        PVMFStatus DoSetConfigSyncMargin(int32 aEarlyMargin, int32 aLateMargin, int32 aMediaType);
        int32 iCapConfigContext;

        // Engine datapath and related variables
        Oscl_Vector<PVPlayerEngineDatapath, OsclMemAllocator> iDatapathList;
        uint32 iNumPendingNodeCmd;
        int32 iNumPendingSkipCompleteEvent;
        bool iResumeAfterReposition;
        PVPlayerWatchdogTimer* iWatchDogTimer;
        uint32 iNumPendingDatapathCmd;
        int32 iNumPVMFInfoStartOfDataPending;

        // Data source, data sink, and nodes
        PVPlayerDataSource* iDataSource;
        PVPlayerDataSourcePacketSource* iDataSourcePS;
        PVMFFormatType iSourceFormatType;
        PVMFNodeInterface* iSourceNode;
        PVMFSessionId iSourceNodeSessionId;
        PVMFDataSourceInitializationExtensionInterface* iSourceNodeInitIF;
        PVMFTrackSelectionExtensionInterface* iSourceNodeTrackSelIF;
        PvmfDataSourcePlaybackControlInterface* iSourceNodePBCtrlIF;
        PvmfDataSourceDirectionControlInterface* iSourceNodeDirCtrlIF;
        PVMFTrackLevelInfoExtensionInterface* iSourceNodeTrackLevelInfoIF;
        PVMFMetadataExtensionInterface* iSourceNodeMetadataExtIF;
        PvmiCapabilityAndConfig* iSourceNodeCapConfigIF;
        PVMFDataSourceNodeRegistryInitInterface* iSourceNodeRegInitIF;
        PVMFCPMPluginLicenseInterface* iSourceNodeCPMLicenseIF;
        PVMFDataSourcePacketSourceInterface* iSourceNodePacketSourceIF;

        // For CPM license acquisition
        struct PVPlayerEngineCPMAcquireLicenseParam
        {
            OsclAny* iLicenseData;
            uint32 iLicenseDataSize;
            char* iContentNameChar;
            oscl_wchar* iContentNameWChar;
            int32 iTimeoutMsec;
        };
        PVPlayerEngineCPMAcquireLicenseParam iCPMAcquireLicenseParam;
        OSCL_HeapString<OsclMemAllocator> iCPMContentNameStr;
        OSCL_wHeapString<OsclMemAllocator> iCPMContentNameWStr;
        PVMFCPMPluginInterface* iCPMPlugin;
        void* iCPMPluginFactory;
        PVMFSessionId iCPMPluginSessionId;
        PVMFCPMPluginLicenseInterface* iCPMPluginLicenseIF;
        PvmiCapabilityAndConfig *iCPMPluginCapConfigIf;
        int32 iCPMPluginCommand;
        PVMFStatus DoGetPluginLicenseIF();
        PVMFCommandId iCPMGetLicenseCmdId;

        // For metadata handling
        // Vector to hold a list of metadata interface available from the node
        struct PVPlayerEngineMetadataIFInfo
        {
            PVMFMetadataExtensionInterface* iInterface;
            PVMFSessionId iSessionId;
        };
        Oscl_Vector<PVPlayerEngineMetadataIFInfo, OsclMemAllocator> iMetadataIFList;

        // Structure to hold the parameters for GetMetadataKeys()
        struct PVPlayerEngineGetMetadataKeysParam
        {
            int32 iStartingKeyIndex;
            int32 iMaxKeyEntries;
            char* iQueryKey;
            PVPMetadataList* iKeyList;

            uint32 iCurrentInterfaceIndex;
            int32 iNumKeyEntriesToFill;
            int32 iNumKeyEntriesInList;
        };
        PVPlayerEngineGetMetadataKeysParam iGetMetadataKeysParam;

        // Structure to hold the parameters for GetMetadataValues()
        struct PVPlayerEngineGetMetadataValuesParam
        {
            int32 iStartingValueIndex;
            int32 iMaxValueEntries;
            int32* iNumAvailableValues;
            PVPMetadataList* iKeyList;
            Oscl_Vector<PvmiKvp, OsclMemAllocator>* iValueList;

            uint32 iCurrentInterfaceIndex;
            int32 iNumValueEntriesToFill;
            int32 iNumValueEntriesInList;
        };
        PVPlayerEngineGetMetadataValuesParam iGetMetadataValuesParam;

        // Vector hold a list of metadata interfaces with key/value to release memory
        struct PVPlayerEngineMetadataReleaseEntry
        {
            uint32 iMetadataIFListIndex;
            int32 iStartIndex;
            int32 iEndIndex;
        };
        Oscl_Vector<PVPlayerEngineMetadataReleaseEntry, OsclMemAllocator> iMetadataReleaseList;

        // Engine context related objects and utility functions
        OsclMemPoolFixedChunkAllocator iCurrentContextListMemPool;
        Oscl_Vector<PVPlayerEngineContext*, OsclMemAllocator> iCurrentContextList;
        PVPlayerEngineContext* AllocateEngineContext(PVPlayerEngineDatapath* aEngineDatapath, PVMFNodeInterface* aNode, PVPlayerDatapath* aDatapath, PVCommandId aCmdId, OsclAny* aCmdContext, int32 aCmdType);
        void FreeEngineContext(PVPlayerEngineContext* aContext);
        void RemoveDatapathContextFromList();

        // Cancel and error handling related variables
        uint32 iPendingCancelDueToCancelRequest;
        uint32 iPendingStopDueToCancelRequest;
        uint32 iPendingResetDueToCancelRequest;
        uint32 iPendingCancelDueToErrorRequest;
        bool iErrorOccurredDuringErrorHandling;

        enum
        {
            // Node commands
            PVP_CMD_SourceNodeQueryInitIF,
            PVP_CMD_SourceNodeQueryTrackSelIF,
            PVP_CMD_SourceNodeQueryTrackLevelInfoIF,
            PVP_CMD_SourceNodeQueryPBCtrlIF,
            PVP_CMD_SourceNodeQueryDirCtrlIF,
            PVP_CMD_SourceNodeQueryMetadataIF,
            PVP_CMD_SourceNodeQueryCapConfigIF,
            PVP_CMD_SourceNodeQueryCPMLicenseIF,
            PVP_CMD_SourceNodeQuerySrcNodeRegInitIF,
            PVP_CMD_SourceNodeQueryPacketSourceIF,
            PVP_CMD_SourceNodeInit,
            PVP_CMD_SourceNodeGetDurationValue,
            PVP_CMD_SourceNodeGetDlaData,
            PVP_CMD_SourceNodeSetDataSourceRate,
            PVP_CMD_SourceNodePrepare,
            PVP_CMD_SourceNodeGetLicense,
            PVP_CMD_SourceNodeCancelGetLicense,
            PVP_CMD_SinkNodeQueryFOConfigIF,
            PVP_CMD_SinkNodeQuerySyncCtrlIF,
            PVP_CMD_SinkNodeQueryMetadataIF,
            PVP_CMD_SinkNodeQueryCapConfigIF,
            PVP_CMD_DecNodeQueryMetadataIF,
            PVP_CMD_DecNodeQueryCapConfigIF,
            PVP_CMD_SourceNodeQueryDataSourcePosition,
            PVP_CMD_SourceNodeSetDataSourcePosition,
            PVP_CMD_SourceNodeSetDataSourceDirection,
            PVP_CMD_SourceNodeStart,
            PVP_CMD_SourceNodeQueryDataSourcePositionDuringPlayback,
            PVP_CMD_SourceNodeSetDataSourcePositionDuringPlayback,
            PVP_CMD_SinkNodeSkipMediaDataDuringPlayback,
            PVP_CMD_SinkNodeSkipMediaData,
            PVP_CMD_SinkNodeDecNodeQueryCapConfigIF,
            PVP_CMD_SinkNodeDecNodeVerifyParameter,
            PVP_CMD_SinkNodeDecNodeReset,
            PVP_CMD_GetNodeMetadataValue,
            PVP_CMD_GetNodeMetadataKey,
            PVP_CMD_SinkNodeAutoPause,
            PVP_CMD_SinkNodeAutoResume,
            PVP_CMD_SourceNodeStop,
            PVP_CMD_SourceNodeReset,
            // Datapath commands
            PVP_CMD_DPPrepare,
            PVP_CMD_DPStart,
            PVP_CMD_DPStop,
            PVP_CMD_DPTeardown,
            PVP_CMD_DPReset,
            // CPM plug-in commands
            PVP_CMD_CPMQueryCapConfigIF,
            PVP_CMD_CPMQueryLicenseIF,
            PVP_CMD_CPMGetLicense,
            // Recognizer command
            PVP_CMD_QUERYSOURCEFORMATTYPE,
            // source roll over
            PVP_CMD_SourceNodeRollOver
        };

        // Node command handling functions
        void HandleSourceNodeQueryInitIF(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);
        void HandleSourceNodeQueryTrackSelIF(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);
        void HandleSourceNodeQueryInterfaceOptional(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);
        void HandleSourceNodeInit(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);
        void HandleSourceNodeGetDurationValue(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);
        void HandleSourceNodeGetDlaData(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);
        void HandleSourceNodeGetLicense(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);
        void HandleSourceNodeCancelGetLicense(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);

        void HandleSourceNodeSetDataSourceRate(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);
        PVMFStatus DoSinkNodeChangeClockRate();
        PVMFStatus DoSinkPlaybackDirectionChange();
        PVMFStatus UpdateCurrentDirection(PVMFCommandId, OsclAny*);
        void UpdateTimebaseAndRate();
        void UpdateDirection(PVMFTimestamp, PVMFTimestamp, PVPPlaybackPosition&);
        void HandleSourceNodePrepare(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);
        void HandleSinkNodeQueryFileOutConfigIF(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);
        void HandleSinkNodeQueryInterfaceOptional(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);
        void HandleDecNodeQueryInterfaceOptional(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);
        void HandleSourceNodeQueryDataSourcePosition(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);
        void HandleSourceNodeSetDataSourcePosition(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);
        void HandleSourceNodeSetDataSourceDirection(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);
        void HandleSourceNodeStart(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);
        void HandleSinkNodeSkipMediaData(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);

        void HandleSourceNodeQueryDataSourcePositionDuringPlayback(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);
        void HandleSourceNodeSetDataSourcePositionDuringPlayback(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);
        void HandleSinkNodeSkipMediaDataDuringPlayback(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);

        void HandleSourceNodePause(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);
        void HandleSourceNodeResume(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);
        void HandleSourceNodeStop(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);
        void HandleSourceNodeReset(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);

        void HandleSinkNodePause(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);
        void HandleSinkNodeResume(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);

        void HandleSourceNodeStopDueToError(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);
        void HandleSourceNodeResetDueToError(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);
        void HandleSinkNodeDecNodeQueryCapConfigIF(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);
        void HandleSinkNodeDecNodeVerifyParameter(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);
        void HandleSinkNodeDecNodeReset(PVPlayerEngineContext& aNodeContext, const PVMFCmdResp& aNodeResp);

        // Datapath command handling functions
        void HandleDatapathPrepare(PVPlayerEngineContext& aDatapathContext, PVMFStatus aDatapathStatus, PVMFCmdResp* aCmdResp);
        void HandleDatapathStart(PVPlayerEngineContext& aDatapathContext, PVMFStatus aDatapathStatus, PVMFCmdResp* aCmdResp);
        void HandleDatapathPause(PVPlayerEngineContext& aDatapathContext, PVMFStatus aDatapathStatus, PVMFCmdResp* aCmdResp);
        void HandleDatapathResume(PVPlayerEngineContext& aDatapathContext, PVMFStatus aDatapathStatus, PVMFCmdResp* aCmdResp);
        void HandleDatapathStop(PVPlayerEngineContext& aDatapathContext, PVMFStatus aDatapathStatus, PVMFCmdResp* aCmdResp);
        void HandleDatapathTeardown(PVPlayerEngineContext& aDatapathContext, PVMFStatus aDatapathStatus, PVMFCmdResp* aCmdResp);
        void HandleDatapathReset(PVPlayerEngineContext& aDatapathContext, PVMFStatus aDatapathStatus, PVMFCmdResp* aCmdResp);

        void HandleDatapathStopDueToError(PVPlayerEngineContext& aDatapathContext, PVMFStatus aDatapathStatus, PVMFCmdResp* aCmdResp);
        void HandleDatapathTeardownDueToError(PVPlayerEngineContext& aDatapathContext, PVMFStatus aDatapathStatus, PVMFCmdResp* aCmdResp);
        void HandleDatapathResetDueToError(PVPlayerEngineContext& aDatapathContext, PVMFStatus aDatapathStatus, PVMFCmdResp* aCmdResp);

        // CPM plug-in command handling functions
        void HandleCPMPluginQueryCapConfigIF(const PVMFCmdResp& aCmdResp);
        void HandleCPMPluginQueryLicenseIF(const PVMFCmdResp& aCmdResp);
        void HandleCPMPluginGetLicense(const PVMFCmdResp& aCmdResp);

        // Node error event handling functions
        void HandleSourceNodeErrorEvent(const PVMFAsyncEvent& aEvent);
        void HandleDecNodeErrorEvent(const PVMFAsyncEvent& aEvent, int32 aDatapathIndex);
        void HandleSinkNodeErrorEvent(const PVMFAsyncEvent& aEvent, int32 aDatapathIndex);
        void HandleErrorBasedOnPlayerState(void);
        bool HandleAsyncErrorBasedOnPlayerState(PVMFEventType aErrorCode, PVMFBasicErrorInfoMessage* aErrMsg = NULL);

        // Node informational event handling functions
        void HandleSourceNodeInfoEvent(const PVMFAsyncEvent& aEvent);
        void HandleDecNodeInfoEvent(const PVMFAsyncEvent& aEvent, int32 aDatapathIndex);
        void HandleSinkNodeInfoEvent(const PVMFAsyncEvent& aEvent, int32 aDatapathIndex);
        bool AllDatapathReceivedEndOfData();

        // Utility functions to send specific async events
        void SendEndOfClipInfoEvent(PVMFStatus aStatus, PVInterface* aExtInterface = NULL);
        void SendEndTimeReachedInfoEvent(PVMFStatus aStatus, PVInterface* aExtInterface = NULL);
        void SendSourceUnderflowInfoEvent(PVMFStatus aStatus, PVInterface* aExtInterface = NULL);
        void SendSourceDataReadyInfoEvent(PVMFStatus aStatus, PVInterface* aExtInterface = NULL);
        void SendErrorHandlingCompleteEvent(PVMFStatus aStatus, PVInterface* aExtInterface = NULL);

        // Utility to retrieve the PVMFErrorInfoMessageInterface from a PVInterface
        PVMFErrorInfoMessageInterface* GetErrorInfoMessageInterface(PVInterface& aInterface);

        // Utility functions to start/stop playback status timer
        void StartPlaybackStatusTimer(void);
        void StopPlaybackStatusTimer(void);

        // Utility Fucntion to calculate the nearest sync frame
        void CalculateActualPlaybackPosition();

        // Save config values in case of protocol rollover
        PVMFStatus VerifyAndSaveKVPValues(PvmiKvp *aKvpValue);
        void SetRollOverKVPValues();
        void DeleteKVPValues();

        // Handle to the logger node
        PVLogger* iLogger;
        PVLogger* iReposLogger;
        PVLogger* iPerfLogger;

        // The node registry for the player engine
        PVPlayerNodeRegistry iPlayerNodeRegistry;

        // The recognizer registry for the player engine
        PVPlayerRecognizerRegistry iPlayerRecognizerRegistry;

        // Objects for playback clock and playback rate control
        PVPlayerTimebase iPlaybackTimebase;
        OsclClock iPlaybackClock;
        int32 iPlaybackClockRate;//always >=0
        OsclTimebase* iOutsideTimebase;
        int32 iPlaybackClockRate_New;
        OsclTimebase* iOutsideTimebase_New;
        PVMFTimestamp iActualPlaybackPosition;

        PVMFTimestamp iSeekPointBeforeTargetNPT;
        PVMFTimestamp iSeekPointAfterTargetNPT;

        uint32 iWatchDogTimerInterval;

        PVMFTimestamp iActualMediaDataTS;
        PVMFTimestamp iAdjustedMediaDataTS;
        PVMFTimestamp iStartNPT;
        PVMFTimestamp iStartMediaDataTS;
        // forward and reverse flags, a single flag can also serve, but kept for MP4 parser alignment.
        bool iForwardReposFlag;
        bool iBackwardReposFlag;

        PVMFDataSourcePositionParams iDataSourcePosParams;

        // Objects for direction control.
        int32 iPlaybackDirection;//1=forward, (-1)=backward.
        int32 iPlaybackDirection_New;
        bool iChangePlaybackDirectionWhenResuming;
        PVPPlaybackPosition iChangeDirectionNPT;

        // Variables to store data for SetPlaybackRange()
        PVPPlaybackPosition iCurrentBeginPosition;
        PVPPlaybackPosition iCurrentEndPosition;
        bool iEndTimeCheckEnabled;
        bool iQueuedRangePresent;
        PVPPlaybackPosition iQueuedBeginPosition;
        PVPPlaybackPosition iQueuedEndPosition;
        bool iChangePlaybackPositionWhenResuming;

        // Flag to keep track of whether play status event is enabled or not
        bool iPlayStatusTimerEnabled;

        // Flags to keep track of source auto-pause/resume
        bool iDataReadySent;
        bool removeCmdFromQ(OsclPriorityQueue<PVPlayerEngineCommand, OsclMemAllocator, Oscl_Vector<PVPlayerEngineCommand, OsclMemAllocator>, PVPlayerEngineCommandCompareLess> &aVec, const PVPlayerEngineCommandType aCmdType, bool aRemove);
        bool removeCmdFromQ(Oscl_Vector<PVPlayerEngineCommand, OsclMemAllocator> &aVec, const PVPlayerEngineCommandType aCmdType, bool aRemove);

        // Flag to keep track of whether playback has ended with end of clip
        bool iPlaybackPausedDueToEndOfClip;

        // Variables to store the source data duration
        bool iSourceDurationAvailable;
        uint32 iSourceDurationInMS;
        PVMFMetadataList iSourceDurationKeyList;
        Oscl_Vector<PvmiKvp, OsclMemAllocator> iSourceDurationValueList;

        // Variables to store the source data duration
        PVMFMetadataList iDlaDataKeyList;
        Oscl_Vector<PvmiKvp, OsclMemAllocator> iDlaDataValueList;

        // Player engine configuration
        bool iPBPosEnable;
        PVPPlaybackPositionUnit iPBPosStatusUnit;
        uint32 iPBPosStatusInterval;
        uint32 iEndTimeCheckInterval;
        bool iSeekToSyncPoint;
        bool iSkipToRequestedPosition;
        bool iRenderSkipped;
        bool iBackwardRepos; /* To avoid backward looping :: Flag to remember if this is a case of backward repositioning */
        uint32 iSyncPointSeekWindow;
        range_int32 iSyncMarginVideo;
        range_int32 iSyncMarginAudio;
        range_int32 iSyncMarginText;
        uint32 iNodeCmdTimeout;
        uint32 iNodeDataQueuingTimeout;
        OSCL_HeapString<OsclMemAllocator> iProdInfoProdName;
        OSCL_HeapString<OsclMemAllocator> iProdInfoPartNum;
        OSCL_HeapString<OsclMemAllocator> iProdInfoHWPlatform;
        OSCL_HeapString<OsclMemAllocator> iProdInfoSWPlatform;
        OSCL_HeapString<OsclMemAllocator> iProdInfoDevice;
        // stream ID for media streams
        int32 iStreamID;

        //source roll over related
        PVMFStatus DoSourceNodeRollOver(PVCommandId aCmdId, OsclAny* aCmdContext);
        uint32 iAlternateSrcFormatIndex;
        bool CheckForSourceRollOver();
        enum RollOverState
        {
            RollOverStateIdle,
            RollOverStateStart,
            RollOverStateInProgress
        };
        RollOverState iRollOverState;

        //To save CapnCapability in case of Protocol Rollover
        Oscl_Vector<PvmiKvp *, OsclMemAllocator> iPvmiKvpCapNConfig;

        struct PVPlayerEngineUuidNodeMapping
        {
            PVUuid			iUuid;
            PVMFNodeInterface*	iNode;
            PVPlayerEngineUuidNodeMapping(PVUuid aUuid, PVMFNodeInterface* aNode):
                    iUuid(aUuid), iNode(aNode) {}
        };
        //Vector to store the Uuids for the nodes created throughout the playback
        Oscl_Vector<PVPlayerEngineUuidNodeMapping, OsclMemAllocator> iNodeUuids;

        PVMFMediaPresentationInfo iPlayableList;
        PVMFMediaPresentationInfo iPreferenceList;
        PVMFTrackSelectionHelper* iTrackSelectionHelper;

        PVPPlaybackPositionMode iPlaybackPositionMode;
#ifdef HAS_OSCL_LIB_SUPPORT
        struct PVPlayerEngineNodeSharedLibInfo
        {
            OsclSharedLibrary* iLib;
            NodeRegistrySharedLibraryInterface* iNodeLibIfacePtr;
            OsclAny* iContext;
        };

        struct PVPlayerEngineRecognizerSharedLibInfo
        {
            OsclSharedLibrary* iLib;
            RecognizerSharedLibraryInterface* iRecognizerLibIfacePtr;
            OsclAny* iContext;
        };

        Oscl_Vector<struct PVPlayerEngineNodeSharedLibInfo*, OsclMemAllocator> iNodeLibInfoList;
        Oscl_Vector<struct PVPlayerEngineRecognizerSharedLibInfo*, OsclMemAllocator> iRecognizerLibInfoList;
#endif
};

/**
 * Inactivity timer object to Jitter Buffer node. This object generates event
 * on remote inactivity (no UDP traffic from server for a certain time)
 */
#define DEFAULT_WATCHDOG_TIMERDURATION 10
class PVPlayerWatchdogTimer : public OsclTimerObject
{
    public:
        PVPlayerWatchdogTimer(PVPlayerWatchdogTimerObserver* aTimerObserver):
                OsclTimerObject(OsclActiveObject::EPriorityNominal, "PVPlayerWatchDogTimer"),
                iTimerDuration(DEFAULT_WATCHDOG_TIMERDURATION),
                iObserver(aTimerObserver),
                iStarted(false)
        {
            AddToScheduler();
        }

        virtual ~PVPlayerWatchdogTimer()
        {
            Stop();
        }

        /** Start Timer */
        PVMFStatus Start()
        {
            if (iTimerDuration >= 0)
            {
                RunIfNotReady(iTimerDuration * 1000);
                iStarted = true;
                return PVMFSuccess;
            }
            else
            {
                return PVMFFailure;
            }
        }

        void setTimerDuration(uint32 aTimerDuration)
        {
            iTimerDuration = aTimerDuration;
        }

        uint32 getTimerDurationInMS()
        {
            return iTimerDuration;
        }

        /** Stop Timer events */
        PVMFStatus Stop()
        {
            Cancel();
            iStarted = false;
            return PVMFSuccess;
        }

        bool IsTimerStarted()
        {
            return iStarted;
        }

    private:
        void Run()
        {
            if (!iStarted)
                return;

            if (!iObserver)
            {
                // Error, No observer set
                return;
            }

            iObserver->PVPlayerWatchdogTimerEvent();
            /*
             * Do not reschudule the AO here. Observer would reschedule this AO
             * once it is done processing the timer event.
             */
        }


        uint32 iTimerDuration;
        PVPlayerWatchdogTimerObserver* iObserver;
        PVLogger* iLogger;
        bool iStarted;
};

#endif
