/* Do not modify this file.                                                   */
/* It is created automatically by the ASN.1 to Wireshark dissector compiler   */
/* packet-lte-rrc.c                                                           */
/* ../../tools/asn2wrs.py -e -L -p lte-rrc -c ./lte-rrc.cnf -s ./packet-lte-rrc-template -D . EUTRA-RRC-Definitions.asn EUTRA-UE-Variables.asn EUTRA-InterNodeDefinitions.asn */

/* Input file: packet-lte-rrc-template.c */

#line 1 "packet-lte-rrc-template.c"
/* packet-lte-rrc-template.c
 * Routines for Evolved Universal Terrestrial Radio Access (E-UTRA);
 * Radio Resource Control (RRC) protocol specification
 * (3GPP TS 36.331 V8.3.0 Release 8) packet dissection
 * Copyright 2008, Vincent Helfre
 *
 * $Id: packet-lte-rrc.c 33294 2010-06-23 04:50:52Z etxrab $
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <glib.h>
#include <epan/packet.h>
#include <epan/asn1.h>

#include "packet-ber.h"
#include "packet-per.h"
#include "packet-rrc.h"
#include "packet-gsm_a_common.h"


#define PNAME  "LTE Radio Resource Control (RRC) protocol"
#define PSNAME "LTE RRC"
#define PFNAME "lte_rrc"

static dissector_handle_t nas_eps_handle = NULL;
static guint32 lte_rrc_rat_type_value = -1;

static dissector_handle_t UL_DCCH_handle = NULL; /* MQ 08-18-2010 */


/* Include constants */

/*--- Included file: packet-lte-rrc-val.h ---*/
#line 1 "packet-lte-rrc-val.h"
#define maxBands                       64
#define maxCDMA_BandClass              32
#define maxCellBlack                   16
#define maxCellInter                   16
#define maxCellIntra                   16
#define maxCellMeas                    32
#define maxCellReport                  8
#define maxDRB                         11
#define maxEARFCN                      65535
#define maxFreq                        8
#define maxCellInfo_GERAN_r9           32
#define maxGERAN_SI                    10
#define maxGNFG                        16
#define maxMBSFN_Allocations           8
#define maxMBSFN_Area                  8
#define maxSessionPerPMCH              29
#define maxSessionPerPMCH_1            28
#define maxPMCH_PerMBSFN               15
#define maxMeasId                      32
#define maxObjectId                    32
#define maxPageRec                     16
#define maxPNOffset                    511
#define maxRAT_Capabilities            8
#define maxReportConfigId              32
#define maxSIB                         32
#define maxSIB_1                       31
#define maxSI_Message                  32
#define maxUTRA_FDD_Carrier            16
#define maxUTRA_TDD_Carrier            16
#define maxUTRA_CellInfo_r9            16
#define maxReestabInfo                 32

/*--- End of included file: packet-lte-rrc-val.h ---*/
#line 52 "packet-lte-rrc-template.c"

/* Initialize the protocol and registered fields */
static int proto_lte_rrc = -1;


/*--- Included file: packet-lte-rrc-hf.c ---*/
#line 1 "packet-lte-rrc-hf.c"
static int hf_lte_rrc_BCCH_BCH_Message_PDU = -1;  /* BCCH_BCH_Message */
static int hf_lte_rrc_BCCH_DL_SCH_Message_PDU = -1;  /* BCCH_DL_SCH_Message */
static int hf_lte_rrc_MCCH_Message_PDU = -1;      /* MCCH_Message */
static int hf_lte_rrc_PCCH_Message_PDU = -1;      /* PCCH_Message */
static int hf_lte_rrc_DL_CCCH_Message_PDU = -1;   /* DL_CCCH_Message */
static int hf_lte_rrc_DL_DCCH_Message_PDU = -1;   /* DL_DCCH_Message */
static int hf_lte_rrc_UL_CCCH_Message_PDU = -1;   /* UL_CCCH_Message */
static int hf_lte_rrc_UL_DCCH_Message_PDU = -1;   /* UL_DCCH_Message */
static int hf_lte_rrc_UECapabilityInformation_PDU = -1;  /* UECapabilityInformation */
static int hf_lte_rrc_UE_EUTRA_Capability_PDU = -1;  /* UE_EUTRA_Capability */
static int hf_lte_rrc_lte_rrc_HandoverCommand_PDU = -1;  /* HandoverCommand */
static int hf_lte_rrc_lte_rrc_HandoverPreparationInformation_PDU = -1;  /* HandoverPreparationInformation */
static int hf_lte_rrc_lte_rrc_UERadioAccessCapabilityInformation_PDU = -1;  /* UERadioAccessCapabilityInformation */
static int hf_lte_rrc_SystemInformationBlockType1_v890_IEs_PDU = -1;  /* SystemInformationBlockType1_v890_IEs */
static int hf_lte_rrc_message = -1;               /* BCCH_BCH_MessageType */
static int hf_lte_rrc_message_01 = -1;            /* BCCH_DL_SCH_MessageType */
static int hf_lte_rrc_c1 = -1;                    /* T_c1 */
static int hf_lte_rrc_systemInformation = -1;     /* SystemInformation */
static int hf_lte_rrc_systemInformationBlockType1 = -1;  /* SystemInformationBlockType1 */
static int hf_lte_rrc_messageClassExtension = -1;  /* T_messageClassExtension */
static int hf_lte_rrc_message_02 = -1;            /* MCCH_MessageType */
static int hf_lte_rrc_c1_01 = -1;                 /* T_c1_01 */
static int hf_lte_rrc_mbsfnAreaConfiguration_r9 = -1;  /* MBSFNAreaConfiguration_r9 */
static int hf_lte_rrc_messageClassExtension_01 = -1;  /* T_messageClassExtension_01 */
static int hf_lte_rrc_message_03 = -1;            /* PCCH_MessageType */
static int hf_lte_rrc_c1_02 = -1;                 /* T_c1_02 */
static int hf_lte_rrc_paging = -1;                /* Paging */
static int hf_lte_rrc_messageClassExtension_02 = -1;  /* T_messageClassExtension_02 */
static int hf_lte_rrc_message_04 = -1;            /* DL_CCCH_MessageType */
static int hf_lte_rrc_c1_03 = -1;                 /* T_c1_03 */
static int hf_lte_rrc_rrcConnectionReestablishment = -1;  /* RRCConnectionReestablishment */
static int hf_lte_rrc_rrcConnectionReestablishmentReject = -1;  /* RRCConnectionReestablishmentReject */
static int hf_lte_rrc_rrcConnectionReject = -1;   /* RRCConnectionReject */
static int hf_lte_rrc_rrcConnectionSetup = -1;    /* RRCConnectionSetup */
static int hf_lte_rrc_messageClassExtension_03 = -1;  /* T_messageClassExtension_03 */
static int hf_lte_rrc_message_05 = -1;            /* DL_DCCH_MessageType */
static int hf_lte_rrc_c1_04 = -1;                 /* T_c1_04 */
static int hf_lte_rrc_csfbParametersResponseCDMA2000 = -1;  /* CSFBParametersResponseCDMA2000 */
static int hf_lte_rrc_dlInformationTransfer = -1;  /* DLInformationTransfer */
static int hf_lte_rrc_handoverFromEUTRAPreparationRequest = -1;  /* HandoverFromEUTRAPreparationRequest */
static int hf_lte_rrc_mobilityFromEUTRACommand = -1;  /* MobilityFromEUTRACommand */
static int hf_lte_rrc_rrcConnectionReconfiguration = -1;  /* RRCConnectionReconfiguration */
static int hf_lte_rrc_rrcConnectionRelease = -1;  /* RRCConnectionRelease */
static int hf_lte_rrc_securityModeCommand = -1;   /* SecurityModeCommand */
static int hf_lte_rrc_ueCapabilityEnquiry = -1;   /* UECapabilityEnquiry */
static int hf_lte_rrc_counterCheck = -1;          /* CounterCheck */
static int hf_lte_rrc_ueInformationRequest_r9 = -1;  /* UEInformationRequest_r9 */
static int hf_lte_rrc_spare6 = -1;                /* NULL */
static int hf_lte_rrc_spare5 = -1;                /* NULL */
static int hf_lte_rrc_spare4 = -1;                /* NULL */
static int hf_lte_rrc_spare3 = -1;                /* NULL */
static int hf_lte_rrc_spare2 = -1;                /* NULL */
static int hf_lte_rrc_spare1 = -1;                /* NULL */
static int hf_lte_rrc_messageClassExtension_04 = -1;  /* T_messageClassExtension_04 */
static int hf_lte_rrc_message_06 = -1;            /* UL_CCCH_MessageType */
static int hf_lte_rrc_c1_05 = -1;                 /* T_c1_05 */
static int hf_lte_rrc_rrcConnectionReestablishmentRequest = -1;  /* RRCConnectionReestablishmentRequest */
static int hf_lte_rrc_rrcConnectionRequest = -1;  /* RRCConnectionRequest */
static int hf_lte_rrc_messageClassExtension_05 = -1;  /* T_messageClassExtension_05 */
static int hf_lte_rrc_message_07 = -1;            /* UL_DCCH_MessageType */
static int hf_lte_rrc_c1_06 = -1;                 /* T_c1_06 */
static int hf_lte_rrc_csfbParametersRequestCDMA2000 = -1;  /* CSFBParametersRequestCDMA2000 */
static int hf_lte_rrc_measurementReport = -1;     /* MeasurementReport */
static int hf_lte_rrc_rrcConnectionReconfigurationComplete = -1;  /* RRCConnectionReconfigurationComplete */
static int hf_lte_rrc_rrcConnectionReestablishmentComplete = -1;  /* RRCConnectionReestablishmentComplete */
static int hf_lte_rrc_rrcConnectionSetupComplete = -1;  /* RRCConnectionSetupComplete */
static int hf_lte_rrc_securityModeComplete = -1;  /* SecurityModeComplete */
static int hf_lte_rrc_securityModeFailure = -1;   /* SecurityModeFailure */
static int hf_lte_rrc_ueCapabilityInformation = -1;  /* UECapabilityInformation */
static int hf_lte_rrc_ulHandoverPreparationTransfer = -1;  /* ULHandoverPreparationTransfer */
static int hf_lte_rrc_ulInformationTransfer = -1;  /* ULInformationTransfer */
static int hf_lte_rrc_counterCheckResponse = -1;  /* CounterCheckResponse */
static int hf_lte_rrc_ueInformationResponse_r9 = -1;  /* UEInformationResponse_r9 */
static int hf_lte_rrc_proximityIndication_r9 = -1;  /* ProximityIndication_r9 */
static int hf_lte_rrc_messageClassExtension_06 = -1;  /* T_messageClassExtension_06 */
static int hf_lte_rrc_rrc_TransactionIdentifier = -1;  /* RRC_TransactionIdentifier */
static int hf_lte_rrc_criticalExtensions = -1;    /* T_criticalExtensions */
static int hf_lte_rrc_c1_07 = -1;                 /* T_c1_07 */
static int hf_lte_rrc_counterCheck_r8 = -1;       /* CounterCheck_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture = -1;  /* T_criticalExtensionsFuture */
static int hf_lte_rrc_drb_CountMSB_InfoList = -1;  /* DRB_CountMSB_InfoList */
static int hf_lte_rrc_nonCriticalExtension = -1;  /* T_nonCriticalExtension */
static int hf_lte_rrc_DRB_CountMSB_InfoList_item = -1;  /* DRB_CountMSB_Info */
static int hf_lte_rrc_drb_Identity = -1;          /* DRB_Identity */
static int hf_lte_rrc_countMSB_Uplink = -1;       /* INTEGER_0_33554431 */
static int hf_lte_rrc_countMSB_Downlink = -1;     /* INTEGER_0_33554431 */
static int hf_lte_rrc_criticalExtensions_01 = -1;  /* T_criticalExtensions_01 */
static int hf_lte_rrc_counterCheckResponse_r8 = -1;  /* CounterCheckResponse_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_01 = -1;  /* T_criticalExtensionsFuture_01 */
static int hf_lte_rrc_drb_CountInfoList = -1;     /* DRB_CountInfoList */
static int hf_lte_rrc_nonCriticalExtension_01 = -1;  /* T_nonCriticalExtension_01 */
static int hf_lte_rrc_DRB_CountInfoList_item = -1;  /* DRB_CountInfo */
static int hf_lte_rrc_count_Uplink = -1;          /* INTEGER_0_4294967295 */
static int hf_lte_rrc_count_Downlink = -1;        /* INTEGER_0_4294967295 */
static int hf_lte_rrc_criticalExtensions_02 = -1;  /* T_criticalExtensions_02 */
static int hf_lte_rrc_csfbParametersRequestCDMA2000_r8 = -1;  /* CSFBParametersRequestCDMA2000_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_02 = -1;  /* T_criticalExtensionsFuture_02 */
static int hf_lte_rrc_nonCriticalExtension_02 = -1;  /* T_nonCriticalExtension_02 */
static int hf_lte_rrc_criticalExtensions_03 = -1;  /* T_criticalExtensions_03 */
static int hf_lte_rrc_csfbParametersResponseCDMA2000_r8 = -1;  /* CSFBParametersResponseCDMA2000_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_03 = -1;  /* T_criticalExtensionsFuture_03 */
static int hf_lte_rrc_rand = -1;                  /* RAND_CDMA2000 */
static int hf_lte_rrc_mobilityParameters = -1;    /* MobilityParametersCDMA2000 */
static int hf_lte_rrc_nonCriticalExtension_03 = -1;  /* T_nonCriticalExtension_03 */
static int hf_lte_rrc_criticalExtensions_04 = -1;  /* T_criticalExtensions_04 */
static int hf_lte_rrc_c1_08 = -1;                 /* T_c1_08 */
static int hf_lte_rrc_dlInformationTransfer_r8 = -1;  /* DLInformationTransfer_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_04 = -1;  /* T_criticalExtensionsFuture_04 */
static int hf_lte_rrc_dedicatedInfoType = -1;     /* T_dedicatedInfoType */
static int hf_lte_rrc_dedicatedInfoNAS = -1;      /* DedicatedInfoNAS */
static int hf_lte_rrc_dedicatedInfoCDMA2000_1XRTT = -1;  /* DedicatedInfoCDMA2000 */
static int hf_lte_rrc_dedicatedInfoCDMA2000_HRPD = -1;  /* DedicatedInfoCDMA2000 */
static int hf_lte_rrc_nonCriticalExtension_04 = -1;  /* T_nonCriticalExtension_04 */
static int hf_lte_rrc_criticalExtensions_05 = -1;  /* T_criticalExtensions_05 */
static int hf_lte_rrc_c1_09 = -1;                 /* T_c1_09 */
static int hf_lte_rrc_handoverFromEUTRAPreparationRequest_r8 = -1;  /* HandoverFromEUTRAPreparationRequest_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_05 = -1;  /* T_criticalExtensionsFuture_05 */
static int hf_lte_rrc_cdma2000_Type = -1;         /* CDMA2000_Type */
static int hf_lte_rrc_nonCriticalExtension_05 = -1;  /* HandoverFromEUTRAPreparationRequest_v890_IEs */
static int hf_lte_rrc_lateR8NonCriticalExtension = -1;  /* OCTET_STRING */
static int hf_lte_rrc_nonCriticalExtension_06 = -1;  /* HandoverFromEUTRAPreparationRequest_v920_IEs */
static int hf_lte_rrc_concurrPrepCDMA2000_HRPD_r9 = -1;  /* BOOLEAN */
static int hf_lte_rrc_nonCriticalExtension_07 = -1;  /* T_nonCriticalExtension_05 */
static int hf_lte_rrc_dl_Bandwidth = -1;          /* T_dl_Bandwidth */
static int hf_lte_rrc_phich_Config = -1;          /* PHICH_Config */
static int hf_lte_rrc_systemFrameNumber = -1;     /* BIT_STRING_SIZE_8 */
static int hf_lte_rrc_spare = -1;                 /* BIT_STRING_SIZE_10 */
static int hf_lte_rrc_commonSF_Alloc_r9 = -1;     /* CommonSF_AllocPatternList_r9 */
static int hf_lte_rrc_commonSF_AllocPeriod_r9 = -1;  /* T_commonSF_AllocPeriod_r9 */
static int hf_lte_rrc_pmch_InfoList_r9 = -1;      /* PMCH_InfoList_r9 */
static int hf_lte_rrc_nonCriticalExtension_08 = -1;  /* T_nonCriticalExtension_06 */
static int hf_lte_rrc_CommonSF_AllocPatternList_r9_item = -1;  /* MBSFN_SubframeConfig */
static int hf_lte_rrc_criticalExtensions_06 = -1;  /* T_criticalExtensions_06 */
static int hf_lte_rrc_c1_10 = -1;                 /* T_c1_10 */
static int hf_lte_rrc_measurementReport_r8 = -1;  /* MeasurementReport_r8_IEs */
static int hf_lte_rrc_spare7 = -1;                /* NULL */
static int hf_lte_rrc_criticalExtensionsFuture_06 = -1;  /* T_criticalExtensionsFuture_06 */
static int hf_lte_rrc_measResults = -1;           /* MeasResults */
static int hf_lte_rrc_nonCriticalExtension_09 = -1;  /* T_nonCriticalExtension_07 */
static int hf_lte_rrc_criticalExtensions_07 = -1;  /* T_criticalExtensions_07 */
static int hf_lte_rrc_c1_11 = -1;                 /* T_c1_11 */
static int hf_lte_rrc_mobilityFromEUTRACommand_r8 = -1;  /* MobilityFromEUTRACommand_r8_IEs */
static int hf_lte_rrc_mobilityFromEUTRACommand_r9 = -1;  /* MobilityFromEUTRACommand_r9_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_07 = -1;  /* T_criticalExtensionsFuture_07 */
static int hf_lte_rrc_cs_FallbackIndicator = -1;  /* BOOLEAN */
static int hf_lte_rrc_purpose = -1;               /* T_purpose */
static int hf_lte_rrc_handover = -1;              /* Handover */
static int hf_lte_rrc_cellChangeOrder = -1;       /* CellChangeOrder */
static int hf_lte_rrc_nonCriticalExtension_10 = -1;  /* T_nonCriticalExtension_08 */
static int hf_lte_rrc_purpose_01 = -1;            /* T_purpose_01 */
static int hf_lte_rrc_e_CSFB_r9 = -1;             /* E_CSFB_r9 */
static int hf_lte_rrc_nonCriticalExtension_11 = -1;  /* T_nonCriticalExtension_09 */
static int hf_lte_rrc_targetRAT_Type = -1;        /* T_targetRAT_Type */
static int hf_lte_rrc_targetRAT_MessageContainer = -1;  /* OCTET_STRING */
static int hf_lte_rrc_nas_SecurityParamFromEUTRA = -1;  /* OCTET_STRING_SIZE_1 */
static int hf_lte_rrc_systemInformation_01 = -1;  /* SI_OrPSI_GERAN */
static int hf_lte_rrc_t304 = -1;                  /* T_t304 */
static int hf_lte_rrc_targetRAT_Type_01 = -1;     /* T_targetRAT_Type_01 */
static int hf_lte_rrc_geran = -1;                 /* T_geran */
static int hf_lte_rrc_physCellId = -1;            /* PhysCellIdGERAN */
static int hf_lte_rrc_carrierFreq = -1;           /* CarrierFreqGERAN */
static int hf_lte_rrc_networkControlOrder = -1;   /* BIT_STRING_SIZE_2 */
static int hf_lte_rrc_si = -1;                    /* SystemInfoListGERAN */
static int hf_lte_rrc_psi = -1;                   /* SystemInfoListGERAN */
static int hf_lte_rrc_messageContCDMA2000_1XRTT_r9 = -1;  /* OCTET_STRING */
static int hf_lte_rrc_mobilityCDMA2000_HRPD_r9 = -1;  /* T_mobilityCDMA2000_HRPD_r9 */
static int hf_lte_rrc_messageContCDMA2000_HRPD_r9 = -1;  /* OCTET_STRING */
static int hf_lte_rrc_redirectCarrierCDMA2000_HRPD_r9 = -1;  /* CarrierFreqCDMA2000 */
static int hf_lte_rrc_pagingRecordList = -1;      /* PagingRecordList */
static int hf_lte_rrc_systemInfoModification = -1;  /* T_systemInfoModification */
static int hf_lte_rrc_etws_Indication = -1;       /* T_etws_Indication */
static int hf_lte_rrc_nonCriticalExtension_12 = -1;  /* Paging_v890_IEs */
static int hf_lte_rrc_nonCriticalExtension_13 = -1;  /* Paging_v920_IEs */
static int hf_lte_rrc_cmas_Indication_r9 = -1;    /* T_cmas_Indication_r9 */
static int hf_lte_rrc_nonCriticalExtension_14 = -1;  /* T_nonCriticalExtension_10 */
static int hf_lte_rrc_PagingRecordList_item = -1;  /* PagingRecord */
static int hf_lte_rrc_ue_Identity = -1;           /* PagingUE_Identity */
static int hf_lte_rrc_cn_Domain = -1;             /* T_cn_Domain */
static int hf_lte_rrc_s_TMSI = -1;                /* S_TMSI */
static int hf_lte_rrc_imsi = -1;                  /* IMSI */
static int hf_lte_rrc_IMSI_item = -1;             /* IMSI_Digit */
static int hf_lte_rrc_criticalExtensions_08 = -1;  /* T_criticalExtensions_08 */
static int hf_lte_rrc_c1_12 = -1;                 /* T_c1_12 */
static int hf_lte_rrc_proximityIndication_r9_01 = -1;  /* ProximityIndication_r9_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_08 = -1;  /* T_criticalExtensionsFuture_08 */
static int hf_lte_rrc_type_r9 = -1;               /* T_type_r9 */
static int hf_lte_rrc_carrierFreq_r9 = -1;        /* T_carrierFreq_r9 */
static int hf_lte_rrc_eutra_r9 = -1;              /* ARFCN_ValueEUTRA */
static int hf_lte_rrc_utra_r9 = -1;               /* ARFCN_ValueUTRA */
static int hf_lte_rrc_nonCriticalExtension_15 = -1;  /* T_nonCriticalExtension_11 */
static int hf_lte_rrc_criticalExtensions_09 = -1;  /* T_criticalExtensions_09 */
static int hf_lte_rrc_c1_13 = -1;                 /* T_c1_13 */
static int hf_lte_rrc_rrcConnectionReconfiguration_r8 = -1;  /* RRCConnectionReconfiguration_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_09 = -1;  /* T_criticalExtensionsFuture_09 */
static int hf_lte_rrc_measConfig = -1;            /* MeasConfig */
static int hf_lte_rrc_mobilityControlInfo = -1;   /* MobilityControlInfo */
static int hf_lte_rrc_dedicatedInfoNASList = -1;  /* SEQUENCE_SIZE_1_maxDRB_OF_DedicatedInfoNAS */
static int hf_lte_rrc_dedicatedInfoNASList_item = -1;  /* DedicatedInfoNAS */
static int hf_lte_rrc_radioResourceConfigDedicated = -1;  /* RadioResourceConfigDedicated */
static int hf_lte_rrc_securityConfigHO = -1;      /* SecurityConfigHO */
static int hf_lte_rrc_nonCriticalExtension_16 = -1;  /* RRCConnectionReconfiguration_v890_IEs */
static int hf_lte_rrc_nonCriticalExtension_17 = -1;  /* RRCConnectionReconfiguration_v920_IEs */
static int hf_lte_rrc_otherConfig_r9 = -1;        /* OtherConfig_r9 */
static int hf_lte_rrc_fullConfig_r9 = -1;         /* T_fullConfig_r9 */
static int hf_lte_rrc_nonCriticalExtension_18 = -1;  /* T_nonCriticalExtension_12 */
static int hf_lte_rrc_handoverType = -1;          /* T_handoverType */
static int hf_lte_rrc_intraLTE = -1;              /* T_intraLTE */
static int hf_lte_rrc_securityAlgorithmConfig = -1;  /* SecurityAlgorithmConfig */
static int hf_lte_rrc_keyChangeIndicator = -1;    /* BOOLEAN */
static int hf_lte_rrc_nextHopChainingCount = -1;  /* NextHopChainingCount */
static int hf_lte_rrc_interRAT = -1;              /* T_interRAT */
static int hf_lte_rrc_nas_SecurityParamToEUTRA = -1;  /* OCTET_STRING_SIZE_6 */
static int hf_lte_rrc_criticalExtensions_10 = -1;  /* T_criticalExtensions_10 */
static int hf_lte_rrc_rrcConnectionReconfigurationComplete_r8 = -1;  /* RRCConnectionReconfigurationComplete_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_10 = -1;  /* T_criticalExtensionsFuture_10 */
static int hf_lte_rrc_nonCriticalExtension_19 = -1;  /* T_nonCriticalExtension_13 */
static int hf_lte_rrc_criticalExtensions_11 = -1;  /* T_criticalExtensions_11 */
static int hf_lte_rrc_c1_14 = -1;                 /* T_c1_14 */
static int hf_lte_rrc_rrcConnectionReestablishment_r8 = -1;  /* RRCConnectionReestablishment_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_11 = -1;  /* T_criticalExtensionsFuture_11 */
static int hf_lte_rrc_nonCriticalExtension_20 = -1;  /* T_nonCriticalExtension_14 */
static int hf_lte_rrc_criticalExtensions_12 = -1;  /* T_criticalExtensions_12 */
static int hf_lte_rrc_rrcConnectionReestablishmentComplete_r8 = -1;  /* RRCConnectionReestablishmentComplete_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_12 = -1;  /* T_criticalExtensionsFuture_12 */
static int hf_lte_rrc_nonCriticalExtension_21 = -1;  /* RRCConnectionReestablishmentComplete_v920_IEs */
static int hf_lte_rrc_rlf_InfoAvailable_r9 = -1;  /* T_rlf_InfoAvailable_r9 */
static int hf_lte_rrc_nonCriticalExtension_22 = -1;  /* T_nonCriticalExtension_15 */
static int hf_lte_rrc_criticalExtensions_13 = -1;  /* T_criticalExtensions_13 */
static int hf_lte_rrc_rrcConnectionReestablishmentReject_r8 = -1;  /* RRCConnectionReestablishmentReject_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_13 = -1;  /* T_criticalExtensionsFuture_13 */
static int hf_lte_rrc_nonCriticalExtension_23 = -1;  /* T_nonCriticalExtension_16 */
static int hf_lte_rrc_criticalExtensions_14 = -1;  /* T_criticalExtensions_14 */
static int hf_lte_rrc_rrcConnectionReestablishmentRequest_r8 = -1;  /* RRCConnectionReestablishmentRequest_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_14 = -1;  /* T_criticalExtensionsFuture_14 */
static int hf_lte_rrc_ue_Identity_01 = -1;        /* ReestabUE_Identity */
static int hf_lte_rrc_reestablishmentCause = -1;  /* ReestablishmentCause */
static int hf_lte_rrc_spare_01 = -1;              /* BIT_STRING_SIZE_2 */
static int hf_lte_rrc_c_RNTI = -1;                /* C_RNTI */
static int hf_lte_rrc_physCellId_01 = -1;         /* PhysCellId */
static int hf_lte_rrc_shortMAC_I = -1;            /* ShortMAC_I */
static int hf_lte_rrc_criticalExtensions_15 = -1;  /* T_criticalExtensions_15 */
static int hf_lte_rrc_c1_15 = -1;                 /* T_c1_15 */
static int hf_lte_rrc_rrcConnectionReject_r8 = -1;  /* RRCConnectionReject_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_15 = -1;  /* T_criticalExtensionsFuture_15 */
static int hf_lte_rrc_waitTime = -1;              /* INTEGER_1_16 */
static int hf_lte_rrc_nonCriticalExtension_24 = -1;  /* T_nonCriticalExtension_17 */
static int hf_lte_rrc_criticalExtensions_16 = -1;  /* T_criticalExtensions_16 */
static int hf_lte_rrc_c1_16 = -1;                 /* T_c1_16 */
static int hf_lte_rrc_rrcConnectionRelease_r8 = -1;  /* RRCConnectionRelease_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_16 = -1;  /* T_criticalExtensionsFuture_16 */
static int hf_lte_rrc_releaseCause = -1;          /* ReleaseCause */
static int hf_lte_rrc_redirectedCarrierInfo = -1;  /* RedirectedCarrierInfo */
static int hf_lte_rrc_idleModeMobilityControlInfo = -1;  /* IdleModeMobilityControlInfo */
static int hf_lte_rrc_nonCriticalExtension_25 = -1;  /* RRCConnectionRelease_v890_IEs */
static int hf_lte_rrc_nonCriticalExtension_26 = -1;  /* RRCConnectionRelease_v920_IEs */
static int hf_lte_rrc_cellInfoList_r9 = -1;       /* T_cellInfoList_r9 */
static int hf_lte_rrc_geran_r9 = -1;              /* CellInfoListGERAN_r9 */
static int hf_lte_rrc_utra_FDD_r9 = -1;           /* CellInfoListUTRA_FDD_r9 */
static int hf_lte_rrc_utra_TDD_r9 = -1;           /* CellInfoListUTRA_TDD_r9 */
static int hf_lte_rrc_nonCriticalExtension_27 = -1;  /* T_nonCriticalExtension_18 */
static int hf_lte_rrc_eutra = -1;                 /* ARFCN_ValueEUTRA */
static int hf_lte_rrc_geran_01 = -1;              /* CarrierFreqsGERAN */
static int hf_lte_rrc_utra_FDD = -1;              /* ARFCN_ValueUTRA */
static int hf_lte_rrc_utra_TDD = -1;              /* ARFCN_ValueUTRA */
static int hf_lte_rrc_cdma2000_HRPD = -1;         /* CarrierFreqCDMA2000 */
static int hf_lte_rrc_cdma2000_1xRTT = -1;        /* CarrierFreqCDMA2000 */
static int hf_lte_rrc_freqPriorityListEUTRA = -1;  /* FreqPriorityListEUTRA */
static int hf_lte_rrc_freqPriorityListGERAN = -1;  /* FreqsPriorityListGERAN */
static int hf_lte_rrc_freqPriorityListUTRA_FDD = -1;  /* FreqPriorityListUTRA_FDD */
static int hf_lte_rrc_freqPriorityListUTRA_TDD = -1;  /* FreqPriorityListUTRA_TDD */
static int hf_lte_rrc_bandClassPriorityListHRPD = -1;  /* BandClassPriorityListHRPD */
static int hf_lte_rrc_bandClassPriorityList1XRTT = -1;  /* BandClassPriorityList1XRTT */
static int hf_lte_rrc_t320 = -1;                  /* T_t320 */
static int hf_lte_rrc_FreqPriorityListEUTRA_item = -1;  /* FreqPriorityEUTRA */
static int hf_lte_rrc_carrierFreq_01 = -1;        /* ARFCN_ValueEUTRA */
static int hf_lte_rrc_cellReselectionPriority = -1;  /* CellReselectionPriority */
static int hf_lte_rrc_FreqsPriorityListGERAN_item = -1;  /* FreqsPriorityGERAN */
static int hf_lte_rrc_carrierFreqs = -1;          /* CarrierFreqsGERAN */
static int hf_lte_rrc_FreqPriorityListUTRA_FDD_item = -1;  /* FreqPriorityUTRA_FDD */
static int hf_lte_rrc_carrierFreq_02 = -1;        /* ARFCN_ValueUTRA */
static int hf_lte_rrc_FreqPriorityListUTRA_TDD_item = -1;  /* FreqPriorityUTRA_TDD */
static int hf_lte_rrc_BandClassPriorityListHRPD_item = -1;  /* BandClassPriorityHRPD */
static int hf_lte_rrc_bandClass = -1;             /* BandclassCDMA2000 */
static int hf_lte_rrc_BandClassPriorityList1XRTT_item = -1;  /* BandClassPriority1XRTT */
static int hf_lte_rrc_CellInfoListGERAN_r9_item = -1;  /* CellInfoGERAN_r9 */
static int hf_lte_rrc_physCellId_r9 = -1;         /* PhysCellIdGERAN */
static int hf_lte_rrc_carrierFreq_r9_01 = -1;     /* CarrierFreqGERAN */
static int hf_lte_rrc_systemInformation_r9 = -1;  /* SystemInfoListGERAN */
static int hf_lte_rrc_CellInfoListUTRA_FDD_r9_item = -1;  /* CellInfoUTRA_FDD_r9 */
static int hf_lte_rrc_physCellId_r9_01 = -1;      /* PhysCellIdUTRA_FDD */
static int hf_lte_rrc_utra_BCCH_Container_r9 = -1;  /* OCTET_STRING */
static int hf_lte_rrc_CellInfoListUTRA_TDD_r9_item = -1;  /* CellInfoUTRA_TDD_r9 */
static int hf_lte_rrc_physCellId_r9_02 = -1;      /* PhysCellIdUTRA_TDD */
static int hf_lte_rrc_criticalExtensions_17 = -1;  /* T_criticalExtensions_17 */
static int hf_lte_rrc_rrcConnectionRequest_r8 = -1;  /* RRCConnectionRequest_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_17 = -1;  /* T_criticalExtensionsFuture_17 */
static int hf_lte_rrc_ue_Identity_02 = -1;        /* InitialUE_Identity */
static int hf_lte_rrc_establishmentCause = -1;    /* EstablishmentCause */
static int hf_lte_rrc_spare_02 = -1;              /* BIT_STRING_SIZE_1 */
static int hf_lte_rrc_randomValue = -1;           /* BIT_STRING_SIZE_40 */
static int hf_lte_rrc_criticalExtensions_18 = -1;  /* T_criticalExtensions_18 */
static int hf_lte_rrc_c1_17 = -1;                 /* T_c1_17 */
static int hf_lte_rrc_rrcConnectionSetup_r8 = -1;  /* RRCConnectionSetup_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_18 = -1;  /* T_criticalExtensionsFuture_18 */
static int hf_lte_rrc_nonCriticalExtension_28 = -1;  /* T_nonCriticalExtension_19 */
static int hf_lte_rrc_criticalExtensions_19 = -1;  /* T_criticalExtensions_19 */
static int hf_lte_rrc_c1_18 = -1;                 /* T_c1_18 */
static int hf_lte_rrc_rrcConnectionSetupComplete_r8 = -1;  /* RRCConnectionSetupComplete_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_19 = -1;  /* T_criticalExtensionsFuture_19 */
static int hf_lte_rrc_selectedPLMN_Identity = -1;  /* INTEGER_1_6 */
static int hf_lte_rrc_registeredMME = -1;         /* RegisteredMME */
static int hf_lte_rrc_nonCriticalExtension_29 = -1;  /* T_nonCriticalExtension_20 */
static int hf_lte_rrc_plmn_Identity = -1;         /* PLMN_Identity */
static int hf_lte_rrc_mmegi = -1;                 /* BIT_STRING_SIZE_16 */
static int hf_lte_rrc_mmec = -1;                  /* MMEC */
static int hf_lte_rrc_criticalExtensions_20 = -1;  /* T_criticalExtensions_20 */
static int hf_lte_rrc_c1_19 = -1;                 /* T_c1_19 */
static int hf_lte_rrc_securityModeCommand_r8 = -1;  /* SecurityModeCommand_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_20 = -1;  /* T_criticalExtensionsFuture_20 */
static int hf_lte_rrc_securityConfigSMC = -1;     /* SecurityConfigSMC */
static int hf_lte_rrc_nonCriticalExtension_30 = -1;  /* T_nonCriticalExtension_21 */
static int hf_lte_rrc_criticalExtensions_21 = -1;  /* T_criticalExtensions_21 */
static int hf_lte_rrc_securityModeComplete_r8 = -1;  /* SecurityModeComplete_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_21 = -1;  /* T_criticalExtensionsFuture_21 */
static int hf_lte_rrc_nonCriticalExtension_31 = -1;  /* T_nonCriticalExtension_22 */
static int hf_lte_rrc_criticalExtensions_22 = -1;  /* T_criticalExtensions_22 */
static int hf_lte_rrc_securityModeFailure_r8 = -1;  /* SecurityModeFailure_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_22 = -1;  /* T_criticalExtensionsFuture_22 */
static int hf_lte_rrc_nonCriticalExtension_32 = -1;  /* T_nonCriticalExtension_23 */
static int hf_lte_rrc_criticalExtensions_23 = -1;  /* T_criticalExtensions_23 */
static int hf_lte_rrc_systemInformation_r8 = -1;  /* SystemInformation_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_23 = -1;  /* T_criticalExtensionsFuture_23 */
static int hf_lte_rrc_sib_TypeAndInfo = -1;       /* T_sib_TypeAndInfo */
static int hf_lte_rrc_sib_TypeAndInfo_item = -1;  /* T_sib_TypeAndInfo_item */
static int hf_lte_rrc_sib2 = -1;                  /* SystemInformationBlockType2 */
static int hf_lte_rrc_sib3 = -1;                  /* SystemInformationBlockType3 */
static int hf_lte_rrc_sib4 = -1;                  /* SystemInformationBlockType4 */
static int hf_lte_rrc_sib5 = -1;                  /* SystemInformationBlockType5 */
static int hf_lte_rrc_sib6 = -1;                  /* SystemInformationBlockType6 */
static int hf_lte_rrc_sib7 = -1;                  /* SystemInformationBlockType7 */
static int hf_lte_rrc_sib8 = -1;                  /* SystemInformationBlockType8 */
static int hf_lte_rrc_sib9 = -1;                  /* SystemInformationBlockType9 */
static int hf_lte_rrc_sib10 = -1;                 /* SystemInformationBlockType10 */
static int hf_lte_rrc_sib11 = -1;                 /* SystemInformationBlockType11 */
static int hf_lte_rrc_sib12_v920 = -1;            /* SystemInformationBlockType12_r9 */
static int hf_lte_rrc_sib13_v920 = -1;            /* SystemInformationBlockType13_r9 */
static int hf_lte_rrc_nonCriticalExtension_33 = -1;  /* T_nonCriticalExtension_24 */
static int hf_lte_rrc_cellAccessRelatedInfo = -1;  /* T_cellAccessRelatedInfo */
static int hf_lte_rrc_plmn_IdentityList = -1;     /* PLMN_IdentityList */
static int hf_lte_rrc_trackingAreaCode = -1;      /* TrackingAreaCode */
static int hf_lte_rrc_cellIdentity = -1;          /* CellIdentity */
static int hf_lte_rrc_cellBarred = -1;            /* T_cellBarred */
static int hf_lte_rrc_intraFreqReselection = -1;  /* T_intraFreqReselection */
static int hf_lte_rrc_csg_Indication = -1;        /* BOOLEAN */
static int hf_lte_rrc_csg_Identity = -1;          /* CSG_Identity */
static int hf_lte_rrc_cellSelectionInfo = -1;     /* T_cellSelectionInfo */
static int hf_lte_rrc_q_RxLevMin = -1;            /* Q_RxLevMin */
static int hf_lte_rrc_q_RxLevMinOffset = -1;      /* INTEGER_1_8 */
static int hf_lte_rrc_p_Max = -1;                 /* P_Max */
static int hf_lte_rrc_freqBandIndicator = -1;     /* INTEGER_1_64 */
static int hf_lte_rrc_schedulingInfoList = -1;    /* SchedulingInfoList */
static int hf_lte_rrc_tdd_Config = -1;            /* TDD_Config */
static int hf_lte_rrc_si_WindowLength = -1;       /* T_si_WindowLength */
static int hf_lte_rrc_systemInfoValueTag = -1;    /* INTEGER_0_31 */
static int hf_lte_rrc_nonCriticalExtension_34 = -1;  /* SystemInformationBlockType1_v890_IEs */
static int hf_lte_rrc_nonCriticalExtension_35 = -1;  /* SystemInformationBlockType1_v920_IEs */
static int hf_lte_rrc_ims_EmergencySupport_r9 = -1;  /* T_ims_EmergencySupport_r9 */
static int hf_lte_rrc_cellSelectionInfo_v920 = -1;  /* CellSelectionInfo_v920 */
static int hf_lte_rrc_nonCriticalExtension_36 = -1;  /* T_nonCriticalExtension_25 */
static int hf_lte_rrc_PLMN_IdentityList_item = -1;  /* PLMN_IdentityInfo */
static int hf_lte_rrc_cellReservedForOperatorUse = -1;  /* T_cellReservedForOperatorUse */
static int hf_lte_rrc_SchedulingInfoList_item = -1;  /* SchedulingInfo */
static int hf_lte_rrc_si_Periodicity = -1;        /* T_si_Periodicity */
static int hf_lte_rrc_sib_MappingInfo = -1;       /* SIB_MappingInfo */
static int hf_lte_rrc_SIB_MappingInfo_item = -1;  /* SIB_Type */
static int hf_lte_rrc_q_QualMin_r9 = -1;          /* Q_QualMin_r9 */
static int hf_lte_rrc_q_QualMinOffset_r9 = -1;    /* INTEGER_1_8 */
static int hf_lte_rrc_criticalExtensions_24 = -1;  /* T_criticalExtensions_24 */
static int hf_lte_rrc_c1_20 = -1;                 /* T_c1_20 */
static int hf_lte_rrc_ueCapabilityEnquiry_r8 = -1;  /* UECapabilityEnquiry_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_24 = -1;  /* T_criticalExtensionsFuture_24 */
static int hf_lte_rrc_ue_CapabilityRequest = -1;  /* UE_CapabilityRequest */
static int hf_lte_rrc_nonCriticalExtension_37 = -1;  /* T_nonCriticalExtension_26 */
static int hf_lte_rrc_UE_CapabilityRequest_item = -1;  /* RAT_Type */
static int hf_lte_rrc_criticalExtensions_25 = -1;  /* T_criticalExtensions_25 */
static int hf_lte_rrc_c1_21 = -1;                 /* T_c1_21 */
static int hf_lte_rrc_ueCapabilityInformation_r8 = -1;  /* UECapabilityInformation_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_25 = -1;  /* T_criticalExtensionsFuture_25 */
static int hf_lte_rrc_ue_CapabilityRAT_ContainerList = -1;  /* UE_CapabilityRAT_ContainerList */
static int hf_lte_rrc_nonCriticalExtension_38 = -1;  /* T_nonCriticalExtension_27 */
static int hf_lte_rrc_criticalExtensions_26 = -1;  /* T_criticalExtensions_26 */
static int hf_lte_rrc_c1_22 = -1;                 /* T_c1_22 */
static int hf_lte_rrc_ueInformationRequest_r9_01 = -1;  /* UEInformationRequest_r9_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_26 = -1;  /* T_criticalExtensionsFuture_26 */
static int hf_lte_rrc_rach_ReportReq_r9 = -1;     /* BOOLEAN */
static int hf_lte_rrc_rlf_ReportReq_r9 = -1;      /* BOOLEAN */
static int hf_lte_rrc_nonCriticalExtension_39 = -1;  /* T_nonCriticalExtension_28 */
static int hf_lte_rrc_criticalExtensions_27 = -1;  /* T_criticalExtensions_27 */
static int hf_lte_rrc_c1_23 = -1;                 /* T_c1_23 */
static int hf_lte_rrc_ueInformationResponse_r9_01 = -1;  /* UEInformationResponse_r9_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_27 = -1;  /* T_criticalExtensionsFuture_27 */
static int hf_lte_rrc_rach_Report_r9 = -1;        /* T_rach_Report_r9 */
static int hf_lte_rrc_numberOfPreamblesSent_r9 = -1;  /* INTEGER_1_200 */
static int hf_lte_rrc_contentionDetected_r9 = -1;  /* BOOLEAN */
static int hf_lte_rrc_rlfReport_r9 = -1;          /* RLF_Report_r9 */
static int hf_lte_rrc_nonCriticalExtension_40 = -1;  /* T_nonCriticalExtension_29 */
static int hf_lte_rrc_measResultLastServCell = -1;  /* T_measResultLastServCell */
static int hf_lte_rrc_rsrpResult = -1;            /* RSRP_Range */
static int hf_lte_rrc_rsrqResult = -1;            /* RSRQ_Range */
static int hf_lte_rrc_measResultNeighCells = -1;  /* T_measResultNeighCells */
static int hf_lte_rrc_measResultListEUTRA = -1;   /* MeasResultList2EUTRA */
static int hf_lte_rrc_measResultListUTRA = -1;    /* MeasResultList2UTRA */
static int hf_lte_rrc_measResultListGERAN = -1;   /* MeasResultListGERAN */
static int hf_lte_rrc_measResultsCDMA2000 = -1;   /* MeasResultList2CDMA2000 */
static int hf_lte_rrc_MeasResultList2EUTRA_item = -1;  /* MeasResultList2EUTRA_item */
static int hf_lte_rrc_measResultList = -1;        /* MeasResultListEUTRA */
static int hf_lte_rrc_MeasResultList2UTRA_item = -1;  /* MeasResultList2UTRA_item */
static int hf_lte_rrc_measResultList_01 = -1;     /* MeasResultListUTRA */
static int hf_lte_rrc_MeasResultList2CDMA2000_item = -1;  /* MeasResultList2CDMA2000_item */
static int hf_lte_rrc_carrierFreq_03 = -1;        /* CarrierFreqCDMA2000 */
static int hf_lte_rrc_measResultList_02 = -1;     /* MeasResultsCDMA2000 */
static int hf_lte_rrc_criticalExtensions_28 = -1;  /* T_criticalExtensions_28 */
static int hf_lte_rrc_c1_24 = -1;                 /* T_c1_24 */
static int hf_lte_rrc_ulHandoverPreparationTransfer_r8 = -1;  /* ULHandoverPreparationTransfer_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_28 = -1;  /* T_criticalExtensionsFuture_28 */
static int hf_lte_rrc_meid = -1;                  /* BIT_STRING_SIZE_56 */
static int hf_lte_rrc_dedicatedInfo = -1;         /* DedicatedInfoCDMA2000 */
static int hf_lte_rrc_nonCriticalExtension_41 = -1;  /* T_nonCriticalExtension_30 */
static int hf_lte_rrc_criticalExtensions_29 = -1;  /* T_criticalExtensions_29 */
static int hf_lte_rrc_c1_25 = -1;                 /* T_c1_25 */
static int hf_lte_rrc_ulInformationTransfer_r8 = -1;  /* ULInformationTransfer_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_29 = -1;  /* T_criticalExtensionsFuture_29 */
static int hf_lte_rrc_dedicatedInfoType_01 = -1;  /* T_dedicatedInfoType_01 */
static int hf_lte_rrc_nonCriticalExtension_42 = -1;  /* T_nonCriticalExtension_31 */
static int hf_lte_rrc_ac_BarringInfo = -1;        /* T_ac_BarringInfo */
static int hf_lte_rrc_ac_BarringForEmergency = -1;  /* BOOLEAN */
static int hf_lte_rrc_ac_BarringForMO_Signalling = -1;  /* AC_BarringConfig */
static int hf_lte_rrc_ac_BarringForMO_Data = -1;  /* AC_BarringConfig */
static int hf_lte_rrc_radioResourceConfigCommon = -1;  /* RadioResourceConfigCommonSIB */
static int hf_lte_rrc_ue_TimersAndConstants = -1;  /* UE_TimersAndConstants */
static int hf_lte_rrc_freqInfo = -1;              /* T_freqInfo */
static int hf_lte_rrc_ul_CarrierFreq = -1;        /* ARFCN_ValueEUTRA */
static int hf_lte_rrc_ul_Bandwidth = -1;          /* T_ul_Bandwidth */
static int hf_lte_rrc_additionalSpectrumEmission = -1;  /* AdditionalSpectrumEmission */
static int hf_lte_rrc_mbsfn_SubframeConfigList = -1;  /* MBSFN_SubframeConfigList */
static int hf_lte_rrc_timeAlignmentTimerCommon = -1;  /* TimeAlignmentTimer */
static int hf_lte_rrc_ssac_BarringForMMTEL_Voice_r9 = -1;  /* AC_BarringConfig */
static int hf_lte_rrc_ssac_BarringForMMTEL_Video_r9 = -1;  /* AC_BarringConfig */
static int hf_lte_rrc_ac_BarringFactor = -1;      /* T_ac_BarringFactor */
static int hf_lte_rrc_ac_BarringTime = -1;        /* T_ac_BarringTime */
static int hf_lte_rrc_ac_BarringForSpecialAC = -1;  /* BIT_STRING_SIZE_5 */
static int hf_lte_rrc_MBSFN_SubframeConfigList_item = -1;  /* MBSFN_SubframeConfig */
static int hf_lte_rrc_cellReselectionInfoCommon = -1;  /* T_cellReselectionInfoCommon */
static int hf_lte_rrc_q_Hyst = -1;                /* T_q_Hyst */
static int hf_lte_rrc_speedStateReselectionPars = -1;  /* T_speedStateReselectionPars */
static int hf_lte_rrc_mobilityStateParameters = -1;  /* MobilityStateParameters */
static int hf_lte_rrc_q_HystSF = -1;              /* T_q_HystSF */
static int hf_lte_rrc_sf_Medium = -1;             /* T_sf_Medium */
static int hf_lte_rrc_sf_High = -1;               /* T_sf_High */
static int hf_lte_rrc_cellReselectionServingFreqInfo = -1;  /* T_cellReselectionServingFreqInfo */
static int hf_lte_rrc_s_NonIntraSearch = -1;      /* ReselectionThreshold */
static int hf_lte_rrc_threshServingLow = -1;      /* ReselectionThreshold */
static int hf_lte_rrc_intraFreqCellReselectionInfo = -1;  /* T_intraFreqCellReselectionInfo */
static int hf_lte_rrc_s_IntraSearch = -1;         /* ReselectionThreshold */
static int hf_lte_rrc_allowedMeasBandwidth = -1;  /* AllowedMeasBandwidth */
static int hf_lte_rrc_presenceAntennaPort1 = -1;  /* PresenceAntennaPort1 */
static int hf_lte_rrc_neighCellConfig = -1;       /* NeighCellConfig */
static int hf_lte_rrc_t_ReselectionEUTRA = -1;    /* T_Reselection */
static int hf_lte_rrc_t_ReselectionEUTRA_SF = -1;  /* SpeedStateScaleFactors */
static int hf_lte_rrc_s_IntraSearch_v920 = -1;    /* T_s_IntraSearch_v920 */
static int hf_lte_rrc_s_IntraSearchP_r9 = -1;     /* ReselectionThreshold */
static int hf_lte_rrc_s_IntraSearchQ_r9 = -1;     /* ReselectionThresholdQ_r9 */
static int hf_lte_rrc_s_NonIntraSearch_v920 = -1;  /* T_s_NonIntraSearch_v920 */
static int hf_lte_rrc_s_NonIntraSearchP_r9 = -1;  /* ReselectionThreshold */
static int hf_lte_rrc_s_NonIntraSearchQ_r9 = -1;  /* ReselectionThresholdQ_r9 */
static int hf_lte_rrc_threshServingLowQ_r9 = -1;  /* ReselectionThresholdQ_r9 */
static int hf_lte_rrc_intraFreqNeighCellList = -1;  /* IntraFreqNeighCellList */
static int hf_lte_rrc_intraFreqBlackCellList = -1;  /* IntraFreqBlackCellList */
static int hf_lte_rrc_csg_PhysCellIdRange = -1;   /* PhysCellIdRange */
static int hf_lte_rrc_IntraFreqNeighCellList_item = -1;  /* IntraFreqNeighCellInfo */
static int hf_lte_rrc_q_OffsetCell = -1;          /* Q_OffsetRange */
static int hf_lte_rrc_IntraFreqBlackCellList_item = -1;  /* PhysCellIdRange */
static int hf_lte_rrc_interFreqCarrierFreqList = -1;  /* InterFreqCarrierFreqList */
static int hf_lte_rrc_InterFreqCarrierFreqList_item = -1;  /* InterFreqCarrierFreqInfo */
static int hf_lte_rrc_dl_CarrierFreq = -1;        /* ARFCN_ValueEUTRA */
static int hf_lte_rrc_threshX_High = -1;          /* ReselectionThreshold */
static int hf_lte_rrc_threshX_Low = -1;           /* ReselectionThreshold */
static int hf_lte_rrc_q_OffsetFreq = -1;          /* Q_OffsetRange */
static int hf_lte_rrc_interFreqNeighCellList = -1;  /* InterFreqNeighCellList */
static int hf_lte_rrc_interFreqBlackCellList = -1;  /* InterFreqBlackCellList */
static int hf_lte_rrc_threshX_Q_r9 = -1;          /* T_threshX_Q_r9 */
static int hf_lte_rrc_threshX_HighQ_r9 = -1;      /* ReselectionThresholdQ_r9 */
static int hf_lte_rrc_threshX_LowQ_r9 = -1;       /* ReselectionThresholdQ_r9 */
static int hf_lte_rrc_InterFreqNeighCellList_item = -1;  /* InterFreqNeighCellInfo */
static int hf_lte_rrc_InterFreqBlackCellList_item = -1;  /* PhysCellIdRange */
static int hf_lte_rrc_carrierFreqListUTRA_FDD = -1;  /* CarrierFreqListUTRA_FDD */
static int hf_lte_rrc_carrierFreqListUTRA_TDD = -1;  /* CarrierFreqListUTRA_TDD */
static int hf_lte_rrc_t_ReselectionUTRA = -1;     /* T_Reselection */
static int hf_lte_rrc_t_ReselectionUTRA_SF = -1;  /* SpeedStateScaleFactors */
static int hf_lte_rrc_CarrierFreqListUTRA_FDD_item = -1;  /* CarrierFreqUTRA_FDD */
static int hf_lte_rrc_q_RxLevMin_01 = -1;         /* INTEGER_M60_M13 */
static int hf_lte_rrc_p_MaxUTRA = -1;             /* INTEGER_M50_33 */
static int hf_lte_rrc_q_QualMin = -1;             /* INTEGER_M24_0 */
static int hf_lte_rrc_threshX_Q_r9_01 = -1;       /* T_threshX_Q_r9_01 */
static int hf_lte_rrc_CarrierFreqListUTRA_TDD_item = -1;  /* CarrierFreqUTRA_TDD */
static int hf_lte_rrc_t_ReselectionGERAN = -1;    /* T_Reselection */
static int hf_lte_rrc_t_ReselectionGERAN_SF = -1;  /* SpeedStateScaleFactors */
static int hf_lte_rrc_carrierFreqsInfoList = -1;  /* CarrierFreqsInfoListGERAN */
static int hf_lte_rrc_CarrierFreqsInfoListGERAN_item = -1;  /* CarrierFreqsInfoGERAN */
static int hf_lte_rrc_commonInfo = -1;            /* T_commonInfo */
static int hf_lte_rrc_ncc_Permitted = -1;         /* BIT_STRING_SIZE_8 */
static int hf_lte_rrc_q_RxLevMin_02 = -1;         /* INTEGER_0_45 */
static int hf_lte_rrc_p_MaxGERAN = -1;            /* INTEGER_0_39 */
static int hf_lte_rrc_systemTimeInfo = -1;        /* SystemTimeInfoCDMA2000 */
static int hf_lte_rrc_searchWindowSize = -1;      /* INTEGER_0_15 */
static int hf_lte_rrc_parametersHRPD = -1;        /* T_parametersHRPD */
static int hf_lte_rrc_preRegistrationInfoHRPD = -1;  /* PreRegistrationInfoHRPD */
static int hf_lte_rrc_cellReselectionParametersHRPD = -1;  /* CellReselectionParametersCDMA2000 */
static int hf_lte_rrc_parameters1XRTT = -1;       /* T_parameters1XRTT */
static int hf_lte_rrc_csfb_RegistrationParam1XRTT = -1;  /* CSFB_RegistrationParam1XRTT */
static int hf_lte_rrc_longCodeState1XRTT = -1;    /* BIT_STRING_SIZE_42 */
static int hf_lte_rrc_cellReselectionParameters1XRTT = -1;  /* CellReselectionParametersCDMA2000 */
static int hf_lte_rrc_csfb_SupportForDualRxUEs_r9 = -1;  /* BOOLEAN */
static int hf_lte_rrc_cellReselectionParametersHRPD_v920 = -1;  /* CellReselectionParametersCDMA2000_v920 */
static int hf_lte_rrc_cellReselectionParameters1XRTT_v920 = -1;  /* CellReselectionParametersCDMA2000_v920 */
static int hf_lte_rrc_csfb_RegistrationParam1XRTT_v920 = -1;  /* CSFB_RegistrationParam1XRTT_v920 */
static int hf_lte_rrc_ac_BarringConfig1XRTT_r9 = -1;  /* AC_BarringConfig1XRTT_r9 */
static int hf_lte_rrc_bandClassList = -1;         /* BandClassListCDMA2000 */
static int hf_lte_rrc_neighCellList = -1;         /* NeighCellListCDMA2000 */
static int hf_lte_rrc_t_ReselectionCDMA2000 = -1;  /* T_Reselection */
static int hf_lte_rrc_t_ReselectionCDMA2000_SF = -1;  /* SpeedStateScaleFactors */
static int hf_lte_rrc_neighCellList_v920 = -1;    /* NeighCellListCDMA2000_v920 */
static int hf_lte_rrc_NeighCellListCDMA2000_item = -1;  /* NeighCellCDMA2000 */
static int hf_lte_rrc_neighCellsPerFreqList = -1;  /* NeighCellsPerBandclassListCDMA2000 */
static int hf_lte_rrc_NeighCellsPerBandclassListCDMA2000_item = -1;  /* NeighCellsPerBandclassCDMA2000 */
static int hf_lte_rrc_arfcn = -1;                 /* ARFCN_ValueCDMA2000 */
static int hf_lte_rrc_physCellIdList = -1;        /* PhysCellIdListCDMA2000 */
static int hf_lte_rrc_NeighCellListCDMA2000_v920_item = -1;  /* NeighCellCDMA2000_v920 */
static int hf_lte_rrc_neighCellsPerFreqList_v920 = -1;  /* NeighCellsPerBandclassListCDMA2000_v920 */
static int hf_lte_rrc_NeighCellsPerBandclassListCDMA2000_v920_item = -1;  /* NeighCellsPerBandclassCDMA2000_v920 */
static int hf_lte_rrc_physCellIdList_v920 = -1;   /* PhysCellIdListCDMA2000_v920 */
static int hf_lte_rrc_PhysCellIdListCDMA2000_item = -1;  /* PhysCellIdCDMA2000 */
static int hf_lte_rrc_PhysCellIdListCDMA2000_v920_item = -1;  /* PhysCellIdCDMA2000 */
static int hf_lte_rrc_BandClassListCDMA2000_item = -1;  /* BandClassInfoCDMA2000 */
static int hf_lte_rrc_threshX_High_01 = -1;       /* INTEGER_0_63 */
static int hf_lte_rrc_threshX_Low_01 = -1;        /* INTEGER_0_63 */
static int hf_lte_rrc_ac_Barring0to9_r9 = -1;     /* INTEGER_0_63 */
static int hf_lte_rrc_ac_Barring10_r9 = -1;       /* INTEGER_0_7 */
static int hf_lte_rrc_ac_Barring11_r9 = -1;       /* INTEGER_0_7 */
static int hf_lte_rrc_ac_Barring12_r9 = -1;       /* INTEGER_0_7 */
static int hf_lte_rrc_ac_Barring13_r9 = -1;       /* INTEGER_0_7 */
static int hf_lte_rrc_ac_Barring14_r9 = -1;       /* INTEGER_0_7 */
static int hf_lte_rrc_ac_Barring15_r9 = -1;       /* INTEGER_0_7 */
static int hf_lte_rrc_ac_BarringMsg_r9 = -1;      /* INTEGER_0_7 */
static int hf_lte_rrc_ac_BarringReg_r9 = -1;      /* INTEGER_0_7 */
static int hf_lte_rrc_ac_BarringEmg_r9 = -1;      /* INTEGER_0_7 */
static int hf_lte_rrc_hnb_Name = -1;              /* OCTET_STRING_SIZE_1_48 */
static int hf_lte_rrc_messageIdentifier = -1;     /* BIT_STRING_SIZE_16 */
static int hf_lte_rrc_serialNumber = -1;          /* BIT_STRING_SIZE_16 */
static int hf_lte_rrc_warningType = -1;           /* OCTET_STRING_SIZE_2 */
static int hf_lte_rrc_warningSecurityInfo = -1;   /* OCTET_STRING_SIZE_50 */
static int hf_lte_rrc_warningMessageSegmentType = -1;  /* T_warningMessageSegmentType */
static int hf_lte_rrc_warningMessageSegmentNumber = -1;  /* INTEGER_0_63 */
static int hf_lte_rrc_warningMessageSegment = -1;  /* OCTET_STRING */
static int hf_lte_rrc_dataCodingScheme = -1;      /* OCTET_STRING_SIZE_1 */
static int hf_lte_rrc_messageIdentifier_r9 = -1;  /* BIT_STRING_SIZE_16 */
static int hf_lte_rrc_serialNumber_r9 = -1;       /* BIT_STRING_SIZE_16 */
static int hf_lte_rrc_warningMessageSegmentType_r9 = -1;  /* T_warningMessageSegmentType_r9 */
static int hf_lte_rrc_warningMessageSegmentNumber_r9 = -1;  /* INTEGER_0_63 */
static int hf_lte_rrc_warningMessageSegment_r9 = -1;  /* OCTET_STRING */
static int hf_lte_rrc_dataCodingScheme_r9 = -1;   /* OCTET_STRING_SIZE_1 */
static int hf_lte_rrc_lateR9NonCriticalExtension = -1;  /* OCTET_STRING */
static int hf_lte_rrc_mbsfn_AreaInfoList_r9 = -1;  /* MBSFN_AreaInfoList_r9 */
static int hf_lte_rrc_notificationConfig_r9 = -1;  /* MBMS_NotificationConfig_r9 */
static int hf_lte_rrc_antennaPortsCount = -1;     /* T_antennaPortsCount */
static int hf_lte_rrc_transmissionMode = -1;      /* T_transmissionMode */
static int hf_lte_rrc_codebookSubsetRestriction = -1;  /* T_codebookSubsetRestriction */
static int hf_lte_rrc_n2TxAntenna_tm3 = -1;       /* BIT_STRING_SIZE_2 */
static int hf_lte_rrc_n4TxAntenna_tm3 = -1;       /* BIT_STRING_SIZE_4 */
static int hf_lte_rrc_n2TxAntenna_tm4 = -1;       /* BIT_STRING_SIZE_6 */
static int hf_lte_rrc_n4TxAntenna_tm4 = -1;       /* BIT_STRING_SIZE_64 */
static int hf_lte_rrc_n2TxAntenna_tm5 = -1;       /* BIT_STRING_SIZE_4 */
static int hf_lte_rrc_n4TxAntenna_tm5 = -1;       /* BIT_STRING_SIZE_16 */
static int hf_lte_rrc_n2TxAntenna_tm6 = -1;       /* BIT_STRING_SIZE_4 */
static int hf_lte_rrc_n4TxAntenna_tm6 = -1;       /* BIT_STRING_SIZE_16 */
static int hf_lte_rrc_ue_TransmitAntennaSelection = -1;  /* T_ue_TransmitAntennaSelection */
static int hf_lte_rrc_release = -1;               /* NULL */
static int hf_lte_rrc_setup = -1;                 /* T_setup */
static int hf_lte_rrc_codebookSubsetRestriction_v920 = -1;  /* T_codebookSubsetRestriction_v920 */
static int hf_lte_rrc_n2TxAntenna_tm8_r9 = -1;    /* BIT_STRING_SIZE_6 */
static int hf_lte_rrc_n4TxAntenna_tm8_r9 = -1;    /* BIT_STRING_SIZE_32 */
static int hf_lte_rrc_cqi_ReportModeAperiodic = -1;  /* T_cqi_ReportModeAperiodic */
static int hf_lte_rrc_nomPDSCH_RS_EPRE_Offset = -1;  /* INTEGER_M1_6 */
static int hf_lte_rrc_cqi_ReportPeriodic = -1;    /* CQI_ReportPeriodic */
static int hf_lte_rrc_cqi_Mask_r9 = -1;           /* T_cqi_Mask_r9 */
static int hf_lte_rrc_pmi_RI_Report_r9 = -1;      /* T_pmi_RI_Report_r9 */
static int hf_lte_rrc_setup_01 = -1;              /* T_setup_01 */
static int hf_lte_rrc_cqi_PUCCH_ResourceIndex = -1;  /* INTEGER_0_1185 */
static int hf_lte_rrc_cqi_pmi_ConfigIndex = -1;   /* INTEGER_0_1023 */
static int hf_lte_rrc_cqi_FormatIndicatorPeriodic = -1;  /* T_cqi_FormatIndicatorPeriodic */
static int hf_lte_rrc_widebandCQI = -1;           /* NULL */
static int hf_lte_rrc_subbandCQI = -1;            /* T_subbandCQI */
static int hf_lte_rrc_k = -1;                     /* INTEGER_1_4 */
static int hf_lte_rrc_ri_ConfigIndex = -1;        /* INTEGER_0_1023 */
static int hf_lte_rrc_simultaneousAckNackAndCQI = -1;  /* BOOLEAN */
static int hf_lte_rrc_ul_SpecificParameters = -1;  /* T_ul_SpecificParameters */
static int hf_lte_rrc_priority = -1;              /* INTEGER_1_16 */
static int hf_lte_rrc_prioritisedBitRate = -1;    /* T_prioritisedBitRate */
static int hf_lte_rrc_bucketSizeDuration = -1;    /* T_bucketSizeDuration */
static int hf_lte_rrc_logicalChannelGroup = -1;   /* INTEGER_0_3 */
static int hf_lte_rrc_logicalChannelSR_Mask_r9 = -1;  /* T_logicalChannelSR_Mask_r9 */
static int hf_lte_rrc_ul_SCH_Config = -1;         /* T_ul_SCH_Config */
static int hf_lte_rrc_maxHARQ_Tx = -1;            /* T_maxHARQ_Tx */
static int hf_lte_rrc_periodicBSR_Timer = -1;     /* T_periodicBSR_Timer */
static int hf_lte_rrc_retxBSR_Timer = -1;         /* T_retxBSR_Timer */
static int hf_lte_rrc_ttiBundling = -1;           /* BOOLEAN */
static int hf_lte_rrc_drx_Config = -1;            /* DRX_Config */
static int hf_lte_rrc_timeAlignmentTimerDedicated = -1;  /* TimeAlignmentTimer */
static int hf_lte_rrc_phr_Config = -1;            /* T_phr_Config */
static int hf_lte_rrc_setup_02 = -1;              /* T_setup_02 */
static int hf_lte_rrc_periodicPHR_Timer = -1;     /* T_periodicPHR_Timer */
static int hf_lte_rrc_prohibitPHR_Timer = -1;     /* T_prohibitPHR_Timer */
static int hf_lte_rrc_dl_PathlossChange = -1;     /* T_dl_PathlossChange */
static int hf_lte_rrc_sr_ProhibitTimer_r9 = -1;   /* INTEGER_0_7 */
static int hf_lte_rrc_setup_03 = -1;              /* T_setup_03 */
static int hf_lte_rrc_onDurationTimer = -1;       /* T_onDurationTimer */
static int hf_lte_rrc_drx_InactivityTimer = -1;   /* T_drx_InactivityTimer */
static int hf_lte_rrc_drx_RetransmissionTimer = -1;  /* T_drx_RetransmissionTimer */
static int hf_lte_rrc_longDRX_CycleStartOffset = -1;  /* T_longDRX_CycleStartOffset */
static int hf_lte_rrc_sf10 = -1;                  /* INTEGER_0_9 */
static int hf_lte_rrc_sf20 = -1;                  /* INTEGER_0_19 */
static int hf_lte_rrc_sf32 = -1;                  /* INTEGER_0_31 */
static int hf_lte_rrc_sf40 = -1;                  /* INTEGER_0_39 */
static int hf_lte_rrc_sf64 = -1;                  /* INTEGER_0_63 */
static int hf_lte_rrc_sf80 = -1;                  /* INTEGER_0_79 */
static int hf_lte_rrc_sf128 = -1;                 /* INTEGER_0_127 */
static int hf_lte_rrc_sf160 = -1;                 /* INTEGER_0_159 */
static int hf_lte_rrc_sf256 = -1;                 /* INTEGER_0_255 */
static int hf_lte_rrc_sf320 = -1;                 /* INTEGER_0_319 */
static int hf_lte_rrc_sf512 = -1;                 /* INTEGER_0_511 */
static int hf_lte_rrc_sf640 = -1;                 /* INTEGER_0_639 */
static int hf_lte_rrc_sf1024 = -1;                /* INTEGER_0_1023 */
static int hf_lte_rrc_sf1280 = -1;                /* INTEGER_0_1279 */
static int hf_lte_rrc_sf2048 = -1;                /* INTEGER_0_2047 */
static int hf_lte_rrc_sf2560 = -1;                /* INTEGER_0_2559 */
static int hf_lte_rrc_shortDRX = -1;              /* T_shortDRX */
static int hf_lte_rrc_shortDRX_Cycle = -1;        /* T_shortDRX_Cycle */
static int hf_lte_rrc_drxShortCycleTimer = -1;    /* INTEGER_1_16 */
static int hf_lte_rrc_discardTimer = -1;          /* T_discardTimer */
static int hf_lte_rrc_rlc_AM = -1;                /* T_rlc_AM */
static int hf_lte_rrc_statusReportRequired = -1;  /* BOOLEAN */
static int hf_lte_rrc_rlc_UM = -1;                /* T_rlc_UM */
static int hf_lte_rrc_pdcp_SN_Size = -1;          /* T_pdcp_SN_Size */
static int hf_lte_rrc_headerCompression = -1;     /* T_headerCompression */
static int hf_lte_rrc_notUsed = -1;               /* NULL */
static int hf_lte_rrc_rohc = -1;                  /* T_rohc */
static int hf_lte_rrc_maxCID = -1;                /* INTEGER_1_16383 */
static int hf_lte_rrc_profiles = -1;              /* T_profiles */
static int hf_lte_rrc_profile0x0001 = -1;         /* BOOLEAN */
static int hf_lte_rrc_profile0x0002 = -1;         /* BOOLEAN */
static int hf_lte_rrc_profile0x0003 = -1;         /* BOOLEAN */
static int hf_lte_rrc_profile0x0004 = -1;         /* BOOLEAN */
static int hf_lte_rrc_profile0x0006 = -1;         /* BOOLEAN */
static int hf_lte_rrc_profile0x0101 = -1;         /* BOOLEAN */
static int hf_lte_rrc_profile0x0102 = -1;         /* BOOLEAN */
static int hf_lte_rrc_profile0x0103 = -1;         /* BOOLEAN */
static int hf_lte_rrc_profile0x0104 = -1;         /* BOOLEAN */
static int hf_lte_rrc_referenceSignalPower = -1;  /* INTEGER_M60_50 */
static int hf_lte_rrc_p_b = -1;                   /* INTEGER_0_3 */
static int hf_lte_rrc_p_a = -1;                   /* T_p_a */
static int hf_lte_rrc_phich_Duration = -1;        /* T_phich_Duration */
static int hf_lte_rrc_phich_Resource = -1;        /* T_phich_Resource */
static int hf_lte_rrc_pdsch_ConfigDedicated = -1;  /* PDSCH_ConfigDedicated */
static int hf_lte_rrc_pucch_ConfigDedicated = -1;  /* PUCCH_ConfigDedicated */
static int hf_lte_rrc_pusch_ConfigDedicated = -1;  /* PUSCH_ConfigDedicated */
static int hf_lte_rrc_uplinkPowerControlDedicated = -1;  /* UplinkPowerControlDedicated */
static int hf_lte_rrc_tpc_PDCCH_ConfigPUCCH = -1;  /* TPC_PDCCH_Config */
static int hf_lte_rrc_tpc_PDCCH_ConfigPUSCH = -1;  /* TPC_PDCCH_Config */
static int hf_lte_rrc_cqi_ReportConfig = -1;      /* CQI_ReportConfig */
static int hf_lte_rrc_soundingRS_UL_ConfigDedicated = -1;  /* SoundingRS_UL_ConfigDedicated */
static int hf_lte_rrc_antennaInfo = -1;           /* T_antennaInfo */
static int hf_lte_rrc_explicitValue = -1;         /* AntennaInfoDedicated */
static int hf_lte_rrc_defaultValue = -1;          /* NULL */
static int hf_lte_rrc_schedulingRequestConfig = -1;  /* SchedulingRequestConfig */
static int hf_lte_rrc_cqi_ReportConfig_v920 = -1;  /* CQI_ReportConfig_v920 */
static int hf_lte_rrc_antennaInfo_v920 = -1;      /* AntennaInfoDedicated_v920 */
static int hf_lte_rrc_rootSequenceIndex = -1;     /* INTEGER_0_837 */
static int hf_lte_rrc_prach_ConfigInfo = -1;      /* PRACH_ConfigInfo */
static int hf_lte_rrc_prach_ConfigIndex = -1;     /* INTEGER_0_63 */
static int hf_lte_rrc_highSpeedFlag = -1;         /* BOOLEAN */
static int hf_lte_rrc_zeroCorrelationZoneConfig = -1;  /* INTEGER_0_15 */
static int hf_lte_rrc_prach_FreqOffset = -1;      /* INTEGER_0_94 */
static int hf_lte_rrc_deltaPUCCH_Shift = -1;      /* T_deltaPUCCH_Shift */
static int hf_lte_rrc_nRB_CQI = -1;               /* INTEGER_0_98 */
static int hf_lte_rrc_nCS_AN = -1;                /* INTEGER_0_7 */
static int hf_lte_rrc_n1PUCCH_AN = -1;            /* INTEGER_0_2047 */
static int hf_lte_rrc_ackNackRepetition = -1;     /* T_ackNackRepetition */
static int hf_lte_rrc_setup_04 = -1;              /* T_setup_04 */
static int hf_lte_rrc_repetitionFactor = -1;      /* T_repetitionFactor */
static int hf_lte_rrc_n1PUCCH_AN_Rep = -1;        /* INTEGER_0_2047 */
static int hf_lte_rrc_tdd_AckNackFeedbackMode = -1;  /* T_tdd_AckNackFeedbackMode */
static int hf_lte_rrc_pusch_ConfigBasic = -1;     /* T_pusch_ConfigBasic */
static int hf_lte_rrc_n_SB = -1;                  /* INTEGER_1_4 */
static int hf_lte_rrc_hoppingMode = -1;           /* T_hoppingMode */
static int hf_lte_rrc_pusch_HoppingOffset = -1;   /* INTEGER_0_98 */
static int hf_lte_rrc_enable64QAM = -1;           /* BOOLEAN */
static int hf_lte_rrc_ul_ReferenceSignalsPUSCH = -1;  /* UL_ReferenceSignalsPUSCH */
static int hf_lte_rrc_betaOffset_ACK_Index = -1;  /* INTEGER_0_15 */
static int hf_lte_rrc_betaOffset_RI_Index = -1;   /* INTEGER_0_15 */
static int hf_lte_rrc_betaOffset_CQI_Index = -1;  /* INTEGER_0_15 */
static int hf_lte_rrc_groupHoppingEnabled = -1;   /* BOOLEAN */
static int hf_lte_rrc_groupAssignmentPUSCH = -1;  /* INTEGER_0_29 */
static int hf_lte_rrc_sequenceHoppingEnabled = -1;  /* BOOLEAN */
static int hf_lte_rrc_cyclicShift = -1;           /* INTEGER_0_7 */
static int hf_lte_rrc_preambleInfo = -1;          /* T_preambleInfo */
static int hf_lte_rrc_numberOfRA_Preambles = -1;  /* T_numberOfRA_Preambles */
static int hf_lte_rrc_preamblesGroupAConfig = -1;  /* T_preamblesGroupAConfig */
static int hf_lte_rrc_sizeOfRA_PreamblesGroupA = -1;  /* T_sizeOfRA_PreamblesGroupA */
static int hf_lte_rrc_messageSizeGroupA = -1;     /* T_messageSizeGroupA */
static int hf_lte_rrc_messagePowerOffsetGroupB = -1;  /* T_messagePowerOffsetGroupB */
static int hf_lte_rrc_powerRampingParameters = -1;  /* T_powerRampingParameters */
static int hf_lte_rrc_powerRampingStep = -1;      /* T_powerRampingStep */
static int hf_lte_rrc_preambleInitialReceivedTargetPower = -1;  /* T_preambleInitialReceivedTargetPower */
static int hf_lte_rrc_ra_SupervisionInfo = -1;    /* T_ra_SupervisionInfo */
static int hf_lte_rrc_preambleTransMax = -1;      /* T_preambleTransMax */
static int hf_lte_rrc_ra_ResponseWindowSize = -1;  /* T_ra_ResponseWindowSize */
static int hf_lte_rrc_mac_ContentionResolutionTimer = -1;  /* T_mac_ContentionResolutionTimer */
static int hf_lte_rrc_maxHARQ_Msg3Tx = -1;        /* INTEGER_1_8 */
static int hf_lte_rrc_ra_PreambleIndex = -1;      /* INTEGER_0_63 */
static int hf_lte_rrc_ra_PRACH_MaskIndex = -1;    /* INTEGER_0_15 */
static int hf_lte_rrc_rach_ConfigCommon = -1;     /* RACH_ConfigCommon */
static int hf_lte_rrc_bcch_Config = -1;           /* BCCH_Config */
static int hf_lte_rrc_pcch_Config = -1;           /* PCCH_Config */
static int hf_lte_rrc_prach_Config = -1;          /* PRACH_ConfigSIB */
static int hf_lte_rrc_pdsch_ConfigCommon = -1;    /* PDSCH_ConfigCommon */
static int hf_lte_rrc_pusch_ConfigCommon = -1;    /* PUSCH_ConfigCommon */
static int hf_lte_rrc_pucch_ConfigCommon = -1;    /* PUCCH_ConfigCommon */
static int hf_lte_rrc_soundingRS_UL_ConfigCommon = -1;  /* SoundingRS_UL_ConfigCommon */
static int hf_lte_rrc_uplinkPowerControlCommon = -1;  /* UplinkPowerControlCommon */
static int hf_lte_rrc_ul_CyclicPrefixLength = -1;  /* UL_CyclicPrefixLength */
static int hf_lte_rrc_prach_Config_01 = -1;       /* PRACH_Config */
static int hf_lte_rrc_antennaInfoCommon = -1;     /* AntennaInfoCommon */
static int hf_lte_rrc_modificationPeriodCoeff = -1;  /* T_modificationPeriodCoeff */
static int hf_lte_rrc_defaultPagingCycle = -1;    /* T_defaultPagingCycle */
static int hf_lte_rrc_nB = -1;                    /* T_nB */
static int hf_lte_rrc_srb_ToAddModList = -1;      /* SRB_ToAddModList */
static int hf_lte_rrc_drb_ToAddModList = -1;      /* DRB_ToAddModList */
static int hf_lte_rrc_drb_ToReleaseList = -1;     /* DRB_ToReleaseList */
static int hf_lte_rrc_mac_MainConfig = -1;        /* T_mac_MainConfig */
static int hf_lte_rrc_explicitValue_01 = -1;      /* MAC_MainConfig */
static int hf_lte_rrc_sps_Config = -1;            /* SPS_Config */
static int hf_lte_rrc_physicalConfigDedicated = -1;  /* PhysicalConfigDedicated */
static int hf_lte_rrc_rlf_TimersAndConstants_r9 = -1;  /* RLF_TimersAndConstants_r9 */
static int hf_lte_rrc_SRB_ToAddModList_item = -1;  /* SRB_ToAddMod */
static int hf_lte_rrc_srb_Identity = -1;          /* INTEGER_1_2 */
static int hf_lte_rrc_rlc_Config = -1;            /* T_rlc_Config */
static int hf_lte_rrc_explicitValue_02 = -1;      /* RLC_Config */
static int hf_lte_rrc_logicalChannelConfig = -1;  /* T_logicalChannelConfig */
static int hf_lte_rrc_explicitValue_03 = -1;      /* LogicalChannelConfig */
static int hf_lte_rrc_DRB_ToAddModList_item = -1;  /* DRB_ToAddMod */
static int hf_lte_rrc_eps_BearerIdentity = -1;    /* INTEGER_0_15 */
static int hf_lte_rrc_pdcp_Config = -1;           /* PDCP_Config */
static int hf_lte_rrc_rlc_Config_01 = -1;         /* RLC_Config */
static int hf_lte_rrc_logicalChannelIdentity = -1;  /* INTEGER_3_10 */
static int hf_lte_rrc_logicalChannelConfig_01 = -1;  /* LogicalChannelConfig */
static int hf_lte_rrc_DRB_ToReleaseList_item = -1;  /* DRB_Identity */
static int hf_lte_rrc_am = -1;                    /* T_am */
static int hf_lte_rrc_ul_AM_RLC = -1;             /* UL_AM_RLC */
static int hf_lte_rrc_dl_AM_RLC = -1;             /* DL_AM_RLC */
static int hf_lte_rrc_um_Bi_Directional = -1;     /* T_um_Bi_Directional */
static int hf_lte_rrc_ul_UM_RLC = -1;             /* UL_UM_RLC */
static int hf_lte_rrc_dl_UM_RLC = -1;             /* DL_UM_RLC */
static int hf_lte_rrc_um_Uni_Directional_UL = -1;  /* T_um_Uni_Directional_UL */
static int hf_lte_rrc_um_Uni_Directional_DL = -1;  /* T_um_Uni_Directional_DL */
static int hf_lte_rrc_t_PollRetransmit = -1;      /* T_PollRetransmit */
static int hf_lte_rrc_pollPDU = -1;               /* PollPDU */
static int hf_lte_rrc_pollByte = -1;              /* PollByte */
static int hf_lte_rrc_maxRetxThreshold = -1;      /* T_maxRetxThreshold */
static int hf_lte_rrc_t_Reordering = -1;          /* T_Reordering */
static int hf_lte_rrc_t_StatusProhibit = -1;      /* T_StatusProhibit */
static int hf_lte_rrc_sn_FieldLength = -1;        /* SN_FieldLength */
static int hf_lte_rrc_setup_05 = -1;              /* T_setup_05 */
static int hf_lte_rrc_t301_r9 = -1;               /* T_t301_r9 */
static int hf_lte_rrc_t310_r9 = -1;               /* T_t310_r9 */
static int hf_lte_rrc_n310_r9 = -1;               /* T_n310_r9 */
static int hf_lte_rrc_t311_r9 = -1;               /* T_t311_r9 */
static int hf_lte_rrc_n311_r9 = -1;               /* T_n311_r9 */
static int hf_lte_rrc_setup_06 = -1;              /* T_setup_06 */
static int hf_lte_rrc_sr_PUCCH_ResourceIndex = -1;  /* INTEGER_0_2047 */
static int hf_lte_rrc_sr_ConfigIndex = -1;        /* INTEGER_0_157 */
static int hf_lte_rrc_dsr_TransMax = -1;          /* T_dsr_TransMax */
static int hf_lte_rrc_setup_07 = -1;              /* T_setup_07 */
static int hf_lte_rrc_srs_BandwidthConfig = -1;   /* T_srs_BandwidthConfig */
static int hf_lte_rrc_srs_SubframeConfig = -1;    /* T_srs_SubframeConfig */
static int hf_lte_rrc_ackNackSRS_SimultaneousTransmission = -1;  /* BOOLEAN */
static int hf_lte_rrc_srs_MaxUpPts = -1;          /* T_srs_MaxUpPts */
static int hf_lte_rrc_setup_08 = -1;              /* T_setup_08 */
static int hf_lte_rrc_srs_Bandwidth = -1;         /* T_srs_Bandwidth */
static int hf_lte_rrc_srs_HoppingBandwidth = -1;  /* T_srs_HoppingBandwidth */
static int hf_lte_rrc_freqDomainPosition = -1;    /* INTEGER_0_23 */
static int hf_lte_rrc_duration = -1;              /* BOOLEAN */
static int hf_lte_rrc_srs_ConfigIndex = -1;       /* INTEGER_0_1023 */
static int hf_lte_rrc_transmissionComb = -1;      /* INTEGER_0_1 */
static int hf_lte_rrc_cyclicShift_01 = -1;        /* T_cyclicShift */
static int hf_lte_rrc_semiPersistSchedC_RNTI = -1;  /* C_RNTI */
static int hf_lte_rrc_sps_ConfigDL = -1;          /* SPS_ConfigDL */
static int hf_lte_rrc_sps_ConfigUL = -1;          /* SPS_ConfigUL */
static int hf_lte_rrc_setup_09 = -1;              /* T_setup_09 */
static int hf_lte_rrc_semiPersistSchedIntervalDL = -1;  /* T_semiPersistSchedIntervalDL */
static int hf_lte_rrc_numberOfConfSPS_Processes = -1;  /* INTEGER_1_8 */
static int hf_lte_rrc_n1_PUCCH_AN_PersistentList = -1;  /* N1_PUCCH_AN_PersistentList */
static int hf_lte_rrc_setup_10 = -1;              /* T_setup_10 */
static int hf_lte_rrc_semiPersistSchedIntervalUL = -1;  /* T_semiPersistSchedIntervalUL */
static int hf_lte_rrc_implicitReleaseAfter = -1;  /* T_implicitReleaseAfter */
static int hf_lte_rrc_p0_Persistent = -1;         /* T_p0_Persistent */
static int hf_lte_rrc_p0_NominalPUSCH_Persistent = -1;  /* INTEGER_M126_24 */
static int hf_lte_rrc_p0_UE_PUSCH_Persistent = -1;  /* INTEGER_M8_7 */
static int hf_lte_rrc_twoIntervalsConfig = -1;    /* T_twoIntervalsConfig */
static int hf_lte_rrc_N1_PUCCH_AN_PersistentList_item = -1;  /* INTEGER_0_2047 */
static int hf_lte_rrc_subframeAssignment = -1;    /* T_subframeAssignment */
static int hf_lte_rrc_specialSubframePatterns = -1;  /* T_specialSubframePatterns */
static int hf_lte_rrc_setup_11 = -1;              /* T_setup_11 */
static int hf_lte_rrc_tpc_RNTI = -1;              /* BIT_STRING_SIZE_16 */
static int hf_lte_rrc_tpc_Index = -1;             /* TPC_Index */
static int hf_lte_rrc_indexOfFormat3 = -1;        /* INTEGER_1_15 */
static int hf_lte_rrc_indexOfFormat3A = -1;       /* INTEGER_1_31 */
static int hf_lte_rrc_p0_NominalPUSCH = -1;       /* INTEGER_M126_24 */
static int hf_lte_rrc_alpha = -1;                 /* T_alpha */
static int hf_lte_rrc_p0_NominalPUCCH = -1;       /* INTEGER_M127_M96 */
static int hf_lte_rrc_deltaFList_PUCCH = -1;      /* DeltaFList_PUCCH */
static int hf_lte_rrc_deltaPreambleMsg3 = -1;     /* INTEGER_M1_6 */
static int hf_lte_rrc_p0_UE_PUSCH = -1;           /* INTEGER_M8_7 */
static int hf_lte_rrc_deltaMCS_Enabled = -1;      /* T_deltaMCS_Enabled */
static int hf_lte_rrc_accumulationEnabled = -1;   /* BOOLEAN */
static int hf_lte_rrc_p0_UE_PUCCH = -1;           /* INTEGER_M8_7 */
static int hf_lte_rrc_pSRS_Offset = -1;           /* INTEGER_0_15 */
static int hf_lte_rrc_filterCoefficient = -1;     /* FilterCoefficient */
static int hf_lte_rrc_deltaF_PUCCH_Format1 = -1;  /* T_deltaF_PUCCH_Format1 */
static int hf_lte_rrc_deltaF_PUCCH_Format1b = -1;  /* T_deltaF_PUCCH_Format1b */
static int hf_lte_rrc_deltaF_PUCCH_Format2 = -1;  /* T_deltaF_PUCCH_Format2 */
static int hf_lte_rrc_deltaF_PUCCH_Format2a = -1;  /* T_deltaF_PUCCH_Format2a */
static int hf_lte_rrc_deltaF_PUCCH_Format2b = -1;  /* T_deltaF_PUCCH_Format2b */
static int hf_lte_rrc_cipheringAlgorithm = -1;    /* T_cipheringAlgorithm */
static int hf_lte_rrc_integrityProtAlgorithm = -1;  /* T_integrityProtAlgorithm */
static int hf_lte_rrc_arfcn_01 = -1;              /* ARFCN_ValueGERAN */
static int hf_lte_rrc_bandIndicator = -1;         /* BandIndicatorGERAN */
static int hf_lte_rrc_startingARFCN = -1;         /* ARFCN_ValueGERAN */
static int hf_lte_rrc_followingARFCNs = -1;       /* T_followingARFCNs */
static int hf_lte_rrc_explicitListOfARFCNs = -1;  /* ExplicitListOfARFCNs */
static int hf_lte_rrc_equallySpacedARFCNs = -1;   /* T_equallySpacedARFCNs */
static int hf_lte_rrc_arfcn_Spacing = -1;         /* INTEGER_1_8 */
static int hf_lte_rrc_numberOfFollowingARFCNs = -1;  /* INTEGER_0_31 */
static int hf_lte_rrc_variableBitMapOfARFCNs = -1;  /* OCTET_STRING_SIZE_1_16 */
static int hf_lte_rrc_ExplicitListOfARFCNs_item = -1;  /* ARFCN_ValueGERAN */
static int hf_lte_rrc_CellIndexList_item = -1;    /* CellIndex */
static int hf_lte_rrc_sid = -1;                   /* BIT_STRING_SIZE_15 */
static int hf_lte_rrc_nid = -1;                   /* BIT_STRING_SIZE_16 */
static int hf_lte_rrc_multipleSID = -1;           /* BOOLEAN */
static int hf_lte_rrc_multipleNID = -1;           /* BOOLEAN */
static int hf_lte_rrc_homeReg = -1;               /* BOOLEAN */
static int hf_lte_rrc_foreignSIDReg = -1;         /* BOOLEAN */
static int hf_lte_rrc_foreignNIDReg = -1;         /* BOOLEAN */
static int hf_lte_rrc_parameterReg = -1;          /* BOOLEAN */
static int hf_lte_rrc_powerUpReg = -1;            /* BOOLEAN */
static int hf_lte_rrc_registrationPeriod = -1;    /* BIT_STRING_SIZE_7 */
static int hf_lte_rrc_registrationZone = -1;      /* BIT_STRING_SIZE_12 */
static int hf_lte_rrc_totalZone = -1;             /* BIT_STRING_SIZE_3 */
static int hf_lte_rrc_zoneTimer = -1;             /* BIT_STRING_SIZE_3 */
static int hf_lte_rrc_powerDownReg_r9 = -1;       /* T_powerDownReg_r9 */
static int hf_lte_rrc_cellIdentity_01 = -1;       /* BIT_STRING_SIZE_28 */
static int hf_lte_rrc_locationAreaCode = -1;      /* BIT_STRING_SIZE_16 */
static int hf_lte_rrc_cellIdentity_02 = -1;       /* BIT_STRING_SIZE_16 */
static int hf_lte_rrc_cellGlobalId1XRTT = -1;     /* BIT_STRING_SIZE_47 */
static int hf_lte_rrc_cellGlobalIdHRPD = -1;      /* BIT_STRING_SIZE_128 */
static int hf_lte_rrc_targetPhysCellId = -1;      /* PhysCellId */
static int hf_lte_rrc_carrierFreq_04 = -1;        /* CarrierFreqEUTRA */
static int hf_lte_rrc_carrierBandwidth = -1;      /* CarrierBandwidthEUTRA */
static int hf_lte_rrc_t304_01 = -1;               /* T_t304_01 */
static int hf_lte_rrc_newUE_Identity = -1;        /* C_RNTI */
static int hf_lte_rrc_radioResourceConfigCommon_01 = -1;  /* RadioResourceConfigCommon */
static int hf_lte_rrc_rach_ConfigDedicated = -1;  /* RACH_ConfigDedicated */
static int hf_lte_rrc_dl_Bandwidth_01 = -1;       /* T_dl_Bandwidth_01 */
static int hf_lte_rrc_ul_Bandwidth_01 = -1;       /* T_ul_Bandwidth_01 */
static int hf_lte_rrc_t_Evaluation = -1;          /* T_t_Evaluation */
static int hf_lte_rrc_t_HystNormal = -1;          /* T_t_HystNormal */
static int hf_lte_rrc_n_CellChangeMedium = -1;    /* INTEGER_1_16 */
static int hf_lte_rrc_n_CellChangeHigh = -1;      /* INTEGER_1_16 */
static int hf_lte_rrc_start = -1;                 /* PhysCellId */
static int hf_lte_rrc_range = -1;                 /* T_range */
static int hf_lte_rrc_networkColourCode = -1;     /* BIT_STRING_SIZE_3 */
static int hf_lte_rrc_baseStationColourCode = -1;  /* BIT_STRING_SIZE_3 */
static int hf_lte_rrc_mcc = -1;                   /* MCC */
static int hf_lte_rrc_mnc = -1;                   /* MNC */
static int hf_lte_rrc_MCC_item = -1;              /* MCC_MNC_Digit */
static int hf_lte_rrc_MNC_item = -1;              /* MCC_MNC_Digit */
static int hf_lte_rrc_preRegistrationAllowed = -1;  /* BOOLEAN */
static int hf_lte_rrc_preRegistrationZoneId = -1;  /* PreRegistrationZoneIdHRPD */
static int hf_lte_rrc_secondaryPreRegistrationZoneIdList = -1;  /* SecondaryPreRegistrationZoneIdListHRPD */
static int hf_lte_rrc_SecondaryPreRegistrationZoneIdListHRPD_item = -1;  /* PreRegistrationZoneIdHRPD */
static int hf_lte_rrc_sf_Medium_01 = -1;          /* T_sf_Medium_01 */
static int hf_lte_rrc_sf_High_01 = -1;            /* T_sf_High_01 */
static int hf_lte_rrc_SystemInfoListGERAN_item = -1;  /* OCTET_STRING_SIZE_1_23 */
static int hf_lte_rrc_cdma_EUTRA_Synchronisation = -1;  /* BOOLEAN */
static int hf_lte_rrc_cdma_SystemTime = -1;       /* T_cdma_SystemTime */
static int hf_lte_rrc_synchronousSystemTime = -1;  /* BIT_STRING_SIZE_39 */
static int hf_lte_rrc_asynchronousSystemTime = -1;  /* BIT_STRING_SIZE_49 */
static int hf_lte_rrc_measObjectToRemoveList = -1;  /* MeasObjectToRemoveList */
static int hf_lte_rrc_measObjectToAddModList = -1;  /* MeasObjectToAddModList */
static int hf_lte_rrc_reportConfigToRemoveList = -1;  /* ReportConfigToRemoveList */
static int hf_lte_rrc_reportConfigToAddModList = -1;  /* ReportConfigToAddModList */
static int hf_lte_rrc_measIdToRemoveList = -1;    /* MeasIdToRemoveList */
static int hf_lte_rrc_measIdToAddModList = -1;    /* MeasIdToAddModList */
static int hf_lte_rrc_quantityConfig = -1;        /* QuantityConfig */
static int hf_lte_rrc_measGapConfig = -1;         /* MeasGapConfig */
static int hf_lte_rrc_s_Measure = -1;             /* RSRP_Range */
static int hf_lte_rrc_speedStatePars = -1;        /* T_speedStatePars */
static int hf_lte_rrc_setup_12 = -1;              /* T_setup_12 */
static int hf_lte_rrc_timeToTrigger_SF = -1;      /* SpeedStateScaleFactors */
static int hf_lte_rrc_MeasIdToRemoveList_item = -1;  /* MeasId */
static int hf_lte_rrc_MeasObjectToRemoveList_item = -1;  /* MeasObjectId */
static int hf_lte_rrc_ReportConfigToRemoveList_item = -1;  /* ReportConfigId */
static int hf_lte_rrc_setup_13 = -1;              /* T_setup_13 */
static int hf_lte_rrc_gapOffset = -1;             /* T_gapOffset */
static int hf_lte_rrc_gp0 = -1;                   /* INTEGER_0_39 */
static int hf_lte_rrc_gp1 = -1;                   /* INTEGER_0_79 */
static int hf_lte_rrc_MeasIdToAddModList_item = -1;  /* MeasIdToAddMod */
static int hf_lte_rrc_measId = -1;                /* MeasId */
static int hf_lte_rrc_measObjectId = -1;          /* MeasObjectId */
static int hf_lte_rrc_reportConfigId = -1;        /* ReportConfigId */
static int hf_lte_rrc_offsetFreq = -1;            /* Q_OffsetRangeInterRAT */
static int hf_lte_rrc_cellsToRemoveList = -1;     /* CellIndexList */
static int hf_lte_rrc_cellsToAddModList = -1;     /* CellsToAddModListCDMA2000 */
static int hf_lte_rrc_cellForWhichToReportCGI = -1;  /* PhysCellIdCDMA2000 */
static int hf_lte_rrc_CellsToAddModListCDMA2000_item = -1;  /* CellsToAddModCDMA2000 */
static int hf_lte_rrc_cellIndex = -1;             /* INTEGER_1_maxCellMeas */
static int hf_lte_rrc_physCellId_02 = -1;         /* PhysCellIdCDMA2000 */
static int hf_lte_rrc_offsetFreq_01 = -1;         /* Q_OffsetRange */
static int hf_lte_rrc_cellsToAddModList_01 = -1;  /* CellsToAddModList */
static int hf_lte_rrc_blackCellsToRemoveList = -1;  /* CellIndexList */
static int hf_lte_rrc_blackCellsToAddModList = -1;  /* BlackCellsToAddModList */
static int hf_lte_rrc_cellForWhichToReportCGI_01 = -1;  /* PhysCellId */
static int hf_lte_rrc_CellsToAddModList_item = -1;  /* CellsToAddMod */
static int hf_lte_rrc_cellIndividualOffset = -1;  /* Q_OffsetRange */
static int hf_lte_rrc_BlackCellsToAddModList_item = -1;  /* BlackCellsToAddMod */
static int hf_lte_rrc_physCellIdRange = -1;       /* PhysCellIdRange */
static int hf_lte_rrc_cellForWhichToReportCGI_02 = -1;  /* PhysCellIdGERAN */
static int hf_lte_rrc_MeasObjectToAddModList_item = -1;  /* MeasObjectToAddMod */
static int hf_lte_rrc_measObject = -1;            /* T_measObject */
static int hf_lte_rrc_measObjectEUTRA = -1;       /* MeasObjectEUTRA */
static int hf_lte_rrc_measObjectUTRA = -1;        /* MeasObjectUTRA */
static int hf_lte_rrc_measObjectGERAN = -1;       /* MeasObjectGERAN */
static int hf_lte_rrc_measObjectCDMA2000 = -1;    /* MeasObjectCDMA2000 */
static int hf_lte_rrc_cellsToAddModList_02 = -1;  /* T_cellsToAddModList */
static int hf_lte_rrc_cellsToAddModListUTRA_FDD = -1;  /* CellsToAddModListUTRA_FDD */
static int hf_lte_rrc_cellsToAddModListUTRA_TDD = -1;  /* CellsToAddModListUTRA_TDD */
static int hf_lte_rrc_cellForWhichToReportCGI_03 = -1;  /* T_cellForWhichToReportCGI */
static int hf_lte_rrc_utra_FDD_01 = -1;           /* PhysCellIdUTRA_FDD */
static int hf_lte_rrc_utra_TDD_01 = -1;           /* PhysCellIdUTRA_TDD */
static int hf_lte_rrc_CellsToAddModListUTRA_FDD_item = -1;  /* CellsToAddModUTRA_FDD */
static int hf_lte_rrc_physCellId_03 = -1;         /* PhysCellIdUTRA_FDD */
static int hf_lte_rrc_CellsToAddModListUTRA_TDD_item = -1;  /* CellsToAddModUTRA_TDD */
static int hf_lte_rrc_physCellId_04 = -1;         /* PhysCellIdUTRA_TDD */
static int hf_lte_rrc_measResultServCell = -1;    /* T_measResultServCell */
static int hf_lte_rrc_measResultNeighCells_01 = -1;  /* T_measResultNeighCells_01 */
static int hf_lte_rrc_measResultListEUTRA_01 = -1;  /* MeasResultListEUTRA */
static int hf_lte_rrc_measResultListUTRA_01 = -1;  /* MeasResultListUTRA */
static int hf_lte_rrc_measResultsCDMA2000_01 = -1;  /* MeasResultsCDMA2000 */
static int hf_lte_rrc_measResultForECID_r9 = -1;  /* MeasResultForECID_r9 */
static int hf_lte_rrc_MeasResultListEUTRA_item = -1;  /* MeasResultEUTRA */
static int hf_lte_rrc_cgi_Info = -1;              /* T_cgi_Info */
static int hf_lte_rrc_cellGlobalId = -1;          /* CellGlobalIdEUTRA */
static int hf_lte_rrc_plmn_IdentityList_01 = -1;  /* PLMN_IdentityList2 */
static int hf_lte_rrc_measResult = -1;            /* T_measResult */
static int hf_lte_rrc_additionalSI_Info_r9 = -1;  /* AdditionalSI_Info_r9 */
static int hf_lte_rrc_MeasResultListUTRA_item = -1;  /* MeasResultUTRA */
static int hf_lte_rrc_physCellId_05 = -1;         /* T_physCellId */
static int hf_lte_rrc_fdd = -1;                   /* PhysCellIdUTRA_FDD */
static int hf_lte_rrc_tdd = -1;                   /* PhysCellIdUTRA_TDD */
static int hf_lte_rrc_cgi_Info_01 = -1;           /* T_cgi_Info_01 */
static int hf_lte_rrc_cellGlobalId_01 = -1;       /* CellGlobalIdUTRA */
static int hf_lte_rrc_routingAreaCode = -1;       /* BIT_STRING_SIZE_8 */
static int hf_lte_rrc_measResult_01 = -1;         /* T_measResult_01 */
static int hf_lte_rrc_utra_RSCP = -1;             /* INTEGER_M5_91 */
static int hf_lte_rrc_utra_EcN0 = -1;             /* INTEGER_0_49 */
static int hf_lte_rrc_MeasResultListGERAN_item = -1;  /* MeasResultGERAN */
static int hf_lte_rrc_cgi_Info_02 = -1;           /* T_cgi_Info_02 */
static int hf_lte_rrc_cellGlobalId_02 = -1;       /* CellGlobalIdGERAN */
static int hf_lte_rrc_measResult_02 = -1;         /* T_measResult_02 */
static int hf_lte_rrc_rssi = -1;                  /* INTEGER_0_63 */
static int hf_lte_rrc_preRegistrationStatusHRPD = -1;  /* BOOLEAN */
static int hf_lte_rrc_measResultListCDMA2000 = -1;  /* MeasResultListCDMA2000 */
static int hf_lte_rrc_MeasResultListCDMA2000_item = -1;  /* MeasResultCDMA2000 */
static int hf_lte_rrc_cgi_Info_03 = -1;           /* CellGlobalIdCDMA2000 */
static int hf_lte_rrc_measResult_03 = -1;         /* T_measResult_03 */
static int hf_lte_rrc_pilotPnPhase = -1;          /* INTEGER_0_32767 */
static int hf_lte_rrc_pilotStrength = -1;         /* INTEGER_0_63 */
static int hf_lte_rrc_ue_RxTxTimeDiffResult_r9 = -1;  /* INTEGER_0_4095 */
static int hf_lte_rrc_currentSFN_r9 = -1;         /* BIT_STRING_SIZE_10 */
static int hf_lte_rrc_PLMN_IdentityList2_item = -1;  /* PLMN_Identity */
static int hf_lte_rrc_csg_MemberStatus_r9 = -1;   /* T_csg_MemberStatus_r9 */
static int hf_lte_rrc_csg_Identity_r9 = -1;       /* CSG_Identity */
static int hf_lte_rrc_quantityConfigEUTRA = -1;   /* QuantityConfigEUTRA */
static int hf_lte_rrc_quantityConfigUTRA = -1;    /* QuantityConfigUTRA */
static int hf_lte_rrc_quantityConfigGERAN = -1;   /* QuantityConfigGERAN */
static int hf_lte_rrc_quantityConfigCDMA2000 = -1;  /* QuantityConfigCDMA2000 */
static int hf_lte_rrc_filterCoefficientRSRP = -1;  /* FilterCoefficient */
static int hf_lte_rrc_filterCoefficientRSRQ = -1;  /* FilterCoefficient */
static int hf_lte_rrc_measQuantityUTRA_FDD = -1;  /* T_measQuantityUTRA_FDD */
static int hf_lte_rrc_measQuantityUTRA_TDD = -1;  /* T_measQuantityUTRA_TDD */
static int hf_lte_rrc_measQuantityGERAN = -1;     /* T_measQuantityGERAN */
static int hf_lte_rrc_measQuantityCDMA2000 = -1;  /* T_measQuantityCDMA2000 */
static int hf_lte_rrc_triggerType = -1;           /* T_triggerType */
static int hf_lte_rrc_event = -1;                 /* T_event */
static int hf_lte_rrc_eventId = -1;               /* T_eventId */
static int hf_lte_rrc_eventA1 = -1;               /* T_eventA1 */
static int hf_lte_rrc_a1_Threshold = -1;          /* ThresholdEUTRA */
static int hf_lte_rrc_eventA2 = -1;               /* T_eventA2 */
static int hf_lte_rrc_a2_Threshold = -1;          /* ThresholdEUTRA */
static int hf_lte_rrc_eventA3 = -1;               /* T_eventA3 */
static int hf_lte_rrc_a3_Offset = -1;             /* INTEGER_M30_30 */
static int hf_lte_rrc_reportOnLeave = -1;         /* BOOLEAN */
static int hf_lte_rrc_eventA4 = -1;               /* T_eventA4 */
static int hf_lte_rrc_a4_Threshold = -1;          /* ThresholdEUTRA */
static int hf_lte_rrc_eventA5 = -1;               /* T_eventA5 */
static int hf_lte_rrc_a5_Threshold1 = -1;         /* ThresholdEUTRA */
static int hf_lte_rrc_a5_Threshold2 = -1;         /* ThresholdEUTRA */
static int hf_lte_rrc_hysteresis = -1;            /* Hysteresis */
static int hf_lte_rrc_timeToTrigger = -1;         /* TimeToTrigger */
static int hf_lte_rrc_periodical = -1;            /* T_periodical */
static int hf_lte_rrc_purpose_02 = -1;            /* T_purpose_02 */
static int hf_lte_rrc_triggerQuantity = -1;       /* T_triggerQuantity */
static int hf_lte_rrc_reportQuantity = -1;        /* T_reportQuantity */
static int hf_lte_rrc_maxReportCells = -1;        /* INTEGER_1_maxCellReport */
static int hf_lte_rrc_reportInterval = -1;        /* ReportInterval */
static int hf_lte_rrc_reportAmount = -1;          /* T_reportAmount */
static int hf_lte_rrc_si_RequestForHO_r9 = -1;    /* T_si_RequestForHO_r9 */
static int hf_lte_rrc_ue_RxTxTimeDiffPeriodical_r9 = -1;  /* T_ue_RxTxTimeDiffPeriodical_r9 */
static int hf_lte_rrc_threshold_RSRP = -1;        /* RSRP_Range */
static int hf_lte_rrc_threshold_RSRQ = -1;        /* RSRQ_Range */
static int hf_lte_rrc_triggerType_01 = -1;        /* T_triggerType_01 */
static int hf_lte_rrc_event_01 = -1;              /* T_event_01 */
static int hf_lte_rrc_eventId_01 = -1;            /* T_eventId_01 */
static int hf_lte_rrc_eventB1 = -1;               /* T_eventB1 */
static int hf_lte_rrc_b1_Threshold = -1;          /* T_b1_Threshold */
static int hf_lte_rrc_b1_ThresholdUTRA = -1;      /* ThresholdUTRA */
static int hf_lte_rrc_b1_ThresholdGERAN = -1;     /* ThresholdGERAN */
static int hf_lte_rrc_b1_ThresholdCDMA2000 = -1;  /* ThresholdCDMA2000 */
static int hf_lte_rrc_eventB2 = -1;               /* T_eventB2 */
static int hf_lte_rrc_b2_Threshold1 = -1;         /* ThresholdEUTRA */
static int hf_lte_rrc_b2_Threshold2 = -1;         /* T_b2_Threshold2 */
static int hf_lte_rrc_b2_Threshold2UTRA = -1;     /* ThresholdUTRA */
static int hf_lte_rrc_b2_Threshold2GERAN = -1;    /* ThresholdGERAN */
static int hf_lte_rrc_b2_Threshold2CDMA2000 = -1;  /* ThresholdCDMA2000 */
static int hf_lte_rrc_periodical_01 = -1;         /* T_periodical_01 */
static int hf_lte_rrc_purpose_03 = -1;            /* T_purpose_03 */
static int hf_lte_rrc_reportAmount_01 = -1;       /* T_reportAmount_01 */
static int hf_lte_rrc_si_RequestForHO_r9_01 = -1;  /* T_si_RequestForHO_r9_01 */
static int hf_lte_rrc_ReportConfigToAddModList_item = -1;  /* ReportConfigToAddMod */
static int hf_lte_rrc_reportConfig = -1;          /* T_reportConfig */
static int hf_lte_rrc_reportConfigEUTRA = -1;     /* ReportConfigEUTRA */
static int hf_lte_rrc_reportConfigInterRAT = -1;  /* ReportConfigInterRAT */
static int hf_lte_rrc_reportProximityConfig_r9 = -1;  /* ReportProximityConfig_r9 */
static int hf_lte_rrc_proximityIndicationEUTRA_r9 = -1;  /* T_proximityIndicationEUTRA_r9 */
static int hf_lte_rrc_proximityIndicationUTRA_r9 = -1;  /* T_proximityIndicationUTRA_r9 */
static int hf_lte_rrc_m_TMSI = -1;                /* BIT_STRING_SIZE_32 */
static int hf_lte_rrc_UE_CapabilityRAT_ContainerList_item = -1;  /* UE_CapabilityRAT_Container */
static int hf_lte_rrc_rat_Type = -1;              /* RAT_Type */
static int hf_lte_rrc_ueCapabilityRAT_Container = -1;  /* T_ueCapabilityRAT_Container */
static int hf_lte_rrc_accessStratumRelease = -1;  /* AccessStratumRelease */
static int hf_lte_rrc_ue_Category = -1;           /* INTEGER_1_5 */
static int hf_lte_rrc_pdcp_Parameters = -1;       /* PDCP_Parameters */
static int hf_lte_rrc_phyLayerParameters = -1;    /* PhyLayerParameters */
static int hf_lte_rrc_rf_Parameters = -1;         /* RF_Parameters */
static int hf_lte_rrc_measParameters = -1;        /* MeasParameters */
static int hf_lte_rrc_featureGroupIndicators = -1;  /* BIT_STRING_SIZE_32 */
static int hf_lte_rrc_interRAT_Parameters = -1;   /* T_interRAT_Parameters */
static int hf_lte_rrc_utraFDD = -1;               /* IRAT_ParametersUTRA_FDD */
static int hf_lte_rrc_utraTDD128 = -1;            /* IRAT_ParametersUTRA_TDD128 */
static int hf_lte_rrc_utraTDD384 = -1;            /* IRAT_ParametersUTRA_TDD384 */
static int hf_lte_rrc_utraTDD768 = -1;            /* IRAT_ParametersUTRA_TDD768 */
static int hf_lte_rrc_geran_02 = -1;              /* IRAT_ParametersGERAN */
static int hf_lte_rrc_cdma2000_HRPD_01 = -1;      /* IRAT_ParametersCDMA2000_HRPD */
static int hf_lte_rrc_cdma2000_1xRTT_01 = -1;     /* IRAT_ParametersCDMA2000_1XRTT */
static int hf_lte_rrc_nonCriticalExtension_43 = -1;  /* UE_EUTRA_Capability_v920_IEs */
static int hf_lte_rrc_phyLayerParameters_v920 = -1;  /* PhyLayerParameters_v920 */
static int hf_lte_rrc_interRAT_ParametersGERAN_v920 = -1;  /* IRAT_ParametersGERAN_v920 */
static int hf_lte_rrc_interRAT_ParametersUTRA_v920 = -1;  /* IRAT_ParametersUTRA_v920 */
static int hf_lte_rrc_interRAT_Parameters_v920 = -1;  /* IRAT_ParametersCDMA2000_1XRTT_v920 */
static int hf_lte_rrc_deviceType_r9 = -1;         /* T_deviceType_r9 */
static int hf_lte_rrc_csg_ProximityIndicationParameters_r9 = -1;  /* CSG_ProximityIndicationParameters_r9 */
static int hf_lte_rrc_neighCellSI_AcquisitionParameters_r9 = -1;  /* NeighCellSI_AcquisitionParameters_r9 */
static int hf_lte_rrc_son_Parameters_r9 = -1;     /* SON_Parameters_r9 */
static int hf_lte_rrc_nonCriticalExtension_44 = -1;  /* T_nonCriticalExtension_32 */
static int hf_lte_rrc_supportedROHC_Profiles = -1;  /* T_supportedROHC_Profiles */
static int hf_lte_rrc_maxNumberROHC_ContextSessions = -1;  /* T_maxNumberROHC_ContextSessions */
static int hf_lte_rrc_ue_TxAntennaSelectionSupported = -1;  /* BOOLEAN */
static int hf_lte_rrc_ue_SpecificRefSigsSupported = -1;  /* BOOLEAN */
static int hf_lte_rrc_enhancedDualLayerFDD_Supported_r9 = -1;  /* BOOLEAN */
static int hf_lte_rrc_enhancedDualLayerTDD_Supported_r9 = -1;  /* BOOLEAN */
static int hf_lte_rrc_supportedBandListEUTRA = -1;  /* SupportedBandListEUTRA */
static int hf_lte_rrc_SupportedBandListEUTRA_item = -1;  /* SupportedBandEUTRA */
static int hf_lte_rrc_bandEUTRA = -1;             /* INTEGER_1_64 */
static int hf_lte_rrc_halfDuplex = -1;            /* BOOLEAN */
static int hf_lte_rrc_bandListEUTRA = -1;         /* BandListEUTRA */
static int hf_lte_rrc_BandListEUTRA_item = -1;    /* BandInfoEUTRA */
static int hf_lte_rrc_interFreqBandList = -1;     /* InterFreqBandList */
static int hf_lte_rrc_interRAT_BandList = -1;     /* InterRAT_BandList */
static int hf_lte_rrc_InterFreqBandList_item = -1;  /* InterFreqBandInfo */
static int hf_lte_rrc_interFreqNeedForGaps = -1;  /* BOOLEAN */
static int hf_lte_rrc_InterRAT_BandList_item = -1;  /* InterRAT_BandInfo */
static int hf_lte_rrc_interRAT_NeedForGaps = -1;  /* BOOLEAN */
static int hf_lte_rrc_supportedBandListUTRA_FDD = -1;  /* SupportedBandListUTRA_FDD */
static int hf_lte_rrc_e_Redirection_r9 = -1;      /* T_e_Redirection_r9 */
static int hf_lte_rrc_SupportedBandListUTRA_FDD_item = -1;  /* SupportedBandUTRA_FDD */
static int hf_lte_rrc_supportedBandListUTRA_TDD128 = -1;  /* SupportedBandListUTRA_TDD128 */
static int hf_lte_rrc_SupportedBandListUTRA_TDD128_item = -1;  /* SupportedBandUTRA_TDD128 */
static int hf_lte_rrc_supportedBandListUTRA_TDD384 = -1;  /* SupportedBandListUTRA_TDD384 */
static int hf_lte_rrc_SupportedBandListUTRA_TDD384_item = -1;  /* SupportedBandUTRA_TDD384 */
static int hf_lte_rrc_supportedBandListUTRA_TDD768 = -1;  /* SupportedBandListUTRA_TDD768 */
static int hf_lte_rrc_SupportedBandListUTRA_TDD768_item = -1;  /* SupportedBandUTRA_TDD768 */
static int hf_lte_rrc_supportedBandListGERAN = -1;  /* SupportedBandListGERAN */
static int hf_lte_rrc_interRAT_PS_HO_ToGERAN = -1;  /* BOOLEAN */
static int hf_lte_rrc_dtm_r9 = -1;                /* T_dtm_r9 */
static int hf_lte_rrc_e_RedirectionGERAN_r9 = -1;  /* T_e_RedirectionGERAN_r9 */
static int hf_lte_rrc_SupportedBandListGERAN_item = -1;  /* SupportedBandGERAN */
static int hf_lte_rrc_supportedBandListHRPD = -1;  /* SupportedBandListHRPD */
static int hf_lte_rrc_tx_ConfigHRPD = -1;         /* T_tx_ConfigHRPD */
static int hf_lte_rrc_rx_ConfigHRPD = -1;         /* T_rx_ConfigHRPD */
static int hf_lte_rrc_SupportedBandListHRPD_item = -1;  /* BandclassCDMA2000 */
static int hf_lte_rrc_supportedBandList1XRTT = -1;  /* SupportedBandList1XRTT */
static int hf_lte_rrc_tx_Config1XRTT = -1;        /* T_tx_Config1XRTT */
static int hf_lte_rrc_rx_Config1XRTT = -1;        /* T_rx_Config1XRTT */
static int hf_lte_rrc_e_CSFB_r9_01 = -1;          /* T_e_CSFB_r9 */
static int hf_lte_rrc_e_CSFB_ConcPS_Mob_r9 = -1;  /* T_e_CSFB_ConcPS_Mob_r9 */
static int hf_lte_rrc_SupportedBandList1XRTT_item = -1;  /* BandclassCDMA2000 */
static int hf_lte_rrc_intraFreqProximityIndicationSupported_r9 = -1;  /* BOOLEAN */
static int hf_lte_rrc_interFreqProximityIndicationSupported_r9 = -1;  /* BOOLEAN */
static int hf_lte_rrc_utran_ProximityIndicationSupported_r9 = -1;  /* BOOLEAN */
static int hf_lte_rrc_intraFreqSI_AcquisitionForHO_Supported_r9 = -1;  /* BOOLEAN */
static int hf_lte_rrc_interFreqSI_AcquisitionForHO_Supported_r9 = -1;  /* BOOLEAN */
static int hf_lte_rrc_utran_SI_AcquisitionForHO_Supported_r9 = -1;  /* BOOLEAN */
static int hf_lte_rrc_rach_ReportSupported_r9 = -1;  /* BOOLEAN */
static int hf_lte_rrc_t300 = -1;                  /* T_t300 */
static int hf_lte_rrc_t301 = -1;                  /* T_t301 */
static int hf_lte_rrc_t310 = -1;                  /* T_t310 */
static int hf_lte_rrc_n310 = -1;                  /* T_n310 */
static int hf_lte_rrc_t311 = -1;                  /* T_t311 */
static int hf_lte_rrc_n311 = -1;                  /* T_n311 */
static int hf_lte_rrc_notificationRepetitionCoeff_r9 = -1;  /* T_notificationRepetitionCoeff_r9 */
static int hf_lte_rrc_notificationOffset_r9 = -1;  /* INTEGER_0_10 */
static int hf_lte_rrc_notificationSF_Index_r9 = -1;  /* INTEGER_1_6 */
static int hf_lte_rrc_MBSFN_AreaInfoList_r9_item = -1;  /* MBSFN_AreaInfo_r9 */
static int hf_lte_rrc_mbsfn_AreaId_r9 = -1;       /* INTEGER_0_255 */
static int hf_lte_rrc_non_MBSFNregionLength = -1;  /* T_non_MBSFNregionLength */
static int hf_lte_rrc_notificationIndicator_r9 = -1;  /* INTEGER_0_7 */
static int hf_lte_rrc_mcch_Config_r9 = -1;        /* T_mcch_Config_r9 */
static int hf_lte_rrc_mcch_RepetitionPeriod_r9 = -1;  /* T_mcch_RepetitionPeriod_r9 */
static int hf_lte_rrc_mcch_Offset_r9 = -1;        /* INTEGER_0_10 */
static int hf_lte_rrc_mcch_ModificationPeriod_r9 = -1;  /* T_mcch_ModificationPeriod_r9 */
static int hf_lte_rrc_sf_AllocInfo_r9 = -1;       /* BIT_STRING_SIZE_6 */
static int hf_lte_rrc_signallingMCS_r9 = -1;      /* T_signallingMCS_r9 */
static int hf_lte_rrc_radioframeAllocationPeriod = -1;  /* T_radioframeAllocationPeriod */
static int hf_lte_rrc_radioframeAllocationOffset = -1;  /* INTEGER_0_7 */
static int hf_lte_rrc_subframeAllocation = -1;    /* T_subframeAllocation */
static int hf_lte_rrc_oneFrame = -1;              /* BIT_STRING_SIZE_6 */
static int hf_lte_rrc_fourFrames = -1;            /* BIT_STRING_SIZE_24 */
static int hf_lte_rrc_PMCH_InfoList_r9_item = -1;  /* PMCH_Info_r9 */
static int hf_lte_rrc_pmch_Config_r9 = -1;        /* PMCH_Config_r9 */
static int hf_lte_rrc_mbms_SessionInfoList_r9 = -1;  /* MBMS_SessionInfoList_r9 */
static int hf_lte_rrc_MBMS_SessionInfoList_r9_item = -1;  /* MBMS_SessionInfo_r9 */
static int hf_lte_rrc_tmgi_r9 = -1;               /* TMGI_r9 */
static int hf_lte_rrc_sessionId_r9 = -1;          /* OCTET_STRING_SIZE_1 */
static int hf_lte_rrc_logicalChannelIdentity_r9 = -1;  /* INTEGER_0_maxSessionPerPMCH_1 */
static int hf_lte_rrc_sf_AllocEnd_r9 = -1;        /* INTEGER_0_1535 */
static int hf_lte_rrc_dataMCS_r9 = -1;            /* INTEGER_0_28 */
static int hf_lte_rrc_mch_SchedulingPeriod_r9 = -1;  /* T_mch_SchedulingPeriod_r9 */
static int hf_lte_rrc_plmn_Id_r9 = -1;            /* T_plmn_Id_r9 */
static int hf_lte_rrc_plmn_Index_r9 = -1;         /* INTEGER_1_6 */
static int hf_lte_rrc_explicitValue_r9 = -1;      /* PLMN_Identity */
static int hf_lte_rrc_serviceId_r9 = -1;          /* OCTET_STRING_SIZE_3 */
static int hf_lte_rrc_CellsTriggeredList_item = -1;  /* CellsTriggeredList_item */
static int hf_lte_rrc_physCellIdEUTRA = -1;       /* PhysCellId */
static int hf_lte_rrc_physCellIdUTRA = -1;        /* T_physCellIdUTRA */
static int hf_lte_rrc_physCellIdGERAN = -1;       /* T_physCellIdGERAN */
static int hf_lte_rrc_physCellIdCDMA2000 = -1;    /* PhysCellIdCDMA2000 */
static int hf_lte_rrc_criticalExtensions_30 = -1;  /* T_criticalExtensions_30 */
static int hf_lte_rrc_c1_26 = -1;                 /* T_c1_26 */
static int hf_lte_rrc_handoverCommand_r8 = -1;    /* HandoverCommand_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_30 = -1;  /* T_criticalExtensionsFuture_30 */
static int hf_lte_rrc_handoverCommandMessage = -1;  /* T_handoverCommandMessage */
static int hf_lte_rrc_nonCriticalExtension_45 = -1;  /* T_nonCriticalExtension_33 */
static int hf_lte_rrc_criticalExtensions_31 = -1;  /* T_criticalExtensions_31 */
static int hf_lte_rrc_c1_27 = -1;                 /* T_c1_27 */
static int hf_lte_rrc_handoverPreparationInformation_r8 = -1;  /* HandoverPreparationInformation_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_31 = -1;  /* T_criticalExtensionsFuture_31 */
static int hf_lte_rrc_ue_RadioAccessCapabilityInfo = -1;  /* UE_CapabilityRAT_ContainerList */
static int hf_lte_rrc_as_Config = -1;             /* AS_Config */
static int hf_lte_rrc_rrm_Config = -1;            /* RRM_Config */
static int hf_lte_rrc_as_Context = -1;            /* AS_Context */
static int hf_lte_rrc_nonCriticalExtension_46 = -1;  /* HandoverPreparationInformation_v920_IEs */
static int hf_lte_rrc_ue_ConfigRelease_r9 = -1;   /* T_ue_ConfigRelease_r9 */
static int hf_lte_rrc_nonCriticalExtension_47 = -1;  /* T_nonCriticalExtension_34 */
static int hf_lte_rrc_criticalExtensions_32 = -1;  /* T_criticalExtensions_32 */
static int hf_lte_rrc_c1_28 = -1;                 /* T_c1_28 */
static int hf_lte_rrc_ueRadioAccessCapabilityInformation_r8 = -1;  /* UERadioAccessCapabilityInformation_r8_IEs */
static int hf_lte_rrc_criticalExtensionsFuture_32 = -1;  /* T_criticalExtensionsFuture_32 */
static int hf_lte_rrc_ue_RadioAccessCapabilityInfo_01 = -1;  /* T_ue_RadioAccessCapabilityInfo */
static int hf_lte_rrc_nonCriticalExtension_48 = -1;  /* T_nonCriticalExtension_35 */
static int hf_lte_rrc_sourceMeasConfig = -1;      /* MeasConfig */
static int hf_lte_rrc_sourceRadioResourceConfig = -1;  /* RadioResourceConfigDedicated */
static int hf_lte_rrc_sourceSecurityAlgorithmConfig = -1;  /* SecurityAlgorithmConfig */
static int hf_lte_rrc_sourceUE_Identity = -1;     /* C_RNTI */
static int hf_lte_rrc_sourceMasterInformationBlock = -1;  /* MasterInformationBlock */
static int hf_lte_rrc_sourceSystemInformationBlockType1 = -1;  /* SystemInformationBlockType1 */
static int hf_lte_rrc_sourceSystemInformationBlockType2 = -1;  /* SystemInformationBlockType2 */
static int hf_lte_rrc_sourceDl_CarrierFreq = -1;  /* ARFCN_ValueEUTRA */
static int hf_lte_rrc_sourceSystemInformationBlockType1Ext = -1;  /* T_sourceSystemInformationBlockType1Ext */
static int hf_lte_rrc_sourceOtherConfig_r9 = -1;  /* OtherConfig_r9 */
static int hf_lte_rrc_reestablishmentInfo = -1;   /* ReestablishmentInfo */
static int hf_lte_rrc_sourcePhysCellId = -1;      /* PhysCellId */
static int hf_lte_rrc_targetCellShortMAC_I = -1;  /* ShortMAC_I */
static int hf_lte_rrc_additionalReestabInfoList = -1;  /* AdditionalReestabInfoList */
static int hf_lte_rrc_AdditionalReestabInfoList_item = -1;  /* AdditionalReestabInfo */
static int hf_lte_rrc_key_eNodeB_Star = -1;       /* Key_eNodeB_Star */
static int hf_lte_rrc_ue_InactiveTime = -1;       /* T_ue_InactiveTime */

/*--- End of included file: packet-lte-rrc-hf.c ---*/
#line 57 "packet-lte-rrc-template.c"

/* Initialize the subtree pointers */
static int ett_lte_rrc = -1;


/*--- Included file: packet-lte-rrc-ett.c ---*/
#line 1 "packet-lte-rrc-ett.c"
static gint ett_lte_rrc_BCCH_BCH_Message = -1;
static gint ett_lte_rrc_BCCH_DL_SCH_Message = -1;
static gint ett_lte_rrc_BCCH_DL_SCH_MessageType = -1;
static gint ett_lte_rrc_T_c1 = -1;
static gint ett_lte_rrc_T_messageClassExtension = -1;
static gint ett_lte_rrc_MCCH_Message = -1;
static gint ett_lte_rrc_MCCH_MessageType = -1;
static gint ett_lte_rrc_T_c1_01 = -1;
static gint ett_lte_rrc_T_messageClassExtension_01 = -1;
static gint ett_lte_rrc_PCCH_Message = -1;
static gint ett_lte_rrc_PCCH_MessageType = -1;
static gint ett_lte_rrc_T_c1_02 = -1;
static gint ett_lte_rrc_T_messageClassExtension_02 = -1;
static gint ett_lte_rrc_DL_CCCH_Message = -1;
static gint ett_lte_rrc_DL_CCCH_MessageType = -1;
static gint ett_lte_rrc_T_c1_03 = -1;
static gint ett_lte_rrc_T_messageClassExtension_03 = -1;
static gint ett_lte_rrc_DL_DCCH_Message = -1;
static gint ett_lte_rrc_DL_DCCH_MessageType = -1;
static gint ett_lte_rrc_T_c1_04 = -1;
static gint ett_lte_rrc_T_messageClassExtension_04 = -1;
static gint ett_lte_rrc_UL_CCCH_Message = -1;
static gint ett_lte_rrc_UL_CCCH_MessageType = -1;
static gint ett_lte_rrc_T_c1_05 = -1;
static gint ett_lte_rrc_T_messageClassExtension_05 = -1;
static gint ett_lte_rrc_UL_DCCH_Message = -1;
static gint ett_lte_rrc_UL_DCCH_MessageType = -1;
static gint ett_lte_rrc_T_c1_06 = -1;
static gint ett_lte_rrc_T_messageClassExtension_06 = -1;
static gint ett_lte_rrc_CounterCheck = -1;
static gint ett_lte_rrc_T_criticalExtensions = -1;
static gint ett_lte_rrc_T_c1_07 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture = -1;
static gint ett_lte_rrc_CounterCheck_r8_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension = -1;
static gint ett_lte_rrc_DRB_CountMSB_InfoList = -1;
static gint ett_lte_rrc_DRB_CountMSB_Info = -1;
static gint ett_lte_rrc_CounterCheckResponse = -1;
static gint ett_lte_rrc_T_criticalExtensions_01 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_01 = -1;
static gint ett_lte_rrc_CounterCheckResponse_r8_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_01 = -1;
static gint ett_lte_rrc_DRB_CountInfoList = -1;
static gint ett_lte_rrc_DRB_CountInfo = -1;
static gint ett_lte_rrc_CSFBParametersRequestCDMA2000 = -1;
static gint ett_lte_rrc_T_criticalExtensions_02 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_02 = -1;
static gint ett_lte_rrc_CSFBParametersRequestCDMA2000_r8_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_02 = -1;
static gint ett_lte_rrc_CSFBParametersResponseCDMA2000 = -1;
static gint ett_lte_rrc_T_criticalExtensions_03 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_03 = -1;
static gint ett_lte_rrc_CSFBParametersResponseCDMA2000_r8_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_03 = -1;
static gint ett_lte_rrc_DLInformationTransfer = -1;
static gint ett_lte_rrc_T_criticalExtensions_04 = -1;
static gint ett_lte_rrc_T_c1_08 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_04 = -1;
static gint ett_lte_rrc_DLInformationTransfer_r8_IEs = -1;
static gint ett_lte_rrc_T_dedicatedInfoType = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_04 = -1;
static gint ett_lte_rrc_HandoverFromEUTRAPreparationRequest = -1;
static gint ett_lte_rrc_T_criticalExtensions_05 = -1;
static gint ett_lte_rrc_T_c1_09 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_05 = -1;
static gint ett_lte_rrc_HandoverFromEUTRAPreparationRequest_r8_IEs = -1;
static gint ett_lte_rrc_HandoverFromEUTRAPreparationRequest_v890_IEs = -1;
static gint ett_lte_rrc_HandoverFromEUTRAPreparationRequest_v920_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_05 = -1;
static gint ett_lte_rrc_MasterInformationBlock = -1;
static gint ett_lte_rrc_MBSFNAreaConfiguration_r9 = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_06 = -1;
static gint ett_lte_rrc_CommonSF_AllocPatternList_r9 = -1;
static gint ett_lte_rrc_MeasurementReport = -1;
static gint ett_lte_rrc_T_criticalExtensions_06 = -1;
static gint ett_lte_rrc_T_c1_10 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_06 = -1;
static gint ett_lte_rrc_MeasurementReport_r8_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_07 = -1;
static gint ett_lte_rrc_MobilityFromEUTRACommand = -1;
static gint ett_lte_rrc_T_criticalExtensions_07 = -1;
static gint ett_lte_rrc_T_c1_11 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_07 = -1;
static gint ett_lte_rrc_MobilityFromEUTRACommand_r8_IEs = -1;
static gint ett_lte_rrc_T_purpose = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_08 = -1;
static gint ett_lte_rrc_MobilityFromEUTRACommand_r9_IEs = -1;
static gint ett_lte_rrc_T_purpose_01 = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_09 = -1;
static gint ett_lte_rrc_Handover = -1;
static gint ett_lte_rrc_CellChangeOrder = -1;
static gint ett_lte_rrc_T_targetRAT_Type_01 = -1;
static gint ett_lte_rrc_T_geran = -1;
static gint ett_lte_rrc_SI_OrPSI_GERAN = -1;
static gint ett_lte_rrc_E_CSFB_r9 = -1;
static gint ett_lte_rrc_Paging = -1;
static gint ett_lte_rrc_Paging_v890_IEs = -1;
static gint ett_lte_rrc_Paging_v920_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_10 = -1;
static gint ett_lte_rrc_PagingRecordList = -1;
static gint ett_lte_rrc_PagingRecord = -1;
static gint ett_lte_rrc_PagingUE_Identity = -1;
static gint ett_lte_rrc_IMSI = -1;
static gint ett_lte_rrc_ProximityIndication_r9 = -1;
static gint ett_lte_rrc_T_criticalExtensions_08 = -1;
static gint ett_lte_rrc_T_c1_12 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_08 = -1;
static gint ett_lte_rrc_ProximityIndication_r9_IEs = -1;
static gint ett_lte_rrc_T_carrierFreq_r9 = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_11 = -1;
static gint ett_lte_rrc_RRCConnectionReconfiguration = -1;
static gint ett_lte_rrc_T_criticalExtensions_09 = -1;
static gint ett_lte_rrc_T_c1_13 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_09 = -1;
static gint ett_lte_rrc_RRCConnectionReconfiguration_r8_IEs = -1;
static gint ett_lte_rrc_SEQUENCE_SIZE_1_maxDRB_OF_DedicatedInfoNAS = -1;
static gint ett_lte_rrc_RRCConnectionReconfiguration_v890_IEs = -1;
static gint ett_lte_rrc_RRCConnectionReconfiguration_v920_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_12 = -1;
static gint ett_lte_rrc_SecurityConfigHO = -1;
static gint ett_lte_rrc_T_handoverType = -1;
static gint ett_lte_rrc_T_intraLTE = -1;
static gint ett_lte_rrc_T_interRAT = -1;
static gint ett_lte_rrc_RRCConnectionReconfigurationComplete = -1;
static gint ett_lte_rrc_T_criticalExtensions_10 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_10 = -1;
static gint ett_lte_rrc_RRCConnectionReconfigurationComplete_r8_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_13 = -1;
static gint ett_lte_rrc_RRCConnectionReestablishment = -1;
static gint ett_lte_rrc_T_criticalExtensions_11 = -1;
static gint ett_lte_rrc_T_c1_14 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_11 = -1;
static gint ett_lte_rrc_RRCConnectionReestablishment_r8_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_14 = -1;
static gint ett_lte_rrc_RRCConnectionReestablishmentComplete = -1;
static gint ett_lte_rrc_T_criticalExtensions_12 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_12 = -1;
static gint ett_lte_rrc_RRCConnectionReestablishmentComplete_r8_IEs = -1;
static gint ett_lte_rrc_RRCConnectionReestablishmentComplete_v920_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_15 = -1;
static gint ett_lte_rrc_RRCConnectionReestablishmentReject = -1;
static gint ett_lte_rrc_T_criticalExtensions_13 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_13 = -1;
static gint ett_lte_rrc_RRCConnectionReestablishmentReject_r8_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_16 = -1;
static gint ett_lte_rrc_RRCConnectionReestablishmentRequest = -1;
static gint ett_lte_rrc_T_criticalExtensions_14 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_14 = -1;
static gint ett_lte_rrc_RRCConnectionReestablishmentRequest_r8_IEs = -1;
static gint ett_lte_rrc_ReestabUE_Identity = -1;
static gint ett_lte_rrc_RRCConnectionReject = -1;
static gint ett_lte_rrc_T_criticalExtensions_15 = -1;
static gint ett_lte_rrc_T_c1_15 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_15 = -1;
static gint ett_lte_rrc_RRCConnectionReject_r8_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_17 = -1;
static gint ett_lte_rrc_RRCConnectionRelease = -1;
static gint ett_lte_rrc_T_criticalExtensions_16 = -1;
static gint ett_lte_rrc_T_c1_16 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_16 = -1;
static gint ett_lte_rrc_RRCConnectionRelease_r8_IEs = -1;
static gint ett_lte_rrc_RRCConnectionRelease_v890_IEs = -1;
static gint ett_lte_rrc_RRCConnectionRelease_v920_IEs = -1;
static gint ett_lte_rrc_T_cellInfoList_r9 = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_18 = -1;
static gint ett_lte_rrc_RedirectedCarrierInfo = -1;
static gint ett_lte_rrc_IdleModeMobilityControlInfo = -1;
static gint ett_lte_rrc_FreqPriorityListEUTRA = -1;
static gint ett_lte_rrc_FreqPriorityEUTRA = -1;
static gint ett_lte_rrc_FreqsPriorityListGERAN = -1;
static gint ett_lte_rrc_FreqsPriorityGERAN = -1;
static gint ett_lte_rrc_FreqPriorityListUTRA_FDD = -1;
static gint ett_lte_rrc_FreqPriorityUTRA_FDD = -1;
static gint ett_lte_rrc_FreqPriorityListUTRA_TDD = -1;
static gint ett_lte_rrc_FreqPriorityUTRA_TDD = -1;
static gint ett_lte_rrc_BandClassPriorityListHRPD = -1;
static gint ett_lte_rrc_BandClassPriorityHRPD = -1;
static gint ett_lte_rrc_BandClassPriorityList1XRTT = -1;
static gint ett_lte_rrc_BandClassPriority1XRTT = -1;
static gint ett_lte_rrc_CellInfoListGERAN_r9 = -1;
static gint ett_lte_rrc_CellInfoGERAN_r9 = -1;
static gint ett_lte_rrc_CellInfoListUTRA_FDD_r9 = -1;
static gint ett_lte_rrc_CellInfoUTRA_FDD_r9 = -1;
static gint ett_lte_rrc_CellInfoListUTRA_TDD_r9 = -1;
static gint ett_lte_rrc_CellInfoUTRA_TDD_r9 = -1;
static gint ett_lte_rrc_RRCConnectionRequest = -1;
static gint ett_lte_rrc_T_criticalExtensions_17 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_17 = -1;
static gint ett_lte_rrc_RRCConnectionRequest_r8_IEs = -1;
static gint ett_lte_rrc_InitialUE_Identity = -1;
static gint ett_lte_rrc_RRCConnectionSetup = -1;
static gint ett_lte_rrc_T_criticalExtensions_18 = -1;
static gint ett_lte_rrc_T_c1_17 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_18 = -1;
static gint ett_lte_rrc_RRCConnectionSetup_r8_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_19 = -1;
static gint ett_lte_rrc_RRCConnectionSetupComplete = -1;
static gint ett_lte_rrc_T_criticalExtensions_19 = -1;
static gint ett_lte_rrc_T_c1_18 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_19 = -1;
static gint ett_lte_rrc_RRCConnectionSetupComplete_r8_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_20 = -1;
static gint ett_lte_rrc_RegisteredMME = -1;
static gint ett_lte_rrc_SecurityModeCommand = -1;
static gint ett_lte_rrc_T_criticalExtensions_20 = -1;
static gint ett_lte_rrc_T_c1_19 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_20 = -1;
static gint ett_lte_rrc_SecurityModeCommand_r8_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_21 = -1;
static gint ett_lte_rrc_SecurityConfigSMC = -1;
static gint ett_lte_rrc_SecurityModeComplete = -1;
static gint ett_lte_rrc_T_criticalExtensions_21 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_21 = -1;
static gint ett_lte_rrc_SecurityModeComplete_r8_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_22 = -1;
static gint ett_lte_rrc_SecurityModeFailure = -1;
static gint ett_lte_rrc_T_criticalExtensions_22 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_22 = -1;
static gint ett_lte_rrc_SecurityModeFailure_r8_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_23 = -1;
static gint ett_lte_rrc_SystemInformation = -1;
static gint ett_lte_rrc_T_criticalExtensions_23 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_23 = -1;
static gint ett_lte_rrc_SystemInformation_r8_IEs = -1;
static gint ett_lte_rrc_T_sib_TypeAndInfo = -1;
static gint ett_lte_rrc_T_sib_TypeAndInfo_item = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_24 = -1;
static gint ett_lte_rrc_SystemInformationBlockType1 = -1;
static gint ett_lte_rrc_T_cellAccessRelatedInfo = -1;
static gint ett_lte_rrc_T_cellSelectionInfo = -1;
static gint ett_lte_rrc_SystemInformationBlockType1_v890_IEs = -1;
static gint ett_lte_rrc_SystemInformationBlockType1_v920_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_25 = -1;
static gint ett_lte_rrc_PLMN_IdentityList = -1;
static gint ett_lte_rrc_PLMN_IdentityInfo = -1;
static gint ett_lte_rrc_SchedulingInfoList = -1;
static gint ett_lte_rrc_SchedulingInfo = -1;
static gint ett_lte_rrc_SIB_MappingInfo = -1;
static gint ett_lte_rrc_CellSelectionInfo_v920 = -1;
static gint ett_lte_rrc_UECapabilityEnquiry = -1;
static gint ett_lte_rrc_T_criticalExtensions_24 = -1;
static gint ett_lte_rrc_T_c1_20 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_24 = -1;
static gint ett_lte_rrc_UECapabilityEnquiry_r8_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_26 = -1;
static gint ett_lte_rrc_UE_CapabilityRequest = -1;
static gint ett_lte_rrc_UECapabilityInformation = -1;
static gint ett_lte_rrc_T_criticalExtensions_25 = -1;
static gint ett_lte_rrc_T_c1_21 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_25 = -1;
static gint ett_lte_rrc_UECapabilityInformation_r8_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_27 = -1;
static gint ett_lte_rrc_UEInformationRequest_r9 = -1;
static gint ett_lte_rrc_T_criticalExtensions_26 = -1;
static gint ett_lte_rrc_T_c1_22 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_26 = -1;
static gint ett_lte_rrc_UEInformationRequest_r9_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_28 = -1;
static gint ett_lte_rrc_UEInformationResponse_r9 = -1;
static gint ett_lte_rrc_T_criticalExtensions_27 = -1;
static gint ett_lte_rrc_T_c1_23 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_27 = -1;
static gint ett_lte_rrc_UEInformationResponse_r9_IEs = -1;
static gint ett_lte_rrc_T_rach_Report_r9 = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_29 = -1;
static gint ett_lte_rrc_RLF_Report_r9 = -1;
static gint ett_lte_rrc_T_measResultLastServCell = -1;
static gint ett_lte_rrc_T_measResultNeighCells = -1;
static gint ett_lte_rrc_MeasResultList2EUTRA = -1;
static gint ett_lte_rrc_MeasResultList2EUTRA_item = -1;
static gint ett_lte_rrc_MeasResultList2UTRA = -1;
static gint ett_lte_rrc_MeasResultList2UTRA_item = -1;
static gint ett_lte_rrc_MeasResultList2CDMA2000 = -1;
static gint ett_lte_rrc_MeasResultList2CDMA2000_item = -1;
static gint ett_lte_rrc_ULHandoverPreparationTransfer = -1;
static gint ett_lte_rrc_T_criticalExtensions_28 = -1;
static gint ett_lte_rrc_T_c1_24 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_28 = -1;
static gint ett_lte_rrc_ULHandoverPreparationTransfer_r8_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_30 = -1;
static gint ett_lte_rrc_ULInformationTransfer = -1;
static gint ett_lte_rrc_T_criticalExtensions_29 = -1;
static gint ett_lte_rrc_T_c1_25 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_29 = -1;
static gint ett_lte_rrc_ULInformationTransfer_r8_IEs = -1;
static gint ett_lte_rrc_T_dedicatedInfoType_01 = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_31 = -1;
static gint ett_lte_rrc_SystemInformationBlockType2 = -1;
static gint ett_lte_rrc_T_ac_BarringInfo = -1;
static gint ett_lte_rrc_T_freqInfo = -1;
static gint ett_lte_rrc_AC_BarringConfig = -1;
static gint ett_lte_rrc_MBSFN_SubframeConfigList = -1;
static gint ett_lte_rrc_SystemInformationBlockType3 = -1;
static gint ett_lte_rrc_T_cellReselectionInfoCommon = -1;
static gint ett_lte_rrc_T_speedStateReselectionPars = -1;
static gint ett_lte_rrc_T_q_HystSF = -1;
static gint ett_lte_rrc_T_cellReselectionServingFreqInfo = -1;
static gint ett_lte_rrc_T_intraFreqCellReselectionInfo = -1;
static gint ett_lte_rrc_T_s_IntraSearch_v920 = -1;
static gint ett_lte_rrc_T_s_NonIntraSearch_v920 = -1;
static gint ett_lte_rrc_SystemInformationBlockType4 = -1;
static gint ett_lte_rrc_IntraFreqNeighCellList = -1;
static gint ett_lte_rrc_IntraFreqNeighCellInfo = -1;
static gint ett_lte_rrc_IntraFreqBlackCellList = -1;
static gint ett_lte_rrc_SystemInformationBlockType5 = -1;
static gint ett_lte_rrc_InterFreqCarrierFreqList = -1;
static gint ett_lte_rrc_InterFreqCarrierFreqInfo = -1;
static gint ett_lte_rrc_T_threshX_Q_r9 = -1;
static gint ett_lte_rrc_InterFreqNeighCellList = -1;
static gint ett_lte_rrc_InterFreqNeighCellInfo = -1;
static gint ett_lte_rrc_InterFreqBlackCellList = -1;
static gint ett_lte_rrc_SystemInformationBlockType6 = -1;
static gint ett_lte_rrc_CarrierFreqListUTRA_FDD = -1;
static gint ett_lte_rrc_CarrierFreqUTRA_FDD = -1;
static gint ett_lte_rrc_T_threshX_Q_r9_01 = -1;
static gint ett_lte_rrc_CarrierFreqListUTRA_TDD = -1;
static gint ett_lte_rrc_CarrierFreqUTRA_TDD = -1;
static gint ett_lte_rrc_SystemInformationBlockType7 = -1;
static gint ett_lte_rrc_CarrierFreqsInfoListGERAN = -1;
static gint ett_lte_rrc_CarrierFreqsInfoGERAN = -1;
static gint ett_lte_rrc_T_commonInfo = -1;
static gint ett_lte_rrc_SystemInformationBlockType8 = -1;
static gint ett_lte_rrc_T_parametersHRPD = -1;
static gint ett_lte_rrc_T_parameters1XRTT = -1;
static gint ett_lte_rrc_CellReselectionParametersCDMA2000 = -1;
static gint ett_lte_rrc_CellReselectionParametersCDMA2000_v920 = -1;
static gint ett_lte_rrc_NeighCellListCDMA2000 = -1;
static gint ett_lte_rrc_NeighCellCDMA2000 = -1;
static gint ett_lte_rrc_NeighCellsPerBandclassListCDMA2000 = -1;
static gint ett_lte_rrc_NeighCellsPerBandclassCDMA2000 = -1;
static gint ett_lte_rrc_NeighCellListCDMA2000_v920 = -1;
static gint ett_lte_rrc_NeighCellCDMA2000_v920 = -1;
static gint ett_lte_rrc_NeighCellsPerBandclassListCDMA2000_v920 = -1;
static gint ett_lte_rrc_NeighCellsPerBandclassCDMA2000_v920 = -1;
static gint ett_lte_rrc_PhysCellIdListCDMA2000 = -1;
static gint ett_lte_rrc_PhysCellIdListCDMA2000_v920 = -1;
static gint ett_lte_rrc_BandClassListCDMA2000 = -1;
static gint ett_lte_rrc_BandClassInfoCDMA2000 = -1;
static gint ett_lte_rrc_AC_BarringConfig1XRTT_r9 = -1;
static gint ett_lte_rrc_SystemInformationBlockType9 = -1;
static gint ett_lte_rrc_SystemInformationBlockType10 = -1;
static gint ett_lte_rrc_SystemInformationBlockType11 = -1;
static gint ett_lte_rrc_SystemInformationBlockType12_r9 = -1;
static gint ett_lte_rrc_SystemInformationBlockType13_r9 = -1;
static gint ett_lte_rrc_AntennaInfoCommon = -1;
static gint ett_lte_rrc_AntennaInfoDedicated = -1;
static gint ett_lte_rrc_T_codebookSubsetRestriction = -1;
static gint ett_lte_rrc_T_ue_TransmitAntennaSelection = -1;
static gint ett_lte_rrc_AntennaInfoDedicated_v920 = -1;
static gint ett_lte_rrc_T_codebookSubsetRestriction_v920 = -1;
static gint ett_lte_rrc_CQI_ReportConfig = -1;
static gint ett_lte_rrc_CQI_ReportConfig_v920 = -1;
static gint ett_lte_rrc_CQI_ReportPeriodic = -1;
static gint ett_lte_rrc_T_setup_01 = -1;
static gint ett_lte_rrc_T_cqi_FormatIndicatorPeriodic = -1;
static gint ett_lte_rrc_T_subbandCQI = -1;
static gint ett_lte_rrc_LogicalChannelConfig = -1;
static gint ett_lte_rrc_T_ul_SpecificParameters = -1;
static gint ett_lte_rrc_MAC_MainConfig = -1;
static gint ett_lte_rrc_T_ul_SCH_Config = -1;
static gint ett_lte_rrc_T_phr_Config = -1;
static gint ett_lte_rrc_T_setup_02 = -1;
static gint ett_lte_rrc_DRX_Config = -1;
static gint ett_lte_rrc_T_setup_03 = -1;
static gint ett_lte_rrc_T_longDRX_CycleStartOffset = -1;
static gint ett_lte_rrc_T_shortDRX = -1;
static gint ett_lte_rrc_PDCP_Config = -1;
static gint ett_lte_rrc_T_rlc_AM = -1;
static gint ett_lte_rrc_T_rlc_UM = -1;
static gint ett_lte_rrc_T_headerCompression = -1;
static gint ett_lte_rrc_T_rohc = -1;
static gint ett_lte_rrc_T_profiles = -1;
static gint ett_lte_rrc_PDSCH_ConfigCommon = -1;
static gint ett_lte_rrc_PDSCH_ConfigDedicated = -1;
static gint ett_lte_rrc_PHICH_Config = -1;
static gint ett_lte_rrc_PhysicalConfigDedicated = -1;
static gint ett_lte_rrc_T_antennaInfo = -1;
static gint ett_lte_rrc_PRACH_ConfigSIB = -1;
static gint ett_lte_rrc_PRACH_Config = -1;
static gint ett_lte_rrc_PRACH_ConfigInfo = -1;
static gint ett_lte_rrc_PUCCH_ConfigCommon = -1;
static gint ett_lte_rrc_PUCCH_ConfigDedicated = -1;
static gint ett_lte_rrc_T_ackNackRepetition = -1;
static gint ett_lte_rrc_T_setup_04 = -1;
static gint ett_lte_rrc_PUSCH_ConfigCommon = -1;
static gint ett_lte_rrc_T_pusch_ConfigBasic = -1;
static gint ett_lte_rrc_PUSCH_ConfigDedicated = -1;
static gint ett_lte_rrc_UL_ReferenceSignalsPUSCH = -1;
static gint ett_lte_rrc_RACH_ConfigCommon = -1;
static gint ett_lte_rrc_T_preambleInfo = -1;
static gint ett_lte_rrc_T_preamblesGroupAConfig = -1;
static gint ett_lte_rrc_T_powerRampingParameters = -1;
static gint ett_lte_rrc_T_ra_SupervisionInfo = -1;
static gint ett_lte_rrc_RACH_ConfigDedicated = -1;
static gint ett_lte_rrc_RadioResourceConfigCommonSIB = -1;
static gint ett_lte_rrc_RadioResourceConfigCommon = -1;
static gint ett_lte_rrc_BCCH_Config = -1;
static gint ett_lte_rrc_PCCH_Config = -1;
static gint ett_lte_rrc_RadioResourceConfigDedicated = -1;
static gint ett_lte_rrc_T_mac_MainConfig = -1;
static gint ett_lte_rrc_SRB_ToAddModList = -1;
static gint ett_lte_rrc_SRB_ToAddMod = -1;
static gint ett_lte_rrc_T_rlc_Config = -1;
static gint ett_lte_rrc_T_logicalChannelConfig = -1;
static gint ett_lte_rrc_DRB_ToAddModList = -1;
static gint ett_lte_rrc_DRB_ToAddMod = -1;
static gint ett_lte_rrc_DRB_ToReleaseList = -1;
static gint ett_lte_rrc_RLC_Config = -1;
static gint ett_lte_rrc_T_am = -1;
static gint ett_lte_rrc_T_um_Bi_Directional = -1;
static gint ett_lte_rrc_T_um_Uni_Directional_UL = -1;
static gint ett_lte_rrc_T_um_Uni_Directional_DL = -1;
static gint ett_lte_rrc_UL_AM_RLC = -1;
static gint ett_lte_rrc_DL_AM_RLC = -1;
static gint ett_lte_rrc_UL_UM_RLC = -1;
static gint ett_lte_rrc_DL_UM_RLC = -1;
static gint ett_lte_rrc_RLF_TimersAndConstants_r9 = -1;
static gint ett_lte_rrc_T_setup_05 = -1;
static gint ett_lte_rrc_SchedulingRequestConfig = -1;
static gint ett_lte_rrc_T_setup_06 = -1;
static gint ett_lte_rrc_SoundingRS_UL_ConfigCommon = -1;
static gint ett_lte_rrc_T_setup_07 = -1;
static gint ett_lte_rrc_SoundingRS_UL_ConfigDedicated = -1;
static gint ett_lte_rrc_T_setup_08 = -1;
static gint ett_lte_rrc_SPS_Config = -1;
static gint ett_lte_rrc_SPS_ConfigDL = -1;
static gint ett_lte_rrc_T_setup_09 = -1;
static gint ett_lte_rrc_SPS_ConfigUL = -1;
static gint ett_lte_rrc_T_setup_10 = -1;
static gint ett_lte_rrc_T_p0_Persistent = -1;
static gint ett_lte_rrc_N1_PUCCH_AN_PersistentList = -1;
static gint ett_lte_rrc_TDD_Config = -1;
static gint ett_lte_rrc_TPC_PDCCH_Config = -1;
static gint ett_lte_rrc_T_setup_11 = -1;
static gint ett_lte_rrc_TPC_Index = -1;
static gint ett_lte_rrc_UplinkPowerControlCommon = -1;
static gint ett_lte_rrc_UplinkPowerControlDedicated = -1;
static gint ett_lte_rrc_DeltaFList_PUCCH = -1;
static gint ett_lte_rrc_SecurityAlgorithmConfig = -1;
static gint ett_lte_rrc_CarrierFreqCDMA2000 = -1;
static gint ett_lte_rrc_CarrierFreqGERAN = -1;
static gint ett_lte_rrc_CarrierFreqsGERAN = -1;
static gint ett_lte_rrc_T_followingARFCNs = -1;
static gint ett_lte_rrc_T_equallySpacedARFCNs = -1;
static gint ett_lte_rrc_ExplicitListOfARFCNs = -1;
static gint ett_lte_rrc_CellIndexList = -1;
static gint ett_lte_rrc_CSFB_RegistrationParam1XRTT = -1;
static gint ett_lte_rrc_CSFB_RegistrationParam1XRTT_v920 = -1;
static gint ett_lte_rrc_CellGlobalIdEUTRA = -1;
static gint ett_lte_rrc_CellGlobalIdUTRA = -1;
static gint ett_lte_rrc_CellGlobalIdGERAN = -1;
static gint ett_lte_rrc_CellGlobalIdCDMA2000 = -1;
static gint ett_lte_rrc_MobilityControlInfo = -1;
static gint ett_lte_rrc_CarrierBandwidthEUTRA = -1;
static gint ett_lte_rrc_CarrierFreqEUTRA = -1;
static gint ett_lte_rrc_MobilityStateParameters = -1;
static gint ett_lte_rrc_PhysCellIdRange = -1;
static gint ett_lte_rrc_PhysCellIdGERAN = -1;
static gint ett_lte_rrc_PLMN_Identity = -1;
static gint ett_lte_rrc_MCC = -1;
static gint ett_lte_rrc_MNC = -1;
static gint ett_lte_rrc_PreRegistrationInfoHRPD = -1;
static gint ett_lte_rrc_SecondaryPreRegistrationZoneIdListHRPD = -1;
static gint ett_lte_rrc_SpeedStateScaleFactors = -1;
static gint ett_lte_rrc_SystemInfoListGERAN = -1;
static gint ett_lte_rrc_SystemTimeInfoCDMA2000 = -1;
static gint ett_lte_rrc_T_cdma_SystemTime = -1;
static gint ett_lte_rrc_MeasConfig = -1;
static gint ett_lte_rrc_T_speedStatePars = -1;
static gint ett_lte_rrc_T_setup_12 = -1;
static gint ett_lte_rrc_MeasIdToRemoveList = -1;
static gint ett_lte_rrc_MeasObjectToRemoveList = -1;
static gint ett_lte_rrc_ReportConfigToRemoveList = -1;
static gint ett_lte_rrc_MeasGapConfig = -1;
static gint ett_lte_rrc_T_setup_13 = -1;
static gint ett_lte_rrc_T_gapOffset = -1;
static gint ett_lte_rrc_MeasIdToAddModList = -1;
static gint ett_lte_rrc_MeasIdToAddMod = -1;
static gint ett_lte_rrc_MeasObjectCDMA2000 = -1;
static gint ett_lte_rrc_CellsToAddModListCDMA2000 = -1;
static gint ett_lte_rrc_CellsToAddModCDMA2000 = -1;
static gint ett_lte_rrc_MeasObjectEUTRA = -1;
static gint ett_lte_rrc_CellsToAddModList = -1;
static gint ett_lte_rrc_CellsToAddMod = -1;
static gint ett_lte_rrc_BlackCellsToAddModList = -1;
static gint ett_lte_rrc_BlackCellsToAddMod = -1;
static gint ett_lte_rrc_MeasObjectGERAN = -1;
static gint ett_lte_rrc_MeasObjectToAddModList = -1;
static gint ett_lte_rrc_MeasObjectToAddMod = -1;
static gint ett_lte_rrc_T_measObject = -1;
static gint ett_lte_rrc_MeasObjectUTRA = -1;
static gint ett_lte_rrc_T_cellsToAddModList = -1;
static gint ett_lte_rrc_T_cellForWhichToReportCGI = -1;
static gint ett_lte_rrc_CellsToAddModListUTRA_FDD = -1;
static gint ett_lte_rrc_CellsToAddModUTRA_FDD = -1;
static gint ett_lte_rrc_CellsToAddModListUTRA_TDD = -1;
static gint ett_lte_rrc_CellsToAddModUTRA_TDD = -1;
static gint ett_lte_rrc_MeasResults = -1;
static gint ett_lte_rrc_T_measResultServCell = -1;
static gint ett_lte_rrc_T_measResultNeighCells_01 = -1;
static gint ett_lte_rrc_MeasResultListEUTRA = -1;
static gint ett_lte_rrc_MeasResultEUTRA = -1;
static gint ett_lte_rrc_T_cgi_Info = -1;
static gint ett_lte_rrc_T_measResult = -1;
static gint ett_lte_rrc_MeasResultListUTRA = -1;
static gint ett_lte_rrc_MeasResultUTRA = -1;
static gint ett_lte_rrc_T_physCellId = -1;
static gint ett_lte_rrc_T_cgi_Info_01 = -1;
static gint ett_lte_rrc_T_measResult_01 = -1;
static gint ett_lte_rrc_MeasResultListGERAN = -1;
static gint ett_lte_rrc_MeasResultGERAN = -1;
static gint ett_lte_rrc_T_cgi_Info_02 = -1;
static gint ett_lte_rrc_T_measResult_02 = -1;
static gint ett_lte_rrc_MeasResultsCDMA2000 = -1;
static gint ett_lte_rrc_MeasResultListCDMA2000 = -1;
static gint ett_lte_rrc_MeasResultCDMA2000 = -1;
static gint ett_lte_rrc_T_measResult_03 = -1;
static gint ett_lte_rrc_MeasResultForECID_r9 = -1;
static gint ett_lte_rrc_PLMN_IdentityList2 = -1;
static gint ett_lte_rrc_AdditionalSI_Info_r9 = -1;
static gint ett_lte_rrc_QuantityConfig = -1;
static gint ett_lte_rrc_QuantityConfigEUTRA = -1;
static gint ett_lte_rrc_QuantityConfigUTRA = -1;
static gint ett_lte_rrc_QuantityConfigGERAN = -1;
static gint ett_lte_rrc_QuantityConfigCDMA2000 = -1;
static gint ett_lte_rrc_ReportConfigEUTRA = -1;
static gint ett_lte_rrc_T_triggerType = -1;
static gint ett_lte_rrc_T_event = -1;
static gint ett_lte_rrc_T_eventId = -1;
static gint ett_lte_rrc_T_eventA1 = -1;
static gint ett_lte_rrc_T_eventA2 = -1;
static gint ett_lte_rrc_T_eventA3 = -1;
static gint ett_lte_rrc_T_eventA4 = -1;
static gint ett_lte_rrc_T_eventA5 = -1;
static gint ett_lte_rrc_T_periodical = -1;
static gint ett_lte_rrc_ThresholdEUTRA = -1;
static gint ett_lte_rrc_ReportConfigInterRAT = -1;
static gint ett_lte_rrc_T_triggerType_01 = -1;
static gint ett_lte_rrc_T_event_01 = -1;
static gint ett_lte_rrc_T_eventId_01 = -1;
static gint ett_lte_rrc_T_eventB1 = -1;
static gint ett_lte_rrc_T_b1_Threshold = -1;
static gint ett_lte_rrc_T_eventB2 = -1;
static gint ett_lte_rrc_T_b2_Threshold2 = -1;
static gint ett_lte_rrc_T_periodical_01 = -1;
static gint ett_lte_rrc_ThresholdUTRA = -1;
static gint ett_lte_rrc_ReportConfigToAddModList = -1;
static gint ett_lte_rrc_ReportConfigToAddMod = -1;
static gint ett_lte_rrc_T_reportConfig = -1;
static gint ett_lte_rrc_OtherConfig_r9 = -1;
static gint ett_lte_rrc_ReportProximityConfig_r9 = -1;
static gint ett_lte_rrc_S_TMSI = -1;
static gint ett_lte_rrc_UE_CapabilityRAT_ContainerList = -1;
static gint ett_lte_rrc_UE_CapabilityRAT_Container = -1;
static gint ett_lte_rrc_UE_EUTRA_Capability = -1;
static gint ett_lte_rrc_T_interRAT_Parameters = -1;
static gint ett_lte_rrc_UE_EUTRA_Capability_v920_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_32 = -1;
static gint ett_lte_rrc_PDCP_Parameters = -1;
static gint ett_lte_rrc_T_supportedROHC_Profiles = -1;
static gint ett_lte_rrc_PhyLayerParameters = -1;
static gint ett_lte_rrc_PhyLayerParameters_v920 = -1;
static gint ett_lte_rrc_RF_Parameters = -1;
static gint ett_lte_rrc_SupportedBandListEUTRA = -1;
static gint ett_lte_rrc_SupportedBandEUTRA = -1;
static gint ett_lte_rrc_MeasParameters = -1;
static gint ett_lte_rrc_BandListEUTRA = -1;
static gint ett_lte_rrc_BandInfoEUTRA = -1;
static gint ett_lte_rrc_InterFreqBandList = -1;
static gint ett_lte_rrc_InterFreqBandInfo = -1;
static gint ett_lte_rrc_InterRAT_BandList = -1;
static gint ett_lte_rrc_InterRAT_BandInfo = -1;
static gint ett_lte_rrc_IRAT_ParametersUTRA_FDD = -1;
static gint ett_lte_rrc_IRAT_ParametersUTRA_v920 = -1;
static gint ett_lte_rrc_SupportedBandListUTRA_FDD = -1;
static gint ett_lte_rrc_IRAT_ParametersUTRA_TDD128 = -1;
static gint ett_lte_rrc_SupportedBandListUTRA_TDD128 = -1;
static gint ett_lte_rrc_IRAT_ParametersUTRA_TDD384 = -1;
static gint ett_lte_rrc_SupportedBandListUTRA_TDD384 = -1;
static gint ett_lte_rrc_IRAT_ParametersUTRA_TDD768 = -1;
static gint ett_lte_rrc_SupportedBandListUTRA_TDD768 = -1;
static gint ett_lte_rrc_IRAT_ParametersGERAN = -1;
static gint ett_lte_rrc_IRAT_ParametersGERAN_v920 = -1;
static gint ett_lte_rrc_SupportedBandListGERAN = -1;
static gint ett_lte_rrc_IRAT_ParametersCDMA2000_HRPD = -1;
static gint ett_lte_rrc_SupportedBandListHRPD = -1;
static gint ett_lte_rrc_IRAT_ParametersCDMA2000_1XRTT = -1;
static gint ett_lte_rrc_IRAT_ParametersCDMA2000_1XRTT_v920 = -1;
static gint ett_lte_rrc_SupportedBandList1XRTT = -1;
static gint ett_lte_rrc_CSG_ProximityIndicationParameters_r9 = -1;
static gint ett_lte_rrc_NeighCellSI_AcquisitionParameters_r9 = -1;
static gint ett_lte_rrc_SON_Parameters_r9 = -1;
static gint ett_lte_rrc_UE_TimersAndConstants = -1;
static gint ett_lte_rrc_MBMS_NotificationConfig_r9 = -1;
static gint ett_lte_rrc_MBSFN_AreaInfoList_r9 = -1;
static gint ett_lte_rrc_MBSFN_AreaInfo_r9 = -1;
static gint ett_lte_rrc_T_mcch_Config_r9 = -1;
static gint ett_lte_rrc_MBSFN_SubframeConfig = -1;
static gint ett_lte_rrc_T_subframeAllocation = -1;
static gint ett_lte_rrc_PMCH_InfoList_r9 = -1;
static gint ett_lte_rrc_PMCH_Info_r9 = -1;
static gint ett_lte_rrc_MBMS_SessionInfoList_r9 = -1;
static gint ett_lte_rrc_MBMS_SessionInfo_r9 = -1;
static gint ett_lte_rrc_PMCH_Config_r9 = -1;
static gint ett_lte_rrc_TMGI_r9 = -1;
static gint ett_lte_rrc_T_plmn_Id_r9 = -1;
static gint ett_lte_rrc_CellsTriggeredList = -1;
static gint ett_lte_rrc_CellsTriggeredList_item = -1;
static gint ett_lte_rrc_T_physCellIdUTRA = -1;
static gint ett_lte_rrc_T_physCellIdGERAN = -1;
static gint ett_lte_rrc_HandoverCommand = -1;
static gint ett_lte_rrc_T_criticalExtensions_30 = -1;
static gint ett_lte_rrc_T_c1_26 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_30 = -1;
static gint ett_lte_rrc_HandoverCommand_r8_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_33 = -1;
static gint ett_lte_rrc_HandoverPreparationInformation = -1;
static gint ett_lte_rrc_T_criticalExtensions_31 = -1;
static gint ett_lte_rrc_T_c1_27 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_31 = -1;
static gint ett_lte_rrc_HandoverPreparationInformation_r8_IEs = -1;
static gint ett_lte_rrc_HandoverPreparationInformation_v920_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_34 = -1;
static gint ett_lte_rrc_UERadioAccessCapabilityInformation = -1;
static gint ett_lte_rrc_T_criticalExtensions_32 = -1;
static gint ett_lte_rrc_T_c1_28 = -1;
static gint ett_lte_rrc_T_criticalExtensionsFuture_32 = -1;
static gint ett_lte_rrc_UERadioAccessCapabilityInformation_r8_IEs = -1;
static gint ett_lte_rrc_T_nonCriticalExtension_35 = -1;
static gint ett_lte_rrc_AS_Config = -1;
static gint ett_lte_rrc_AS_Context = -1;
static gint ett_lte_rrc_ReestablishmentInfo = -1;
static gint ett_lte_rrc_AdditionalReestabInfoList = -1;
static gint ett_lte_rrc_AdditionalReestabInfo = -1;
static gint ett_lte_rrc_RRM_Config = -1;

/*--- End of included file: packet-lte-rrc-ett.c ---*/
#line 62 "packet-lte-rrc-template.c"

/* Forward declarations */
static int dissect_DL_DCCH_Message_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_);
static int dissect_UECapabilityInformation_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_);
static int dissect_UE_EUTRA_Capability_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_);

/*--- Included file: packet-lte-rrc-fn.c ---*/
#line 1 "packet-lte-rrc-fn.c"
/*--- PDUs declarations ---*/
static int dissect_SystemInformationBlockType1_v890_IEs_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_);


static const value_string lte_rrc_T_dl_Bandwidth_vals[] = {
  {   0, "n6" },
  {   1, "n15" },
  {   2, "n25" },
  {   3, "n50" },
  {   4, "n75" },
  {   5, "n100" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_dl_Bandwidth(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     6, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_phich_Duration_vals[] = {
  {   0, "normal" },
  {   1, "extended" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_phich_Duration(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_phich_Resource_vals[] = {
  {   0, "oneSixth" },
  {   1, "half" },
  {   2, "one" },
  {   3, "two" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_phich_Resource(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t PHICH_Config_sequence[] = {
  { &hf_lte_rrc_phich_Duration, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_phich_Duration },
  { &hf_lte_rrc_phich_Resource, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_phich_Resource },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_PHICH_Config(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_PHICH_Config, PHICH_Config_sequence);

  return offset;
}



static int
dissect_lte_rrc_BIT_STRING_SIZE_8(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     8, 8, FALSE, NULL);

  return offset;
}



static int
dissect_lte_rrc_BIT_STRING_SIZE_10(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     10, 10, FALSE, NULL);

  return offset;
}


static const per_sequence_t MasterInformationBlock_sequence[] = {
  { &hf_lte_rrc_dl_Bandwidth, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_dl_Bandwidth },
  { &hf_lte_rrc_phich_Config, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PHICH_Config },
  { &hf_lte_rrc_systemFrameNumber, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_8 },
  { &hf_lte_rrc_spare       , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_10 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MasterInformationBlock(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ*/
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:MasterInformationBlock ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MasterInformationBlock, MasterInformationBlock_sequence);

  return offset;
}



static int
dissect_lte_rrc_BCCH_BCH_MessageType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_lte_rrc_MasterInformationBlock(tvb, offset, actx, tree, hf_index);

  return offset;
}


static const per_sequence_t BCCH_BCH_Message_sequence[] = {
  { &hf_lte_rrc_message     , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BCCH_BCH_MessageType },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_BCCH_BCH_Message(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_BCCH_BCH_Message, BCCH_BCH_Message_sequence);

  return offset;
}



static int
dissect_lte_rrc_BOOLEAN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_boolean(tvb, offset, actx, tree, hf_index, NULL);

  return offset;
}


static const value_string lte_rrc_T_ac_BarringFactor_vals[] = {
  {   0, "p00" },
  {   1, "p05" },
  {   2, "p10" },
  {   3, "p15" },
  {   4, "p20" },
  {   5, "p25" },
  {   6, "p30" },
  {   7, "p40" },
  {   8, "p50" },
  {   9, "p60" },
  {  10, "p70" },
  {  11, "p75" },
  {  12, "p80" },
  {  13, "p85" },
  {  14, "p90" },
  {  15, "p95" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_ac_BarringFactor(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_ac_BarringTime_vals[] = {
  {   0, "s4" },
  {   1, "s8" },
  {   2, "s16" },
  {   3, "s32" },
  {   4, "s64" },
  {   5, "s128" },
  {   6, "s256" },
  {   7, "s512" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_ac_BarringTime(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}



static int
dissect_lte_rrc_BIT_STRING_SIZE_5(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     5, 5, FALSE, NULL);

  return offset;
}


static const per_sequence_t AC_BarringConfig_sequence[] = {
  { &hf_lte_rrc_ac_BarringFactor, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_ac_BarringFactor },
  { &hf_lte_rrc_ac_BarringTime, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_ac_BarringTime },
  { &hf_lte_rrc_ac_BarringForSpecialAC, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_5 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_AC_BarringConfig(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_AC_BarringConfig, AC_BarringConfig_sequence);

  return offset;
}


static const per_sequence_t T_ac_BarringInfo_sequence[] = {
  { &hf_lte_rrc_ac_BarringForEmergency, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_ac_BarringForMO_Signalling, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_AC_BarringConfig },
  { &hf_lte_rrc_ac_BarringForMO_Data, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_AC_BarringConfig },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_ac_BarringInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_ac_BarringInfo, T_ac_BarringInfo_sequence);

  return offset;
}


static const value_string lte_rrc_T_numberOfRA_Preambles_vals[] = {
  {   0, "n4" },
  {   1, "n8" },
  {   2, "n12" },
  {   3, "n16" },
  {   4, "n20" },
  {   5, "n24" },
  {   6, "n28" },
  {   7, "n32" },
  {   8, "n36" },
  {   9, "n40" },
  {  10, "n44" },
  {  11, "n48" },
  {  12, "n52" },
  {  13, "n56" },
  {  14, "n60" },
  {  15, "n64" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_numberOfRA_Preambles(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_sizeOfRA_PreamblesGroupA_vals[] = {
  {   0, "n4" },
  {   1, "n8" },
  {   2, "n12" },
  {   3, "n16" },
  {   4, "n20" },
  {   5, "n24" },
  {   6, "n28" },
  {   7, "n32" },
  {   8, "n36" },
  {   9, "n40" },
  {  10, "n44" },
  {  11, "n48" },
  {  12, "n52" },
  {  13, "n56" },
  {  14, "n60" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_sizeOfRA_PreamblesGroupA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     15, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_messageSizeGroupA_vals[] = {
  {   0, "b56" },
  {   1, "b144" },
  {   2, "b208" },
  {   3, "b256" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_messageSizeGroupA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_messagePowerOffsetGroupB_vals[] = {
  {   0, "minusinfinity" },
  {   1, "dB0" },
  {   2, "dB5" },
  {   3, "dB8" },
  {   4, "dB10" },
  {   5, "dB12" },
  {   6, "dB15" },
  {   7, "dB18" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_messagePowerOffsetGroupB(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t T_preamblesGroupAConfig_sequence[] = {
  { &hf_lte_rrc_sizeOfRA_PreamblesGroupA, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_sizeOfRA_PreamblesGroupA },
  { &hf_lte_rrc_messageSizeGroupA, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_messageSizeGroupA },
  { &hf_lte_rrc_messagePowerOffsetGroupB, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_messagePowerOffsetGroupB },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_preamblesGroupAConfig(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_preamblesGroupAConfig, T_preamblesGroupAConfig_sequence);

  return offset;
}


static const per_sequence_t T_preambleInfo_sequence[] = {
  { &hf_lte_rrc_numberOfRA_Preambles, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_numberOfRA_Preambles },
  { &hf_lte_rrc_preamblesGroupAConfig, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_preamblesGroupAConfig },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_preambleInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_preambleInfo, T_preambleInfo_sequence);

  return offset;
}


static const value_string lte_rrc_T_powerRampingStep_vals[] = {
  {   0, "dB0" },
  {   1, "dB2" },
  {   2, "dB4" },
  {   3, "dB6" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_powerRampingStep(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_preambleInitialReceivedTargetPower_vals[] = {
  {   0, "dBm-120" },
  {   1, "dBm-118" },
  {   2, "dBm-116" },
  {   3, "dBm-114" },
  {   4, "dBm-112" },
  {   5, "dBm-110" },
  {   6, "dBm-108" },
  {   7, "dBm-106" },
  {   8, "dBm-104" },
  {   9, "dBm-102" },
  {  10, "dBm-100" },
  {  11, "dBm-98" },
  {  12, "dBm-96" },
  {  13, "dBm-94" },
  {  14, "dBm-92" },
  {  15, "dBm-90" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_preambleInitialReceivedTargetPower(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t T_powerRampingParameters_sequence[] = {
  { &hf_lte_rrc_powerRampingStep, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_powerRampingStep },
  { &hf_lte_rrc_preambleInitialReceivedTargetPower, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_preambleInitialReceivedTargetPower },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_powerRampingParameters(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_powerRampingParameters, T_powerRampingParameters_sequence);

  return offset;
}


static const value_string lte_rrc_T_preambleTransMax_vals[] = {
  {   0, "n3" },
  {   1, "n4" },
  {   2, "n5" },
  {   3, "n6" },
  {   4, "n7" },
  {   5, "n8" },
  {   6, "n10" },
  {   7, "n20" },
  {   8, "n50" },
  {   9, "n100" },
  {  10, "n200" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_preambleTransMax(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     11, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_ra_ResponseWindowSize_vals[] = {
  {   0, "sf2" },
  {   1, "sf3" },
  {   2, "sf4" },
  {   3, "sf5" },
  {   4, "sf6" },
  {   5, "sf7" },
  {   6, "sf8" },
  {   7, "sf10" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_ra_ResponseWindowSize(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_mac_ContentionResolutionTimer_vals[] = {
  {   0, "sf8" },
  {   1, "sf16" },
  {   2, "sf24" },
  {   3, "sf32" },
  {   4, "sf40" },
  {   5, "sf48" },
  {   6, "sf56" },
  {   7, "sf64" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_mac_ContentionResolutionTimer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t T_ra_SupervisionInfo_sequence[] = {
  { &hf_lte_rrc_preambleTransMax, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_preambleTransMax },
  { &hf_lte_rrc_ra_ResponseWindowSize, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_ra_ResponseWindowSize },
  { &hf_lte_rrc_mac_ContentionResolutionTimer, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_mac_ContentionResolutionTimer },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_ra_SupervisionInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_ra_SupervisionInfo, T_ra_SupervisionInfo_sequence);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_1_8(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, 8U, NULL, FALSE);

  return offset;
}


static const per_sequence_t RACH_ConfigCommon_sequence[] = {
  { &hf_lte_rrc_preambleInfo, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_preambleInfo },
  { &hf_lte_rrc_powerRampingParameters, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_powerRampingParameters },
  { &hf_lte_rrc_ra_SupervisionInfo, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_ra_SupervisionInfo },
  { &hf_lte_rrc_maxHARQ_Msg3Tx, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_1_8 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RACH_ConfigCommon(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RACH_ConfigCommon, RACH_ConfigCommon_sequence);

  return offset;
}


static const value_string lte_rrc_T_modificationPeriodCoeff_vals[] = {
  {   0, "n2" },
  {   1, "n4" },
  {   2, "n8" },
  {   3, "n16" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_modificationPeriodCoeff(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t BCCH_Config_sequence[] = {
  { &hf_lte_rrc_modificationPeriodCoeff, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_modificationPeriodCoeff },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_BCCH_Config(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_BCCH_Config, BCCH_Config_sequence);

  return offset;
}


static const value_string lte_rrc_T_defaultPagingCycle_vals[] = {
  {   0, "rf32" },
  {   1, "rf64" },
  {   2, "rf128" },
  {   3, "rf256" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_defaultPagingCycle(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_nB_vals[] = {
  {   0, "fourT" },
  {   1, "twoT" },
  {   2, "oneT" },
  {   3, "halfT" },
  {   4, "quarterT" },
  {   5, "oneEighthT" },
  {   6, "oneSixteenthT" },
  {   7, "oneThirtySecondT" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_nB(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t PCCH_Config_sequence[] = {
  { &hf_lte_rrc_defaultPagingCycle, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_defaultPagingCycle },
  { &hf_lte_rrc_nB          , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_nB },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_PCCH_Config(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_PCCH_Config, PCCH_Config_sequence);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_837(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 837U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_63(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 63U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_15(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 15U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_94(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 94U, NULL, FALSE);

  return offset;
}


static const per_sequence_t PRACH_ConfigInfo_sequence[] = {
  { &hf_lte_rrc_prach_ConfigIndex, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_63 },
  { &hf_lte_rrc_highSpeedFlag, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_zeroCorrelationZoneConfig, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_15 },
  { &hf_lte_rrc_prach_FreqOffset, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_94 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_PRACH_ConfigInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_PRACH_ConfigInfo, PRACH_ConfigInfo_sequence);

  return offset;
}


static const per_sequence_t PRACH_ConfigSIB_sequence[] = {
  { &hf_lte_rrc_rootSequenceIndex, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_837 },
  { &hf_lte_rrc_prach_ConfigInfo, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PRACH_ConfigInfo },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_PRACH_ConfigSIB(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_PRACH_ConfigSIB, PRACH_ConfigSIB_sequence);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_M60_50(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            -60, 50U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_3(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 3U, NULL, FALSE);

  return offset;
}


static const per_sequence_t PDSCH_ConfigCommon_sequence[] = {
  { &hf_lte_rrc_referenceSignalPower, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_M60_50 },
  { &hf_lte_rrc_p_b         , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_3 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_PDSCH_ConfigCommon(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_PDSCH_ConfigCommon, PDSCH_ConfigCommon_sequence);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_1_4(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, 4U, NULL, FALSE);

  return offset;
}


static const value_string lte_rrc_T_hoppingMode_vals[] = {
  {   0, "interSubFrame" },
  {   1, "intraAndInterSubFrame" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_hoppingMode(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_98(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 98U, NULL, FALSE);

  return offset;
}


static const per_sequence_t T_pusch_ConfigBasic_sequence[] = {
  { &hf_lte_rrc_n_SB        , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_1_4 },
  { &hf_lte_rrc_hoppingMode , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_hoppingMode },
  { &hf_lte_rrc_pusch_HoppingOffset, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_98 },
  { &hf_lte_rrc_enable64QAM , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_pusch_ConfigBasic(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_pusch_ConfigBasic, T_pusch_ConfigBasic_sequence);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_29(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 29U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_7(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 7U, NULL, FALSE);

  return offset;
}


static const per_sequence_t UL_ReferenceSignalsPUSCH_sequence[] = {
  { &hf_lte_rrc_groupHoppingEnabled, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_groupAssignmentPUSCH, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_29 },
  { &hf_lte_rrc_sequenceHoppingEnabled, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_cyclicShift , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_7 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_UL_ReferenceSignalsPUSCH(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_UL_ReferenceSignalsPUSCH, UL_ReferenceSignalsPUSCH_sequence);

  return offset;
}


static const per_sequence_t PUSCH_ConfigCommon_sequence[] = {
  { &hf_lte_rrc_pusch_ConfigBasic, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_pusch_ConfigBasic },
  { &hf_lte_rrc_ul_ReferenceSignalsPUSCH, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_UL_ReferenceSignalsPUSCH },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_PUSCH_ConfigCommon(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_PUSCH_ConfigCommon, PUSCH_ConfigCommon_sequence);

  return offset;
}


static const value_string lte_rrc_T_deltaPUCCH_Shift_vals[] = {
  {   0, "ds1" },
  {   1, "ds2" },
  {   2, "ds3" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_deltaPUCCH_Shift(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     3, NULL, FALSE, 0, NULL);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_2047(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 2047U, NULL, FALSE);

  return offset;
}


static const per_sequence_t PUCCH_ConfigCommon_sequence[] = {
  { &hf_lte_rrc_deltaPUCCH_Shift, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_deltaPUCCH_Shift },
  { &hf_lte_rrc_nRB_CQI     , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_98 },
  { &hf_lte_rrc_nCS_AN      , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_7 },
  { &hf_lte_rrc_n1PUCCH_AN  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_2047 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_PUCCH_ConfigCommon(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_PUCCH_ConfigCommon, PUCCH_ConfigCommon_sequence);

  return offset;
}



static int
dissect_lte_rrc_NULL(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_null(tvb, offset, actx, tree, hf_index);

  return offset;
}


static const value_string lte_rrc_T_srs_BandwidthConfig_vals[] = {
  {   0, "bw0" },
  {   1, "bw1" },
  {   2, "bw2" },
  {   3, "bw3" },
  {   4, "bw4" },
  {   5, "bw5" },
  {   6, "bw6" },
  {   7, "bw7" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_srs_BandwidthConfig(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_srs_SubframeConfig_vals[] = {
  {   0, "sc0" },
  {   1, "sc1" },
  {   2, "sc2" },
  {   3, "sc3" },
  {   4, "sc4" },
  {   5, "sc5" },
  {   6, "sc6" },
  {   7, "sc7" },
  {   8, "sc8" },
  {   9, "sc9" },
  {  10, "sc10" },
  {  11, "sc11" },
  {  12, "sc12" },
  {  13, "sc13" },
  {  14, "sc14" },
  {  15, "sc15" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_srs_SubframeConfig(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_srs_MaxUpPts_vals[] = {
  {   0, "true" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_srs_MaxUpPts(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t T_setup_07_sequence[] = {
  { &hf_lte_rrc_srs_BandwidthConfig, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_srs_BandwidthConfig },
  { &hf_lte_rrc_srs_SubframeConfig, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_srs_SubframeConfig },
  { &hf_lte_rrc_ackNackSRS_SimultaneousTransmission, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_srs_MaxUpPts, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_srs_MaxUpPts },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_setup_07(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_setup_07, T_setup_07_sequence);

  return offset;
}


static const value_string lte_rrc_SoundingRS_UL_ConfigCommon_vals[] = {
  {   0, "release" },
  {   1, "setup" },
  { 0, NULL }
};

static const per_choice_t SoundingRS_UL_ConfigCommon_choice[] = {
  {   0, &hf_lte_rrc_release     , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   1, &hf_lte_rrc_setup_07    , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_setup_07 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_SoundingRS_UL_ConfigCommon(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_SoundingRS_UL_ConfigCommon, SoundingRS_UL_ConfigCommon_choice,
                                 NULL);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_M126_24(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            -126, 24U, NULL, FALSE);

  return offset;
}


static const value_string lte_rrc_T_alpha_vals[] = {
  {   0, "al0" },
  {   1, "al04" },
  {   2, "al05" },
  {   3, "al06" },
  {   4, "al07" },
  {   5, "al08" },
  {   6, "al09" },
  {   7, "al1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_alpha(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_M127_M96(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            -127, -96, NULL, FALSE);

  return offset;
}


static const value_string lte_rrc_T_deltaF_PUCCH_Format1_vals[] = {
  {   0, "deltaF-2" },
  {   1, "deltaF0" },
  {   2, "deltaF2" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_deltaF_PUCCH_Format1(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     3, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_deltaF_PUCCH_Format1b_vals[] = {
  {   0, "deltaF1" },
  {   1, "deltaF3" },
  {   2, "deltaF5" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_deltaF_PUCCH_Format1b(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     3, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_deltaF_PUCCH_Format2_vals[] = {
  {   0, "deltaF-2" },
  {   1, "deltaF0" },
  {   2, "deltaF1" },
  {   3, "deltaF2" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_deltaF_PUCCH_Format2(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_deltaF_PUCCH_Format2a_vals[] = {
  {   0, "deltaF-2" },
  {   1, "deltaF0" },
  {   2, "deltaF2" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_deltaF_PUCCH_Format2a(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     3, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_deltaF_PUCCH_Format2b_vals[] = {
  {   0, "deltaF-2" },
  {   1, "deltaF0" },
  {   2, "deltaF2" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_deltaF_PUCCH_Format2b(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     3, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t DeltaFList_PUCCH_sequence[] = {
  { &hf_lte_rrc_deltaF_PUCCH_Format1, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_deltaF_PUCCH_Format1 },
  { &hf_lte_rrc_deltaF_PUCCH_Format1b, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_deltaF_PUCCH_Format1b },
  { &hf_lte_rrc_deltaF_PUCCH_Format2, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_deltaF_PUCCH_Format2 },
  { &hf_lte_rrc_deltaF_PUCCH_Format2a, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_deltaF_PUCCH_Format2a },
  { &hf_lte_rrc_deltaF_PUCCH_Format2b, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_deltaF_PUCCH_Format2b },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_DeltaFList_PUCCH(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_DeltaFList_PUCCH, DeltaFList_PUCCH_sequence);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_M1_6(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            -1, 6U, NULL, FALSE);

  return offset;
}


static const per_sequence_t UplinkPowerControlCommon_sequence[] = {
  { &hf_lte_rrc_p0_NominalPUSCH, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_M126_24 },
  { &hf_lte_rrc_alpha       , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_alpha },
  { &hf_lte_rrc_p0_NominalPUCCH, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_M127_M96 },
  { &hf_lte_rrc_deltaFList_PUCCH, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_DeltaFList_PUCCH },
  { &hf_lte_rrc_deltaPreambleMsg3, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_M1_6 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_UplinkPowerControlCommon(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_UplinkPowerControlCommon, UplinkPowerControlCommon_sequence);

  return offset;
}


static const value_string lte_rrc_UL_CyclicPrefixLength_vals[] = {
  {   0, "len1" },
  {   1, "len2" },
  { 0, NULL }
};


static int
dissect_lte_rrc_UL_CyclicPrefixLength(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t RadioResourceConfigCommonSIB_sequence[] = {
  { &hf_lte_rrc_rach_ConfigCommon, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RACH_ConfigCommon },
  { &hf_lte_rrc_bcch_Config , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BCCH_Config },
  { &hf_lte_rrc_pcch_Config , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PCCH_Config },
  { &hf_lte_rrc_prach_Config, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PRACH_ConfigSIB },
  { &hf_lte_rrc_pdsch_ConfigCommon, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PDSCH_ConfigCommon },
  { &hf_lte_rrc_pusch_ConfigCommon, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PUSCH_ConfigCommon },
  { &hf_lte_rrc_pucch_ConfigCommon, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PUCCH_ConfigCommon },
  { &hf_lte_rrc_soundingRS_UL_ConfigCommon, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SoundingRS_UL_ConfigCommon },
  { &hf_lte_rrc_uplinkPowerControlCommon, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_UplinkPowerControlCommon },
  { &hf_lte_rrc_ul_CyclicPrefixLength, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_UL_CyclicPrefixLength },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RadioResourceConfigCommonSIB(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RadioResourceConfigCommonSIB, RadioResourceConfigCommonSIB_sequence);

  return offset;
}


static const value_string lte_rrc_T_t300_vals[] = {
  {   0, "ms100" },
  {   1, "ms200" },
  {   2, "ms300" },
  {   3, "ms400" },
  {   4, "ms600" },
  {   5, "ms1000" },
  {   6, "ms1500" },
  {   7, "ms2000" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_t300(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_t301_vals[] = {
  {   0, "ms100" },
  {   1, "ms200" },
  {   2, "ms300" },
  {   3, "ms400" },
  {   4, "ms600" },
  {   5, "ms1000" },
  {   6, "ms1500" },
  {   7, "ms2000" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_t301(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_t310_vals[] = {
  {   0, "ms0" },
  {   1, "ms50" },
  {   2, "ms100" },
  {   3, "ms200" },
  {   4, "ms500" },
  {   5, "ms1000" },
  {   6, "ms2000" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_t310(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     7, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_n310_vals[] = {
  {   0, "n1" },
  {   1, "n2" },
  {   2, "n3" },
  {   3, "n4" },
  {   4, "n6" },
  {   5, "n8" },
  {   6, "n10" },
  {   7, "n20" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_n310(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_t311_vals[] = {
  {   0, "ms1000" },
  {   1, "ms3000" },
  {   2, "ms5000" },
  {   3, "ms10000" },
  {   4, "ms15000" },
  {   5, "ms20000" },
  {   6, "ms30000" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_t311(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     7, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_n311_vals[] = {
  {   0, "n1" },
  {   1, "n2" },
  {   2, "n3" },
  {   3, "n4" },
  {   4, "n5" },
  {   5, "n6" },
  {   6, "n8" },
  {   7, "n10" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_n311(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t UE_TimersAndConstants_sequence[] = {
  { &hf_lte_rrc_t300        , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_t300 },
  { &hf_lte_rrc_t301        , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_t301 },
  { &hf_lte_rrc_t310        , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_t310 },
  { &hf_lte_rrc_n310        , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_n310 },
  { &hf_lte_rrc_t311        , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_t311 },
  { &hf_lte_rrc_n311        , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_n311 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_UE_TimersAndConstants(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_UE_TimersAndConstants, UE_TimersAndConstants_sequence);

  return offset;
}



static int
dissect_lte_rrc_ARFCN_ValueEUTRA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, maxEARFCN, NULL, FALSE);

  return offset;
}


static const value_string lte_rrc_T_ul_Bandwidth_vals[] = {
  {   0, "n6" },
  {   1, "n15" },
  {   2, "n25" },
  {   3, "n50" },
  {   4, "n75" },
  {   5, "n100" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_ul_Bandwidth(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     6, NULL, FALSE, 0, NULL);

  return offset;
}



static int
dissect_lte_rrc_AdditionalSpectrumEmission(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, 32U, NULL, FALSE);

  return offset;
}


static const per_sequence_t T_freqInfo_sequence[] = {
  { &hf_lte_rrc_ul_CarrierFreq, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_ARFCN_ValueEUTRA },
  { &hf_lte_rrc_ul_Bandwidth, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_ul_Bandwidth },
  { &hf_lte_rrc_additionalSpectrumEmission, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_AdditionalSpectrumEmission },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_freqInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_freqInfo, T_freqInfo_sequence);

  return offset;
}


static const value_string lte_rrc_T_radioframeAllocationPeriod_vals[] = {
  {   0, "n1" },
  {   1, "n2" },
  {   2, "n4" },
  {   3, "n8" },
  {   4, "n16" },
  {   5, "n32" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_radioframeAllocationPeriod(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     6, NULL, FALSE, 0, NULL);

  return offset;
}



static int
dissect_lte_rrc_BIT_STRING_SIZE_6(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     6, 6, FALSE, NULL);

  return offset;
}



static int
dissect_lte_rrc_BIT_STRING_SIZE_24(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     24, 24, FALSE, NULL);

  return offset;
}


static const value_string lte_rrc_T_subframeAllocation_vals[] = {
  {   0, "oneFrame" },
  {   1, "fourFrames" },
  { 0, NULL }
};

static const per_choice_t T_subframeAllocation_choice[] = {
  {   0, &hf_lte_rrc_oneFrame    , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_BIT_STRING_SIZE_6 },
  {   1, &hf_lte_rrc_fourFrames  , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_BIT_STRING_SIZE_24 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_subframeAllocation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_subframeAllocation, T_subframeAllocation_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t MBSFN_SubframeConfig_sequence[] = {
  { &hf_lte_rrc_radioframeAllocationPeriod, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_radioframeAllocationPeriod },
  { &hf_lte_rrc_radioframeAllocationOffset, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_7 },
  { &hf_lte_rrc_subframeAllocation, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_subframeAllocation },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MBSFN_SubframeConfig(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MBSFN_SubframeConfig, MBSFN_SubframeConfig_sequence);

  return offset;
}


static const per_sequence_t MBSFN_SubframeConfigList_sequence_of[1] = {
  { &hf_lte_rrc_MBSFN_SubframeConfigList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MBSFN_SubframeConfig },
};

static int
dissect_lte_rrc_MBSFN_SubframeConfigList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_MBSFN_SubframeConfigList, MBSFN_SubframeConfigList_sequence_of,
                                                  1, maxMBSFN_Allocations, FALSE);

  return offset;
}


static const value_string lte_rrc_TimeAlignmentTimer_vals[] = {
  {   0, "sf500" },
  {   1, "sf750" },
  {   2, "sf1280" },
  {   3, "sf1920" },
  {   4, "sf2560" },
  {   5, "sf5120" },
  {   6, "sf10240" },
  {   7, "infinity" },
  { 0, NULL }
};


static int
dissect_lte_rrc_TimeAlignmentTimer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}



static int
dissect_lte_rrc_OCTET_STRING(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, NULL);

  return offset;
}


static const per_sequence_t SystemInformationBlockType2_sequence[] = {
  { &hf_lte_rrc_ac_BarringInfo, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_T_ac_BarringInfo },
  { &hf_lte_rrc_radioResourceConfigCommon, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RadioResourceConfigCommonSIB },
  { &hf_lte_rrc_ue_TimersAndConstants, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_UE_TimersAndConstants },
  { &hf_lte_rrc_freqInfo    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_freqInfo },
  { &hf_lte_rrc_mbsfn_SubframeConfigList, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_MBSFN_SubframeConfigList },
  { &hf_lte_rrc_timeAlignmentTimerCommon, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_TimeAlignmentTimer },
  { &hf_lte_rrc_lateR8NonCriticalExtension, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_OCTET_STRING },
  { &hf_lte_rrc_ssac_BarringForMMTEL_Voice_r9, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_AC_BarringConfig },
  { &hf_lte_rrc_ssac_BarringForMMTEL_Video_r9, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_AC_BarringConfig },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SystemInformationBlockType2(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SystemInformationBlockType2, SystemInformationBlockType2_sequence);

  return offset;
}


static const value_string lte_rrc_T_q_Hyst_vals[] = {
  {   0, "dB0" },
  {   1, "dB1" },
  {   2, "dB2" },
  {   3, "dB3" },
  {   4, "dB4" },
  {   5, "dB5" },
  {   6, "dB6" },
  {   7, "dB8" },
  {   8, "dB10" },
  {   9, "dB12" },
  {  10, "dB14" },
  {  11, "dB16" },
  {  12, "dB18" },
  {  13, "dB20" },
  {  14, "dB22" },
  {  15, "dB24" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_q_Hyst(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_t_Evaluation_vals[] = {
  {   0, "s30" },
  {   1, "s60" },
  {   2, "s120" },
  {   3, "s180" },
  {   4, "s240" },
  {   5, "spare3" },
  {   6, "spare2" },
  {   7, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_t_Evaluation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_t_HystNormal_vals[] = {
  {   0, "s30" },
  {   1, "s60" },
  {   2, "s120" },
  {   3, "s180" },
  {   4, "s240" },
  {   5, "spare3" },
  {   6, "spare2" },
  {   7, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_t_HystNormal(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_1_16(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, 16U, NULL, FALSE);

  return offset;
}


static const per_sequence_t MobilityStateParameters_sequence[] = {
  { &hf_lte_rrc_t_Evaluation, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_t_Evaluation },
  { &hf_lte_rrc_t_HystNormal, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_t_HystNormal },
  { &hf_lte_rrc_n_CellChangeMedium, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_1_16 },
  { &hf_lte_rrc_n_CellChangeHigh, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_1_16 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MobilityStateParameters(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MobilityStateParameters, MobilityStateParameters_sequence);

  return offset;
}


static const value_string lte_rrc_T_sf_Medium_vals[] = {
  {   0, "dB-6" },
  {   1, "dB-4" },
  {   2, "dB-2" },
  {   3, "dB0" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_sf_Medium(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_sf_High_vals[] = {
  {   0, "dB-6" },
  {   1, "dB-4" },
  {   2, "dB-2" },
  {   3, "dB0" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_sf_High(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t T_q_HystSF_sequence[] = {
  { &hf_lte_rrc_sf_Medium   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_sf_Medium },
  { &hf_lte_rrc_sf_High     , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_sf_High },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_q_HystSF(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_q_HystSF, T_q_HystSF_sequence);

  return offset;
}


static const per_sequence_t T_speedStateReselectionPars_sequence[] = {
  { &hf_lte_rrc_mobilityStateParameters, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MobilityStateParameters },
  { &hf_lte_rrc_q_HystSF    , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_q_HystSF },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_speedStateReselectionPars(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_speedStateReselectionPars, T_speedStateReselectionPars_sequence);

  return offset;
}


static const per_sequence_t T_cellReselectionInfoCommon_sequence[] = {
  { &hf_lte_rrc_q_Hyst      , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_q_Hyst },
  { &hf_lte_rrc_speedStateReselectionPars, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_speedStateReselectionPars },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_cellReselectionInfoCommon(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_cellReselectionInfoCommon, T_cellReselectionInfoCommon_sequence);

  return offset;
}



static int
dissect_lte_rrc_ReselectionThreshold(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 31U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_CellReselectionPriority(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 7U, NULL, FALSE);

  return offset;
}


static const per_sequence_t T_cellReselectionServingFreqInfo_sequence[] = {
  { &hf_lte_rrc_s_NonIntraSearch, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_ReselectionThreshold },
  { &hf_lte_rrc_threshServingLow, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ReselectionThreshold },
  { &hf_lte_rrc_cellReselectionPriority, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CellReselectionPriority },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_cellReselectionServingFreqInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_cellReselectionServingFreqInfo, T_cellReselectionServingFreqInfo_sequence);

  return offset;
}



static int
dissect_lte_rrc_Q_RxLevMin(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            -70, -22, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_P_Max(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            -30, 33U, NULL, FALSE);

  return offset;
}


static const value_string lte_rrc_AllowedMeasBandwidth_vals[] = {
  {   0, "mbw6" },
  {   1, "mbw15" },
  {   2, "mbw25" },
  {   3, "mbw50" },
  {   4, "mbw75" },
  {   5, "mbw100" },
  { 0, NULL }
};


static int
dissect_lte_rrc_AllowedMeasBandwidth(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     6, NULL, FALSE, 0, NULL);

  return offset;
}



static int
dissect_lte_rrc_PresenceAntennaPort1(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_boolean(tvb, offset, actx, tree, hf_index, NULL);

  return offset;
}



static int
dissect_lte_rrc_NeighCellConfig(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     2, 2, FALSE, NULL);

  return offset;
}



static int
dissect_lte_rrc_T_Reselection(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 7U, NULL, FALSE);

  return offset;
}


static const value_string lte_rrc_T_sf_Medium_01_vals[] = {
  {   0, "oDot25" },
  {   1, "oDot5" },
  {   2, "oDot75" },
  {   3, "lDot0" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_sf_Medium_01(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_sf_High_01_vals[] = {
  {   0, "oDot25" },
  {   1, "oDot5" },
  {   2, "oDot75" },
  {   3, "lDot0" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_sf_High_01(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t SpeedStateScaleFactors_sequence[] = {
  { &hf_lte_rrc_sf_Medium_01, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_sf_Medium_01 },
  { &hf_lte_rrc_sf_High_01  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_sf_High_01 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SpeedStateScaleFactors(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SpeedStateScaleFactors, SpeedStateScaleFactors_sequence);

  return offset;
}


static const per_sequence_t T_intraFreqCellReselectionInfo_sequence[] = {
  { &hf_lte_rrc_q_RxLevMin  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_Q_RxLevMin },
  { &hf_lte_rrc_p_Max       , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_P_Max },
  { &hf_lte_rrc_s_IntraSearch, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_ReselectionThreshold },
  { &hf_lte_rrc_allowedMeasBandwidth, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_AllowedMeasBandwidth },
  { &hf_lte_rrc_presenceAntennaPort1, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PresenceAntennaPort1 },
  { &hf_lte_rrc_neighCellConfig, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_NeighCellConfig },
  { &hf_lte_rrc_t_ReselectionEUTRA, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_Reselection },
  { &hf_lte_rrc_t_ReselectionEUTRA_SF, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_SpeedStateScaleFactors },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_intraFreqCellReselectionInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_intraFreqCellReselectionInfo, T_intraFreqCellReselectionInfo_sequence);

  return offset;
}



static int
dissect_lte_rrc_ReselectionThresholdQ_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 31U, NULL, FALSE);

  return offset;
}


static const per_sequence_t T_s_IntraSearch_v920_sequence[] = {
  { &hf_lte_rrc_s_IntraSearchP_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ReselectionThreshold },
  { &hf_lte_rrc_s_IntraSearchQ_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ReselectionThresholdQ_r9 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_s_IntraSearch_v920(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_s_IntraSearch_v920, T_s_IntraSearch_v920_sequence);

  return offset;
}


static const per_sequence_t T_s_NonIntraSearch_v920_sequence[] = {
  { &hf_lte_rrc_s_NonIntraSearchP_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ReselectionThreshold },
  { &hf_lte_rrc_s_NonIntraSearchQ_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ReselectionThresholdQ_r9 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_s_NonIntraSearch_v920(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_s_NonIntraSearch_v920, T_s_NonIntraSearch_v920_sequence);

  return offset;
}



static int
dissect_lte_rrc_Q_QualMin_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            -34, -3, NULL, FALSE);

  return offset;
}


static const per_sequence_t SystemInformationBlockType3_sequence[] = {
  { &hf_lte_rrc_cellReselectionInfoCommon, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_cellReselectionInfoCommon },
  { &hf_lte_rrc_cellReselectionServingFreqInfo, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_cellReselectionServingFreqInfo },
  { &hf_lte_rrc_intraFreqCellReselectionInfo, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_intraFreqCellReselectionInfo },
  { &hf_lte_rrc_lateR8NonCriticalExtension, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_OCTET_STRING },
  { &hf_lte_rrc_s_IntraSearch_v920, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_T_s_IntraSearch_v920 },
  { &hf_lte_rrc_s_NonIntraSearch_v920, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_T_s_NonIntraSearch_v920 },
  { &hf_lte_rrc_q_QualMin_r9, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_Q_QualMin_r9 },
  { &hf_lte_rrc_threshServingLowQ_r9, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_ReselectionThresholdQ_r9 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SystemInformationBlockType3(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SystemInformationBlockType3, SystemInformationBlockType3_sequence);

  return offset;
}



static int
dissect_lte_rrc_PhysCellId(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 503U, NULL, FALSE);

  return offset;
}


static const value_string lte_rrc_Q_OffsetRange_vals[] = {
  {   0, "dB-24" },
  {   1, "dB-22" },
  {   2, "dB-20" },
  {   3, "dB-18" },
  {   4, "dB-16" },
  {   5, "dB-14" },
  {   6, "dB-12" },
  {   7, "dB-10" },
  {   8, "dB-8" },
  {   9, "dB-6" },
  {  10, "dB-5" },
  {  11, "dB-4" },
  {  12, "dB-3" },
  {  13, "dB-2" },
  {  14, "dB-1" },
  {  15, "dB0" },
  {  16, "dB1" },
  {  17, "dB2" },
  {  18, "dB3" },
  {  19, "dB4" },
  {  20, "dB5" },
  {  21, "dB6" },
  {  22, "dB8" },
  {  23, "dB10" },
  {  24, "dB12" },
  {  25, "dB14" },
  {  26, "dB16" },
  {  27, "dB18" },
  {  28, "dB20" },
  {  29, "dB22" },
  {  30, "dB24" },
  { 0, NULL }
};


static int
dissect_lte_rrc_Q_OffsetRange(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     31, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t IntraFreqNeighCellInfo_sequence[] = {
  { &hf_lte_rrc_physCellId_01, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhysCellId },
  { &hf_lte_rrc_q_OffsetCell, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_Q_OffsetRange },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_IntraFreqNeighCellInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_IntraFreqNeighCellInfo, IntraFreqNeighCellInfo_sequence);

  return offset;
}


static const per_sequence_t IntraFreqNeighCellList_sequence_of[1] = {
  { &hf_lte_rrc_IntraFreqNeighCellList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_IntraFreqNeighCellInfo },
};

static int
dissect_lte_rrc_IntraFreqNeighCellList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_IntraFreqNeighCellList, IntraFreqNeighCellList_sequence_of,
                                                  1, maxCellIntra, FALSE);

  return offset;
}


static const value_string lte_rrc_T_range_vals[] = {
  {   0, "n4" },
  {   1, "n8" },
  {   2, "n12" },
  {   3, "n16" },
  {   4, "n24" },
  {   5, "n32" },
  {   6, "n48" },
  {   7, "n64" },
  {   8, "n84" },
  {   9, "n96" },
  {  10, "n128" },
  {  11, "n168" },
  {  12, "n252" },
  {  13, "n504" },
  {  14, "spare2" },
  {  15, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_range(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t PhysCellIdRange_sequence[] = {
  { &hf_lte_rrc_start       , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhysCellId },
  { &hf_lte_rrc_range       , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_range },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_PhysCellIdRange(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_PhysCellIdRange, PhysCellIdRange_sequence);

  return offset;
}


static const per_sequence_t IntraFreqBlackCellList_sequence_of[1] = {
  { &hf_lte_rrc_IntraFreqBlackCellList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhysCellIdRange },
};

static int
dissect_lte_rrc_IntraFreqBlackCellList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_IntraFreqBlackCellList, IntraFreqBlackCellList_sequence_of,
                                                  1, maxCellBlack, FALSE);

  return offset;
}


static const per_sequence_t SystemInformationBlockType4_sequence[] = {
  { &hf_lte_rrc_intraFreqNeighCellList, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_IntraFreqNeighCellList },
  { &hf_lte_rrc_intraFreqBlackCellList, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_IntraFreqBlackCellList },
  { &hf_lte_rrc_csg_PhysCellIdRange, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_PhysCellIdRange },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SystemInformationBlockType4(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SystemInformationBlockType4, SystemInformationBlockType4_sequence);

  return offset;
}


static const per_sequence_t InterFreqNeighCellInfo_sequence[] = {
  { &hf_lte_rrc_physCellId_01, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhysCellId },
  { &hf_lte_rrc_q_OffsetCell, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_Q_OffsetRange },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_InterFreqNeighCellInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_InterFreqNeighCellInfo, InterFreqNeighCellInfo_sequence);

  return offset;
}


static const per_sequence_t InterFreqNeighCellList_sequence_of[1] = {
  { &hf_lte_rrc_InterFreqNeighCellList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_InterFreqNeighCellInfo },
};

static int
dissect_lte_rrc_InterFreqNeighCellList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_InterFreqNeighCellList, InterFreqNeighCellList_sequence_of,
                                                  1, maxCellInter, FALSE);

  return offset;
}


static const per_sequence_t InterFreqBlackCellList_sequence_of[1] = {
  { &hf_lte_rrc_InterFreqBlackCellList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhysCellIdRange },
};

static int
dissect_lte_rrc_InterFreqBlackCellList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_InterFreqBlackCellList, InterFreqBlackCellList_sequence_of,
                                                  1, maxCellBlack, FALSE);

  return offset;
}


static const per_sequence_t T_threshX_Q_r9_sequence[] = {
  { &hf_lte_rrc_threshX_HighQ_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ReselectionThresholdQ_r9 },
  { &hf_lte_rrc_threshX_LowQ_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ReselectionThresholdQ_r9 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_threshX_Q_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_threshX_Q_r9, T_threshX_Q_r9_sequence);

  return offset;
}


static const per_sequence_t InterFreqCarrierFreqInfo_sequence[] = {
  { &hf_lte_rrc_dl_CarrierFreq, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ARFCN_ValueEUTRA },
  { &hf_lte_rrc_q_RxLevMin  , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_Q_RxLevMin },
  { &hf_lte_rrc_p_Max       , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_P_Max },
  { &hf_lte_rrc_t_ReselectionEUTRA, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_Reselection },
  { &hf_lte_rrc_t_ReselectionEUTRA_SF, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_SpeedStateScaleFactors },
  { &hf_lte_rrc_threshX_High, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ReselectionThreshold },
  { &hf_lte_rrc_threshX_Low , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ReselectionThreshold },
  { &hf_lte_rrc_allowedMeasBandwidth, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_AllowedMeasBandwidth },
  { &hf_lte_rrc_presenceAntennaPort1, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PresenceAntennaPort1 },
  { &hf_lte_rrc_cellReselectionPriority, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_CellReselectionPriority },
  { &hf_lte_rrc_neighCellConfig, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_NeighCellConfig },
  { &hf_lte_rrc_q_OffsetFreq, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_Q_OffsetRange },
  { &hf_lte_rrc_interFreqNeighCellList, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_InterFreqNeighCellList },
  { &hf_lte_rrc_interFreqBlackCellList, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_InterFreqBlackCellList },
  { &hf_lte_rrc_q_QualMin_r9, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_Q_QualMin_r9 },
  { &hf_lte_rrc_threshX_Q_r9, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_T_threshX_Q_r9 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_InterFreqCarrierFreqInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_InterFreqCarrierFreqInfo, InterFreqCarrierFreqInfo_sequence);

  return offset;
}


static const per_sequence_t InterFreqCarrierFreqList_sequence_of[1] = {
  { &hf_lte_rrc_InterFreqCarrierFreqList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_InterFreqCarrierFreqInfo },
};

static int
dissect_lte_rrc_InterFreqCarrierFreqList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_InterFreqCarrierFreqList, InterFreqCarrierFreqList_sequence_of,
                                                  1, maxFreq, FALSE);

  return offset;
}


static const per_sequence_t SystemInformationBlockType5_sequence[] = {
  { &hf_lte_rrc_interFreqCarrierFreqList, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_InterFreqCarrierFreqList },
  { &hf_lte_rrc_lateR8NonCriticalExtension, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_OCTET_STRING },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SystemInformationBlockType5(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SystemInformationBlockType5, SystemInformationBlockType5_sequence);

  return offset;
}



static int
dissect_lte_rrc_ARFCN_ValueUTRA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 16383U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_M60_M13(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            -60, -13, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_M50_33(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            -50, 33U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_M24_0(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            -24, 0U, NULL, FALSE);

  return offset;
}


static const per_sequence_t T_threshX_Q_r9_01_sequence[] = {
  { &hf_lte_rrc_threshX_HighQ_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ReselectionThresholdQ_r9 },
  { &hf_lte_rrc_threshX_LowQ_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ReselectionThresholdQ_r9 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_threshX_Q_r9_01(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_threshX_Q_r9_01, T_threshX_Q_r9_01_sequence);

  return offset;
}


static const per_sequence_t CarrierFreqUTRA_FDD_sequence[] = {
  { &hf_lte_rrc_carrierFreq_02, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ARFCN_ValueUTRA },
  { &hf_lte_rrc_cellReselectionPriority, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_CellReselectionPriority },
  { &hf_lte_rrc_threshX_High, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ReselectionThreshold },
  { &hf_lte_rrc_threshX_Low , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ReselectionThreshold },
  { &hf_lte_rrc_q_RxLevMin_01, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_M60_M13 },
  { &hf_lte_rrc_p_MaxUTRA   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_M50_33 },
  { &hf_lte_rrc_q_QualMin   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_M24_0 },
  { &hf_lte_rrc_threshX_Q_r9_01, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_T_threshX_Q_r9_01 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CarrierFreqUTRA_FDD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CarrierFreqUTRA_FDD, CarrierFreqUTRA_FDD_sequence);

  return offset;
}


static const per_sequence_t CarrierFreqListUTRA_FDD_sequence_of[1] = {
  { &hf_lte_rrc_CarrierFreqListUTRA_FDD_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CarrierFreqUTRA_FDD },
};

static int
dissect_lte_rrc_CarrierFreqListUTRA_FDD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_CarrierFreqListUTRA_FDD, CarrierFreqListUTRA_FDD_sequence_of,
                                                  1, maxUTRA_FDD_Carrier, FALSE);

  return offset;
}


static const per_sequence_t CarrierFreqUTRA_TDD_sequence[] = {
  { &hf_lte_rrc_carrierFreq_02, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ARFCN_ValueUTRA },
  { &hf_lte_rrc_cellReselectionPriority, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_CellReselectionPriority },
  { &hf_lte_rrc_threshX_High, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ReselectionThreshold },
  { &hf_lte_rrc_threshX_Low , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ReselectionThreshold },
  { &hf_lte_rrc_q_RxLevMin_01, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_M60_M13 },
  { &hf_lte_rrc_p_MaxUTRA   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_M50_33 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CarrierFreqUTRA_TDD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CarrierFreqUTRA_TDD, CarrierFreqUTRA_TDD_sequence);

  return offset;
}


static const per_sequence_t CarrierFreqListUTRA_TDD_sequence_of[1] = {
  { &hf_lte_rrc_CarrierFreqListUTRA_TDD_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CarrierFreqUTRA_TDD },
};

static int
dissect_lte_rrc_CarrierFreqListUTRA_TDD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_CarrierFreqListUTRA_TDD, CarrierFreqListUTRA_TDD_sequence_of,
                                                  1, maxUTRA_TDD_Carrier, FALSE);

  return offset;
}


static const per_sequence_t SystemInformationBlockType6_sequence[] = {
  { &hf_lte_rrc_carrierFreqListUTRA_FDD, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_CarrierFreqListUTRA_FDD },
  { &hf_lte_rrc_carrierFreqListUTRA_TDD, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_CarrierFreqListUTRA_TDD },
  { &hf_lte_rrc_t_ReselectionUTRA, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_Reselection },
  { &hf_lte_rrc_t_ReselectionUTRA_SF, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_SpeedStateScaleFactors },
  { &hf_lte_rrc_lateR8NonCriticalExtension, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_OCTET_STRING },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SystemInformationBlockType6(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SystemInformationBlockType6, SystemInformationBlockType6_sequence);

  return offset;
}



static int
dissect_lte_rrc_ARFCN_ValueGERAN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 1023U, NULL, FALSE);

  return offset;
}


static const value_string lte_rrc_BandIndicatorGERAN_vals[] = {
  {   0, "dcs1800" },
  {   1, "pcs1900" },
  { 0, NULL }
};


static int
dissect_lte_rrc_BandIndicatorGERAN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t ExplicitListOfARFCNs_sequence_of[1] = {
  { &hf_lte_rrc_ExplicitListOfARFCNs_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ARFCN_ValueGERAN },
};

static int
dissect_lte_rrc_ExplicitListOfARFCNs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_ExplicitListOfARFCNs, ExplicitListOfARFCNs_sequence_of,
                                                  0, 31, FALSE);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_31(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 31U, NULL, FALSE);

  return offset;
}


static const per_sequence_t T_equallySpacedARFCNs_sequence[] = {
  { &hf_lte_rrc_arfcn_Spacing, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_1_8 },
  { &hf_lte_rrc_numberOfFollowingARFCNs, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_31 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_equallySpacedARFCNs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_equallySpacedARFCNs, T_equallySpacedARFCNs_sequence);

  return offset;
}



static int
dissect_lte_rrc_OCTET_STRING_SIZE_1_16(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       1, 16, FALSE, NULL);

  return offset;
}


static const value_string lte_rrc_T_followingARFCNs_vals[] = {
  {   0, "explicitListOfARFCNs" },
  {   1, "equallySpacedARFCNs" },
  {   2, "variableBitMapOfARFCNs" },
  { 0, NULL }
};

static const per_choice_t T_followingARFCNs_choice[] = {
  {   0, &hf_lte_rrc_explicitListOfARFCNs, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_ExplicitListOfARFCNs },
  {   1, &hf_lte_rrc_equallySpacedARFCNs, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_equallySpacedARFCNs },
  {   2, &hf_lte_rrc_variableBitMapOfARFCNs, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_OCTET_STRING_SIZE_1_16 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_followingARFCNs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_followingARFCNs, T_followingARFCNs_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t CarrierFreqsGERAN_sequence[] = {
  { &hf_lte_rrc_startingARFCN, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ARFCN_ValueGERAN },
  { &hf_lte_rrc_bandIndicator, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BandIndicatorGERAN },
  { &hf_lte_rrc_followingARFCNs, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_followingARFCNs },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CarrierFreqsGERAN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CarrierFreqsGERAN, CarrierFreqsGERAN_sequence);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_45(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 45U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_39(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 39U, NULL, FALSE);

  return offset;
}


static const per_sequence_t T_commonInfo_sequence[] = {
  { &hf_lte_rrc_cellReselectionPriority, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_CellReselectionPriority },
  { &hf_lte_rrc_ncc_Permitted, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_8 },
  { &hf_lte_rrc_q_RxLevMin_02, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_45 },
  { &hf_lte_rrc_p_MaxGERAN  , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_INTEGER_0_39 },
  { &hf_lte_rrc_threshX_High, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ReselectionThreshold },
  { &hf_lte_rrc_threshX_Low , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ReselectionThreshold },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_commonInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_commonInfo, T_commonInfo_sequence);

  return offset;
}


static const per_sequence_t CarrierFreqsInfoGERAN_sequence[] = {
  { &hf_lte_rrc_carrierFreqs, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CarrierFreqsGERAN },
  { &hf_lte_rrc_commonInfo  , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_commonInfo },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CarrierFreqsInfoGERAN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CarrierFreqsInfoGERAN, CarrierFreqsInfoGERAN_sequence);

  return offset;
}


static const per_sequence_t CarrierFreqsInfoListGERAN_sequence_of[1] = {
  { &hf_lte_rrc_CarrierFreqsInfoListGERAN_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CarrierFreqsInfoGERAN },
};

static int
dissect_lte_rrc_CarrierFreqsInfoListGERAN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_CarrierFreqsInfoListGERAN, CarrierFreqsInfoListGERAN_sequence_of,
                                                  1, maxGNFG, FALSE);

  return offset;
}


static const per_sequence_t SystemInformationBlockType7_sequence[] = {
  { &hf_lte_rrc_t_ReselectionGERAN, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_Reselection },
  { &hf_lte_rrc_t_ReselectionGERAN_SF, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_SpeedStateScaleFactors },
  { &hf_lte_rrc_carrierFreqsInfoList, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_CarrierFreqsInfoListGERAN },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SystemInformationBlockType7(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SystemInformationBlockType7, SystemInformationBlockType7_sequence);

  return offset;
}



static int
dissect_lte_rrc_BIT_STRING_SIZE_39(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     39, 39, FALSE, NULL);

  return offset;
}



static int
dissect_lte_rrc_BIT_STRING_SIZE_49(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     49, 49, FALSE, NULL);

  return offset;
}


static const value_string lte_rrc_T_cdma_SystemTime_vals[] = {
  {   0, "synchronousSystemTime" },
  {   1, "asynchronousSystemTime" },
  { 0, NULL }
};

static const per_choice_t T_cdma_SystemTime_choice[] = {
  {   0, &hf_lte_rrc_synchronousSystemTime, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_BIT_STRING_SIZE_39 },
  {   1, &hf_lte_rrc_asynchronousSystemTime, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_BIT_STRING_SIZE_49 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_cdma_SystemTime(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_cdma_SystemTime, T_cdma_SystemTime_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t SystemTimeInfoCDMA2000_sequence[] = {
  { &hf_lte_rrc_cdma_EUTRA_Synchronisation, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_cdma_SystemTime, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_cdma_SystemTime },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SystemTimeInfoCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SystemTimeInfoCDMA2000, SystemTimeInfoCDMA2000_sequence);

  return offset;
}



static int
dissect_lte_rrc_PreRegistrationZoneIdHRPD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 255U, NULL, FALSE);

  return offset;
}


static const per_sequence_t SecondaryPreRegistrationZoneIdListHRPD_sequence_of[1] = {
  { &hf_lte_rrc_SecondaryPreRegistrationZoneIdListHRPD_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PreRegistrationZoneIdHRPD },
};

static int
dissect_lte_rrc_SecondaryPreRegistrationZoneIdListHRPD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_SecondaryPreRegistrationZoneIdListHRPD, SecondaryPreRegistrationZoneIdListHRPD_sequence_of,
                                                  1, 2, FALSE);

  return offset;
}


static const per_sequence_t PreRegistrationInfoHRPD_sequence[] = {
  { &hf_lte_rrc_preRegistrationAllowed, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_preRegistrationZoneId, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_PreRegistrationZoneIdHRPD },
  { &hf_lte_rrc_secondaryPreRegistrationZoneIdList, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_SecondaryPreRegistrationZoneIdListHRPD },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_PreRegistrationInfoHRPD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_PreRegistrationInfoHRPD, PreRegistrationInfoHRPD_sequence);

  return offset;
}


static const value_string lte_rrc_BandclassCDMA2000_vals[] = {
  {   0, "bc0" },
  {   1, "bc1" },
  {   2, "bc2" },
  {   3, "bc3" },
  {   4, "bc4" },
  {   5, "bc5" },
  {   6, "bc6" },
  {   7, "bc7" },
  {   8, "bc8" },
  {   9, "bc9" },
  {  10, "bc10" },
  {  11, "bc11" },
  {  12, "bc12" },
  {  13, "bc13" },
  {  14, "bc14" },
  {  15, "bc15" },
  {  16, "bc16" },
  {  17, "bc17" },
  {  18, "spare14" },
  {  19, "spare13" },
  {  20, "spare12" },
  {  21, "spare11" },
  {  22, "spare10" },
  {  23, "spare9" },
  {  24, "spare8" },
  {  25, "spare7" },
  {  26, "spare6" },
  {  27, "spare5" },
  {  28, "spare4" },
  {  29, "spare3" },
  {  30, "spare2" },
  {  31, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_BandclassCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     32, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t BandClassInfoCDMA2000_sequence[] = {
  { &hf_lte_rrc_bandClass   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BandclassCDMA2000 },
  { &hf_lte_rrc_cellReselectionPriority, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_CellReselectionPriority },
  { &hf_lte_rrc_threshX_High_01, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_63 },
  { &hf_lte_rrc_threshX_Low_01, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_63 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_BandClassInfoCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_BandClassInfoCDMA2000, BandClassInfoCDMA2000_sequence);

  return offset;
}


static const per_sequence_t BandClassListCDMA2000_sequence_of[1] = {
  { &hf_lte_rrc_BandClassListCDMA2000_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BandClassInfoCDMA2000 },
};

static int
dissect_lte_rrc_BandClassListCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_BandClassListCDMA2000, BandClassListCDMA2000_sequence_of,
                                                  1, maxCDMA_BandClass, FALSE);

  return offset;
}



static int
dissect_lte_rrc_ARFCN_ValueCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 2047U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_PhysCellIdCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, maxPNOffset, NULL, FALSE);

  return offset;
}


static const per_sequence_t PhysCellIdListCDMA2000_sequence_of[1] = {
  { &hf_lte_rrc_PhysCellIdListCDMA2000_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhysCellIdCDMA2000 },
};

static int
dissect_lte_rrc_PhysCellIdListCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_PhysCellIdListCDMA2000, PhysCellIdListCDMA2000_sequence_of,
                                                  1, 16, FALSE);

  return offset;
}


static const per_sequence_t NeighCellsPerBandclassCDMA2000_sequence[] = {
  { &hf_lte_rrc_arfcn       , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ARFCN_ValueCDMA2000 },
  { &hf_lte_rrc_physCellIdList, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhysCellIdListCDMA2000 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_NeighCellsPerBandclassCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_NeighCellsPerBandclassCDMA2000, NeighCellsPerBandclassCDMA2000_sequence);

  return offset;
}


static const per_sequence_t NeighCellsPerBandclassListCDMA2000_sequence_of[1] = {
  { &hf_lte_rrc_NeighCellsPerBandclassListCDMA2000_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_NeighCellsPerBandclassCDMA2000 },
};

static int
dissect_lte_rrc_NeighCellsPerBandclassListCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_NeighCellsPerBandclassListCDMA2000, NeighCellsPerBandclassListCDMA2000_sequence_of,
                                                  1, 16, FALSE);

  return offset;
}


static const per_sequence_t NeighCellCDMA2000_sequence[] = {
  { &hf_lte_rrc_bandClass   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BandclassCDMA2000 },
  { &hf_lte_rrc_neighCellsPerFreqList, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_NeighCellsPerBandclassListCDMA2000 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_NeighCellCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_NeighCellCDMA2000, NeighCellCDMA2000_sequence);

  return offset;
}


static const per_sequence_t NeighCellListCDMA2000_sequence_of[1] = {
  { &hf_lte_rrc_NeighCellListCDMA2000_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_NeighCellCDMA2000 },
};

static int
dissect_lte_rrc_NeighCellListCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_NeighCellListCDMA2000, NeighCellListCDMA2000_sequence_of,
                                                  1, 16, FALSE);

  return offset;
}


static const per_sequence_t CellReselectionParametersCDMA2000_sequence[] = {
  { &hf_lte_rrc_bandClassList, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BandClassListCDMA2000 },
  { &hf_lte_rrc_neighCellList, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_NeighCellListCDMA2000 },
  { &hf_lte_rrc_t_ReselectionCDMA2000, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_Reselection },
  { &hf_lte_rrc_t_ReselectionCDMA2000_SF, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_SpeedStateScaleFactors },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CellReselectionParametersCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CellReselectionParametersCDMA2000, CellReselectionParametersCDMA2000_sequence);

  return offset;
}


static const per_sequence_t T_parametersHRPD_sequence[] = {
  { &hf_lte_rrc_preRegistrationInfoHRPD, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PreRegistrationInfoHRPD },
  { &hf_lte_rrc_cellReselectionParametersHRPD, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_CellReselectionParametersCDMA2000 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_parametersHRPD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_parametersHRPD, T_parametersHRPD_sequence);

  return offset;
}



static int
dissect_lte_rrc_BIT_STRING_SIZE_15(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     15, 15, FALSE, NULL);

  return offset;
}



static int
dissect_lte_rrc_BIT_STRING_SIZE_16(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     16, 16, FALSE, NULL);

  return offset;
}



static int
dissect_lte_rrc_BIT_STRING_SIZE_7(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     7, 7, FALSE, NULL);

  return offset;
}



static int
dissect_lte_rrc_BIT_STRING_SIZE_12(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     12, 12, FALSE, NULL);

  return offset;
}



static int
dissect_lte_rrc_BIT_STRING_SIZE_3(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     3, 3, FALSE, NULL);

  return offset;
}


static const per_sequence_t CSFB_RegistrationParam1XRTT_sequence[] = {
  { &hf_lte_rrc_sid         , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_15 },
  { &hf_lte_rrc_nid         , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_16 },
  { &hf_lte_rrc_multipleSID , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_multipleNID , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_homeReg     , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_foreignSIDReg, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_foreignNIDReg, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_parameterReg, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_powerUpReg  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_registrationPeriod, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_7 },
  { &hf_lte_rrc_registrationZone, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_12 },
  { &hf_lte_rrc_totalZone   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_3 },
  { &hf_lte_rrc_zoneTimer   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_3 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CSFB_RegistrationParam1XRTT(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CSFB_RegistrationParam1XRTT, CSFB_RegistrationParam1XRTT_sequence);

  return offset;
}



static int
dissect_lte_rrc_BIT_STRING_SIZE_42(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     42, 42, FALSE, NULL);

  return offset;
}


static const per_sequence_t T_parameters1XRTT_sequence[] = {
  { &hf_lte_rrc_csfb_RegistrationParam1XRTT, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_CSFB_RegistrationParam1XRTT },
  { &hf_lte_rrc_longCodeState1XRTT, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_BIT_STRING_SIZE_42 },
  { &hf_lte_rrc_cellReselectionParameters1XRTT, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_CellReselectionParametersCDMA2000 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_parameters1XRTT(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_parameters1XRTT, T_parameters1XRTT_sequence);

  return offset;
}


static const per_sequence_t PhysCellIdListCDMA2000_v920_sequence_of[1] = {
  { &hf_lte_rrc_PhysCellIdListCDMA2000_v920_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhysCellIdCDMA2000 },
};

static int
dissect_lte_rrc_PhysCellIdListCDMA2000_v920(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_PhysCellIdListCDMA2000_v920, PhysCellIdListCDMA2000_v920_sequence_of,
                                                  0, 24, FALSE);

  return offset;
}


static const per_sequence_t NeighCellsPerBandclassCDMA2000_v920_sequence[] = {
  { &hf_lte_rrc_physCellIdList_v920, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhysCellIdListCDMA2000_v920 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_NeighCellsPerBandclassCDMA2000_v920(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_NeighCellsPerBandclassCDMA2000_v920, NeighCellsPerBandclassCDMA2000_v920_sequence);

  return offset;
}


static const per_sequence_t NeighCellsPerBandclassListCDMA2000_v920_sequence_of[1] = {
  { &hf_lte_rrc_NeighCellsPerBandclassListCDMA2000_v920_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_NeighCellsPerBandclassCDMA2000_v920 },
};

static int
dissect_lte_rrc_NeighCellsPerBandclassListCDMA2000_v920(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_NeighCellsPerBandclassListCDMA2000_v920, NeighCellsPerBandclassListCDMA2000_v920_sequence_of,
                                                  1, 16, FALSE);

  return offset;
}


static const per_sequence_t NeighCellCDMA2000_v920_sequence[] = {
  { &hf_lte_rrc_neighCellsPerFreqList_v920, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_NeighCellsPerBandclassListCDMA2000_v920 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_NeighCellCDMA2000_v920(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_NeighCellCDMA2000_v920, NeighCellCDMA2000_v920_sequence);

  return offset;
}


static const per_sequence_t NeighCellListCDMA2000_v920_sequence_of[1] = {
  { &hf_lte_rrc_NeighCellListCDMA2000_v920_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_NeighCellCDMA2000_v920 },
};

static int
dissect_lte_rrc_NeighCellListCDMA2000_v920(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_NeighCellListCDMA2000_v920, NeighCellListCDMA2000_v920_sequence_of,
                                                  1, 16, FALSE);

  return offset;
}


static const per_sequence_t CellReselectionParametersCDMA2000_v920_sequence[] = {
  { &hf_lte_rrc_neighCellList_v920, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_NeighCellListCDMA2000_v920 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CellReselectionParametersCDMA2000_v920(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CellReselectionParametersCDMA2000_v920, CellReselectionParametersCDMA2000_v920_sequence);

  return offset;
}


static const value_string lte_rrc_T_powerDownReg_r9_vals[] = {
  {   0, "true" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_powerDownReg_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t CSFB_RegistrationParam1XRTT_v920_sequence[] = {
  { &hf_lte_rrc_powerDownReg_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_powerDownReg_r9 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CSFB_RegistrationParam1XRTT_v920(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CSFB_RegistrationParam1XRTT_v920, CSFB_RegistrationParam1XRTT_v920_sequence);

  return offset;
}


static const per_sequence_t AC_BarringConfig1XRTT_r9_sequence[] = {
  { &hf_lte_rrc_ac_Barring0to9_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_63 },
  { &hf_lte_rrc_ac_Barring10_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_7 },
  { &hf_lte_rrc_ac_Barring11_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_7 },
  { &hf_lte_rrc_ac_Barring12_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_7 },
  { &hf_lte_rrc_ac_Barring13_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_7 },
  { &hf_lte_rrc_ac_Barring14_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_7 },
  { &hf_lte_rrc_ac_Barring15_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_7 },
  { &hf_lte_rrc_ac_BarringMsg_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_7 },
  { &hf_lte_rrc_ac_BarringReg_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_7 },
  { &hf_lte_rrc_ac_BarringEmg_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_7 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_AC_BarringConfig1XRTT_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_AC_BarringConfig1XRTT_r9, AC_BarringConfig1XRTT_r9_sequence);

  return offset;
}


static const per_sequence_t SystemInformationBlockType8_sequence[] = {
  { &hf_lte_rrc_systemTimeInfo, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_SystemTimeInfoCDMA2000 },
  { &hf_lte_rrc_searchWindowSize, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_INTEGER_0_15 },
  { &hf_lte_rrc_parametersHRPD, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_T_parametersHRPD },
  { &hf_lte_rrc_parameters1XRTT, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_T_parameters1XRTT },
  { &hf_lte_rrc_lateR8NonCriticalExtension, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_OCTET_STRING },
  { &hf_lte_rrc_csfb_SupportForDualRxUEs_r9, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_cellReselectionParametersHRPD_v920, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_CellReselectionParametersCDMA2000_v920 },
  { &hf_lte_rrc_cellReselectionParameters1XRTT_v920, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_CellReselectionParametersCDMA2000_v920 },
  { &hf_lte_rrc_csfb_RegistrationParam1XRTT_v920, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_CSFB_RegistrationParam1XRTT_v920 },
  { &hf_lte_rrc_ac_BarringConfig1XRTT_r9, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_AC_BarringConfig1XRTT_r9 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SystemInformationBlockType8(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SystemInformationBlockType8, SystemInformationBlockType8_sequence);

  return offset;
}



static int
dissect_lte_rrc_OCTET_STRING_SIZE_1_48(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       1, 48, FALSE, NULL);

  return offset;
}


static const per_sequence_t SystemInformationBlockType9_sequence[] = {
  { &hf_lte_rrc_hnb_Name    , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_OCTET_STRING_SIZE_1_48 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SystemInformationBlockType9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SystemInformationBlockType9, SystemInformationBlockType9_sequence);

  return offset;
}



static int
dissect_lte_rrc_OCTET_STRING_SIZE_2(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       2, 2, FALSE, NULL);

  return offset;
}



static int
dissect_lte_rrc_OCTET_STRING_SIZE_50(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       50, 50, FALSE, NULL);

  return offset;
}


static const per_sequence_t SystemInformationBlockType10_sequence[] = {
  { &hf_lte_rrc_messageIdentifier, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_16 },
  { &hf_lte_rrc_serialNumber, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_16 },
  { &hf_lte_rrc_warningType , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_OCTET_STRING_SIZE_2 },
  { &hf_lte_rrc_warningSecurityInfo, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_OCTET_STRING_SIZE_50 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SystemInformationBlockType10(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SystemInformationBlockType10, SystemInformationBlockType10_sequence);

  return offset;
}


static const value_string lte_rrc_T_warningMessageSegmentType_vals[] = {
  {   0, "notLastSegment" },
  {   1, "lastSegment" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_warningMessageSegmentType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}



static int
dissect_lte_rrc_OCTET_STRING_SIZE_1(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       1, 1, FALSE, NULL);

  return offset;
}


static const per_sequence_t SystemInformationBlockType11_sequence[] = {
  { &hf_lte_rrc_messageIdentifier, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_16 },
  { &hf_lte_rrc_serialNumber, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_16 },
  { &hf_lte_rrc_warningMessageSegmentType, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_warningMessageSegmentType },
  { &hf_lte_rrc_warningMessageSegmentNumber, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_63 },
  { &hf_lte_rrc_warningMessageSegment, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_OCTET_STRING },
  { &hf_lte_rrc_dataCodingScheme, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_OCTET_STRING_SIZE_1 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SystemInformationBlockType11(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SystemInformationBlockType11, SystemInformationBlockType11_sequence);

  return offset;
}


static const value_string lte_rrc_T_warningMessageSegmentType_r9_vals[] = {
  {   0, "notLastSegment" },
  {   1, "lastSegment" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_warningMessageSegmentType_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t SystemInformationBlockType12_r9_sequence[] = {
  { &hf_lte_rrc_messageIdentifier_r9, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_16 },
  { &hf_lte_rrc_serialNumber_r9, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_16 },
  { &hf_lte_rrc_warningMessageSegmentType_r9, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_warningMessageSegmentType_r9 },
  { &hf_lte_rrc_warningMessageSegmentNumber_r9, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_63 },
  { &hf_lte_rrc_warningMessageSegment_r9, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_OCTET_STRING },
  { &hf_lte_rrc_dataCodingScheme_r9, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_OCTET_STRING_SIZE_1 },
  { &hf_lte_rrc_lateR9NonCriticalExtension, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_OCTET_STRING },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SystemInformationBlockType12_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SystemInformationBlockType12_r9, SystemInformationBlockType12_r9_sequence);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_255(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 255U, NULL, FALSE);

  return offset;
}


static const value_string lte_rrc_T_non_MBSFNregionLength_vals[] = {
  {   0, "s1" },
  {   1, "s2" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_non_MBSFNregionLength(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_mcch_RepetitionPeriod_r9_vals[] = {
  {   0, "rf32" },
  {   1, "rf64" },
  {   2, "rf128" },
  {   3, "rf256" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_mcch_RepetitionPeriod_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, FALSE, 0, NULL);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_10(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 10U, NULL, FALSE);

  return offset;
}


static const value_string lte_rrc_T_mcch_ModificationPeriod_r9_vals[] = {
  {   0, "rf512" },
  {   1, "rf1024" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_mcch_ModificationPeriod_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_signallingMCS_r9_vals[] = {
  {   0, "n2" },
  {   1, "n7" },
  {   2, "n13" },
  {   3, "n19" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_signallingMCS_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t T_mcch_Config_r9_sequence[] = {
  { &hf_lte_rrc_mcch_RepetitionPeriod_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_mcch_RepetitionPeriod_r9 },
  { &hf_lte_rrc_mcch_Offset_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_10 },
  { &hf_lte_rrc_mcch_ModificationPeriod_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_mcch_ModificationPeriod_r9 },
  { &hf_lte_rrc_sf_AllocInfo_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_6 },
  { &hf_lte_rrc_signallingMCS_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_signallingMCS_r9 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_mcch_Config_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_mcch_Config_r9, T_mcch_Config_r9_sequence);

  return offset;
}


static const per_sequence_t MBSFN_AreaInfo_r9_sequence[] = {
  { &hf_lte_rrc_mbsfn_AreaId_r9, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_255 },
  { &hf_lte_rrc_non_MBSFNregionLength, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_non_MBSFNregionLength },
  { &hf_lte_rrc_notificationIndicator_r9, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_7 },
  { &hf_lte_rrc_mcch_Config_r9, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_mcch_Config_r9 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MBSFN_AreaInfo_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MBSFN_AreaInfo_r9, MBSFN_AreaInfo_r9_sequence);

  return offset;
}


static const per_sequence_t MBSFN_AreaInfoList_r9_sequence_of[1] = {
  { &hf_lte_rrc_MBSFN_AreaInfoList_r9_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MBSFN_AreaInfo_r9 },
};

static int
dissect_lte_rrc_MBSFN_AreaInfoList_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_MBSFN_AreaInfoList_r9, MBSFN_AreaInfoList_r9_sequence_of,
                                                  1, maxMBSFN_Area, FALSE);

  return offset;
}


static const value_string lte_rrc_T_notificationRepetitionCoeff_r9_vals[] = {
  {   0, "n2" },
  {   1, "n4" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_notificationRepetitionCoeff_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_1_6(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, 6U, NULL, FALSE);

  return offset;
}


static const per_sequence_t MBMS_NotificationConfig_r9_sequence[] = {
  { &hf_lte_rrc_notificationRepetitionCoeff_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_notificationRepetitionCoeff_r9 },
  { &hf_lte_rrc_notificationOffset_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_10 },
  { &hf_lte_rrc_notificationSF_Index_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_1_6 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MBMS_NotificationConfig_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MBMS_NotificationConfig_r9, MBMS_NotificationConfig_r9_sequence);

  return offset;
}


static const per_sequence_t SystemInformationBlockType13_r9_sequence[] = {
  { &hf_lte_rrc_mbsfn_AreaInfoList_r9, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MBSFN_AreaInfoList_r9 },
  { &hf_lte_rrc_notificationConfig_r9, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MBMS_NotificationConfig_r9 },
  { &hf_lte_rrc_lateR9NonCriticalExtension, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_OCTET_STRING },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SystemInformationBlockType13_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SystemInformationBlockType13_r9, SystemInformationBlockType13_r9_sequence);

  return offset;
}


static const value_string lte_rrc_T_sib_TypeAndInfo_item_vals[] = {
  {   0, "sib2" },
  {   1, "sib3" },
  {   2, "sib4" },
  {   3, "sib5" },
  {   4, "sib6" },
  {   5, "sib7" },
  {   6, "sib8" },
  {   7, "sib9" },
  {   8, "sib10" },
  {   9, "sib11" },
  {  10, "sib12-v920" },
  {  11, "sib13-v920" },
  { 0, NULL }
};

static const per_choice_t T_sib_TypeAndInfo_item_choice[] = {
  {   0, &hf_lte_rrc_sib2        , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_SystemInformationBlockType2 },
  {   1, &hf_lte_rrc_sib3        , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_SystemInformationBlockType3 },
  {   2, &hf_lte_rrc_sib4        , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_SystemInformationBlockType4 },
  {   3, &hf_lte_rrc_sib5        , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_SystemInformationBlockType5 },
  {   4, &hf_lte_rrc_sib6        , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_SystemInformationBlockType6 },
  {   5, &hf_lte_rrc_sib7        , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_SystemInformationBlockType7 },
  {   6, &hf_lte_rrc_sib8        , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_SystemInformationBlockType8 },
  {   7, &hf_lte_rrc_sib9        , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_SystemInformationBlockType9 },
  {   8, &hf_lte_rrc_sib10       , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_SystemInformationBlockType10 },
  {   9, &hf_lte_rrc_sib11       , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_SystemInformationBlockType11 },
  {  10, &hf_lte_rrc_sib12_v920  , ASN1_NOT_EXTENSION_ROOT, dissect_lte_rrc_SystemInformationBlockType12_r9 },
  {  11, &hf_lte_rrc_sib13_v920  , ASN1_NOT_EXTENSION_ROOT, dissect_lte_rrc_SystemInformationBlockType13_r9 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_sib_TypeAndInfo_item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_sib_TypeAndInfo_item, T_sib_TypeAndInfo_item_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_sib_TypeAndInfo_sequence_of[1] = {
  { &hf_lte_rrc_sib_TypeAndInfo_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_sib_TypeAndInfo_item },
};

static int
dissect_lte_rrc_T_sib_TypeAndInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_T_sib_TypeAndInfo, T_sib_TypeAndInfo_sequence_of,
                                                  1, maxSIB, FALSE);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_24_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_24(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_24, T_nonCriticalExtension_24_sequence);

  return offset;
}


static const per_sequence_t SystemInformation_r8_IEs_sequence[] = {
  { &hf_lte_rrc_sib_TypeAndInfo, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_sib_TypeAndInfo },
  { &hf_lte_rrc_nonCriticalExtension_33, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_24 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SystemInformation_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SystemInformation_r8_IEs, SystemInformation_r8_IEs_sequence);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_23_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_23(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_23, T_criticalExtensionsFuture_23_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_23_vals[] = {
  {   0, "systemInformation-r8" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_23_choice[] = {
  {   0, &hf_lte_rrc_systemInformation_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_SystemInformation_r8_IEs },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_23, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_23 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_23(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_23, T_criticalExtensions_23_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t SystemInformation_sequence[] = {
  { &hf_lte_rrc_criticalExtensions_23, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_23 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SystemInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:SystemInformation ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SystemInformation, SystemInformation_sequence);

  return offset;
}



static int
dissect_lte_rrc_MCC_MNC_Digit(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 9U, NULL, FALSE);

  return offset;
}


static const per_sequence_t MCC_sequence_of[1] = {
  { &hf_lte_rrc_MCC_item    , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MCC_MNC_Digit },
};

static int
dissect_lte_rrc_MCC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_MCC, MCC_sequence_of,
                                                  3, 3, FALSE);

  return offset;
}


static const per_sequence_t MNC_sequence_of[1] = {
  { &hf_lte_rrc_MNC_item    , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MCC_MNC_Digit },
};

static int
dissect_lte_rrc_MNC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_MNC, MNC_sequence_of,
                                                  2, 3, FALSE);

  return offset;
}


static const per_sequence_t PLMN_Identity_sequence[] = {
  { &hf_lte_rrc_mcc         , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_MCC },
  { &hf_lte_rrc_mnc         , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MNC },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_PLMN_Identity(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_PLMN_Identity, PLMN_Identity_sequence);

  return offset;
}


static const value_string lte_rrc_T_cellReservedForOperatorUse_vals[] = {
  {   0, "reserved" },
  {   1, "notReserved" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_cellReservedForOperatorUse(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t PLMN_IdentityInfo_sequence[] = {
  { &hf_lte_rrc_plmn_Identity, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PLMN_Identity },
  { &hf_lte_rrc_cellReservedForOperatorUse, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_cellReservedForOperatorUse },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_PLMN_IdentityInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_PLMN_IdentityInfo, PLMN_IdentityInfo_sequence);

  return offset;
}


static const per_sequence_t PLMN_IdentityList_sequence_of[1] = {
  { &hf_lte_rrc_PLMN_IdentityList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PLMN_IdentityInfo },
};

static int
dissect_lte_rrc_PLMN_IdentityList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_PLMN_IdentityList, PLMN_IdentityList_sequence_of,
                                                  1, 6, FALSE);

  return offset;
}



static int
dissect_lte_rrc_TrackingAreaCode(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     16, 16, FALSE, NULL);

  return offset;
}



static int
dissect_lte_rrc_CellIdentity(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     28, 28, FALSE, NULL);

  return offset;
}


static const value_string lte_rrc_T_cellBarred_vals[] = {
  {   0, "barred" },
  {   1, "notBarred" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_cellBarred(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_intraFreqReselection_vals[] = {
  {   0, "allowed" },
  {   1, "notAllowed" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_intraFreqReselection(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}



static int
dissect_lte_rrc_CSG_Identity(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     27, 27, FALSE, NULL);

  return offset;
}


static const per_sequence_t T_cellAccessRelatedInfo_sequence[] = {
  { &hf_lte_rrc_plmn_IdentityList, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PLMN_IdentityList },
  { &hf_lte_rrc_trackingAreaCode, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_TrackingAreaCode },
  { &hf_lte_rrc_cellIdentity, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CellIdentity },
  { &hf_lte_rrc_cellBarred  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_cellBarred },
  { &hf_lte_rrc_intraFreqReselection, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_intraFreqReselection },
  { &hf_lte_rrc_csg_Indication, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_csg_Identity, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_CSG_Identity },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_cellAccessRelatedInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_cellAccessRelatedInfo, T_cellAccessRelatedInfo_sequence);

  return offset;
}


static const per_sequence_t T_cellSelectionInfo_sequence[] = {
  { &hf_lte_rrc_q_RxLevMin  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_Q_RxLevMin },
  { &hf_lte_rrc_q_RxLevMinOffset, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_INTEGER_1_8 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_cellSelectionInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_cellSelectionInfo, T_cellSelectionInfo_sequence);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_1_64(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, 64U, NULL, FALSE);

  return offset;
}


static const value_string lte_rrc_T_si_Periodicity_vals[] = {
  {   0, "rf8" },
  {   1, "rf16" },
  {   2, "rf32" },
  {   3, "rf64" },
  {   4, "rf128" },
  {   5, "rf256" },
  {   6, "rf512" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_si_Periodicity(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     7, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_SIB_Type_vals[] = {
  {   0, "sibType3" },
  {   1, "sibType4" },
  {   2, "sibType5" },
  {   3, "sibType6" },
  {   4, "sibType7" },
  {   5, "sibType8" },
  {   6, "sibType9" },
  {   7, "sibType10" },
  {   8, "sibType11" },
  {   9, "sibType12-v920" },
  {  10, "sibType13-v920" },
  {  11, "spare5" },
  {  12, "spare4" },
  {  13, "spare3" },
  {  14, "spare2" },
  {  15, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_SIB_Type(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t SIB_MappingInfo_sequence_of[1] = {
  { &hf_lte_rrc_SIB_MappingInfo_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SIB_Type },
};

static int
dissect_lte_rrc_SIB_MappingInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_SIB_MappingInfo, SIB_MappingInfo_sequence_of,
                                                  0, maxSIB_1, FALSE);

  return offset;
}


static const per_sequence_t SchedulingInfo_sequence[] = {
  { &hf_lte_rrc_si_Periodicity, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_si_Periodicity },
  { &hf_lte_rrc_sib_MappingInfo, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SIB_MappingInfo },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SchedulingInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SchedulingInfo, SchedulingInfo_sequence);

  return offset;
}


static const per_sequence_t SchedulingInfoList_sequence_of[1] = {
  { &hf_lte_rrc_SchedulingInfoList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SchedulingInfo },
};

static int
dissect_lte_rrc_SchedulingInfoList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_SchedulingInfoList, SchedulingInfoList_sequence_of,
                                                  1, maxSI_Message, FALSE);

  return offset;
}


static const value_string lte_rrc_T_subframeAssignment_vals[] = {
  {   0, "sa0" },
  {   1, "sa1" },
  {   2, "sa2" },
  {   3, "sa3" },
  {   4, "sa4" },
  {   5, "sa5" },
  {   6, "sa6" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_subframeAssignment(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     7, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_specialSubframePatterns_vals[] = {
  {   0, "ssp0" },
  {   1, "ssp1" },
  {   2, "ssp2" },
  {   3, "ssp3" },
  {   4, "ssp4" },
  {   5, "ssp5" },
  {   6, "ssp6" },
  {   7, "ssp7" },
  {   8, "ssp8" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_specialSubframePatterns(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     9, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t TDD_Config_sequence[] = {
  { &hf_lte_rrc_subframeAssignment, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_subframeAssignment },
  { &hf_lte_rrc_specialSubframePatterns, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_specialSubframePatterns },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_TDD_Config(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_TDD_Config, TDD_Config_sequence);

  return offset;
}


static const value_string lte_rrc_T_si_WindowLength_vals[] = {
  {   0, "ms1" },
  {   1, "ms2" },
  {   2, "ms5" },
  {   3, "ms10" },
  {   4, "ms15" },
  {   5, "ms20" },
  {   6, "ms40" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_si_WindowLength(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     7, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_ims_EmergencySupport_r9_vals[] = {
  {   0, "true" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_ims_EmergencySupport_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t CellSelectionInfo_v920_sequence[] = {
  { &hf_lte_rrc_q_QualMin_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_Q_QualMin_r9 },
  { &hf_lte_rrc_q_QualMinOffset_r9, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_INTEGER_1_8 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CellSelectionInfo_v920(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CellSelectionInfo_v920, CellSelectionInfo_v920_sequence);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_25_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_25(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_25, T_nonCriticalExtension_25_sequence);

  return offset;
}


static const per_sequence_t SystemInformationBlockType1_v920_IEs_sequence[] = {
  { &hf_lte_rrc_ims_EmergencySupport_r9, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_ims_EmergencySupport_r9 },
  { &hf_lte_rrc_cellSelectionInfo_v920, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_CellSelectionInfo_v920 },
  { &hf_lte_rrc_nonCriticalExtension_36, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_25 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SystemInformationBlockType1_v920_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SystemInformationBlockType1_v920_IEs, SystemInformationBlockType1_v920_IEs_sequence);

  return offset;
}


static const per_sequence_t SystemInformationBlockType1_v890_IEs_sequence[] = {
  { &hf_lte_rrc_lateR8NonCriticalExtension, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_OCTET_STRING },
  { &hf_lte_rrc_nonCriticalExtension_35, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_SystemInformationBlockType1_v920_IEs },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SystemInformationBlockType1_v890_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SystemInformationBlockType1_v890_IEs, SystemInformationBlockType1_v890_IEs_sequence);

  return offset;
}


static const per_sequence_t SystemInformationBlockType1_sequence[] = {
  { &hf_lte_rrc_cellAccessRelatedInfo, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_cellAccessRelatedInfo },
  { &hf_lte_rrc_cellSelectionInfo, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_cellSelectionInfo },
  { &hf_lte_rrc_p_Max       , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_P_Max },
  { &hf_lte_rrc_freqBandIndicator, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_1_64 },
  { &hf_lte_rrc_schedulingInfoList, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SchedulingInfoList },
  { &hf_lte_rrc_tdd_Config  , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_TDD_Config },
  { &hf_lte_rrc_si_WindowLength, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_si_WindowLength },
  { &hf_lte_rrc_systemInfoValueTag, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_31 },
  { &hf_lte_rrc_nonCriticalExtension_34, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_SystemInformationBlockType1_v890_IEs },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SystemInformationBlockType1(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:SystemInformationBlockType1 ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SystemInformationBlockType1, SystemInformationBlockType1_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_vals[] = {
  {   0, "systemInformation" },
  {   1, "systemInformationBlockType1" },
  { 0, NULL }
};

static const per_choice_t T_c1_choice[] = {
  {   0, &hf_lte_rrc_systemInformation, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_SystemInformation },
  {   1, &hf_lte_rrc_systemInformationBlockType1, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_SystemInformationBlockType1 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1, T_c1_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_messageClassExtension_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_messageClassExtension(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_messageClassExtension, T_messageClassExtension_sequence);

  return offset;
}


static const value_string lte_rrc_BCCH_DL_SCH_MessageType_vals[] = {
  {   0, "c1" },
  {   1, "messageClassExtension" },
  { 0, NULL }
};

static const per_choice_t BCCH_DL_SCH_MessageType_choice[] = {
  {   0, &hf_lte_rrc_c1          , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1 },
  {   1, &hf_lte_rrc_messageClassExtension, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_messageClassExtension },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_BCCH_DL_SCH_MessageType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_BCCH_DL_SCH_MessageType, BCCH_DL_SCH_MessageType_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t BCCH_DL_SCH_Message_sequence[] = {
  { &hf_lte_rrc_message_01  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BCCH_DL_SCH_MessageType },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_BCCH_DL_SCH_Message(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_BCCH_DL_SCH_Message, BCCH_DL_SCH_Message_sequence);

  return offset;
}


static const per_sequence_t CommonSF_AllocPatternList_r9_sequence_of[1] = {
  { &hf_lte_rrc_CommonSF_AllocPatternList_r9_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MBSFN_SubframeConfig },
};

static int
dissect_lte_rrc_CommonSF_AllocPatternList_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_CommonSF_AllocPatternList_r9, CommonSF_AllocPatternList_r9_sequence_of,
                                                  1, maxMBSFN_Allocations, FALSE);

  return offset;
}


static const value_string lte_rrc_T_commonSF_AllocPeriod_r9_vals[] = {
  {   0, "rf4" },
  {   1, "rf8" },
  {   2, "rf16" },
  {   3, "rf32" },
  {   4, "rf64" },
  {   5, "rf128" },
  {   6, "rf256" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_commonSF_AllocPeriod_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     7, NULL, FALSE, 0, NULL);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_1535(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 1535U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_28(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 28U, NULL, FALSE);

  return offset;
}


static const value_string lte_rrc_T_mch_SchedulingPeriod_r9_vals[] = {
  {   0, "rf8" },
  {   1, "rf16" },
  {   2, "rf32" },
  {   3, "rf64" },
  {   4, "rf128" },
  {   5, "rf256" },
  {   6, "rf512" },
  {   7, "rf1024" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_mch_SchedulingPeriod_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t PMCH_Config_r9_sequence[] = {
  { &hf_lte_rrc_sf_AllocEnd_r9, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_1535 },
  { &hf_lte_rrc_dataMCS_r9  , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_28 },
  { &hf_lte_rrc_mch_SchedulingPeriod_r9, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_mch_SchedulingPeriod_r9 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_PMCH_Config_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_PMCH_Config_r9, PMCH_Config_r9_sequence);

  return offset;
}


static const value_string lte_rrc_T_plmn_Id_r9_vals[] = {
  {   0, "plmn-Index-r9" },
  {   1, "explicitValue-r9" },
  { 0, NULL }
};

static const per_choice_t T_plmn_Id_r9_choice[] = {
  {   0, &hf_lte_rrc_plmn_Index_r9, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_INTEGER_1_6 },
  {   1, &hf_lte_rrc_explicitValue_r9, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_PLMN_Identity },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_plmn_Id_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_plmn_Id_r9, T_plmn_Id_r9_choice,
                                 NULL);

  return offset;
}



static int
dissect_lte_rrc_OCTET_STRING_SIZE_3(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       3, 3, FALSE, NULL);

  return offset;
}


static const per_sequence_t TMGI_r9_sequence[] = {
  { &hf_lte_rrc_plmn_Id_r9  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_plmn_Id_r9 },
  { &hf_lte_rrc_serviceId_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_OCTET_STRING_SIZE_3 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_TMGI_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_TMGI_r9, TMGI_r9_sequence);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_maxSessionPerPMCH_1(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, maxSessionPerPMCH_1, NULL, FALSE);

  return offset;
}


static const per_sequence_t MBMS_SessionInfo_r9_sequence[] = {
  { &hf_lte_rrc_tmgi_r9     , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_TMGI_r9 },
  { &hf_lte_rrc_sessionId_r9, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_OCTET_STRING_SIZE_1 },
  { &hf_lte_rrc_logicalChannelIdentity_r9, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_maxSessionPerPMCH_1 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MBMS_SessionInfo_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MBMS_SessionInfo_r9, MBMS_SessionInfo_r9_sequence);

  return offset;
}


static const per_sequence_t MBMS_SessionInfoList_r9_sequence_of[1] = {
  { &hf_lte_rrc_MBMS_SessionInfoList_r9_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MBMS_SessionInfo_r9 },
};

static int
dissect_lte_rrc_MBMS_SessionInfoList_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_MBMS_SessionInfoList_r9, MBMS_SessionInfoList_r9_sequence_of,
                                                  0, maxSessionPerPMCH, FALSE);

  return offset;
}


static const per_sequence_t PMCH_Info_r9_sequence[] = {
  { &hf_lte_rrc_pmch_Config_r9, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PMCH_Config_r9 },
  { &hf_lte_rrc_mbms_SessionInfoList_r9, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MBMS_SessionInfoList_r9 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_PMCH_Info_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_PMCH_Info_r9, PMCH_Info_r9_sequence);

  return offset;
}


static const per_sequence_t PMCH_InfoList_r9_sequence_of[1] = {
  { &hf_lte_rrc_PMCH_InfoList_r9_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PMCH_Info_r9 },
};

static int
dissect_lte_rrc_PMCH_InfoList_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_PMCH_InfoList_r9, PMCH_InfoList_r9_sequence_of,
                                                  0, maxPMCH_PerMBSFN, FALSE);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_06_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_06(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_06, T_nonCriticalExtension_06_sequence);

  return offset;
}


static const per_sequence_t MBSFNAreaConfiguration_r9_sequence[] = {
  { &hf_lte_rrc_commonSF_Alloc_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CommonSF_AllocPatternList_r9 },
  { &hf_lte_rrc_commonSF_AllocPeriod_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_commonSF_AllocPeriod_r9 },
  { &hf_lte_rrc_pmch_InfoList_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PMCH_InfoList_r9 },
  { &hf_lte_rrc_nonCriticalExtension_08, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_06 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MBSFNAreaConfiguration_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:MBSFNAreaConfiguration-r9 ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MBSFNAreaConfiguration_r9, MBSFNAreaConfiguration_r9_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_01_vals[] = {
  {   0, "mbsfnAreaConfiguration-r9" },
  { 0, NULL }
};

static const per_choice_t T_c1_01_choice[] = {
  {   0, &hf_lte_rrc_mbsfnAreaConfiguration_r9, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_MBSFNAreaConfiguration_r9 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_01(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_01, T_c1_01_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_messageClassExtension_01_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_messageClassExtension_01(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_messageClassExtension_01, T_messageClassExtension_01_sequence);

  return offset;
}


static const value_string lte_rrc_MCCH_MessageType_vals[] = {
  {   0, "c1" },
  {   1, "messageClassExtension" },
  { 0, NULL }
};

static const per_choice_t MCCH_MessageType_choice[] = {
  {   0, &hf_lte_rrc_c1_01       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_01 },
  {   1, &hf_lte_rrc_messageClassExtension_01, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_messageClassExtension_01 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_MCCH_MessageType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_MCCH_MessageType, MCCH_MessageType_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t MCCH_Message_sequence[] = {
  { &hf_lte_rrc_message_02  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MCCH_MessageType },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MCCH_Message(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MCCH_Message, MCCH_Message_sequence);

  return offset;
}



static int
dissect_lte_rrc_MMEC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     8, 8, FALSE, NULL);

  return offset;
}



static int
dissect_lte_rrc_BIT_STRING_SIZE_32(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     32, 32, FALSE, NULL);

  return offset;
}


static const per_sequence_t S_TMSI_sequence[] = {
  { &hf_lte_rrc_mmec        , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MMEC },
  { &hf_lte_rrc_m_TMSI      , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_32 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_S_TMSI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_S_TMSI, S_TMSI_sequence);

  return offset;
}



static int
dissect_lte_rrc_IMSI_Digit(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 9U, NULL, FALSE);

  return offset;
}


static const per_sequence_t IMSI_sequence_of[1] = {
  { &hf_lte_rrc_IMSI_item   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_IMSI_Digit },
};

static int
dissect_lte_rrc_IMSI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_IMSI, IMSI_sequence_of,
                                                  6, 21, FALSE);

  return offset;
}


static const value_string lte_rrc_PagingUE_Identity_vals[] = {
  {   0, "s-TMSI" },
  {   1, "imsi" },
  { 0, NULL }
};

static const per_choice_t PagingUE_Identity_choice[] = {
  {   0, &hf_lte_rrc_s_TMSI      , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_S_TMSI },
  {   1, &hf_lte_rrc_imsi        , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_IMSI },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_PagingUE_Identity(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_PagingUE_Identity, PagingUE_Identity_choice,
                                 NULL);

  return offset;
}


static const value_string lte_rrc_T_cn_Domain_vals[] = {
  {   0, "ps" },
  {   1, "cs" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_cn_Domain(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t PagingRecord_sequence[] = {
  { &hf_lte_rrc_ue_Identity , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PagingUE_Identity },
  { &hf_lte_rrc_cn_Domain   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_cn_Domain },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_PagingRecord(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_PagingRecord, PagingRecord_sequence);

  return offset;
}


static const per_sequence_t PagingRecordList_sequence_of[1] = {
  { &hf_lte_rrc_PagingRecordList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PagingRecord },
};

static int
dissect_lte_rrc_PagingRecordList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_PagingRecordList, PagingRecordList_sequence_of,
                                                  1, maxPageRec, FALSE);

  return offset;
}


static const value_string lte_rrc_T_systemInfoModification_vals[] = {
  {   0, "true" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_systemInfoModification(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_etws_Indication_vals[] = {
  {   0, "true" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_etws_Indication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_cmas_Indication_r9_vals[] = {
  {   0, "true" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_cmas_Indication_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_10_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_10(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_10, T_nonCriticalExtension_10_sequence);

  return offset;
}


static const per_sequence_t Paging_v920_IEs_sequence[] = {
  { &hf_lte_rrc_cmas_Indication_r9, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_cmas_Indication_r9 },
  { &hf_lte_rrc_nonCriticalExtension_14, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_10 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_Paging_v920_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_Paging_v920_IEs, Paging_v920_IEs_sequence);

  return offset;
}


static const per_sequence_t Paging_v890_IEs_sequence[] = {
  { &hf_lte_rrc_lateR8NonCriticalExtension, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_OCTET_STRING },
  { &hf_lte_rrc_nonCriticalExtension_13, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_Paging_v920_IEs },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_Paging_v890_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_Paging_v890_IEs, Paging_v890_IEs_sequence);

  return offset;
}


static const per_sequence_t Paging_sequence[] = {
  { &hf_lte_rrc_pagingRecordList, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_PagingRecordList },
  { &hf_lte_rrc_systemInfoModification, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_systemInfoModification },
  { &hf_lte_rrc_etws_Indication, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_etws_Indication },
  { &hf_lte_rrc_nonCriticalExtension_12, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_Paging_v890_IEs },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_Paging(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:Paging ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_Paging, Paging_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_02_vals[] = {
  {   0, "paging" },
  { 0, NULL }
};

static const per_choice_t T_c1_02_choice[] = {
  {   0, &hf_lte_rrc_paging      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_Paging },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_02(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_02, T_c1_02_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_messageClassExtension_02_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_messageClassExtension_02(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_messageClassExtension_02, T_messageClassExtension_02_sequence);

  return offset;
}


static const value_string lte_rrc_PCCH_MessageType_vals[] = {
  {   0, "c1" },
  {   1, "messageClassExtension" },
  { 0, NULL }
};

static const per_choice_t PCCH_MessageType_choice[] = {
  {   0, &hf_lte_rrc_c1_02       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_02 },
  {   1, &hf_lte_rrc_messageClassExtension_02, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_messageClassExtension_02 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_PCCH_MessageType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_PCCH_MessageType, PCCH_MessageType_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t PCCH_Message_sequence[] = {
  { &hf_lte_rrc_message_03  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PCCH_MessageType },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_PCCH_Message(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_PCCH_Message, PCCH_Message_sequence);

  return offset;
}



static int
dissect_lte_rrc_RRC_TransactionIdentifier(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 3U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_1_2(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, 2U, NULL, FALSE);

  return offset;
}


static const value_string lte_rrc_T_PollRetransmit_vals[] = {
  {   0, "ms5" },
  {   1, "ms10" },
  {   2, "ms15" },
  {   3, "ms20" },
  {   4, "ms25" },
  {   5, "ms30" },
  {   6, "ms35" },
  {   7, "ms40" },
  {   8, "ms45" },
  {   9, "ms50" },
  {  10, "ms55" },
  {  11, "ms60" },
  {  12, "ms65" },
  {  13, "ms70" },
  {  14, "ms75" },
  {  15, "ms80" },
  {  16, "ms85" },
  {  17, "ms90" },
  {  18, "ms95" },
  {  19, "ms100" },
  {  20, "ms105" },
  {  21, "ms110" },
  {  22, "ms115" },
  {  23, "ms120" },
  {  24, "ms125" },
  {  25, "ms130" },
  {  26, "ms135" },
  {  27, "ms140" },
  {  28, "ms145" },
  {  29, "ms150" },
  {  30, "ms155" },
  {  31, "ms160" },
  {  32, "ms165" },
  {  33, "ms170" },
  {  34, "ms175" },
  {  35, "ms180" },
  {  36, "ms185" },
  {  37, "ms190" },
  {  38, "ms195" },
  {  39, "ms200" },
  {  40, "ms205" },
  {  41, "ms210" },
  {  42, "ms215" },
  {  43, "ms220" },
  {  44, "ms225" },
  {  45, "ms230" },
  {  46, "ms235" },
  {  47, "ms240" },
  {  48, "ms245" },
  {  49, "ms250" },
  {  50, "ms300" },
  {  51, "ms350" },
  {  52, "ms400" },
  {  53, "ms450" },
  {  54, "ms500" },
  {  55, "spare9" },
  {  56, "spare8" },
  {  57, "spare7" },
  {  58, "spare6" },
  {  59, "spare5" },
  {  60, "spare4" },
  {  61, "spare3" },
  {  62, "spare2" },
  {  63, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_PollRetransmit(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     64, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_PollPDU_vals[] = {
  {   0, "p4" },
  {   1, "p8" },
  {   2, "p16" },
  {   3, "p32" },
  {   4, "p64" },
  {   5, "p128" },
  {   6, "p256" },
  {   7, "pInfinity" },
  { 0, NULL }
};


static int
dissect_lte_rrc_PollPDU(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_PollByte_vals[] = {
  {   0, "kB25" },
  {   1, "kB50" },
  {   2, "kB75" },
  {   3, "kB100" },
  {   4, "kB125" },
  {   5, "kB250" },
  {   6, "kB375" },
  {   7, "kB500" },
  {   8, "kB750" },
  {   9, "kB1000" },
  {  10, "kB1250" },
  {  11, "kB1500" },
  {  12, "kB2000" },
  {  13, "kB3000" },
  {  14, "kBinfinity" },
  {  15, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_PollByte(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_maxRetxThreshold_vals[] = {
  {   0, "t1" },
  {   1, "t2" },
  {   2, "t3" },
  {   3, "t4" },
  {   4, "t6" },
  {   5, "t8" },
  {   6, "t16" },
  {   7, "t32" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_maxRetxThreshold(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t UL_AM_RLC_sequence[] = {
  { &hf_lte_rrc_t_PollRetransmit, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_PollRetransmit },
  { &hf_lte_rrc_pollPDU     , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PollPDU },
  { &hf_lte_rrc_pollByte    , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PollByte },
  { &hf_lte_rrc_maxRetxThreshold, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_maxRetxThreshold },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_UL_AM_RLC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_UL_AM_RLC, UL_AM_RLC_sequence);

  return offset;
}


static const value_string lte_rrc_T_Reordering_vals[] = {
  {   0, "ms0" },
  {   1, "ms5" },
  {   2, "ms10" },
  {   3, "ms15" },
  {   4, "ms20" },
  {   5, "ms25" },
  {   6, "ms30" },
  {   7, "ms35" },
  {   8, "ms40" },
  {   9, "ms45" },
  {  10, "ms50" },
  {  11, "ms55" },
  {  12, "ms60" },
  {  13, "ms65" },
  {  14, "ms70" },
  {  15, "ms75" },
  {  16, "ms80" },
  {  17, "ms85" },
  {  18, "ms90" },
  {  19, "ms95" },
  {  20, "ms100" },
  {  21, "ms110" },
  {  22, "ms120" },
  {  23, "ms130" },
  {  24, "ms140" },
  {  25, "ms150" },
  {  26, "ms160" },
  {  27, "ms170" },
  {  28, "ms180" },
  {  29, "ms190" },
  {  30, "ms200" },
  {  31, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_Reordering(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     32, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_StatusProhibit_vals[] = {
  {   0, "ms0" },
  {   1, "ms5" },
  {   2, "ms10" },
  {   3, "ms15" },
  {   4, "ms20" },
  {   5, "ms25" },
  {   6, "ms30" },
  {   7, "ms35" },
  {   8, "ms40" },
  {   9, "ms45" },
  {  10, "ms50" },
  {  11, "ms55" },
  {  12, "ms60" },
  {  13, "ms65" },
  {  14, "ms70" },
  {  15, "ms75" },
  {  16, "ms80" },
  {  17, "ms85" },
  {  18, "ms90" },
  {  19, "ms95" },
  {  20, "ms100" },
  {  21, "ms105" },
  {  22, "ms110" },
  {  23, "ms115" },
  {  24, "ms120" },
  {  25, "ms125" },
  {  26, "ms130" },
  {  27, "ms135" },
  {  28, "ms140" },
  {  29, "ms145" },
  {  30, "ms150" },
  {  31, "ms155" },
  {  32, "ms160" },
  {  33, "ms165" },
  {  34, "ms170" },
  {  35, "ms175" },
  {  36, "ms180" },
  {  37, "ms185" },
  {  38, "ms190" },
  {  39, "ms195" },
  {  40, "ms200" },
  {  41, "ms205" },
  {  42, "ms210" },
  {  43, "ms215" },
  {  44, "ms220" },
  {  45, "ms225" },
  {  46, "ms230" },
  {  47, "ms235" },
  {  48, "ms240" },
  {  49, "ms245" },
  {  50, "ms250" },
  {  51, "ms300" },
  {  52, "ms350" },
  {  53, "ms400" },
  {  54, "ms450" },
  {  55, "ms500" },
  {  56, "spare8" },
  {  57, "spare7" },
  {  58, "spare6" },
  {  59, "spare5" },
  {  60, "spare4" },
  {  61, "spare3" },
  {  62, "spare2" },
  {  63, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_StatusProhibit(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     64, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t DL_AM_RLC_sequence[] = {
  { &hf_lte_rrc_t_Reordering, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_Reordering },
  { &hf_lte_rrc_t_StatusProhibit, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_StatusProhibit },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_DL_AM_RLC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_DL_AM_RLC, DL_AM_RLC_sequence);

  return offset;
}


static const per_sequence_t T_am_sequence[] = {
  { &hf_lte_rrc_ul_AM_RLC   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_UL_AM_RLC },
  { &hf_lte_rrc_dl_AM_RLC   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_DL_AM_RLC },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_am(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_am, T_am_sequence);

  return offset;
}


static const value_string lte_rrc_SN_FieldLength_vals[] = {
  {   0, "size5" },
  {   1, "size10" },
  { 0, NULL }
};


static int
dissect_lte_rrc_SN_FieldLength(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t UL_UM_RLC_sequence[] = {
  { &hf_lte_rrc_sn_FieldLength, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SN_FieldLength },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_UL_UM_RLC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_UL_UM_RLC, UL_UM_RLC_sequence);

  return offset;
}


static const per_sequence_t DL_UM_RLC_sequence[] = {
  { &hf_lte_rrc_sn_FieldLength, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SN_FieldLength },
  { &hf_lte_rrc_t_Reordering, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_Reordering },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_DL_UM_RLC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_DL_UM_RLC, DL_UM_RLC_sequence);

  return offset;
}


static const per_sequence_t T_um_Bi_Directional_sequence[] = {
  { &hf_lte_rrc_ul_UM_RLC   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_UL_UM_RLC },
  { &hf_lte_rrc_dl_UM_RLC   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_DL_UM_RLC },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_um_Bi_Directional(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_um_Bi_Directional, T_um_Bi_Directional_sequence);

  return offset;
}


static const per_sequence_t T_um_Uni_Directional_UL_sequence[] = {
  { &hf_lte_rrc_ul_UM_RLC   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_UL_UM_RLC },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_um_Uni_Directional_UL(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_um_Uni_Directional_UL, T_um_Uni_Directional_UL_sequence);

  return offset;
}


static const per_sequence_t T_um_Uni_Directional_DL_sequence[] = {
  { &hf_lte_rrc_dl_UM_RLC   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_DL_UM_RLC },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_um_Uni_Directional_DL(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_um_Uni_Directional_DL, T_um_Uni_Directional_DL_sequence);

  return offset;
}


static const value_string lte_rrc_RLC_Config_vals[] = {
  {   0, "am" },
  {   1, "um-Bi-Directional" },
  {   2, "um-Uni-Directional-UL" },
  {   3, "um-Uni-Directional-DL" },
  { 0, NULL }
};

static const per_choice_t RLC_Config_choice[] = {
  {   0, &hf_lte_rrc_am          , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_T_am },
  {   1, &hf_lte_rrc_um_Bi_Directional, ASN1_EXTENSION_ROOT    , dissect_lte_rrc_T_um_Bi_Directional },
  {   2, &hf_lte_rrc_um_Uni_Directional_UL, ASN1_EXTENSION_ROOT    , dissect_lte_rrc_T_um_Uni_Directional_UL },
  {   3, &hf_lte_rrc_um_Uni_Directional_DL, ASN1_EXTENSION_ROOT    , dissect_lte_rrc_T_um_Uni_Directional_DL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_RLC_Config(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_RLC_Config, RLC_Config_choice,
                                 NULL);

  return offset;
}


static const value_string lte_rrc_T_rlc_Config_vals[] = {
  {   0, "explicitValue" },
  {   1, "defaultValue" },
  { 0, NULL }
};

static const per_choice_t T_rlc_Config_choice[] = {
  {   0, &hf_lte_rrc_explicitValue_02, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_RLC_Config },
  {   1, &hf_lte_rrc_defaultValue, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_rlc_Config(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_rlc_Config, T_rlc_Config_choice,
                                 NULL);

  return offset;
}


static const value_string lte_rrc_T_prioritisedBitRate_vals[] = {
  {   0, "kBps0" },
  {   1, "kBps8" },
  {   2, "kBps16" },
  {   3, "kBps32" },
  {   4, "kBps64" },
  {   5, "kBps128" },
  {   6, "kBps256" },
  {   7, "infinity" },
  {   8, "spare8" },
  {   9, "spare7" },
  {  10, "spare6" },
  {  11, "spare5" },
  {  12, "spare4" },
  {  13, "spare3" },
  {  14, "spare2" },
  {  15, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_prioritisedBitRate(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_bucketSizeDuration_vals[] = {
  {   0, "ms50" },
  {   1, "ms100" },
  {   2, "ms150" },
  {   3, "ms300" },
  {   4, "ms500" },
  {   5, "ms1000" },
  {   6, "spare2" },
  {   7, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_bucketSizeDuration(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t T_ul_SpecificParameters_sequence[] = {
  { &hf_lte_rrc_priority    , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_1_16 },
  { &hf_lte_rrc_prioritisedBitRate, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_prioritisedBitRate },
  { &hf_lte_rrc_bucketSizeDuration, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_bucketSizeDuration },
  { &hf_lte_rrc_logicalChannelGroup, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_INTEGER_0_3 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_ul_SpecificParameters(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_ul_SpecificParameters, T_ul_SpecificParameters_sequence);

  return offset;
}


static const value_string lte_rrc_T_logicalChannelSR_Mask_r9_vals[] = {
  {   0, "setup" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_logicalChannelSR_Mask_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t LogicalChannelConfig_sequence[] = {
  { &hf_lte_rrc_ul_SpecificParameters, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_T_ul_SpecificParameters },
  { &hf_lte_rrc_logicalChannelSR_Mask_r9, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_T_logicalChannelSR_Mask_r9 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_LogicalChannelConfig(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_LogicalChannelConfig, LogicalChannelConfig_sequence);

  return offset;
}


static const value_string lte_rrc_T_logicalChannelConfig_vals[] = {
  {   0, "explicitValue" },
  {   1, "defaultValue" },
  { 0, NULL }
};

static const per_choice_t T_logicalChannelConfig_choice[] = {
  {   0, &hf_lte_rrc_explicitValue_03, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_LogicalChannelConfig },
  {   1, &hf_lte_rrc_defaultValue, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_logicalChannelConfig(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_logicalChannelConfig, T_logicalChannelConfig_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t SRB_ToAddMod_sequence[] = {
  { &hf_lte_rrc_srb_Identity, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_1_2 },
  { &hf_lte_rrc_rlc_Config  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_T_rlc_Config },
  { &hf_lte_rrc_logicalChannelConfig, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_T_logicalChannelConfig },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SRB_ToAddMod(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SRB_ToAddMod, SRB_ToAddMod_sequence);

  return offset;
}


static const per_sequence_t SRB_ToAddModList_sequence_of[1] = {
  { &hf_lte_rrc_SRB_ToAddModList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SRB_ToAddMod },
};

static int
dissect_lte_rrc_SRB_ToAddModList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_SRB_ToAddModList, SRB_ToAddModList_sequence_of,
                                                  1, 2, FALSE);

  return offset;
}



static int
dissect_lte_rrc_DRB_Identity(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, 32U, NULL, FALSE);

  return offset;
}


static const value_string lte_rrc_T_discardTimer_vals[] = {
  {   0, "ms50" },
  {   1, "ms100" },
  {   2, "ms150" },
  {   3, "ms300" },
  {   4, "ms500" },
  {   5, "ms750" },
  {   6, "ms1500" },
  {   7, "infinity" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_discardTimer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t T_rlc_AM_sequence[] = {
  { &hf_lte_rrc_statusReportRequired, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_rlc_AM(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_rlc_AM, T_rlc_AM_sequence);

  return offset;
}


static const value_string lte_rrc_T_pdcp_SN_Size_vals[] = {
  {   0, "len7bits" },
  {   1, "len12bits" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_pdcp_SN_Size(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t T_rlc_UM_sequence[] = {
  { &hf_lte_rrc_pdcp_SN_Size, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_pdcp_SN_Size },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_rlc_UM(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_rlc_UM, T_rlc_UM_sequence);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_1_16383(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, 16383U, NULL, FALSE);

  return offset;
}


static const per_sequence_t T_profiles_sequence[] = {
  { &hf_lte_rrc_profile0x0001, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_profile0x0002, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_profile0x0003, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_profile0x0004, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_profile0x0006, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_profile0x0101, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_profile0x0102, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_profile0x0103, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_profile0x0104, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_profiles(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_profiles, T_profiles_sequence);

  return offset;
}


static const per_sequence_t T_rohc_sequence[] = {
  { &hf_lte_rrc_maxCID      , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_INTEGER_1_16383 },
  { &hf_lte_rrc_profiles    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_profiles },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_rohc(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_rohc, T_rohc_sequence);

  return offset;
}


static const value_string lte_rrc_T_headerCompression_vals[] = {
  {   0, "notUsed" },
  {   1, "rohc" },
  { 0, NULL }
};

static const per_choice_t T_headerCompression_choice[] = {
  {   0, &hf_lte_rrc_notUsed     , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   1, &hf_lte_rrc_rohc        , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_rohc },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_headerCompression(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_headerCompression, T_headerCompression_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t PDCP_Config_sequence[] = {
  { &hf_lte_rrc_discardTimer, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_T_discardTimer },
  { &hf_lte_rrc_rlc_AM      , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_T_rlc_AM },
  { &hf_lte_rrc_rlc_UM      , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_T_rlc_UM },
  { &hf_lte_rrc_headerCompression, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_headerCompression },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_PDCP_Config(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_PDCP_Config, PDCP_Config_sequence);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_3_10(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            3U, 10U, NULL, FALSE);

  return offset;
}


static const per_sequence_t DRB_ToAddMod_sequence[] = {
  { &hf_lte_rrc_eps_BearerIdentity, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_INTEGER_0_15 },
  { &hf_lte_rrc_drb_Identity, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_DRB_Identity },
  { &hf_lte_rrc_pdcp_Config , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_PDCP_Config },
  { &hf_lte_rrc_rlc_Config_01, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_RLC_Config },
  { &hf_lte_rrc_logicalChannelIdentity, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_INTEGER_3_10 },
  { &hf_lte_rrc_logicalChannelConfig_01, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_LogicalChannelConfig },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_DRB_ToAddMod(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_DRB_ToAddMod, DRB_ToAddMod_sequence);

  return offset;
}


static const per_sequence_t DRB_ToAddModList_sequence_of[1] = {
  { &hf_lte_rrc_DRB_ToAddModList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_DRB_ToAddMod },
};

static int
dissect_lte_rrc_DRB_ToAddModList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_DRB_ToAddModList, DRB_ToAddModList_sequence_of,
                                                  1, maxDRB, FALSE);

  return offset;
}


static const per_sequence_t DRB_ToReleaseList_sequence_of[1] = {
  { &hf_lte_rrc_DRB_ToReleaseList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_DRB_Identity },
};

static int
dissect_lte_rrc_DRB_ToReleaseList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_DRB_ToReleaseList, DRB_ToReleaseList_sequence_of,
                                                  1, maxDRB, FALSE);

  return offset;
}


static const value_string lte_rrc_T_maxHARQ_Tx_vals[] = {
  {   0, "n1" },
  {   1, "n2" },
  {   2, "n3" },
  {   3, "n4" },
  {   4, "n5" },
  {   5, "n6" },
  {   6, "n7" },
  {   7, "n8" },
  {   8, "n10" },
  {   9, "n12" },
  {  10, "n16" },
  {  11, "n20" },
  {  12, "n24" },
  {  13, "n28" },
  {  14, "spare2" },
  {  15, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_maxHARQ_Tx(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_periodicBSR_Timer_vals[] = {
  {   0, "sf5" },
  {   1, "sf10" },
  {   2, "sf16" },
  {   3, "sf20" },
  {   4, "sf32" },
  {   5, "sf40" },
  {   6, "sf64" },
  {   7, "sf80" },
  {   8, "sf128" },
  {   9, "sf160" },
  {  10, "sf320" },
  {  11, "sf640" },
  {  12, "sf1280" },
  {  13, "sf2560" },
  {  14, "infinity" },
  {  15, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_periodicBSR_Timer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_retxBSR_Timer_vals[] = {
  {   0, "sf320" },
  {   1, "sf640" },
  {   2, "sf1280" },
  {   3, "sf2560" },
  {   4, "sf5120" },
  {   5, "sf10240" },
  {   6, "spare2" },
  {   7, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_retxBSR_Timer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t T_ul_SCH_Config_sequence[] = {
  { &hf_lte_rrc_maxHARQ_Tx  , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_maxHARQ_Tx },
  { &hf_lte_rrc_periodicBSR_Timer, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_periodicBSR_Timer },
  { &hf_lte_rrc_retxBSR_Timer, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_retxBSR_Timer },
  { &hf_lte_rrc_ttiBundling , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_ul_SCH_Config(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_ul_SCH_Config, T_ul_SCH_Config_sequence);

  return offset;
}


static const value_string lte_rrc_T_onDurationTimer_vals[] = {
  {   0, "psf1" },
  {   1, "psf2" },
  {   2, "psf3" },
  {   3, "psf4" },
  {   4, "psf5" },
  {   5, "psf6" },
  {   6, "psf8" },
  {   7, "psf10" },
  {   8, "psf20" },
  {   9, "psf30" },
  {  10, "psf40" },
  {  11, "psf50" },
  {  12, "psf60" },
  {  13, "psf80" },
  {  14, "psf100" },
  {  15, "psf200" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_onDurationTimer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_drx_InactivityTimer_vals[] = {
  {   0, "psf1" },
  {   1, "psf2" },
  {   2, "psf3" },
  {   3, "psf4" },
  {   4, "psf5" },
  {   5, "psf6" },
  {   6, "psf8" },
  {   7, "psf10" },
  {   8, "psf20" },
  {   9, "psf30" },
  {  10, "psf40" },
  {  11, "psf50" },
  {  12, "psf60" },
  {  13, "psf80" },
  {  14, "psf100" },
  {  15, "psf200" },
  {  16, "psf300" },
  {  17, "psf500" },
  {  18, "psf750" },
  {  19, "psf1280" },
  {  20, "psf1920" },
  {  21, "psf2560" },
  {  22, "spare10" },
  {  23, "spare9" },
  {  24, "spare8" },
  {  25, "spare7" },
  {  26, "spare6" },
  {  27, "spare5" },
  {  28, "spare4" },
  {  29, "spare3" },
  {  30, "spare2" },
  {  31, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_drx_InactivityTimer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     32, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_drx_RetransmissionTimer_vals[] = {
  {   0, "psf1" },
  {   1, "psf2" },
  {   2, "psf4" },
  {   3, "psf6" },
  {   4, "psf8" },
  {   5, "psf16" },
  {   6, "psf24" },
  {   7, "psf33" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_drx_RetransmissionTimer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 9U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_19(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 19U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_79(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 79U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_127(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 127U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_159(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 159U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_319(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 319U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_511(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 511U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_639(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 639U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_1023(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 1023U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_1279(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 1279U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_2559(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 2559U, NULL, FALSE);

  return offset;
}


static const value_string lte_rrc_T_longDRX_CycleStartOffset_vals[] = {
  {   0, "sf10" },
  {   1, "sf20" },
  {   2, "sf32" },
  {   3, "sf40" },
  {   4, "sf64" },
  {   5, "sf80" },
  {   6, "sf128" },
  {   7, "sf160" },
  {   8, "sf256" },
  {   9, "sf320" },
  {  10, "sf512" },
  {  11, "sf640" },
  {  12, "sf1024" },
  {  13, "sf1280" },
  {  14, "sf2048" },
  {  15, "sf2560" },
  { 0, NULL }
};

static const per_choice_t T_longDRX_CycleStartOffset_choice[] = {
  {   0, &hf_lte_rrc_sf10        , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_INTEGER_0_9 },
  {   1, &hf_lte_rrc_sf20        , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_INTEGER_0_19 },
  {   2, &hf_lte_rrc_sf32        , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_INTEGER_0_31 },
  {   3, &hf_lte_rrc_sf40        , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_INTEGER_0_39 },
  {   4, &hf_lte_rrc_sf64        , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_INTEGER_0_63 },
  {   5, &hf_lte_rrc_sf80        , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_INTEGER_0_79 },
  {   6, &hf_lte_rrc_sf128       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_INTEGER_0_127 },
  {   7, &hf_lte_rrc_sf160       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_INTEGER_0_159 },
  {   8, &hf_lte_rrc_sf256       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_INTEGER_0_255 },
  {   9, &hf_lte_rrc_sf320       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_INTEGER_0_319 },
  {  10, &hf_lte_rrc_sf512       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_INTEGER_0_511 },
  {  11, &hf_lte_rrc_sf640       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_INTEGER_0_639 },
  {  12, &hf_lte_rrc_sf1024      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_INTEGER_0_1023 },
  {  13, &hf_lte_rrc_sf1280      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_INTEGER_0_1279 },
  {  14, &hf_lte_rrc_sf2048      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_INTEGER_0_2047 },
  {  15, &hf_lte_rrc_sf2560      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_INTEGER_0_2559 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_longDRX_CycleStartOffset(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_longDRX_CycleStartOffset, T_longDRX_CycleStartOffset_choice,
                                 NULL);

  return offset;
}


static const value_string lte_rrc_T_shortDRX_Cycle_vals[] = {
  {   0, "sf2" },
  {   1, "sf5" },
  {   2, "sf8" },
  {   3, "sf10" },
  {   4, "sf16" },
  {   5, "sf20" },
  {   6, "sf32" },
  {   7, "sf40" },
  {   8, "sf64" },
  {   9, "sf80" },
  {  10, "sf128" },
  {  11, "sf160" },
  {  12, "sf256" },
  {  13, "sf320" },
  {  14, "sf512" },
  {  15, "sf640" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_shortDRX_Cycle(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t T_shortDRX_sequence[] = {
  { &hf_lte_rrc_shortDRX_Cycle, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_shortDRX_Cycle },
  { &hf_lte_rrc_drxShortCycleTimer, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_1_16 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_shortDRX(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_shortDRX, T_shortDRX_sequence);

  return offset;
}


static const per_sequence_t T_setup_03_sequence[] = {
  { &hf_lte_rrc_onDurationTimer, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_onDurationTimer },
  { &hf_lte_rrc_drx_InactivityTimer, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_drx_InactivityTimer },
  { &hf_lte_rrc_drx_RetransmissionTimer, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_drx_RetransmissionTimer },
  { &hf_lte_rrc_longDRX_CycleStartOffset, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_longDRX_CycleStartOffset },
  { &hf_lte_rrc_shortDRX    , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_shortDRX },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_setup_03(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_setup_03, T_setup_03_sequence);

  return offset;
}


static const value_string lte_rrc_DRX_Config_vals[] = {
  {   0, "release" },
  {   1, "setup" },
  { 0, NULL }
};

static const per_choice_t DRX_Config_choice[] = {
  {   0, &hf_lte_rrc_release     , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   1, &hf_lte_rrc_setup_03    , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_setup_03 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_DRX_Config(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_DRX_Config, DRX_Config_choice,
                                 NULL);

  return offset;
}


static const value_string lte_rrc_T_periodicPHR_Timer_vals[] = {
  {   0, "sf10" },
  {   1, "sf20" },
  {   2, "sf50" },
  {   3, "sf100" },
  {   4, "sf200" },
  {   5, "sf500" },
  {   6, "sf1000" },
  {   7, "infinity" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_periodicPHR_Timer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_prohibitPHR_Timer_vals[] = {
  {   0, "sf0" },
  {   1, "sf10" },
  {   2, "sf20" },
  {   3, "sf50" },
  {   4, "sf100" },
  {   5, "sf200" },
  {   6, "sf500" },
  {   7, "sf1000" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_prohibitPHR_Timer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_dl_PathlossChange_vals[] = {
  {   0, "dB1" },
  {   1, "dB3" },
  {   2, "dB6" },
  {   3, "infinity" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_dl_PathlossChange(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t T_setup_02_sequence[] = {
  { &hf_lte_rrc_periodicPHR_Timer, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_periodicPHR_Timer },
  { &hf_lte_rrc_prohibitPHR_Timer, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_prohibitPHR_Timer },
  { &hf_lte_rrc_dl_PathlossChange, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_dl_PathlossChange },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_setup_02(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_setup_02, T_setup_02_sequence);

  return offset;
}


static const value_string lte_rrc_T_phr_Config_vals[] = {
  {   0, "release" },
  {   1, "setup" },
  { 0, NULL }
};

static const per_choice_t T_phr_Config_choice[] = {
  {   0, &hf_lte_rrc_release     , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   1, &hf_lte_rrc_setup_02    , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_setup_02 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_phr_Config(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_phr_Config, T_phr_Config_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t MAC_MainConfig_sequence[] = {
  { &hf_lte_rrc_ul_SCH_Config, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_T_ul_SCH_Config },
  { &hf_lte_rrc_drx_Config  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_DRX_Config },
  { &hf_lte_rrc_timeAlignmentTimerDedicated, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_TimeAlignmentTimer },
  { &hf_lte_rrc_phr_Config  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_T_phr_Config },
  { &hf_lte_rrc_sr_ProhibitTimer_r9, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_INTEGER_0_7 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MAC_MainConfig(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MAC_MainConfig, MAC_MainConfig_sequence);

  return offset;
}


static const value_string lte_rrc_T_mac_MainConfig_vals[] = {
  {   0, "explicitValue" },
  {   1, "defaultValue" },
  { 0, NULL }
};

static const per_choice_t T_mac_MainConfig_choice[] = {
  {   0, &hf_lte_rrc_explicitValue_01, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_MAC_MainConfig },
  {   1, &hf_lte_rrc_defaultValue, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_mac_MainConfig(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_mac_MainConfig, T_mac_MainConfig_choice,
                                 NULL);

  return offset;
}



static int
dissect_lte_rrc_C_RNTI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     16, 16, FALSE, NULL);

  return offset;
}


static const value_string lte_rrc_T_semiPersistSchedIntervalDL_vals[] = {
  {   0, "sf10" },
  {   1, "sf20" },
  {   2, "sf32" },
  {   3, "sf40" },
  {   4, "sf64" },
  {   5, "sf80" },
  {   6, "sf128" },
  {   7, "sf160" },
  {   8, "sf320" },
  {   9, "sf640" },
  {  10, "spare6" },
  {  11, "spare5" },
  {  12, "spare4" },
  {  13, "spare3" },
  {  14, "spare2" },
  {  15, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_semiPersistSchedIntervalDL(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t N1_PUCCH_AN_PersistentList_sequence_of[1] = {
  { &hf_lte_rrc_N1_PUCCH_AN_PersistentList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_2047 },
};

static int
dissect_lte_rrc_N1_PUCCH_AN_PersistentList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_N1_PUCCH_AN_PersistentList, N1_PUCCH_AN_PersistentList_sequence_of,
                                                  1, 4, FALSE);

  return offset;
}


static const per_sequence_t T_setup_09_sequence[] = {
  { &hf_lte_rrc_semiPersistSchedIntervalDL, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_semiPersistSchedIntervalDL },
  { &hf_lte_rrc_numberOfConfSPS_Processes, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_1_8 },
  { &hf_lte_rrc_n1_PUCCH_AN_PersistentList, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_N1_PUCCH_AN_PersistentList },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_setup_09(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_setup_09, T_setup_09_sequence);

  return offset;
}


static const value_string lte_rrc_SPS_ConfigDL_vals[] = {
  {   0, "release" },
  {   1, "setup" },
  { 0, NULL }
};

static const per_choice_t SPS_ConfigDL_choice[] = {
  {   0, &hf_lte_rrc_release     , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   1, &hf_lte_rrc_setup_09    , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_setup_09 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_SPS_ConfigDL(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_SPS_ConfigDL, SPS_ConfigDL_choice,
                                 NULL);

  return offset;
}


static const value_string lte_rrc_T_semiPersistSchedIntervalUL_vals[] = {
  {   0, "sf10" },
  {   1, "sf20" },
  {   2, "sf32" },
  {   3, "sf40" },
  {   4, "sf64" },
  {   5, "sf80" },
  {   6, "sf128" },
  {   7, "sf160" },
  {   8, "sf320" },
  {   9, "sf640" },
  {  10, "spare6" },
  {  11, "spare5" },
  {  12, "spare4" },
  {  13, "spare3" },
  {  14, "spare2" },
  {  15, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_semiPersistSchedIntervalUL(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_implicitReleaseAfter_vals[] = {
  {   0, "e2" },
  {   1, "e3" },
  {   2, "e4" },
  {   3, "e8" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_implicitReleaseAfter(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, FALSE, 0, NULL);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_M8_7(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            -8, 7U, NULL, FALSE);

  return offset;
}


static const per_sequence_t T_p0_Persistent_sequence[] = {
  { &hf_lte_rrc_p0_NominalPUSCH_Persistent, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_M126_24 },
  { &hf_lte_rrc_p0_UE_PUSCH_Persistent, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_M8_7 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_p0_Persistent(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_p0_Persistent, T_p0_Persistent_sequence);

  return offset;
}


static const value_string lte_rrc_T_twoIntervalsConfig_vals[] = {
  {   0, "true" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_twoIntervalsConfig(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t T_setup_10_sequence[] = {
  { &hf_lte_rrc_semiPersistSchedIntervalUL, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_semiPersistSchedIntervalUL },
  { &hf_lte_rrc_implicitReleaseAfter, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_implicitReleaseAfter },
  { &hf_lte_rrc_p0_Persistent, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_T_p0_Persistent },
  { &hf_lte_rrc_twoIntervalsConfig, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_T_twoIntervalsConfig },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_setup_10(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_setup_10, T_setup_10_sequence);

  return offset;
}


static const value_string lte_rrc_SPS_ConfigUL_vals[] = {
  {   0, "release" },
  {   1, "setup" },
  { 0, NULL }
};

static const per_choice_t SPS_ConfigUL_choice[] = {
  {   0, &hf_lte_rrc_release     , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   1, &hf_lte_rrc_setup_10    , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_setup_10 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_SPS_ConfigUL(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_SPS_ConfigUL, SPS_ConfigUL_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t SPS_Config_sequence[] = {
  { &hf_lte_rrc_semiPersistSchedC_RNTI, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_C_RNTI },
  { &hf_lte_rrc_sps_ConfigDL, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_SPS_ConfigDL },
  { &hf_lte_rrc_sps_ConfigUL, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_SPS_ConfigUL },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SPS_Config(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SPS_Config, SPS_Config_sequence);

  return offset;
}


static const value_string lte_rrc_T_p_a_vals[] = {
  {   0, "dB-6" },
  {   1, "dB-4dot77" },
  {   2, "dB-3" },
  {   3, "dB-1dot77" },
  {   4, "dB0" },
  {   5, "dB1" },
  {   6, "dB2" },
  {   7, "dB3" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_p_a(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t PDSCH_ConfigDedicated_sequence[] = {
  { &hf_lte_rrc_p_a         , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_p_a },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_PDSCH_ConfigDedicated(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_PDSCH_ConfigDedicated, PDSCH_ConfigDedicated_sequence);

  return offset;
}


static const value_string lte_rrc_T_repetitionFactor_vals[] = {
  {   0, "n2" },
  {   1, "n4" },
  {   2, "n6" },
  {   3, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_repetitionFactor(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t T_setup_04_sequence[] = {
  { &hf_lte_rrc_repetitionFactor, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_repetitionFactor },
  { &hf_lte_rrc_n1PUCCH_AN_Rep, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_2047 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_setup_04(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_setup_04, T_setup_04_sequence);

  return offset;
}


static const value_string lte_rrc_T_ackNackRepetition_vals[] = {
  {   0, "release" },
  {   1, "setup" },
  { 0, NULL }
};

static const per_choice_t T_ackNackRepetition_choice[] = {
  {   0, &hf_lte_rrc_release     , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   1, &hf_lte_rrc_setup_04    , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_setup_04 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_ackNackRepetition(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_ackNackRepetition, T_ackNackRepetition_choice,
                                 NULL);

  return offset;
}


static const value_string lte_rrc_T_tdd_AckNackFeedbackMode_vals[] = {
  {   0, "bundling" },
  {   1, "multiplexing" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_tdd_AckNackFeedbackMode(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t PUCCH_ConfigDedicated_sequence[] = {
  { &hf_lte_rrc_ackNackRepetition, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_ackNackRepetition },
  { &hf_lte_rrc_tdd_AckNackFeedbackMode, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_tdd_AckNackFeedbackMode },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_PUCCH_ConfigDedicated(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_PUCCH_ConfigDedicated, PUCCH_ConfigDedicated_sequence);

  return offset;
}


static const per_sequence_t PUSCH_ConfigDedicated_sequence[] = {
  { &hf_lte_rrc_betaOffset_ACK_Index, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_15 },
  { &hf_lte_rrc_betaOffset_RI_Index, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_15 },
  { &hf_lte_rrc_betaOffset_CQI_Index, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_15 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_PUSCH_ConfigDedicated(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_PUSCH_ConfigDedicated, PUSCH_ConfigDedicated_sequence);

  return offset;
}


static const value_string lte_rrc_T_deltaMCS_Enabled_vals[] = {
  {   0, "en0" },
  {   1, "en1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_deltaMCS_Enabled(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_FilterCoefficient_vals[] = {
  {   0, "fc0" },
  {   1, "fc1" },
  {   2, "fc2" },
  {   3, "fc3" },
  {   4, "fc4" },
  {   5, "fc5" },
  {   6, "fc6" },
  {   7, "fc7" },
  {   8, "fc8" },
  {   9, "fc9" },
  {  10, "fc11" },
  {  11, "fc13" },
  {  12, "fc15" },
  {  13, "fc17" },
  {  14, "fc19" },
  {  15, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_FilterCoefficient(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t UplinkPowerControlDedicated_sequence[] = {
  { &hf_lte_rrc_p0_UE_PUSCH , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_M8_7 },
  { &hf_lte_rrc_deltaMCS_Enabled, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_deltaMCS_Enabled },
  { &hf_lte_rrc_accumulationEnabled, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_p0_UE_PUCCH , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_M8_7 },
  { &hf_lte_rrc_pSRS_Offset , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_15 },
  { &hf_lte_rrc_filterCoefficient, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_FilterCoefficient },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_UplinkPowerControlDedicated(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_UplinkPowerControlDedicated, UplinkPowerControlDedicated_sequence);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_1_15(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, 15U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_1_31(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, 31U, NULL, FALSE);

  return offset;
}


static const value_string lte_rrc_TPC_Index_vals[] = {
  {   0, "indexOfFormat3" },
  {   1, "indexOfFormat3A" },
  { 0, NULL }
};

static const per_choice_t TPC_Index_choice[] = {
  {   0, &hf_lte_rrc_indexOfFormat3, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_INTEGER_1_15 },
  {   1, &hf_lte_rrc_indexOfFormat3A, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_INTEGER_1_31 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_TPC_Index(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_TPC_Index, TPC_Index_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_setup_11_sequence[] = {
  { &hf_lte_rrc_tpc_RNTI    , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_16 },
  { &hf_lte_rrc_tpc_Index   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_TPC_Index },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_setup_11(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_setup_11, T_setup_11_sequence);

  return offset;
}


static const value_string lte_rrc_TPC_PDCCH_Config_vals[] = {
  {   0, "release" },
  {   1, "setup" },
  { 0, NULL }
};

static const per_choice_t TPC_PDCCH_Config_choice[] = {
  {   0, &hf_lte_rrc_release     , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   1, &hf_lte_rrc_setup_11    , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_setup_11 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_TPC_PDCCH_Config(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_TPC_PDCCH_Config, TPC_PDCCH_Config_choice,
                                 NULL);

  return offset;
}


static const value_string lte_rrc_T_cqi_ReportModeAperiodic_vals[] = {
  {   0, "rm12" },
  {   1, "rm20" },
  {   2, "rm22" },
  {   3, "rm30" },
  {   4, "rm31" },
  {   5, "spare3" },
  {   6, "spare2" },
  {   7, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_cqi_ReportModeAperiodic(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_1185(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 1185U, NULL, FALSE);

  return offset;
}


static const per_sequence_t T_subbandCQI_sequence[] = {
  { &hf_lte_rrc_k           , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_1_4 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_subbandCQI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_subbandCQI, T_subbandCQI_sequence);

  return offset;
}


static const value_string lte_rrc_T_cqi_FormatIndicatorPeriodic_vals[] = {
  {   0, "widebandCQI" },
  {   1, "subbandCQI" },
  { 0, NULL }
};

static const per_choice_t T_cqi_FormatIndicatorPeriodic_choice[] = {
  {   0, &hf_lte_rrc_widebandCQI , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   1, &hf_lte_rrc_subbandCQI  , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_subbandCQI },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_cqi_FormatIndicatorPeriodic(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_cqi_FormatIndicatorPeriodic, T_cqi_FormatIndicatorPeriodic_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_setup_01_sequence[] = {
  { &hf_lte_rrc_cqi_PUCCH_ResourceIndex, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_1185 },
  { &hf_lte_rrc_cqi_pmi_ConfigIndex, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_1023 },
  { &hf_lte_rrc_cqi_FormatIndicatorPeriodic, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_cqi_FormatIndicatorPeriodic },
  { &hf_lte_rrc_ri_ConfigIndex, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_INTEGER_0_1023 },
  { &hf_lte_rrc_simultaneousAckNackAndCQI, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_setup_01(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_setup_01, T_setup_01_sequence);

  return offset;
}


static const value_string lte_rrc_CQI_ReportPeriodic_vals[] = {
  {   0, "release" },
  {   1, "setup" },
  { 0, NULL }
};

static const per_choice_t CQI_ReportPeriodic_choice[] = {
  {   0, &hf_lte_rrc_release     , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   1, &hf_lte_rrc_setup_01    , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_setup_01 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_CQI_ReportPeriodic(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_CQI_ReportPeriodic, CQI_ReportPeriodic_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t CQI_ReportConfig_sequence[] = {
  { &hf_lte_rrc_cqi_ReportModeAperiodic, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_cqi_ReportModeAperiodic },
  { &hf_lte_rrc_nomPDSCH_RS_EPRE_Offset, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_M1_6 },
  { &hf_lte_rrc_cqi_ReportPeriodic, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_CQI_ReportPeriodic },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CQI_ReportConfig(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CQI_ReportConfig, CQI_ReportConfig_sequence);

  return offset;
}


static const value_string lte_rrc_T_srs_Bandwidth_vals[] = {
  {   0, "bw0" },
  {   1, "bw1" },
  {   2, "bw2" },
  {   3, "bw3" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_srs_Bandwidth(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_srs_HoppingBandwidth_vals[] = {
  {   0, "hbw0" },
  {   1, "hbw1" },
  {   2, "hbw2" },
  {   3, "hbw3" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_srs_HoppingBandwidth(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, FALSE, 0, NULL);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_23(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 23U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_1(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 1U, NULL, FALSE);

  return offset;
}


static const value_string lte_rrc_T_cyclicShift_vals[] = {
  {   0, "cs0" },
  {   1, "cs1" },
  {   2, "cs2" },
  {   3, "cs3" },
  {   4, "cs4" },
  {   5, "cs5" },
  {   6, "cs6" },
  {   7, "cs7" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_cyclicShift(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t T_setup_08_sequence[] = {
  { &hf_lte_rrc_srs_Bandwidth, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_srs_Bandwidth },
  { &hf_lte_rrc_srs_HoppingBandwidth, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_srs_HoppingBandwidth },
  { &hf_lte_rrc_freqDomainPosition, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_23 },
  { &hf_lte_rrc_duration    , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_srs_ConfigIndex, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_1023 },
  { &hf_lte_rrc_transmissionComb, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_1 },
  { &hf_lte_rrc_cyclicShift_01, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_cyclicShift },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_setup_08(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_setup_08, T_setup_08_sequence);

  return offset;
}


static const value_string lte_rrc_SoundingRS_UL_ConfigDedicated_vals[] = {
  {   0, "release" },
  {   1, "setup" },
  { 0, NULL }
};

static const per_choice_t SoundingRS_UL_ConfigDedicated_choice[] = {
  {   0, &hf_lte_rrc_release     , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   1, &hf_lte_rrc_setup_08    , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_setup_08 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_SoundingRS_UL_ConfigDedicated(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_SoundingRS_UL_ConfigDedicated, SoundingRS_UL_ConfigDedicated_choice,
                                 NULL);

  return offset;
}


static const value_string lte_rrc_T_transmissionMode_vals[] = {
  {   0, "tm1" },
  {   1, "tm2" },
  {   2, "tm3" },
  {   3, "tm4" },
  {   4, "tm5" },
  {   5, "tm6" },
  {   6, "tm7" },
  {   7, "tm8-v920" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_transmissionMode(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}



static int
dissect_lte_rrc_BIT_STRING_SIZE_2(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     2, 2, FALSE, NULL);

  return offset;
}



static int
dissect_lte_rrc_BIT_STRING_SIZE_4(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     4, 4, FALSE, NULL);

  return offset;
}



static int
dissect_lte_rrc_BIT_STRING_SIZE_64(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     64, 64, FALSE, NULL);

  return offset;
}


static const value_string lte_rrc_T_codebookSubsetRestriction_vals[] = {
  {   0, "n2TxAntenna-tm3" },
  {   1, "n4TxAntenna-tm3" },
  {   2, "n2TxAntenna-tm4" },
  {   3, "n4TxAntenna-tm4" },
  {   4, "n2TxAntenna-tm5" },
  {   5, "n4TxAntenna-tm5" },
  {   6, "n2TxAntenna-tm6" },
  {   7, "n4TxAntenna-tm6" },
  { 0, NULL }
};

static const per_choice_t T_codebookSubsetRestriction_choice[] = {
  {   0, &hf_lte_rrc_n2TxAntenna_tm3, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_BIT_STRING_SIZE_2 },
  {   1, &hf_lte_rrc_n4TxAntenna_tm3, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_BIT_STRING_SIZE_4 },
  {   2, &hf_lte_rrc_n2TxAntenna_tm4, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_BIT_STRING_SIZE_6 },
  {   3, &hf_lte_rrc_n4TxAntenna_tm4, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_BIT_STRING_SIZE_64 },
  {   4, &hf_lte_rrc_n2TxAntenna_tm5, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_BIT_STRING_SIZE_4 },
  {   5, &hf_lte_rrc_n4TxAntenna_tm5, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_BIT_STRING_SIZE_16 },
  {   6, &hf_lte_rrc_n2TxAntenna_tm6, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_BIT_STRING_SIZE_4 },
  {   7, &hf_lte_rrc_n4TxAntenna_tm6, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_BIT_STRING_SIZE_16 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_codebookSubsetRestriction(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_codebookSubsetRestriction, T_codebookSubsetRestriction_choice,
                                 NULL);

  return offset;
}


static const value_string lte_rrc_T_setup_vals[] = {
  {   0, "closedLoop" },
  {   1, "openLoop" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_setup(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_ue_TransmitAntennaSelection_vals[] = {
  {   0, "release" },
  {   1, "setup" },
  { 0, NULL }
};

static const per_choice_t T_ue_TransmitAntennaSelection_choice[] = {
  {   0, &hf_lte_rrc_release     , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   1, &hf_lte_rrc_setup       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_setup },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_ue_TransmitAntennaSelection(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_ue_TransmitAntennaSelection, T_ue_TransmitAntennaSelection_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t AntennaInfoDedicated_sequence[] = {
  { &hf_lte_rrc_transmissionMode, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_transmissionMode },
  { &hf_lte_rrc_codebookSubsetRestriction, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_codebookSubsetRestriction },
  { &hf_lte_rrc_ue_TransmitAntennaSelection, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_ue_TransmitAntennaSelection },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_AntennaInfoDedicated(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_AntennaInfoDedicated, AntennaInfoDedicated_sequence);

  return offset;
}


static const value_string lte_rrc_T_antennaInfo_vals[] = {
  {   0, "explicitValue" },
  {   1, "defaultValue" },
  { 0, NULL }
};

static const per_choice_t T_antennaInfo_choice[] = {
  {   0, &hf_lte_rrc_explicitValue, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_AntennaInfoDedicated },
  {   1, &hf_lte_rrc_defaultValue, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_antennaInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_antennaInfo, T_antennaInfo_choice,
                                 NULL);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_157(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 157U, NULL, FALSE);

  return offset;
}


static const value_string lte_rrc_T_dsr_TransMax_vals[] = {
  {   0, "n4" },
  {   1, "n8" },
  {   2, "n16" },
  {   3, "n32" },
  {   4, "n64" },
  {   5, "spare3" },
  {   6, "spare2" },
  {   7, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_dsr_TransMax(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t T_setup_06_sequence[] = {
  { &hf_lte_rrc_sr_PUCCH_ResourceIndex, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_2047 },
  { &hf_lte_rrc_sr_ConfigIndex, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_157 },
  { &hf_lte_rrc_dsr_TransMax, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_dsr_TransMax },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_setup_06(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_setup_06, T_setup_06_sequence);

  return offset;
}


static const value_string lte_rrc_SchedulingRequestConfig_vals[] = {
  {   0, "release" },
  {   1, "setup" },
  { 0, NULL }
};

static const per_choice_t SchedulingRequestConfig_choice[] = {
  {   0, &hf_lte_rrc_release     , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   1, &hf_lte_rrc_setup_06    , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_setup_06 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_SchedulingRequestConfig(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_SchedulingRequestConfig, SchedulingRequestConfig_choice,
                                 NULL);

  return offset;
}


static const value_string lte_rrc_T_cqi_Mask_r9_vals[] = {
  {   0, "setup" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_cqi_Mask_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_pmi_RI_Report_r9_vals[] = {
  {   0, "setup" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_pmi_RI_Report_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t CQI_ReportConfig_v920_sequence[] = {
  { &hf_lte_rrc_cqi_Mask_r9 , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_cqi_Mask_r9 },
  { &hf_lte_rrc_pmi_RI_Report_r9, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_pmi_RI_Report_r9 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CQI_ReportConfig_v920(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CQI_ReportConfig_v920, CQI_ReportConfig_v920_sequence);

  return offset;
}


static const value_string lte_rrc_T_codebookSubsetRestriction_v920_vals[] = {
  {   0, "n2TxAntenna-tm8-r9" },
  {   1, "n4TxAntenna-tm8-r9" },
  { 0, NULL }
};

static const per_choice_t T_codebookSubsetRestriction_v920_choice[] = {
  {   0, &hf_lte_rrc_n2TxAntenna_tm8_r9, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_BIT_STRING_SIZE_6 },
  {   1, &hf_lte_rrc_n4TxAntenna_tm8_r9, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_BIT_STRING_SIZE_32 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_codebookSubsetRestriction_v920(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_codebookSubsetRestriction_v920, T_codebookSubsetRestriction_v920_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t AntennaInfoDedicated_v920_sequence[] = {
  { &hf_lte_rrc_codebookSubsetRestriction_v920, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_codebookSubsetRestriction_v920 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_AntennaInfoDedicated_v920(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_AntennaInfoDedicated_v920, AntennaInfoDedicated_v920_sequence);

  return offset;
}


static const per_sequence_t PhysicalConfigDedicated_sequence[] = {
  { &hf_lte_rrc_pdsch_ConfigDedicated, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_PDSCH_ConfigDedicated },
  { &hf_lte_rrc_pucch_ConfigDedicated, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_PUCCH_ConfigDedicated },
  { &hf_lte_rrc_pusch_ConfigDedicated, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_PUSCH_ConfigDedicated },
  { &hf_lte_rrc_uplinkPowerControlDedicated, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_UplinkPowerControlDedicated },
  { &hf_lte_rrc_tpc_PDCCH_ConfigPUCCH, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_TPC_PDCCH_Config },
  { &hf_lte_rrc_tpc_PDCCH_ConfigPUSCH, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_TPC_PDCCH_Config },
  { &hf_lte_rrc_cqi_ReportConfig, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_CQI_ReportConfig },
  { &hf_lte_rrc_soundingRS_UL_ConfigDedicated, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_SoundingRS_UL_ConfigDedicated },
  { &hf_lte_rrc_antennaInfo , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_T_antennaInfo },
  { &hf_lte_rrc_schedulingRequestConfig, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_SchedulingRequestConfig },
  { &hf_lte_rrc_cqi_ReportConfig_v920, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_CQI_ReportConfig_v920 },
  { &hf_lte_rrc_antennaInfo_v920, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_AntennaInfoDedicated_v920 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_PhysicalConfigDedicated(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_PhysicalConfigDedicated, PhysicalConfigDedicated_sequence);

  return offset;
}


static const value_string lte_rrc_T_t301_r9_vals[] = {
  {   0, "ms100" },
  {   1, "ms200" },
  {   2, "ms300" },
  {   3, "ms400" },
  {   4, "ms600" },
  {   5, "ms1000" },
  {   6, "ms1500" },
  {   7, "ms2000" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_t301_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_t310_r9_vals[] = {
  {   0, "ms0" },
  {   1, "ms50" },
  {   2, "ms100" },
  {   3, "ms200" },
  {   4, "ms500" },
  {   5, "ms1000" },
  {   6, "ms2000" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_t310_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     7, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_n310_r9_vals[] = {
  {   0, "n1" },
  {   1, "n2" },
  {   2, "n3" },
  {   3, "n4" },
  {   4, "n6" },
  {   5, "n8" },
  {   6, "n10" },
  {   7, "n20" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_n310_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_t311_r9_vals[] = {
  {   0, "ms1000" },
  {   1, "ms3000" },
  {   2, "ms5000" },
  {   3, "ms10000" },
  {   4, "ms15000" },
  {   5, "ms20000" },
  {   6, "ms30000" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_t311_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     7, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_n311_r9_vals[] = {
  {   0, "n1" },
  {   1, "n2" },
  {   2, "n3" },
  {   3, "n4" },
  {   4, "n5" },
  {   5, "n6" },
  {   6, "n8" },
  {   7, "n10" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_n311_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t T_setup_05_sequence[] = {
  { &hf_lte_rrc_t301_r9     , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_t301_r9 },
  { &hf_lte_rrc_t310_r9     , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_t310_r9 },
  { &hf_lte_rrc_n310_r9     , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_n310_r9 },
  { &hf_lte_rrc_t311_r9     , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_t311_r9 },
  { &hf_lte_rrc_n311_r9     , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_n311_r9 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_setup_05(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_setup_05, T_setup_05_sequence);

  return offset;
}


static const value_string lte_rrc_RLF_TimersAndConstants_r9_vals[] = {
  {   0, "release" },
  {   1, "setup" },
  { 0, NULL }
};

static const per_choice_t RLF_TimersAndConstants_r9_choice[] = {
  {   0, &hf_lte_rrc_release     , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   1, &hf_lte_rrc_setup_05    , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_setup_05 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_RLF_TimersAndConstants_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_RLF_TimersAndConstants_r9, RLF_TimersAndConstants_r9_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t RadioResourceConfigDedicated_sequence[] = {
  { &hf_lte_rrc_srb_ToAddModList, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_SRB_ToAddModList },
  { &hf_lte_rrc_drb_ToAddModList, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_DRB_ToAddModList },
  { &hf_lte_rrc_drb_ToReleaseList, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_DRB_ToReleaseList },
  { &hf_lte_rrc_mac_MainConfig, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_T_mac_MainConfig },
  { &hf_lte_rrc_sps_Config  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_SPS_Config },
  { &hf_lte_rrc_physicalConfigDedicated, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_PhysicalConfigDedicated },
  { &hf_lte_rrc_rlf_TimersAndConstants_r9, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_RLF_TimersAndConstants_r9 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RadioResourceConfigDedicated(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RadioResourceConfigDedicated, RadioResourceConfigDedicated_sequence);

  return offset;
}



static int
dissect_lte_rrc_NextHopChainingCount(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 7U, NULL, FALSE);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_14_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_14(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_14, T_nonCriticalExtension_14_sequence);

  return offset;
}


static const per_sequence_t RRCConnectionReestablishment_r8_IEs_sequence[] = {
  { &hf_lte_rrc_radioResourceConfigDedicated, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RadioResourceConfigDedicated },
  { &hf_lte_rrc_nextHopChainingCount, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_NextHopChainingCount },
  { &hf_lte_rrc_nonCriticalExtension_20, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_14 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionReestablishment_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionReestablishment_r8_IEs, RRCConnectionReestablishment_r8_IEs_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_14_vals[] = {
  {   0, "rrcConnectionReestablishment-r8" },
  {   1, "spare7" },
  {   2, "spare6" },
  {   3, "spare5" },
  {   4, "spare4" },
  {   5, "spare3" },
  {   6, "spare2" },
  {   7, "spare1" },
  { 0, NULL }
};

static const per_choice_t T_c1_14_choice[] = {
  {   0, &hf_lte_rrc_rrcConnectionReestablishment_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_RRCConnectionReestablishment_r8_IEs },
  {   1, &hf_lte_rrc_spare7      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   2, &hf_lte_rrc_spare6      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   3, &hf_lte_rrc_spare5      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   4, &hf_lte_rrc_spare4      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   5, &hf_lte_rrc_spare3      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   6, &hf_lte_rrc_spare2      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   7, &hf_lte_rrc_spare1      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_14(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_14, T_c1_14_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_11_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_11(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_11, T_criticalExtensionsFuture_11_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_11_vals[] = {
  {   0, "c1" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_11_choice[] = {
  {   0, &hf_lte_rrc_c1_14       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_14 },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_11, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_11 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_11(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_11, T_criticalExtensions_11_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t RRCConnectionReestablishment_sequence[] = {
  { &hf_lte_rrc_rrc_TransactionIdentifier, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RRC_TransactionIdentifier },
  { &hf_lte_rrc_criticalExtensions_11, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_11 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionReestablishment(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:RRCConnectionReestablishment ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionReestablishment, RRCConnectionReestablishment_sequence);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_16_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_16(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_16, T_nonCriticalExtension_16_sequence);

  return offset;
}


static const per_sequence_t RRCConnectionReestablishmentReject_r8_IEs_sequence[] = {
  { &hf_lte_rrc_nonCriticalExtension_23, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_16 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionReestablishmentReject_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionReestablishmentReject_r8_IEs, RRCConnectionReestablishmentReject_r8_IEs_sequence);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_13_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_13(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_13, T_criticalExtensionsFuture_13_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_13_vals[] = {
  {   0, "rrcConnectionReestablishmentReject-r8" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_13_choice[] = {
  {   0, &hf_lte_rrc_rrcConnectionReestablishmentReject_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_RRCConnectionReestablishmentReject_r8_IEs },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_13, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_13 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_13(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_13, T_criticalExtensions_13_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t RRCConnectionReestablishmentReject_sequence[] = {
  { &hf_lte_rrc_criticalExtensions_13, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_13 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionReestablishmentReject(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:RRCConnectionReestablishmentReject ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionReestablishmentReject, RRCConnectionReestablishmentReject_sequence);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_17_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_17(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_17, T_nonCriticalExtension_17_sequence);

  return offset;
}


static const per_sequence_t RRCConnectionReject_r8_IEs_sequence[] = {
  { &hf_lte_rrc_waitTime    , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_1_16 },
  { &hf_lte_rrc_nonCriticalExtension_24, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_17 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionReject_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionReject_r8_IEs, RRCConnectionReject_r8_IEs_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_15_vals[] = {
  {   0, "rrcConnectionReject-r8" },
  {   1, "spare3" },
  {   2, "spare2" },
  {   3, "spare1" },
  { 0, NULL }
};

static const per_choice_t T_c1_15_choice[] = {
  {   0, &hf_lte_rrc_rrcConnectionReject_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_RRCConnectionReject_r8_IEs },
  {   1, &hf_lte_rrc_spare3      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   2, &hf_lte_rrc_spare2      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   3, &hf_lte_rrc_spare1      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_15(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_15, T_c1_15_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_15_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_15(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_15, T_criticalExtensionsFuture_15_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_15_vals[] = {
  {   0, "c1" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_15_choice[] = {
  {   0, &hf_lte_rrc_c1_15       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_15 },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_15, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_15 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_15(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_15, T_criticalExtensions_15_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t RRCConnectionReject_sequence[] = {
  { &hf_lte_rrc_criticalExtensions_15, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_15 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionReject(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:RRCConnectionReject ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionReject, RRCConnectionReject_sequence);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_19_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_19(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_19, T_nonCriticalExtension_19_sequence);

  return offset;
}


static const per_sequence_t RRCConnectionSetup_r8_IEs_sequence[] = {
  { &hf_lte_rrc_radioResourceConfigDedicated, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RadioResourceConfigDedicated },
  { &hf_lte_rrc_nonCriticalExtension_28, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_19 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionSetup_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionSetup_r8_IEs, RRCConnectionSetup_r8_IEs_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_17_vals[] = {
  {   0, "rrcConnectionSetup-r8" },
  {   1, "spare7" },
  {   2, "spare6" },
  {   3, "spare5" },
  {   4, "spare4" },
  {   5, "spare3" },
  {   6, "spare2" },
  {   7, "spare1" },
  { 0, NULL }
};

static const per_choice_t T_c1_17_choice[] = {
  {   0, &hf_lte_rrc_rrcConnectionSetup_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_RRCConnectionSetup_r8_IEs },
  {   1, &hf_lte_rrc_spare7      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   2, &hf_lte_rrc_spare6      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   3, &hf_lte_rrc_spare5      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   4, &hf_lte_rrc_spare4      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   5, &hf_lte_rrc_spare3      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   6, &hf_lte_rrc_spare2      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   7, &hf_lte_rrc_spare1      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_17(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_17, T_c1_17_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_18_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_18(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_18, T_criticalExtensionsFuture_18_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_18_vals[] = {
  {   0, "c1" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_18_choice[] = {
  {   0, &hf_lte_rrc_c1_17       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_17 },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_18, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_18 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_18(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_18, T_criticalExtensions_18_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t RRCConnectionSetup_sequence[] = {
  { &hf_lte_rrc_rrc_TransactionIdentifier, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RRC_TransactionIdentifier },
  { &hf_lte_rrc_criticalExtensions_18, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_18 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionSetup(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:RRCConnectionSetup ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionSetup, RRCConnectionSetup_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_03_vals[] = {
  {   0, "rrcConnectionReestablishment" },
  {   1, "rrcConnectionReestablishmentReject" },
  {   2, "rrcConnectionReject" },
  {   3, "rrcConnectionSetup" },
  { 0, NULL }
};

static const per_choice_t T_c1_03_choice[] = {
  {   0, &hf_lte_rrc_rrcConnectionReestablishment, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_RRCConnectionReestablishment },
  {   1, &hf_lte_rrc_rrcConnectionReestablishmentReject, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_RRCConnectionReestablishmentReject },
  {   2, &hf_lte_rrc_rrcConnectionReject, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_RRCConnectionReject },
  {   3, &hf_lte_rrc_rrcConnectionSetup, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_RRCConnectionSetup },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_03(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_03, T_c1_03_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_messageClassExtension_03_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_messageClassExtension_03(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_messageClassExtension_03, T_messageClassExtension_03_sequence);

  return offset;
}


static const value_string lte_rrc_DL_CCCH_MessageType_vals[] = {
  {   0, "c1" },
  {   1, "messageClassExtension" },
  { 0, NULL }
};

static const per_choice_t DL_CCCH_MessageType_choice[] = {
  {   0, &hf_lte_rrc_c1_03       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_03 },
  {   1, &hf_lte_rrc_messageClassExtension_03, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_messageClassExtension_03 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_DL_CCCH_MessageType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_DL_CCCH_MessageType, DL_CCCH_MessageType_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t DL_CCCH_Message_sequence[] = {
  { &hf_lte_rrc_message_04  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_DL_CCCH_MessageType },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_DL_CCCH_Message(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_DL_CCCH_Message, DL_CCCH_Message_sequence);

  return offset;
}



static int
dissect_lte_rrc_RAND_CDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     32, 32, FALSE, NULL);

  return offset;
}



static int
dissect_lte_rrc_MobilityParametersCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, NULL);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_03_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_03(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_03, T_nonCriticalExtension_03_sequence);

  return offset;
}


static const per_sequence_t CSFBParametersResponseCDMA2000_r8_IEs_sequence[] = {
  { &hf_lte_rrc_rand        , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RAND_CDMA2000 },
  { &hf_lte_rrc_mobilityParameters, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MobilityParametersCDMA2000 },
  { &hf_lte_rrc_nonCriticalExtension_03, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_03 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CSFBParametersResponseCDMA2000_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CSFBParametersResponseCDMA2000_r8_IEs, CSFBParametersResponseCDMA2000_r8_IEs_sequence);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_03_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_03(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_03, T_criticalExtensionsFuture_03_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_03_vals[] = {
  {   0, "csfbParametersResponseCDMA2000-r8" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_03_choice[] = {
  {   0, &hf_lte_rrc_csfbParametersResponseCDMA2000_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_CSFBParametersResponseCDMA2000_r8_IEs },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_03, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_03 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_03(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_03, T_criticalExtensions_03_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t CSFBParametersResponseCDMA2000_sequence[] = {
  { &hf_lte_rrc_rrc_TransactionIdentifier, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RRC_TransactionIdentifier },
  { &hf_lte_rrc_criticalExtensions_03, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_03 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CSFBParametersResponseCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:CSFBParametersResponseCDMA2000 ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CSFBParametersResponseCDMA2000, CSFBParametersResponseCDMA2000_sequence);

  return offset;
}



static int
dissect_lte_rrc_DedicatedInfoNAS(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  tvbuff_t *nas_eps_tvb=NULL;

  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &nas_eps_tvb);


	if ((nas_eps_tvb)&&(nas_eps_handle))
		call_dissector(nas_eps_handle,nas_eps_tvb,actx->pinfo, tree);


  return offset;
}



static int
dissect_lte_rrc_DedicatedInfoCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, NULL);

  return offset;
}


static const value_string lte_rrc_T_dedicatedInfoType_vals[] = {
  {   0, "dedicatedInfoNAS" },
  {   1, "dedicatedInfoCDMA2000-1XRTT" },
  {   2, "dedicatedInfoCDMA2000-HRPD" },
  { 0, NULL }
};

static const per_choice_t T_dedicatedInfoType_choice[] = {
  {   0, &hf_lte_rrc_dedicatedInfoNAS, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_DedicatedInfoNAS },
  {   1, &hf_lte_rrc_dedicatedInfoCDMA2000_1XRTT, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_DedicatedInfoCDMA2000 },
  {   2, &hf_lte_rrc_dedicatedInfoCDMA2000_HRPD, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_DedicatedInfoCDMA2000 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_dedicatedInfoType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_dedicatedInfoType, T_dedicatedInfoType_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_04_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_04(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_04, T_nonCriticalExtension_04_sequence);

  return offset;
}


static const per_sequence_t DLInformationTransfer_r8_IEs_sequence[] = {
  { &hf_lte_rrc_dedicatedInfoType, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_dedicatedInfoType },
  { &hf_lte_rrc_nonCriticalExtension_04, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_04 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_DLInformationTransfer_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_DLInformationTransfer_r8_IEs, DLInformationTransfer_r8_IEs_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_08_vals[] = {
  {   0, "dlInformationTransfer-r8" },
  {   1, "spare3" },
  {   2, "spare2" },
  {   3, "spare1" },
  { 0, NULL }
};

static const per_choice_t T_c1_08_choice[] = {
  {   0, &hf_lte_rrc_dlInformationTransfer_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_DLInformationTransfer_r8_IEs },
  {   1, &hf_lte_rrc_spare3      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   2, &hf_lte_rrc_spare2      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   3, &hf_lte_rrc_spare1      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_08(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_08, T_c1_08_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_04_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_04(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_04, T_criticalExtensionsFuture_04_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_04_vals[] = {
  {   0, "c1" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_04_choice[] = {
  {   0, &hf_lte_rrc_c1_08       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_08 },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_04, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_04 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_04(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_04, T_criticalExtensions_04_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t DLInformationTransfer_sequence[] = {
  { &hf_lte_rrc_rrc_TransactionIdentifier, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RRC_TransactionIdentifier },
  { &hf_lte_rrc_criticalExtensions_04, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_04 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_DLInformationTransfer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:DLInformationTransfer ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_DLInformationTransfer, DLInformationTransfer_sequence);

  return offset;
}


static const value_string lte_rrc_CDMA2000_Type_vals[] = {
  {   0, "type1XRTT" },
  {   1, "typeHRPD" },
  { 0, NULL }
};


static int
dissect_lte_rrc_CDMA2000_Type(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_05_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_05(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_05, T_nonCriticalExtension_05_sequence);

  return offset;
}


static const per_sequence_t HandoverFromEUTRAPreparationRequest_v920_IEs_sequence[] = {
  { &hf_lte_rrc_concurrPrepCDMA2000_HRPD_r9, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_nonCriticalExtension_07, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_05 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_HandoverFromEUTRAPreparationRequest_v920_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_HandoverFromEUTRAPreparationRequest_v920_IEs, HandoverFromEUTRAPreparationRequest_v920_IEs_sequence);

  return offset;
}


static const per_sequence_t HandoverFromEUTRAPreparationRequest_v890_IEs_sequence[] = {
  { &hf_lte_rrc_lateR8NonCriticalExtension, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_OCTET_STRING },
  { &hf_lte_rrc_nonCriticalExtension_06, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_HandoverFromEUTRAPreparationRequest_v920_IEs },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_HandoverFromEUTRAPreparationRequest_v890_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_HandoverFromEUTRAPreparationRequest_v890_IEs, HandoverFromEUTRAPreparationRequest_v890_IEs_sequence);

  return offset;
}


static const per_sequence_t HandoverFromEUTRAPreparationRequest_r8_IEs_sequence[] = {
  { &hf_lte_rrc_cdma2000_Type, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CDMA2000_Type },
  { &hf_lte_rrc_rand        , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_RAND_CDMA2000 },
  { &hf_lte_rrc_mobilityParameters, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_MobilityParametersCDMA2000 },
  { &hf_lte_rrc_nonCriticalExtension_05, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_HandoverFromEUTRAPreparationRequest_v890_IEs },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_HandoverFromEUTRAPreparationRequest_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_HandoverFromEUTRAPreparationRequest_r8_IEs, HandoverFromEUTRAPreparationRequest_r8_IEs_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_09_vals[] = {
  {   0, "handoverFromEUTRAPreparationRequest-r8" },
  {   1, "spare3" },
  {   2, "spare2" },
  {   3, "spare1" },
  { 0, NULL }
};

static const per_choice_t T_c1_09_choice[] = {
  {   0, &hf_lte_rrc_handoverFromEUTRAPreparationRequest_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_HandoverFromEUTRAPreparationRequest_r8_IEs },
  {   1, &hf_lte_rrc_spare3      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   2, &hf_lte_rrc_spare2      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   3, &hf_lte_rrc_spare1      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_09(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_09, T_c1_09_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_05_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_05(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_05, T_criticalExtensionsFuture_05_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_05_vals[] = {
  {   0, "c1" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_05_choice[] = {
  {   0, &hf_lte_rrc_c1_09       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_09 },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_05, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_05 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_05(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_05, T_criticalExtensions_05_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t HandoverFromEUTRAPreparationRequest_sequence[] = {
  { &hf_lte_rrc_rrc_TransactionIdentifier, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RRC_TransactionIdentifier },
  { &hf_lte_rrc_criticalExtensions_05, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_05 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_HandoverFromEUTRAPreparationRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:HandoverFromEUTRAPreparationRequest ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_HandoverFromEUTRAPreparationRequest, HandoverFromEUTRAPreparationRequest_sequence);

  return offset;
}


static const value_string lte_rrc_T_targetRAT_Type_vals[] = {
  {   0, "utra" },
  {   1, "geran" },
  {   2, "cdma2000-1XRTT" },
  {   3, "cdma2000-HRPD" },
  {   4, "spare4" },
  {   5, "spare3" },
  {   6, "spare2" },
  {   7, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_targetRAT_Type(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, TRUE, 0, NULL);

  return offset;
}



static int
dissect_lte_rrc_OCTET_STRING_SIZE_1_23(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       1, 23, FALSE, NULL);

  return offset;
}


static const per_sequence_t SystemInfoListGERAN_sequence_of[1] = {
  { &hf_lte_rrc_SystemInfoListGERAN_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_OCTET_STRING_SIZE_1_23 },
};

static int
dissect_lte_rrc_SystemInfoListGERAN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_SystemInfoListGERAN, SystemInfoListGERAN_sequence_of,
                                                  1, maxGERAN_SI, FALSE);

  return offset;
}


static const value_string lte_rrc_SI_OrPSI_GERAN_vals[] = {
  {   0, "si" },
  {   1, "psi" },
  { 0, NULL }
};

static const per_choice_t SI_OrPSI_GERAN_choice[] = {
  {   0, &hf_lte_rrc_si          , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_SystemInfoListGERAN },
  {   1, &hf_lte_rrc_psi         , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_SystemInfoListGERAN },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_SI_OrPSI_GERAN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_SI_OrPSI_GERAN, SI_OrPSI_GERAN_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t Handover_sequence[] = {
  { &hf_lte_rrc_targetRAT_Type, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_targetRAT_Type },
  { &hf_lte_rrc_targetRAT_MessageContainer, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_OCTET_STRING },
  { &hf_lte_rrc_nas_SecurityParamFromEUTRA, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_OCTET_STRING_SIZE_1 },
  { &hf_lte_rrc_systemInformation_01, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_SI_OrPSI_GERAN },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_Handover(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_Handover, Handover_sequence);

  return offset;
}


static const value_string lte_rrc_T_t304_vals[] = {
  {   0, "ms100" },
  {   1, "ms200" },
  {   2, "ms500" },
  {   3, "ms1000" },
  {   4, "ms2000" },
  {   5, "ms4000" },
  {   6, "ms8000" },
  {   7, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_t304(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t PhysCellIdGERAN_sequence[] = {
  { &hf_lte_rrc_networkColourCode, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_3 },
  { &hf_lte_rrc_baseStationColourCode, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_3 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_PhysCellIdGERAN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_PhysCellIdGERAN, PhysCellIdGERAN_sequence);

  return offset;
}


static const per_sequence_t CarrierFreqGERAN_sequence[] = {
  { &hf_lte_rrc_arfcn_01    , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ARFCN_ValueGERAN },
  { &hf_lte_rrc_bandIndicator, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BandIndicatorGERAN },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CarrierFreqGERAN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CarrierFreqGERAN, CarrierFreqGERAN_sequence);

  return offset;
}


static const per_sequence_t T_geran_sequence[] = {
  { &hf_lte_rrc_physCellId  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhysCellIdGERAN },
  { &hf_lte_rrc_carrierFreq , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CarrierFreqGERAN },
  { &hf_lte_rrc_networkControlOrder, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_BIT_STRING_SIZE_2 },
  { &hf_lte_rrc_systemInformation_01, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_SI_OrPSI_GERAN },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_geran(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_geran, T_geran_sequence);

  return offset;
}


static const value_string lte_rrc_T_targetRAT_Type_01_vals[] = {
  {   0, "geran" },
  { 0, NULL }
};

static const per_choice_t T_targetRAT_Type_01_choice[] = {
  {   0, &hf_lte_rrc_geran       , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_T_geran },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_targetRAT_Type_01(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_targetRAT_Type_01, T_targetRAT_Type_01_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t CellChangeOrder_sequence[] = {
  { &hf_lte_rrc_t304        , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_t304 },
  { &hf_lte_rrc_targetRAT_Type_01, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_targetRAT_Type_01 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CellChangeOrder(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CellChangeOrder, CellChangeOrder_sequence);

  return offset;
}


static const value_string lte_rrc_T_purpose_vals[] = {
  {   0, "handover" },
  {   1, "cellChangeOrder" },
  { 0, NULL }
};

static const per_choice_t T_purpose_choice[] = {
  {   0, &hf_lte_rrc_handover    , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_Handover },
  {   1, &hf_lte_rrc_cellChangeOrder, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_CellChangeOrder },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_purpose(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_purpose, T_purpose_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_08_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_08(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_08, T_nonCriticalExtension_08_sequence);

  return offset;
}


static const per_sequence_t MobilityFromEUTRACommand_r8_IEs_sequence[] = {
  { &hf_lte_rrc_cs_FallbackIndicator, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_purpose     , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_purpose },
  { &hf_lte_rrc_nonCriticalExtension_10, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_08 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MobilityFromEUTRACommand_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MobilityFromEUTRACommand_r8_IEs, MobilityFromEUTRACommand_r8_IEs_sequence);

  return offset;
}


static const value_string lte_rrc_T_mobilityCDMA2000_HRPD_r9_vals[] = {
  {   0, "handover" },
  {   1, "redirection" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_mobilityCDMA2000_HRPD_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t CarrierFreqCDMA2000_sequence[] = {
  { &hf_lte_rrc_bandClass   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BandclassCDMA2000 },
  { &hf_lte_rrc_arfcn       , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ARFCN_ValueCDMA2000 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CarrierFreqCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CarrierFreqCDMA2000, CarrierFreqCDMA2000_sequence);

  return offset;
}


static const per_sequence_t E_CSFB_r9_sequence[] = {
  { &hf_lte_rrc_messageContCDMA2000_1XRTT_r9, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_OCTET_STRING },
  { &hf_lte_rrc_mobilityCDMA2000_HRPD_r9, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_mobilityCDMA2000_HRPD_r9 },
  { &hf_lte_rrc_messageContCDMA2000_HRPD_r9, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_OCTET_STRING },
  { &hf_lte_rrc_redirectCarrierCDMA2000_HRPD_r9, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_CarrierFreqCDMA2000 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_E_CSFB_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_E_CSFB_r9, E_CSFB_r9_sequence);

  return offset;
}


static const value_string lte_rrc_T_purpose_01_vals[] = {
  {   0, "handover" },
  {   1, "cellChangeOrder" },
  {   2, "e-CSFB-r9" },
  { 0, NULL }
};

static const per_choice_t T_purpose_01_choice[] = {
  {   0, &hf_lte_rrc_handover    , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_Handover },
  {   1, &hf_lte_rrc_cellChangeOrder, ASN1_EXTENSION_ROOT    , dissect_lte_rrc_CellChangeOrder },
  {   2, &hf_lte_rrc_e_CSFB_r9   , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_E_CSFB_r9 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_purpose_01(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_purpose_01, T_purpose_01_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_09_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_09(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_09, T_nonCriticalExtension_09_sequence);

  return offset;
}


static const per_sequence_t MobilityFromEUTRACommand_r9_IEs_sequence[] = {
  { &hf_lte_rrc_cs_FallbackIndicator, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_purpose_01  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_purpose_01 },
  { &hf_lte_rrc_nonCriticalExtension_11, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_09 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MobilityFromEUTRACommand_r9_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MobilityFromEUTRACommand_r9_IEs, MobilityFromEUTRACommand_r9_IEs_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_11_vals[] = {
  {   0, "mobilityFromEUTRACommand-r8" },
  {   1, "mobilityFromEUTRACommand-r9" },
  {   2, "spare2" },
  {   3, "spare1" },
  { 0, NULL }
};

static const per_choice_t T_c1_11_choice[] = {
  {   0, &hf_lte_rrc_mobilityFromEUTRACommand_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_MobilityFromEUTRACommand_r8_IEs },
  {   1, &hf_lte_rrc_mobilityFromEUTRACommand_r9, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_MobilityFromEUTRACommand_r9_IEs },
  {   2, &hf_lte_rrc_spare2      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   3, &hf_lte_rrc_spare1      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_11(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_11, T_c1_11_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_07_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_07(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_07, T_criticalExtensionsFuture_07_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_07_vals[] = {
  {   0, "c1" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_07_choice[] = {
  {   0, &hf_lte_rrc_c1_11       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_11 },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_07, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_07 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_07(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_07, T_criticalExtensions_07_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t MobilityFromEUTRACommand_sequence[] = {
  { &hf_lte_rrc_rrc_TransactionIdentifier, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RRC_TransactionIdentifier },
  { &hf_lte_rrc_criticalExtensions_07, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_07 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MobilityFromEUTRACommand(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:MobilityFromEUTRACommand ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MobilityFromEUTRACommand, MobilityFromEUTRACommand_sequence);

  return offset;
}



static int
dissect_lte_rrc_MeasObjectId(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, maxObjectId, NULL, FALSE);

  return offset;
}


static const per_sequence_t MeasObjectToRemoveList_sequence_of[1] = {
  { &hf_lte_rrc_MeasObjectToRemoveList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MeasObjectId },
};

static int
dissect_lte_rrc_MeasObjectToRemoveList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_MeasObjectToRemoveList, MeasObjectToRemoveList_sequence_of,
                                                  1, maxObjectId, FALSE);

  return offset;
}



static int
dissect_lte_rrc_CellIndex(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, maxCellMeas, NULL, FALSE);

  return offset;
}


static const per_sequence_t CellIndexList_sequence_of[1] = {
  { &hf_lte_rrc_CellIndexList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CellIndex },
};

static int
dissect_lte_rrc_CellIndexList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_CellIndexList, CellIndexList_sequence_of,
                                                  1, maxCellMeas, FALSE);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_1_maxCellMeas(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, maxCellMeas, NULL, FALSE);

  return offset;
}


static const per_sequence_t CellsToAddMod_sequence[] = {
  { &hf_lte_rrc_cellIndex   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_1_maxCellMeas },
  { &hf_lte_rrc_physCellId_01, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhysCellId },
  { &hf_lte_rrc_cellIndividualOffset, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_Q_OffsetRange },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CellsToAddMod(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CellsToAddMod, CellsToAddMod_sequence);

  return offset;
}


static const per_sequence_t CellsToAddModList_sequence_of[1] = {
  { &hf_lte_rrc_CellsToAddModList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CellsToAddMod },
};

static int
dissect_lte_rrc_CellsToAddModList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_CellsToAddModList, CellsToAddModList_sequence_of,
                                                  1, maxCellMeas, FALSE);

  return offset;
}


static const per_sequence_t BlackCellsToAddMod_sequence[] = {
  { &hf_lte_rrc_cellIndex   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_1_maxCellMeas },
  { &hf_lte_rrc_physCellIdRange, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhysCellIdRange },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_BlackCellsToAddMod(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_BlackCellsToAddMod, BlackCellsToAddMod_sequence);

  return offset;
}


static const per_sequence_t BlackCellsToAddModList_sequence_of[1] = {
  { &hf_lte_rrc_BlackCellsToAddModList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BlackCellsToAddMod },
};

static int
dissect_lte_rrc_BlackCellsToAddModList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_BlackCellsToAddModList, BlackCellsToAddModList_sequence_of,
                                                  1, maxCellMeas, FALSE);

  return offset;
}


static const per_sequence_t MeasObjectEUTRA_sequence[] = {
  { &hf_lte_rrc_carrierFreq_01, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ARFCN_ValueEUTRA },
  { &hf_lte_rrc_allowedMeasBandwidth, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_AllowedMeasBandwidth },
  { &hf_lte_rrc_presenceAntennaPort1, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PresenceAntennaPort1 },
  { &hf_lte_rrc_neighCellConfig, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_NeighCellConfig },
  { &hf_lte_rrc_offsetFreq_01, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_Q_OffsetRange },
  { &hf_lte_rrc_cellsToRemoveList, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_CellIndexList },
  { &hf_lte_rrc_cellsToAddModList_01, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_CellsToAddModList },
  { &hf_lte_rrc_blackCellsToRemoveList, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_CellIndexList },
  { &hf_lte_rrc_blackCellsToAddModList, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_BlackCellsToAddModList },
  { &hf_lte_rrc_cellForWhichToReportCGI_01, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_PhysCellId },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MeasObjectEUTRA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MeasObjectEUTRA, MeasObjectEUTRA_sequence);

  return offset;
}



static int
dissect_lte_rrc_Q_OffsetRangeInterRAT(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            -15, 15U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_PhysCellIdUTRA_FDD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 511U, NULL, FALSE);

  return offset;
}


static const per_sequence_t CellsToAddModUTRA_FDD_sequence[] = {
  { &hf_lte_rrc_cellIndex   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_1_maxCellMeas },
  { &hf_lte_rrc_physCellId_03, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhysCellIdUTRA_FDD },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CellsToAddModUTRA_FDD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CellsToAddModUTRA_FDD, CellsToAddModUTRA_FDD_sequence);

  return offset;
}


static const per_sequence_t CellsToAddModListUTRA_FDD_sequence_of[1] = {
  { &hf_lte_rrc_CellsToAddModListUTRA_FDD_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CellsToAddModUTRA_FDD },
};

static int
dissect_lte_rrc_CellsToAddModListUTRA_FDD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_CellsToAddModListUTRA_FDD, CellsToAddModListUTRA_FDD_sequence_of,
                                                  1, maxCellMeas, FALSE);

  return offset;
}



static int
dissect_lte_rrc_PhysCellIdUTRA_TDD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 127U, NULL, FALSE);

  return offset;
}


static const per_sequence_t CellsToAddModUTRA_TDD_sequence[] = {
  { &hf_lte_rrc_cellIndex   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_1_maxCellMeas },
  { &hf_lte_rrc_physCellId_04, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhysCellIdUTRA_TDD },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CellsToAddModUTRA_TDD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CellsToAddModUTRA_TDD, CellsToAddModUTRA_TDD_sequence);

  return offset;
}


static const per_sequence_t CellsToAddModListUTRA_TDD_sequence_of[1] = {
  { &hf_lte_rrc_CellsToAddModListUTRA_TDD_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CellsToAddModUTRA_TDD },
};

static int
dissect_lte_rrc_CellsToAddModListUTRA_TDD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_CellsToAddModListUTRA_TDD, CellsToAddModListUTRA_TDD_sequence_of,
                                                  1, maxCellMeas, FALSE);

  return offset;
}


static const value_string lte_rrc_T_cellsToAddModList_vals[] = {
  {   0, "cellsToAddModListUTRA-FDD" },
  {   1, "cellsToAddModListUTRA-TDD" },
  { 0, NULL }
};

static const per_choice_t T_cellsToAddModList_choice[] = {
  {   0, &hf_lte_rrc_cellsToAddModListUTRA_FDD, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_CellsToAddModListUTRA_FDD },
  {   1, &hf_lte_rrc_cellsToAddModListUTRA_TDD, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_CellsToAddModListUTRA_TDD },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_cellsToAddModList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_cellsToAddModList, T_cellsToAddModList_choice,
                                 NULL);

  return offset;
}


static const value_string lte_rrc_T_cellForWhichToReportCGI_vals[] = {
  {   0, "utra-FDD" },
  {   1, "utra-TDD" },
  { 0, NULL }
};

static const per_choice_t T_cellForWhichToReportCGI_choice[] = {
  {   0, &hf_lte_rrc_utra_FDD_01 , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_PhysCellIdUTRA_FDD },
  {   1, &hf_lte_rrc_utra_TDD_01 , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_PhysCellIdUTRA_TDD },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_cellForWhichToReportCGI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_cellForWhichToReportCGI, T_cellForWhichToReportCGI_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t MeasObjectUTRA_sequence[] = {
  { &hf_lte_rrc_carrierFreq_02, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ARFCN_ValueUTRA },
  { &hf_lte_rrc_offsetFreq  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_Q_OffsetRangeInterRAT },
  { &hf_lte_rrc_cellsToRemoveList, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_CellIndexList },
  { &hf_lte_rrc_cellsToAddModList_02, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_T_cellsToAddModList },
  { &hf_lte_rrc_cellForWhichToReportCGI_03, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_T_cellForWhichToReportCGI },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MeasObjectUTRA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MeasObjectUTRA, MeasObjectUTRA_sequence);

  return offset;
}


static const per_sequence_t MeasObjectGERAN_sequence[] = {
  { &hf_lte_rrc_carrierFreqs, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CarrierFreqsGERAN },
  { &hf_lte_rrc_offsetFreq  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_Q_OffsetRangeInterRAT },
  { &hf_lte_rrc_ncc_Permitted, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_BIT_STRING_SIZE_8 },
  { &hf_lte_rrc_cellForWhichToReportCGI_02, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_PhysCellIdGERAN },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MeasObjectGERAN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MeasObjectGERAN, MeasObjectGERAN_sequence);

  return offset;
}


static const per_sequence_t CellsToAddModCDMA2000_sequence[] = {
  { &hf_lte_rrc_cellIndex   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_1_maxCellMeas },
  { &hf_lte_rrc_physCellId_02, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhysCellIdCDMA2000 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CellsToAddModCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CellsToAddModCDMA2000, CellsToAddModCDMA2000_sequence);

  return offset;
}


static const per_sequence_t CellsToAddModListCDMA2000_sequence_of[1] = {
  { &hf_lte_rrc_CellsToAddModListCDMA2000_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CellsToAddModCDMA2000 },
};

static int
dissect_lte_rrc_CellsToAddModListCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_CellsToAddModListCDMA2000, CellsToAddModListCDMA2000_sequence_of,
                                                  1, maxCellMeas, FALSE);

  return offset;
}


static const per_sequence_t MeasObjectCDMA2000_sequence[] = {
  { &hf_lte_rrc_cdma2000_Type, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CDMA2000_Type },
  { &hf_lte_rrc_carrierFreq_03, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CarrierFreqCDMA2000 },
  { &hf_lte_rrc_searchWindowSize, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_INTEGER_0_15 },
  { &hf_lte_rrc_offsetFreq  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_Q_OffsetRangeInterRAT },
  { &hf_lte_rrc_cellsToRemoveList, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_CellIndexList },
  { &hf_lte_rrc_cellsToAddModList, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_CellsToAddModListCDMA2000 },
  { &hf_lte_rrc_cellForWhichToReportCGI, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_PhysCellIdCDMA2000 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MeasObjectCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MeasObjectCDMA2000, MeasObjectCDMA2000_sequence);

  return offset;
}


static const value_string lte_rrc_T_measObject_vals[] = {
  {   0, "measObjectEUTRA" },
  {   1, "measObjectUTRA" },
  {   2, "measObjectGERAN" },
  {   3, "measObjectCDMA2000" },
  { 0, NULL }
};

static const per_choice_t T_measObject_choice[] = {
  {   0, &hf_lte_rrc_measObjectEUTRA, ASN1_EXTENSION_ROOT    , dissect_lte_rrc_MeasObjectEUTRA },
  {   1, &hf_lte_rrc_measObjectUTRA, ASN1_EXTENSION_ROOT    , dissect_lte_rrc_MeasObjectUTRA },
  {   2, &hf_lte_rrc_measObjectGERAN, ASN1_EXTENSION_ROOT    , dissect_lte_rrc_MeasObjectGERAN },
  {   3, &hf_lte_rrc_measObjectCDMA2000, ASN1_EXTENSION_ROOT    , dissect_lte_rrc_MeasObjectCDMA2000 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_measObject(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_measObject, T_measObject_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t MeasObjectToAddMod_sequence[] = {
  { &hf_lte_rrc_measObjectId, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MeasObjectId },
  { &hf_lte_rrc_measObject  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_measObject },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MeasObjectToAddMod(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MeasObjectToAddMod, MeasObjectToAddMod_sequence);

  return offset;
}


static const per_sequence_t MeasObjectToAddModList_sequence_of[1] = {
  { &hf_lte_rrc_MeasObjectToAddModList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MeasObjectToAddMod },
};

static int
dissect_lte_rrc_MeasObjectToAddModList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_MeasObjectToAddModList, MeasObjectToAddModList_sequence_of,
                                                  1, maxObjectId, FALSE);

  return offset;
}



static int
dissect_lte_rrc_ReportConfigId(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, maxReportConfigId, NULL, FALSE);

  return offset;
}


static const per_sequence_t ReportConfigToRemoveList_sequence_of[1] = {
  { &hf_lte_rrc_ReportConfigToRemoveList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ReportConfigId },
};

static int
dissect_lte_rrc_ReportConfigToRemoveList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_ReportConfigToRemoveList, ReportConfigToRemoveList_sequence_of,
                                                  1, maxReportConfigId, FALSE);

  return offset;
}



static int
dissect_lte_rrc_RSRP_Range(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 97U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_RSRQ_Range(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 34U, NULL, FALSE);

  return offset;
}


static const value_string lte_rrc_ThresholdEUTRA_vals[] = {
  {   0, "threshold-RSRP" },
  {   1, "threshold-RSRQ" },
  { 0, NULL }
};

static const per_choice_t ThresholdEUTRA_choice[] = {
  {   0, &hf_lte_rrc_threshold_RSRP, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_RSRP_Range },
  {   1, &hf_lte_rrc_threshold_RSRQ, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_RSRQ_Range },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_ThresholdEUTRA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_ThresholdEUTRA, ThresholdEUTRA_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_eventA1_sequence[] = {
  { &hf_lte_rrc_a1_Threshold, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ThresholdEUTRA },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_eventA1(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_eventA1, T_eventA1_sequence);

  return offset;
}


static const per_sequence_t T_eventA2_sequence[] = {
  { &hf_lte_rrc_a2_Threshold, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ThresholdEUTRA },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_eventA2(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_eventA2, T_eventA2_sequence);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_M30_30(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            -30, 30U, NULL, FALSE);

  return offset;
}


static const per_sequence_t T_eventA3_sequence[] = {
  { &hf_lte_rrc_a3_Offset   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_M30_30 },
  { &hf_lte_rrc_reportOnLeave, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_eventA3(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_eventA3, T_eventA3_sequence);

  return offset;
}


static const per_sequence_t T_eventA4_sequence[] = {
  { &hf_lte_rrc_a4_Threshold, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ThresholdEUTRA },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_eventA4(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_eventA4, T_eventA4_sequence);

  return offset;
}


static const per_sequence_t T_eventA5_sequence[] = {
  { &hf_lte_rrc_a5_Threshold1, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ThresholdEUTRA },
  { &hf_lte_rrc_a5_Threshold2, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ThresholdEUTRA },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_eventA5(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_eventA5, T_eventA5_sequence);

  return offset;
}


static const value_string lte_rrc_T_eventId_vals[] = {
  {   0, "eventA1" },
  {   1, "eventA2" },
  {   2, "eventA3" },
  {   3, "eventA4" },
  {   4, "eventA5" },
  { 0, NULL }
};

static const per_choice_t T_eventId_choice[] = {
  {   0, &hf_lte_rrc_eventA1     , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_T_eventA1 },
  {   1, &hf_lte_rrc_eventA2     , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_T_eventA2 },
  {   2, &hf_lte_rrc_eventA3     , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_T_eventA3 },
  {   3, &hf_lte_rrc_eventA4     , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_T_eventA4 },
  {   4, &hf_lte_rrc_eventA5     , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_T_eventA5 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_eventId(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_eventId, T_eventId_choice,
                                 NULL);

  return offset;
}



static int
dissect_lte_rrc_Hysteresis(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 30U, NULL, FALSE);

  return offset;
}


static const value_string lte_rrc_TimeToTrigger_vals[] = {
  {   0, "ms0" },
  {   1, "ms40" },
  {   2, "ms64" },
  {   3, "ms80" },
  {   4, "ms100" },
  {   5, "ms128" },
  {   6, "ms160" },
  {   7, "ms256" },
  {   8, "ms320" },
  {   9, "ms480" },
  {  10, "ms512" },
  {  11, "ms640" },
  {  12, "ms1024" },
  {  13, "ms1280" },
  {  14, "ms2560" },
  {  15, "ms5120" },
  { 0, NULL }
};


static int
dissect_lte_rrc_TimeToTrigger(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t T_event_sequence[] = {
  { &hf_lte_rrc_eventId     , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_eventId },
  { &hf_lte_rrc_hysteresis  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_Hysteresis },
  { &hf_lte_rrc_timeToTrigger, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_TimeToTrigger },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_event(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_event, T_event_sequence);

  return offset;
}


static const value_string lte_rrc_T_purpose_02_vals[] = {
  {   0, "reportStrongestCells" },
  {   1, "reportCGI" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_purpose_02(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t T_periodical_sequence[] = {
  { &hf_lte_rrc_purpose_02  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_purpose_02 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_periodical(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_periodical, T_periodical_sequence);

  return offset;
}


static const value_string lte_rrc_T_triggerType_vals[] = {
  {   0, "event" },
  {   1, "periodical" },
  { 0, NULL }
};

static const per_choice_t T_triggerType_choice[] = {
  {   0, &hf_lte_rrc_event       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_event },
  {   1, &hf_lte_rrc_periodical  , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_periodical },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_triggerType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_triggerType, T_triggerType_choice,
                                 NULL);

  return offset;
}


static const value_string lte_rrc_T_triggerQuantity_vals[] = {
  {   0, "rsrp" },
  {   1, "rsrq" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_triggerQuantity(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_reportQuantity_vals[] = {
  {   0, "sameAsTriggerQuantity" },
  {   1, "both" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_reportQuantity(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_1_maxCellReport(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, maxCellReport, NULL, FALSE);

  return offset;
}


static const value_string lte_rrc_ReportInterval_vals[] = {
  {   0, "ms120" },
  {   1, "ms240" },
  {   2, "ms480" },
  {   3, "ms640" },
  {   4, "ms1024" },
  {   5, "ms2048" },
  {   6, "ms5120" },
  {   7, "ms10240" },
  {   8, "min1" },
  {   9, "min6" },
  {  10, "min12" },
  {  11, "min30" },
  {  12, "min60" },
  {  13, "spare3" },
  {  14, "spare2" },
  {  15, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_ReportInterval(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_reportAmount_vals[] = {
  {   0, "r1" },
  {   1, "r2" },
  {   2, "r4" },
  {   3, "r8" },
  {   4, "r16" },
  {   5, "r32" },
  {   6, "r64" },
  {   7, "infinity" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_reportAmount(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_si_RequestForHO_r9_vals[] = {
  {   0, "setup" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_si_RequestForHO_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_ue_RxTxTimeDiffPeriodical_r9_vals[] = {
  {   0, "setup" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_ue_RxTxTimeDiffPeriodical_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t ReportConfigEUTRA_sequence[] = {
  { &hf_lte_rrc_triggerType , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_triggerType },
  { &hf_lte_rrc_triggerQuantity, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_triggerQuantity },
  { &hf_lte_rrc_reportQuantity, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_reportQuantity },
  { &hf_lte_rrc_maxReportCells, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_1_maxCellReport },
  { &hf_lte_rrc_reportInterval, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ReportInterval },
  { &hf_lte_rrc_reportAmount, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_reportAmount },
  { &hf_lte_rrc_si_RequestForHO_r9, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_T_si_RequestForHO_r9 },
  { &hf_lte_rrc_ue_RxTxTimeDiffPeriodical_r9, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_T_ue_RxTxTimeDiffPeriodical_r9 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_ReportConfigEUTRA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_ReportConfigEUTRA, ReportConfigEUTRA_sequence);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_M5_91(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            -5, 91U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_49(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 49U, NULL, FALSE);

  return offset;
}


static const value_string lte_rrc_ThresholdUTRA_vals[] = {
  {   0, "utra-RSCP" },
  {   1, "utra-EcN0" },
  { 0, NULL }
};

static const per_choice_t ThresholdUTRA_choice[] = {
  {   0, &hf_lte_rrc_utra_RSCP   , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_INTEGER_M5_91 },
  {   1, &hf_lte_rrc_utra_EcN0   , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_INTEGER_0_49 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_ThresholdUTRA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_ThresholdUTRA, ThresholdUTRA_choice,
                                 NULL);

  return offset;
}



static int
dissect_lte_rrc_ThresholdGERAN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 63U, NULL, FALSE);

  return offset;
}



static int
dissect_lte_rrc_ThresholdCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 63U, NULL, FALSE);

  return offset;
}


static const value_string lte_rrc_T_b1_Threshold_vals[] = {
  {   0, "b1-ThresholdUTRA" },
  {   1, "b1-ThresholdGERAN" },
  {   2, "b1-ThresholdCDMA2000" },
  { 0, NULL }
};

static const per_choice_t T_b1_Threshold_choice[] = {
  {   0, &hf_lte_rrc_b1_ThresholdUTRA, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_ThresholdUTRA },
  {   1, &hf_lte_rrc_b1_ThresholdGERAN, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_ThresholdGERAN },
  {   2, &hf_lte_rrc_b1_ThresholdCDMA2000, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_ThresholdCDMA2000 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_b1_Threshold(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_b1_Threshold, T_b1_Threshold_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_eventB1_sequence[] = {
  { &hf_lte_rrc_b1_Threshold, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_b1_Threshold },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_eventB1(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_eventB1, T_eventB1_sequence);

  return offset;
}


static const value_string lte_rrc_T_b2_Threshold2_vals[] = {
  {   0, "b2-Threshold2UTRA" },
  {   1, "b2-Threshold2GERAN" },
  {   2, "b2-Threshold2CDMA2000" },
  { 0, NULL }
};

static const per_choice_t T_b2_Threshold2_choice[] = {
  {   0, &hf_lte_rrc_b2_Threshold2UTRA, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_ThresholdUTRA },
  {   1, &hf_lte_rrc_b2_Threshold2GERAN, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_ThresholdGERAN },
  {   2, &hf_lte_rrc_b2_Threshold2CDMA2000, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_ThresholdCDMA2000 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_b2_Threshold2(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_b2_Threshold2, T_b2_Threshold2_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_eventB2_sequence[] = {
  { &hf_lte_rrc_b2_Threshold1, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ThresholdEUTRA },
  { &hf_lte_rrc_b2_Threshold2, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_b2_Threshold2 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_eventB2(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_eventB2, T_eventB2_sequence);

  return offset;
}


static const value_string lte_rrc_T_eventId_01_vals[] = {
  {   0, "eventB1" },
  {   1, "eventB2" },
  { 0, NULL }
};

static const per_choice_t T_eventId_01_choice[] = {
  {   0, &hf_lte_rrc_eventB1     , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_T_eventB1 },
  {   1, &hf_lte_rrc_eventB2     , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_T_eventB2 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_eventId_01(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_eventId_01, T_eventId_01_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_event_01_sequence[] = {
  { &hf_lte_rrc_eventId_01  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_eventId_01 },
  { &hf_lte_rrc_hysteresis  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_Hysteresis },
  { &hf_lte_rrc_timeToTrigger, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_TimeToTrigger },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_event_01(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_event_01, T_event_01_sequence);

  return offset;
}


static const value_string lte_rrc_T_purpose_03_vals[] = {
  {   0, "reportStrongestCells" },
  {   1, "reportStrongestCellsForSON" },
  {   2, "reportCGI" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_purpose_03(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     3, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t T_periodical_01_sequence[] = {
  { &hf_lte_rrc_purpose_03  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_purpose_03 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_periodical_01(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_periodical_01, T_periodical_01_sequence);

  return offset;
}


static const value_string lte_rrc_T_triggerType_01_vals[] = {
  {   0, "event" },
  {   1, "periodical" },
  { 0, NULL }
};

static const per_choice_t T_triggerType_01_choice[] = {
  {   0, &hf_lte_rrc_event_01    , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_event_01 },
  {   1, &hf_lte_rrc_periodical_01, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_periodical_01 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_triggerType_01(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_triggerType_01, T_triggerType_01_choice,
                                 NULL);

  return offset;
}


static const value_string lte_rrc_T_reportAmount_01_vals[] = {
  {   0, "r1" },
  {   1, "r2" },
  {   2, "r4" },
  {   3, "r8" },
  {   4, "r16" },
  {   5, "r32" },
  {   6, "r64" },
  {   7, "infinity" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_reportAmount_01(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_si_RequestForHO_r9_01_vals[] = {
  {   0, "setup" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_si_RequestForHO_r9_01(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t ReportConfigInterRAT_sequence[] = {
  { &hf_lte_rrc_triggerType_01, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_triggerType_01 },
  { &hf_lte_rrc_maxReportCells, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_1_maxCellReport },
  { &hf_lte_rrc_reportInterval, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ReportInterval },
  { &hf_lte_rrc_reportAmount_01, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_reportAmount_01 },
  { &hf_lte_rrc_si_RequestForHO_r9_01, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_T_si_RequestForHO_r9_01 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_ReportConfigInterRAT(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_ReportConfigInterRAT, ReportConfigInterRAT_sequence);

  return offset;
}


static const value_string lte_rrc_T_reportConfig_vals[] = {
  {   0, "reportConfigEUTRA" },
  {   1, "reportConfigInterRAT" },
  { 0, NULL }
};

static const per_choice_t T_reportConfig_choice[] = {
  {   0, &hf_lte_rrc_reportConfigEUTRA, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_ReportConfigEUTRA },
  {   1, &hf_lte_rrc_reportConfigInterRAT, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_ReportConfigInterRAT },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_reportConfig(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_reportConfig, T_reportConfig_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t ReportConfigToAddMod_sequence[] = {
  { &hf_lte_rrc_reportConfigId, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ReportConfigId },
  { &hf_lte_rrc_reportConfig, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_reportConfig },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_ReportConfigToAddMod(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_ReportConfigToAddMod, ReportConfigToAddMod_sequence);

  return offset;
}


static const per_sequence_t ReportConfigToAddModList_sequence_of[1] = {
  { &hf_lte_rrc_ReportConfigToAddModList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ReportConfigToAddMod },
};

static int
dissect_lte_rrc_ReportConfigToAddModList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_ReportConfigToAddModList, ReportConfigToAddModList_sequence_of,
                                                  1, maxReportConfigId, FALSE);

  return offset;
}



static int
dissect_lte_rrc_MeasId(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, maxMeasId, NULL, FALSE);

  return offset;
}


static const per_sequence_t MeasIdToRemoveList_sequence_of[1] = {
  { &hf_lte_rrc_MeasIdToRemoveList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MeasId },
};

static int
dissect_lte_rrc_MeasIdToRemoveList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_MeasIdToRemoveList, MeasIdToRemoveList_sequence_of,
                                                  1, maxMeasId, FALSE);

  return offset;
}


static const per_sequence_t MeasIdToAddMod_sequence[] = {
  { &hf_lte_rrc_measId      , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MeasId },
  { &hf_lte_rrc_measObjectId, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MeasObjectId },
  { &hf_lte_rrc_reportConfigId, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ReportConfigId },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MeasIdToAddMod(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MeasIdToAddMod, MeasIdToAddMod_sequence);

  return offset;
}


static const per_sequence_t MeasIdToAddModList_sequence_of[1] = {
  { &hf_lte_rrc_MeasIdToAddModList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MeasIdToAddMod },
};

static int
dissect_lte_rrc_MeasIdToAddModList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_MeasIdToAddModList, MeasIdToAddModList_sequence_of,
                                                  1, maxMeasId, FALSE);

  return offset;
}


static const per_sequence_t QuantityConfigEUTRA_sequence[] = {
  { &hf_lte_rrc_filterCoefficientRSRP, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_FilterCoefficient },
  { &hf_lte_rrc_filterCoefficientRSRQ, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_FilterCoefficient },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_QuantityConfigEUTRA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_QuantityConfigEUTRA, QuantityConfigEUTRA_sequence);

  return offset;
}


static const value_string lte_rrc_T_measQuantityUTRA_FDD_vals[] = {
  {   0, "cpich-RSCP" },
  {   1, "cpich-EcN0" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_measQuantityUTRA_FDD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_measQuantityUTRA_TDD_vals[] = {
  {   0, "pccpch-RSCP" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_measQuantityUTRA_TDD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t QuantityConfigUTRA_sequence[] = {
  { &hf_lte_rrc_measQuantityUTRA_FDD, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_measQuantityUTRA_FDD },
  { &hf_lte_rrc_measQuantityUTRA_TDD, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_measQuantityUTRA_TDD },
  { &hf_lte_rrc_filterCoefficient, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_FilterCoefficient },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_QuantityConfigUTRA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_QuantityConfigUTRA, QuantityConfigUTRA_sequence);

  return offset;
}


static const value_string lte_rrc_T_measQuantityGERAN_vals[] = {
  {   0, "rssi" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_measQuantityGERAN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t QuantityConfigGERAN_sequence[] = {
  { &hf_lte_rrc_measQuantityGERAN, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_measQuantityGERAN },
  { &hf_lte_rrc_filterCoefficient, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_FilterCoefficient },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_QuantityConfigGERAN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_QuantityConfigGERAN, QuantityConfigGERAN_sequence);

  return offset;
}


static const value_string lte_rrc_T_measQuantityCDMA2000_vals[] = {
  {   0, "pilotStrength" },
  {   1, "pilotPnPhaseAndPilotStrength" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_measQuantityCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t QuantityConfigCDMA2000_sequence[] = {
  { &hf_lte_rrc_measQuantityCDMA2000, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_measQuantityCDMA2000 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_QuantityConfigCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_QuantityConfigCDMA2000, QuantityConfigCDMA2000_sequence);

  return offset;
}


static const per_sequence_t QuantityConfig_sequence[] = {
  { &hf_lte_rrc_quantityConfigEUTRA, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_QuantityConfigEUTRA },
  { &hf_lte_rrc_quantityConfigUTRA, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_QuantityConfigUTRA },
  { &hf_lte_rrc_quantityConfigGERAN, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_QuantityConfigGERAN },
  { &hf_lte_rrc_quantityConfigCDMA2000, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_QuantityConfigCDMA2000 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_QuantityConfig(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_QuantityConfig, QuantityConfig_sequence);

  return offset;
}


static const value_string lte_rrc_T_gapOffset_vals[] = {
  {   0, "gp0" },
  {   1, "gp1" },
  { 0, NULL }
};

static const per_choice_t T_gapOffset_choice[] = {
  {   0, &hf_lte_rrc_gp0         , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_INTEGER_0_39 },
  {   1, &hf_lte_rrc_gp1         , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_INTEGER_0_79 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_gapOffset(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_gapOffset, T_gapOffset_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_setup_13_sequence[] = {
  { &hf_lte_rrc_gapOffset   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_gapOffset },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_setup_13(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_setup_13, T_setup_13_sequence);

  return offset;
}


static const value_string lte_rrc_MeasGapConfig_vals[] = {
  {   0, "release" },
  {   1, "setup" },
  { 0, NULL }
};

static const per_choice_t MeasGapConfig_choice[] = {
  {   0, &hf_lte_rrc_release     , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   1, &hf_lte_rrc_setup_13    , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_setup_13 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_MeasGapConfig(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_MeasGapConfig, MeasGapConfig_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_setup_12_sequence[] = {
  { &hf_lte_rrc_mobilityStateParameters, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MobilityStateParameters },
  { &hf_lte_rrc_timeToTrigger_SF, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SpeedStateScaleFactors },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_setup_12(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_setup_12, T_setup_12_sequence);

  return offset;
}


static const value_string lte_rrc_T_speedStatePars_vals[] = {
  {   0, "release" },
  {   1, "setup" },
  { 0, NULL }
};

static const per_choice_t T_speedStatePars_choice[] = {
  {   0, &hf_lte_rrc_release     , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   1, &hf_lte_rrc_setup_12    , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_setup_12 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_speedStatePars(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_speedStatePars, T_speedStatePars_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t MeasConfig_sequence[] = {
  { &hf_lte_rrc_measObjectToRemoveList, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_MeasObjectToRemoveList },
  { &hf_lte_rrc_measObjectToAddModList, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_MeasObjectToAddModList },
  { &hf_lte_rrc_reportConfigToRemoveList, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_ReportConfigToRemoveList },
  { &hf_lte_rrc_reportConfigToAddModList, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_ReportConfigToAddModList },
  { &hf_lte_rrc_measIdToRemoveList, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_MeasIdToRemoveList },
  { &hf_lte_rrc_measIdToAddModList, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_MeasIdToAddModList },
  { &hf_lte_rrc_quantityConfig, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_QuantityConfig },
  { &hf_lte_rrc_measGapConfig, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_MeasGapConfig },
  { &hf_lte_rrc_s_Measure   , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_RSRP_Range },
  { &hf_lte_rrc_preRegistrationInfoHRPD, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_PreRegistrationInfoHRPD },
  { &hf_lte_rrc_speedStatePars, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_T_speedStatePars },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MeasConfig(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MeasConfig, MeasConfig_sequence);

  return offset;
}


static const per_sequence_t CarrierFreqEUTRA_sequence[] = {
  { &hf_lte_rrc_dl_CarrierFreq, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ARFCN_ValueEUTRA },
  { &hf_lte_rrc_ul_CarrierFreq, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_ARFCN_ValueEUTRA },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CarrierFreqEUTRA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CarrierFreqEUTRA, CarrierFreqEUTRA_sequence);

  return offset;
}


static const value_string lte_rrc_T_dl_Bandwidth_01_vals[] = {
  {   0, "n6" },
  {   1, "n15" },
  {   2, "n25" },
  {   3, "n50" },
  {   4, "n75" },
  {   5, "n100" },
  {   6, "spare10" },
  {   7, "spare9" },
  {   8, "spare8" },
  {   9, "spare7" },
  {  10, "spare6" },
  {  11, "spare5" },
  {  12, "spare4" },
  {  13, "spare3" },
  {  14, "spare2" },
  {  15, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_dl_Bandwidth_01(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_ul_Bandwidth_01_vals[] = {
  {   0, "n6" },
  {   1, "n15" },
  {   2, "n25" },
  {   3, "n50" },
  {   4, "n75" },
  {   5, "n100" },
  {   6, "spare10" },
  {   7, "spare9" },
  {   8, "spare8" },
  {   9, "spare7" },
  {  10, "spare6" },
  {  11, "spare5" },
  {  12, "spare4" },
  {  13, "spare3" },
  {  14, "spare2" },
  {  15, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_ul_Bandwidth_01(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t CarrierBandwidthEUTRA_sequence[] = {
  { &hf_lte_rrc_dl_Bandwidth_01, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_dl_Bandwidth_01 },
  { &hf_lte_rrc_ul_Bandwidth_01, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_ul_Bandwidth_01 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CarrierBandwidthEUTRA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CarrierBandwidthEUTRA, CarrierBandwidthEUTRA_sequence);

  return offset;
}


static const value_string lte_rrc_T_t304_01_vals[] = {
  {   0, "ms50" },
  {   1, "ms100" },
  {   2, "ms150" },
  {   3, "ms200" },
  {   4, "ms500" },
  {   5, "ms1000" },
  {   6, "ms2000" },
  {   7, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_t304_01(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t PRACH_Config_sequence[] = {
  { &hf_lte_rrc_rootSequenceIndex, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_837 },
  { &hf_lte_rrc_prach_ConfigInfo, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_PRACH_ConfigInfo },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_PRACH_Config(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_PRACH_Config, PRACH_Config_sequence);

  return offset;
}


static const value_string lte_rrc_T_antennaPortsCount_vals[] = {
  {   0, "an1" },
  {   1, "an2" },
  {   2, "an4" },
  {   3, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_antennaPortsCount(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t AntennaInfoCommon_sequence[] = {
  { &hf_lte_rrc_antennaPortsCount, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_antennaPortsCount },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_AntennaInfoCommon(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_AntennaInfoCommon, AntennaInfoCommon_sequence);

  return offset;
}


static const per_sequence_t RadioResourceConfigCommon_sequence[] = {
  { &hf_lte_rrc_rach_ConfigCommon, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_RACH_ConfigCommon },
  { &hf_lte_rrc_prach_Config_01, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PRACH_Config },
  { &hf_lte_rrc_pdsch_ConfigCommon, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_PDSCH_ConfigCommon },
  { &hf_lte_rrc_pusch_ConfigCommon, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PUSCH_ConfigCommon },
  { &hf_lte_rrc_phich_Config, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_PHICH_Config },
  { &hf_lte_rrc_pucch_ConfigCommon, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_PUCCH_ConfigCommon },
  { &hf_lte_rrc_soundingRS_UL_ConfigCommon, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_SoundingRS_UL_ConfigCommon },
  { &hf_lte_rrc_uplinkPowerControlCommon, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_UplinkPowerControlCommon },
  { &hf_lte_rrc_antennaInfoCommon, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_AntennaInfoCommon },
  { &hf_lte_rrc_p_Max       , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_P_Max },
  { &hf_lte_rrc_tdd_Config  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_TDD_Config },
  { &hf_lte_rrc_ul_CyclicPrefixLength, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_UL_CyclicPrefixLength },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RadioResourceConfigCommon(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RadioResourceConfigCommon, RadioResourceConfigCommon_sequence);

  return offset;
}


static const per_sequence_t RACH_ConfigDedicated_sequence[] = {
  { &hf_lte_rrc_ra_PreambleIndex, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_63 },
  { &hf_lte_rrc_ra_PRACH_MaskIndex, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_15 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RACH_ConfigDedicated(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RACH_ConfigDedicated, RACH_ConfigDedicated_sequence);

  return offset;
}


static const per_sequence_t MobilityControlInfo_sequence[] = {
  { &hf_lte_rrc_targetPhysCellId, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhysCellId },
  { &hf_lte_rrc_carrierFreq_04, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_CarrierFreqEUTRA },
  { &hf_lte_rrc_carrierBandwidth, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_CarrierBandwidthEUTRA },
  { &hf_lte_rrc_additionalSpectrumEmission, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_AdditionalSpectrumEmission },
  { &hf_lte_rrc_t304_01     , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_t304_01 },
  { &hf_lte_rrc_newUE_Identity, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_C_RNTI },
  { &hf_lte_rrc_radioResourceConfigCommon_01, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RadioResourceConfigCommon },
  { &hf_lte_rrc_rach_ConfigDedicated, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_RACH_ConfigDedicated },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MobilityControlInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MobilityControlInfo, MobilityControlInfo_sequence);

  return offset;
}


static const per_sequence_t SEQUENCE_SIZE_1_maxDRB_OF_DedicatedInfoNAS_sequence_of[1] = {
  { &hf_lte_rrc_dedicatedInfoNASList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_DedicatedInfoNAS },
};

static int
dissect_lte_rrc_SEQUENCE_SIZE_1_maxDRB_OF_DedicatedInfoNAS(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_SEQUENCE_SIZE_1_maxDRB_OF_DedicatedInfoNAS, SEQUENCE_SIZE_1_maxDRB_OF_DedicatedInfoNAS_sequence_of,
                                                  1, maxDRB, FALSE);

  return offset;
}


static const value_string lte_rrc_T_cipheringAlgorithm_vals[] = {
  {   0, "eea0" },
  {   1, "eea1" },
  {   2, "eea2" },
  {   3, "spare5" },
  {   4, "spare4" },
  {   5, "spare3" },
  {   6, "spare2" },
  {   7, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_cipheringAlgorithm(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_integrityProtAlgorithm_vals[] = {
  {   0, "eia0-v920" },
  {   1, "eia1" },
  {   2, "eia2" },
  {   3, "spare5" },
  {   4, "spare4" },
  {   5, "spare3" },
  {   6, "spare2" },
  {   7, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_integrityProtAlgorithm(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t SecurityAlgorithmConfig_sequence[] = {
  { &hf_lte_rrc_cipheringAlgorithm, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_cipheringAlgorithm },
  { &hf_lte_rrc_integrityProtAlgorithm, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_integrityProtAlgorithm },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SecurityAlgorithmConfig(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SecurityAlgorithmConfig, SecurityAlgorithmConfig_sequence);

  return offset;
}


static const per_sequence_t T_intraLTE_sequence[] = {
  { &hf_lte_rrc_securityAlgorithmConfig, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_SecurityAlgorithmConfig },
  { &hf_lte_rrc_keyChangeIndicator, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_nextHopChainingCount, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_NextHopChainingCount },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_intraLTE(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_intraLTE, T_intraLTE_sequence);

  return offset;
}



static int
dissect_lte_rrc_OCTET_STRING_SIZE_6(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       6, 6, FALSE, NULL);

  return offset;
}


static const per_sequence_t T_interRAT_sequence[] = {
  { &hf_lte_rrc_securityAlgorithmConfig, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SecurityAlgorithmConfig },
  { &hf_lte_rrc_nas_SecurityParamToEUTRA, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_OCTET_STRING_SIZE_6 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_interRAT(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_interRAT, T_interRAT_sequence);

  return offset;
}


static const value_string lte_rrc_T_handoverType_vals[] = {
  {   0, "intraLTE" },
  {   1, "interRAT" },
  { 0, NULL }
};

static const per_choice_t T_handoverType_choice[] = {
  {   0, &hf_lte_rrc_intraLTE    , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_intraLTE },
  {   1, &hf_lte_rrc_interRAT    , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_interRAT },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_handoverType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_handoverType, T_handoverType_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t SecurityConfigHO_sequence[] = {
  { &hf_lte_rrc_handoverType, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_handoverType },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SecurityConfigHO(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SecurityConfigHO, SecurityConfigHO_sequence);

  return offset;
}


static const value_string lte_rrc_T_proximityIndicationEUTRA_r9_vals[] = {
  {   0, "enabled" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_proximityIndicationEUTRA_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_proximityIndicationUTRA_r9_vals[] = {
  {   0, "enabled" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_proximityIndicationUTRA_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t ReportProximityConfig_r9_sequence[] = {
  { &hf_lte_rrc_proximityIndicationEUTRA_r9, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_proximityIndicationEUTRA_r9 },
  { &hf_lte_rrc_proximityIndicationUTRA_r9, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_proximityIndicationUTRA_r9 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_ReportProximityConfig_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_ReportProximityConfig_r9, ReportProximityConfig_r9_sequence);

  return offset;
}


static const per_sequence_t OtherConfig_r9_sequence[] = {
  { &hf_lte_rrc_reportProximityConfig_r9, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_ReportProximityConfig_r9 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_OtherConfig_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_OtherConfig_r9, OtherConfig_r9_sequence);

  return offset;
}


static const value_string lte_rrc_T_fullConfig_r9_vals[] = {
  {   0, "true" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_fullConfig_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_12_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_12(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_12, T_nonCriticalExtension_12_sequence);

  return offset;
}


static const per_sequence_t RRCConnectionReconfiguration_v920_IEs_sequence[] = {
  { &hf_lte_rrc_otherConfig_r9, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_OtherConfig_r9 },
  { &hf_lte_rrc_fullConfig_r9, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_fullConfig_r9 },
  { &hf_lte_rrc_nonCriticalExtension_18, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_12 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionReconfiguration_v920_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionReconfiguration_v920_IEs, RRCConnectionReconfiguration_v920_IEs_sequence);

  return offset;
}


static const per_sequence_t RRCConnectionReconfiguration_v890_IEs_sequence[] = {
  { &hf_lte_rrc_lateR8NonCriticalExtension, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_OCTET_STRING },
  { &hf_lte_rrc_nonCriticalExtension_17, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_RRCConnectionReconfiguration_v920_IEs },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionReconfiguration_v890_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionReconfiguration_v890_IEs, RRCConnectionReconfiguration_v890_IEs_sequence);

  return offset;
}


static const per_sequence_t RRCConnectionReconfiguration_r8_IEs_sequence[] = {
  { &hf_lte_rrc_measConfig  , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_MeasConfig },
  { &hf_lte_rrc_mobilityControlInfo, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_MobilityControlInfo },
  { &hf_lte_rrc_dedicatedInfoNASList, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_SEQUENCE_SIZE_1_maxDRB_OF_DedicatedInfoNAS },
  { &hf_lte_rrc_radioResourceConfigDedicated, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_RadioResourceConfigDedicated },
  { &hf_lte_rrc_securityConfigHO, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_SecurityConfigHO },
  { &hf_lte_rrc_nonCriticalExtension_16, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_RRCConnectionReconfiguration_v890_IEs },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionReconfiguration_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionReconfiguration_r8_IEs, RRCConnectionReconfiguration_r8_IEs_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_13_vals[] = {
  {   0, "rrcConnectionReconfiguration-r8" },
  {   1, "spare7" },
  {   2, "spare6" },
  {   3, "spare5" },
  {   4, "spare4" },
  {   5, "spare3" },
  {   6, "spare2" },
  {   7, "spare1" },
  { 0, NULL }
};

static const per_choice_t T_c1_13_choice[] = {
  {   0, &hf_lte_rrc_rrcConnectionReconfiguration_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_RRCConnectionReconfiguration_r8_IEs },
  {   1, &hf_lte_rrc_spare7      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   2, &hf_lte_rrc_spare6      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   3, &hf_lte_rrc_spare5      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   4, &hf_lte_rrc_spare4      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   5, &hf_lte_rrc_spare3      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   6, &hf_lte_rrc_spare2      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   7, &hf_lte_rrc_spare1      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_13(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_13, T_c1_13_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_09_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_09(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_09, T_criticalExtensionsFuture_09_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_09_vals[] = {
  {   0, "c1" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_09_choice[] = {
  {   0, &hf_lte_rrc_c1_13       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_13 },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_09, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_09 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_09(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_09, T_criticalExtensions_09_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t RRCConnectionReconfiguration_sequence[] = {
  { &hf_lte_rrc_rrc_TransactionIdentifier, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RRC_TransactionIdentifier },
  { &hf_lte_rrc_criticalExtensions_09, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_09 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionReconfiguration(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:RRCConnectionReconfiguration ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionReconfiguration, RRCConnectionReconfiguration_sequence);

  return offset;
}


static const value_string lte_rrc_ReleaseCause_vals[] = {
  {   0, "loadBalancingTAUrequired" },
  {   1, "other" },
  {   2, "spare2" },
  {   3, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_ReleaseCause(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_RedirectedCarrierInfo_vals[] = {
  {   0, "eutra" },
  {   1, "geran" },
  {   2, "utra-FDD" },
  {   3, "utra-TDD" },
  {   4, "cdma2000-HRPD" },
  {   5, "cdma2000-1xRTT" },
  { 0, NULL }
};

static const per_choice_t RedirectedCarrierInfo_choice[] = {
  {   0, &hf_lte_rrc_eutra       , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_ARFCN_ValueEUTRA },
  {   1, &hf_lte_rrc_geran_01    , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_CarrierFreqsGERAN },
  {   2, &hf_lte_rrc_utra_FDD    , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_ARFCN_ValueUTRA },
  {   3, &hf_lte_rrc_utra_TDD    , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_ARFCN_ValueUTRA },
  {   4, &hf_lte_rrc_cdma2000_HRPD, ASN1_EXTENSION_ROOT    , dissect_lte_rrc_CarrierFreqCDMA2000 },
  {   5, &hf_lte_rrc_cdma2000_1xRTT, ASN1_EXTENSION_ROOT    , dissect_lte_rrc_CarrierFreqCDMA2000 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_RedirectedCarrierInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_RedirectedCarrierInfo, RedirectedCarrierInfo_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t FreqPriorityEUTRA_sequence[] = {
  { &hf_lte_rrc_carrierFreq_01, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ARFCN_ValueEUTRA },
  { &hf_lte_rrc_cellReselectionPriority, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CellReselectionPriority },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_FreqPriorityEUTRA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_FreqPriorityEUTRA, FreqPriorityEUTRA_sequence);

  return offset;
}


static const per_sequence_t FreqPriorityListEUTRA_sequence_of[1] = {
  { &hf_lte_rrc_FreqPriorityListEUTRA_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_FreqPriorityEUTRA },
};

static int
dissect_lte_rrc_FreqPriorityListEUTRA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_FreqPriorityListEUTRA, FreqPriorityListEUTRA_sequence_of,
                                                  1, maxFreq, FALSE);

  return offset;
}


static const per_sequence_t FreqsPriorityGERAN_sequence[] = {
  { &hf_lte_rrc_carrierFreqs, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CarrierFreqsGERAN },
  { &hf_lte_rrc_cellReselectionPriority, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CellReselectionPriority },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_FreqsPriorityGERAN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_FreqsPriorityGERAN, FreqsPriorityGERAN_sequence);

  return offset;
}


static const per_sequence_t FreqsPriorityListGERAN_sequence_of[1] = {
  { &hf_lte_rrc_FreqsPriorityListGERAN_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_FreqsPriorityGERAN },
};

static int
dissect_lte_rrc_FreqsPriorityListGERAN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_FreqsPriorityListGERAN, FreqsPriorityListGERAN_sequence_of,
                                                  1, maxGNFG, FALSE);

  return offset;
}


static const per_sequence_t FreqPriorityUTRA_FDD_sequence[] = {
  { &hf_lte_rrc_carrierFreq_02, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ARFCN_ValueUTRA },
  { &hf_lte_rrc_cellReselectionPriority, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CellReselectionPriority },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_FreqPriorityUTRA_FDD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_FreqPriorityUTRA_FDD, FreqPriorityUTRA_FDD_sequence);

  return offset;
}


static const per_sequence_t FreqPriorityListUTRA_FDD_sequence_of[1] = {
  { &hf_lte_rrc_FreqPriorityListUTRA_FDD_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_FreqPriorityUTRA_FDD },
};

static int
dissect_lte_rrc_FreqPriorityListUTRA_FDD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_FreqPriorityListUTRA_FDD, FreqPriorityListUTRA_FDD_sequence_of,
                                                  1, maxUTRA_FDD_Carrier, FALSE);

  return offset;
}


static const per_sequence_t FreqPriorityUTRA_TDD_sequence[] = {
  { &hf_lte_rrc_carrierFreq_02, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ARFCN_ValueUTRA },
  { &hf_lte_rrc_cellReselectionPriority, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CellReselectionPriority },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_FreqPriorityUTRA_TDD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_FreqPriorityUTRA_TDD, FreqPriorityUTRA_TDD_sequence);

  return offset;
}


static const per_sequence_t FreqPriorityListUTRA_TDD_sequence_of[1] = {
  { &hf_lte_rrc_FreqPriorityListUTRA_TDD_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_FreqPriorityUTRA_TDD },
};

static int
dissect_lte_rrc_FreqPriorityListUTRA_TDD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_FreqPriorityListUTRA_TDD, FreqPriorityListUTRA_TDD_sequence_of,
                                                  1, maxUTRA_TDD_Carrier, FALSE);

  return offset;
}


static const per_sequence_t BandClassPriorityHRPD_sequence[] = {
  { &hf_lte_rrc_bandClass   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BandclassCDMA2000 },
  { &hf_lte_rrc_cellReselectionPriority, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CellReselectionPriority },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_BandClassPriorityHRPD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_BandClassPriorityHRPD, BandClassPriorityHRPD_sequence);

  return offset;
}


static const per_sequence_t BandClassPriorityListHRPD_sequence_of[1] = {
  { &hf_lte_rrc_BandClassPriorityListHRPD_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BandClassPriorityHRPD },
};

static int
dissect_lte_rrc_BandClassPriorityListHRPD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_BandClassPriorityListHRPD, BandClassPriorityListHRPD_sequence_of,
                                                  1, maxCDMA_BandClass, FALSE);

  return offset;
}


static const per_sequence_t BandClassPriority1XRTT_sequence[] = {
  { &hf_lte_rrc_bandClass   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BandclassCDMA2000 },
  { &hf_lte_rrc_cellReselectionPriority, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CellReselectionPriority },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_BandClassPriority1XRTT(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_BandClassPriority1XRTT, BandClassPriority1XRTT_sequence);

  return offset;
}


static const per_sequence_t BandClassPriorityList1XRTT_sequence_of[1] = {
  { &hf_lte_rrc_BandClassPriorityList1XRTT_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BandClassPriority1XRTT },
};

static int
dissect_lte_rrc_BandClassPriorityList1XRTT(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_BandClassPriorityList1XRTT, BandClassPriorityList1XRTT_sequence_of,
                                                  1, maxCDMA_BandClass, FALSE);

  return offset;
}


static const value_string lte_rrc_T_t320_vals[] = {
  {   0, "min5" },
  {   1, "min10" },
  {   2, "min20" },
  {   3, "min30" },
  {   4, "min60" },
  {   5, "min120" },
  {   6, "min180" },
  {   7, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_t320(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t IdleModeMobilityControlInfo_sequence[] = {
  { &hf_lte_rrc_freqPriorityListEUTRA, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_FreqPriorityListEUTRA },
  { &hf_lte_rrc_freqPriorityListGERAN, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_FreqsPriorityListGERAN },
  { &hf_lte_rrc_freqPriorityListUTRA_FDD, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_FreqPriorityListUTRA_FDD },
  { &hf_lte_rrc_freqPriorityListUTRA_TDD, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_FreqPriorityListUTRA_TDD },
  { &hf_lte_rrc_bandClassPriorityListHRPD, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_BandClassPriorityListHRPD },
  { &hf_lte_rrc_bandClassPriorityList1XRTT, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_BandClassPriorityList1XRTT },
  { &hf_lte_rrc_t320        , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_T_t320 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_IdleModeMobilityControlInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_IdleModeMobilityControlInfo, IdleModeMobilityControlInfo_sequence);

  return offset;
}


static const per_sequence_t CellInfoGERAN_r9_sequence[] = {
  { &hf_lte_rrc_physCellId_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhysCellIdGERAN },
  { &hf_lte_rrc_carrierFreq_r9_01, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CarrierFreqGERAN },
  { &hf_lte_rrc_systemInformation_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SystemInfoListGERAN },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CellInfoGERAN_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CellInfoGERAN_r9, CellInfoGERAN_r9_sequence);

  return offset;
}


static const per_sequence_t CellInfoListGERAN_r9_sequence_of[1] = {
  { &hf_lte_rrc_CellInfoListGERAN_r9_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CellInfoGERAN_r9 },
};

static int
dissect_lte_rrc_CellInfoListGERAN_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_CellInfoListGERAN_r9, CellInfoListGERAN_r9_sequence_of,
                                                  1, maxCellInfo_GERAN_r9, FALSE);

  return offset;
}


static const per_sequence_t CellInfoUTRA_FDD_r9_sequence[] = {
  { &hf_lte_rrc_physCellId_r9_01, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhysCellIdUTRA_FDD },
  { &hf_lte_rrc_utra_BCCH_Container_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_OCTET_STRING },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CellInfoUTRA_FDD_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CellInfoUTRA_FDD_r9, CellInfoUTRA_FDD_r9_sequence);

  return offset;
}


static const per_sequence_t CellInfoListUTRA_FDD_r9_sequence_of[1] = {
  { &hf_lte_rrc_CellInfoListUTRA_FDD_r9_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CellInfoUTRA_FDD_r9 },
};

static int
dissect_lte_rrc_CellInfoListUTRA_FDD_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_CellInfoListUTRA_FDD_r9, CellInfoListUTRA_FDD_r9_sequence_of,
                                                  1, maxUTRA_CellInfo_r9, FALSE);

  return offset;
}


static const per_sequence_t CellInfoUTRA_TDD_r9_sequence[] = {
  { &hf_lte_rrc_physCellId_r9_02, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhysCellIdUTRA_TDD },
  { &hf_lte_rrc_utra_BCCH_Container_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_OCTET_STRING },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CellInfoUTRA_TDD_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CellInfoUTRA_TDD_r9, CellInfoUTRA_TDD_r9_sequence);

  return offset;
}


static const per_sequence_t CellInfoListUTRA_TDD_r9_sequence_of[1] = {
  { &hf_lte_rrc_CellInfoListUTRA_TDD_r9_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CellInfoUTRA_TDD_r9 },
};

static int
dissect_lte_rrc_CellInfoListUTRA_TDD_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_CellInfoListUTRA_TDD_r9, CellInfoListUTRA_TDD_r9_sequence_of,
                                                  1, maxUTRA_CellInfo_r9, FALSE);

  return offset;
}


static const value_string lte_rrc_T_cellInfoList_r9_vals[] = {
  {   0, "geran-r9" },
  {   1, "utra-FDD-r9" },
  {   2, "utra-TDD-r9" },
  { 0, NULL }
};

static const per_choice_t T_cellInfoList_r9_choice[] = {
  {   0, &hf_lte_rrc_geran_r9    , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_CellInfoListGERAN_r9 },
  {   1, &hf_lte_rrc_utra_FDD_r9 , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_CellInfoListUTRA_FDD_r9 },
  {   2, &hf_lte_rrc_utra_TDD_r9 , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_CellInfoListUTRA_TDD_r9 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_cellInfoList_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_cellInfoList_r9, T_cellInfoList_r9_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_18_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_18(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_18, T_nonCriticalExtension_18_sequence);

  return offset;
}


static const per_sequence_t RRCConnectionRelease_v920_IEs_sequence[] = {
  { &hf_lte_rrc_cellInfoList_r9, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_cellInfoList_r9 },
  { &hf_lte_rrc_nonCriticalExtension_27, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_18 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionRelease_v920_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionRelease_v920_IEs, RRCConnectionRelease_v920_IEs_sequence);

  return offset;
}


static const per_sequence_t RRCConnectionRelease_v890_IEs_sequence[] = {
  { &hf_lte_rrc_lateR8NonCriticalExtension, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_OCTET_STRING },
  { &hf_lte_rrc_nonCriticalExtension_26, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_RRCConnectionRelease_v920_IEs },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionRelease_v890_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionRelease_v890_IEs, RRCConnectionRelease_v890_IEs_sequence);

  return offset;
}


static const per_sequence_t RRCConnectionRelease_r8_IEs_sequence[] = {
  { &hf_lte_rrc_releaseCause, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ReleaseCause },
  { &hf_lte_rrc_redirectedCarrierInfo, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_RedirectedCarrierInfo },
  { &hf_lte_rrc_idleModeMobilityControlInfo, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_IdleModeMobilityControlInfo },
  { &hf_lte_rrc_nonCriticalExtension_25, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_RRCConnectionRelease_v890_IEs },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionRelease_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionRelease_r8_IEs, RRCConnectionRelease_r8_IEs_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_16_vals[] = {
  {   0, "rrcConnectionRelease-r8" },
  {   1, "spare3" },
  {   2, "spare2" },
  {   3, "spare1" },
  { 0, NULL }
};

static const per_choice_t T_c1_16_choice[] = {
  {   0, &hf_lte_rrc_rrcConnectionRelease_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_RRCConnectionRelease_r8_IEs },
  {   1, &hf_lte_rrc_spare3      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   2, &hf_lte_rrc_spare2      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   3, &hf_lte_rrc_spare1      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_16(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_16, T_c1_16_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_16_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_16(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_16, T_criticalExtensionsFuture_16_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_16_vals[] = {
  {   0, "c1" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_16_choice[] = {
  {   0, &hf_lte_rrc_c1_16       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_16 },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_16, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_16 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_16(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_16, T_criticalExtensions_16_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t RRCConnectionRelease_sequence[] = {
  { &hf_lte_rrc_rrc_TransactionIdentifier, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RRC_TransactionIdentifier },
  { &hf_lte_rrc_criticalExtensions_16, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_16 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionRelease(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:RRCConnectionRelease ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionRelease, RRCConnectionRelease_sequence);

  return offset;
}


static const per_sequence_t SecurityConfigSMC_sequence[] = {
  { &hf_lte_rrc_securityAlgorithmConfig, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SecurityAlgorithmConfig },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SecurityConfigSMC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SecurityConfigSMC, SecurityConfigSMC_sequence);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_21_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_21(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_21, T_nonCriticalExtension_21_sequence);

  return offset;
}


static const per_sequence_t SecurityModeCommand_r8_IEs_sequence[] = {
  { &hf_lte_rrc_securityConfigSMC, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SecurityConfigSMC },
  { &hf_lte_rrc_nonCriticalExtension_30, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_21 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SecurityModeCommand_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SecurityModeCommand_r8_IEs, SecurityModeCommand_r8_IEs_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_19_vals[] = {
  {   0, "securityModeCommand-r8" },
  {   1, "spare3" },
  {   2, "spare2" },
  {   3, "spare1" },
  { 0, NULL }
};

static const per_choice_t T_c1_19_choice[] = {
  {   0, &hf_lte_rrc_securityModeCommand_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_SecurityModeCommand_r8_IEs },
  {   1, &hf_lte_rrc_spare3      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   2, &hf_lte_rrc_spare2      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   3, &hf_lte_rrc_spare1      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_19(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_19, T_c1_19_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_20_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_20(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_20, T_criticalExtensionsFuture_20_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_20_vals[] = {
  {   0, "c1" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_20_choice[] = {
  {   0, &hf_lte_rrc_c1_19       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_19 },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_20, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_20 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_20(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_20, T_criticalExtensions_20_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t SecurityModeCommand_sequence[] = {
  { &hf_lte_rrc_rrc_TransactionIdentifier, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RRC_TransactionIdentifier },
  { &hf_lte_rrc_criticalExtensions_20, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_20 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SecurityModeCommand(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:SecurityModeCommand ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SecurityModeCommand, SecurityModeCommand_sequence);

  return offset;
}


static const value_string lte_rrc_RAT_Type_vals[] = {
  {   0, "eutra" },
  {   1, "utra" },
  {   2, "geran-cs" },
  {   3, "geran-ps" },
  {   4, "cdma2000-1XRTT" },
  {   5, "spare3" },
  {   6, "spare2" },
  {   7, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_RAT_Type(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, &lte_rrc_rat_type_value, TRUE, 0, NULL);




  return offset;
}


static const per_sequence_t UE_CapabilityRequest_sequence_of[1] = {
  { &hf_lte_rrc_UE_CapabilityRequest_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RAT_Type },
};

static int
dissect_lte_rrc_UE_CapabilityRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_UE_CapabilityRequest, UE_CapabilityRequest_sequence_of,
                                                  1, maxRAT_Capabilities, FALSE);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_26_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_26(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_26, T_nonCriticalExtension_26_sequence);

  return offset;
}


static const per_sequence_t UECapabilityEnquiry_r8_IEs_sequence[] = {
  { &hf_lte_rrc_ue_CapabilityRequest, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_UE_CapabilityRequest },
  { &hf_lte_rrc_nonCriticalExtension_37, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_26 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_UECapabilityEnquiry_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_UECapabilityEnquiry_r8_IEs, UECapabilityEnquiry_r8_IEs_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_20_vals[] = {
  {   0, "ueCapabilityEnquiry-r8" },
  {   1, "spare3" },
  {   2, "spare2" },
  {   3, "spare1" },
  { 0, NULL }
};

static const per_choice_t T_c1_20_choice[] = {
  {   0, &hf_lte_rrc_ueCapabilityEnquiry_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_UECapabilityEnquiry_r8_IEs },
  {   1, &hf_lte_rrc_spare3      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   2, &hf_lte_rrc_spare2      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   3, &hf_lte_rrc_spare1      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_20(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_20, T_c1_20_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_24_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_24(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_24, T_criticalExtensionsFuture_24_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_24_vals[] = {
  {   0, "c1" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_24_choice[] = {
  {   0, &hf_lte_rrc_c1_20       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_20 },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_24, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_24 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_24(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_24, T_criticalExtensions_24_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t UECapabilityEnquiry_sequence[] = {
  { &hf_lte_rrc_rrc_TransactionIdentifier, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RRC_TransactionIdentifier },
  { &hf_lte_rrc_criticalExtensions_24, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_24 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_UECapabilityEnquiry(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:UECapabilityEnquiry ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_UECapabilityEnquiry, UECapabilityEnquiry_sequence);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_33554431(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 33554431U, NULL, FALSE);

  return offset;
}


static const per_sequence_t DRB_CountMSB_Info_sequence[] = {
  { &hf_lte_rrc_drb_Identity, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_DRB_Identity },
  { &hf_lte_rrc_countMSB_Uplink, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_33554431 },
  { &hf_lte_rrc_countMSB_Downlink, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_33554431 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_DRB_CountMSB_Info(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_DRB_CountMSB_Info, DRB_CountMSB_Info_sequence);

  return offset;
}


static const per_sequence_t DRB_CountMSB_InfoList_sequence_of[1] = {
  { &hf_lte_rrc_DRB_CountMSB_InfoList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_DRB_CountMSB_Info },
};

static int
dissect_lte_rrc_DRB_CountMSB_InfoList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_DRB_CountMSB_InfoList, DRB_CountMSB_InfoList_sequence_of,
                                                  1, maxDRB, FALSE);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension, T_nonCriticalExtension_sequence);

  return offset;
}


static const per_sequence_t CounterCheck_r8_IEs_sequence[] = {
  { &hf_lte_rrc_drb_CountMSB_InfoList, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_DRB_CountMSB_InfoList },
  { &hf_lte_rrc_nonCriticalExtension, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CounterCheck_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CounterCheck_r8_IEs, CounterCheck_r8_IEs_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_07_vals[] = {
  {   0, "counterCheck-r8" },
  {   1, "spare3" },
  {   2, "spare2" },
  {   3, "spare1" },
  { 0, NULL }
};

static const per_choice_t T_c1_07_choice[] = {
  {   0, &hf_lte_rrc_counterCheck_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_CounterCheck_r8_IEs },
  {   1, &hf_lte_rrc_spare3      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   2, &hf_lte_rrc_spare2      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   3, &hf_lte_rrc_spare1      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_07(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_07, T_c1_07_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture, T_criticalExtensionsFuture_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_vals[] = {
  {   0, "c1" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_choice[] = {
  {   0, &hf_lte_rrc_c1_07       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_07 },
  {   1, &hf_lte_rrc_criticalExtensionsFuture, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions, T_criticalExtensions_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t CounterCheck_sequence[] = {
  { &hf_lte_rrc_rrc_TransactionIdentifier, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RRC_TransactionIdentifier },
  { &hf_lte_rrc_criticalExtensions, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CounterCheck(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CounterCheck, CounterCheck_sequence);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_28_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_28(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_28, T_nonCriticalExtension_28_sequence);

  return offset;
}


static const per_sequence_t UEInformationRequest_r9_IEs_sequence[] = {
  { &hf_lte_rrc_rach_ReportReq_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_rlf_ReportReq_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_nonCriticalExtension_39, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_28 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_UEInformationRequest_r9_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_UEInformationRequest_r9_IEs, UEInformationRequest_r9_IEs_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_22_vals[] = {
  {   0, "ueInformationRequest-r9" },
  {   1, "spare3" },
  {   2, "spare2" },
  {   3, "spare1" },
  { 0, NULL }
};

static const per_choice_t T_c1_22_choice[] = {
  {   0, &hf_lte_rrc_ueInformationRequest_r9_01, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_UEInformationRequest_r9_IEs },
  {   1, &hf_lte_rrc_spare3      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   2, &hf_lte_rrc_spare2      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   3, &hf_lte_rrc_spare1      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_22(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_22, T_c1_22_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_26_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_26(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_26, T_criticalExtensionsFuture_26_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_26_vals[] = {
  {   0, "c1" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_26_choice[] = {
  {   0, &hf_lte_rrc_c1_22       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_22 },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_26, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_26 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_26(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_26, T_criticalExtensions_26_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t UEInformationRequest_r9_sequence[] = {
  { &hf_lte_rrc_rrc_TransactionIdentifier, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RRC_TransactionIdentifier },
  { &hf_lte_rrc_criticalExtensions_26, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_26 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_UEInformationRequest_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_UEInformationRequest_r9, UEInformationRequest_r9_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_04_vals[] = {
  {   0, "csfbParametersResponseCDMA2000" },
  {   1, "dlInformationTransfer" },
  {   2, "handoverFromEUTRAPreparationRequest" },
  {   3, "mobilityFromEUTRACommand" },
  {   4, "rrcConnectionReconfiguration" },
  {   5, "rrcConnectionRelease" },
  {   6, "securityModeCommand" },
  {   7, "ueCapabilityEnquiry" },
  {   8, "counterCheck" },
  {   9, "ueInformationRequest-r9" },
  {  10, "spare6" },
  {  11, "spare5" },
  {  12, "spare4" },
  {  13, "spare3" },
  {  14, "spare2" },
  {  15, "spare1" },
  { 0, NULL }
};

static const per_choice_t T_c1_04_choice[] = {
  {   0, &hf_lte_rrc_csfbParametersResponseCDMA2000, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_CSFBParametersResponseCDMA2000 },
  {   1, &hf_lte_rrc_dlInformationTransfer, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_DLInformationTransfer },
  {   2, &hf_lte_rrc_handoverFromEUTRAPreparationRequest, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_HandoverFromEUTRAPreparationRequest },
  {   3, &hf_lte_rrc_mobilityFromEUTRACommand, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_MobilityFromEUTRACommand },
  {   4, &hf_lte_rrc_rrcConnectionReconfiguration, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_RRCConnectionReconfiguration },
  {   5, &hf_lte_rrc_rrcConnectionRelease, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_RRCConnectionRelease },
  {   6, &hf_lte_rrc_securityModeCommand, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_SecurityModeCommand },
  {   7, &hf_lte_rrc_ueCapabilityEnquiry, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_UECapabilityEnquiry },
  {   8, &hf_lte_rrc_counterCheck, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_CounterCheck },
  {   9, &hf_lte_rrc_ueInformationRequest_r9, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_UEInformationRequest_r9 },
  {  10, &hf_lte_rrc_spare6      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {  11, &hf_lte_rrc_spare5      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {  12, &hf_lte_rrc_spare4      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {  13, &hf_lte_rrc_spare3      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {  14, &hf_lte_rrc_spare2      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {  15, &hf_lte_rrc_spare1      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_04(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_04, T_c1_04_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_messageClassExtension_04_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_messageClassExtension_04(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_messageClassExtension_04, T_messageClassExtension_04_sequence);

  return offset;
}


static const value_string lte_rrc_DL_DCCH_MessageType_vals[] = {
  {   0, "c1" },
  {   1, "messageClassExtension" },
  { 0, NULL }
};

static const per_choice_t DL_DCCH_MessageType_choice[] = {
  {   0, &hf_lte_rrc_c1_04       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_04 },
  {   1, &hf_lte_rrc_messageClassExtension_04, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_messageClassExtension_04 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_DL_DCCH_MessageType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_DL_DCCH_MessageType, DL_DCCH_MessageType_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t DL_DCCH_Message_sequence[] = {
  { &hf_lte_rrc_message_05  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_DL_DCCH_MessageType },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_DL_DCCH_Message(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  actx->pinfo->link_dir = P2P_DIR_DL;

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_DL_DCCH_Message, DL_DCCH_Message_sequence);

  return offset;
}



static int
dissect_lte_rrc_ShortMAC_I(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     16, 16, FALSE, NULL);

  return offset;
}


static const per_sequence_t ReestabUE_Identity_sequence[] = {
  { &hf_lte_rrc_c_RNTI      , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_C_RNTI },
  { &hf_lte_rrc_physCellId_01, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhysCellId },
  { &hf_lte_rrc_shortMAC_I  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ShortMAC_I },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_ReestabUE_Identity(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_ReestabUE_Identity, ReestabUE_Identity_sequence);

  return offset;
}


static const value_string lte_rrc_ReestablishmentCause_vals[] = {
  {   0, "reconfigurationFailure" },
  {   1, "handoverFailure" },
  {   2, "otherFailure" },
  {   3, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_ReestablishmentCause(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t RRCConnectionReestablishmentRequest_r8_IEs_sequence[] = {
  { &hf_lte_rrc_ue_Identity_01, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ReestabUE_Identity },
  { &hf_lte_rrc_reestablishmentCause, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ReestablishmentCause },
  { &hf_lte_rrc_spare_01    , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_2 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionReestablishmentRequest_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionReestablishmentRequest_r8_IEs, RRCConnectionReestablishmentRequest_r8_IEs_sequence);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_14_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_14(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_14, T_criticalExtensionsFuture_14_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_14_vals[] = {
  {   0, "rrcConnectionReestablishmentRequest-r8" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_14_choice[] = {
  {   0, &hf_lte_rrc_rrcConnectionReestablishmentRequest_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_RRCConnectionReestablishmentRequest_r8_IEs },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_14, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_14 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_14(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_14, T_criticalExtensions_14_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t RRCConnectionReestablishmentRequest_sequence[] = {
  { &hf_lte_rrc_criticalExtensions_14, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_14 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionReestablishmentRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:RRCConnectionReestablishmentRequest ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionReestablishmentRequest, RRCConnectionReestablishmentRequest_sequence);

  return offset;
}



static int
dissect_lte_rrc_BIT_STRING_SIZE_40(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     40, 40, FALSE, NULL);

  return offset;
}


static const value_string lte_rrc_InitialUE_Identity_vals[] = {
  {   0, "s-TMSI" },
  {   1, "randomValue" },
  { 0, NULL }
};

static const per_choice_t InitialUE_Identity_choice[] = {
  {   0, &hf_lte_rrc_s_TMSI      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_S_TMSI },
  {   1, &hf_lte_rrc_randomValue , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_BIT_STRING_SIZE_40 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_InitialUE_Identity(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_InitialUE_Identity, InitialUE_Identity_choice,
                                 NULL);

  return offset;
}


static const value_string lte_rrc_EstablishmentCause_vals[] = {
  {   0, "emergency" },
  {   1, "highPriorityAccess" },
  {   2, "mt-Access" },
  {   3, "mo-Signalling" },
  {   4, "mo-Data" },
  {   5, "spare3" },
  {   6, "spare2" },
  {   7, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_EstablishmentCause(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}



static int
dissect_lte_rrc_BIT_STRING_SIZE_1(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     1, 1, FALSE, NULL);

  return offset;
}


static const per_sequence_t RRCConnectionRequest_r8_IEs_sequence[] = {
  { &hf_lte_rrc_ue_Identity_02, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_InitialUE_Identity },
  { &hf_lte_rrc_establishmentCause, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_EstablishmentCause },
  { &hf_lte_rrc_spare_02    , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_1 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionRequest_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionRequest_r8_IEs, RRCConnectionRequest_r8_IEs_sequence);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_17_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_17(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_17, T_criticalExtensionsFuture_17_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_17_vals[] = {
  {   0, "rrcConnectionRequest-r8" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_17_choice[] = {
  {   0, &hf_lte_rrc_rrcConnectionRequest_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_RRCConnectionRequest_r8_IEs },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_17, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_17 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_17(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_17, T_criticalExtensions_17_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t RRCConnectionRequest_sequence[] = {
  { &hf_lte_rrc_criticalExtensions_17, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_17 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:RRCConnectionRequest ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionRequest, RRCConnectionRequest_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_05_vals[] = {
  {   0, "rrcConnectionReestablishmentRequest" },
  {   1, "rrcConnectionRequest" },
  { 0, NULL }
};

static const per_choice_t T_c1_05_choice[] = {
  {   0, &hf_lte_rrc_rrcConnectionReestablishmentRequest, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_RRCConnectionReestablishmentRequest },
  {   1, &hf_lte_rrc_rrcConnectionRequest, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_RRCConnectionRequest },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_05(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_05, T_c1_05_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_messageClassExtension_05_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_messageClassExtension_05(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_messageClassExtension_05, T_messageClassExtension_05_sequence);

  return offset;
}


static const value_string lte_rrc_UL_CCCH_MessageType_vals[] = {
  {   0, "c1" },
  {   1, "messageClassExtension" },
  { 0, NULL }
};

static const per_choice_t UL_CCCH_MessageType_choice[] = {
  {   0, &hf_lte_rrc_c1_05       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_05 },
  {   1, &hf_lte_rrc_messageClassExtension_05, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_messageClassExtension_05 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_UL_CCCH_MessageType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_UL_CCCH_MessageType, UL_CCCH_MessageType_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t UL_CCCH_Message_sequence[] = {
  { &hf_lte_rrc_message_06  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_UL_CCCH_MessageType },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_UL_CCCH_Message(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_UL_CCCH_Message, UL_CCCH_Message_sequence);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_02_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_02(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_02, T_nonCriticalExtension_02_sequence);

  return offset;
}


static const per_sequence_t CSFBParametersRequestCDMA2000_r8_IEs_sequence[] = {
  { &hf_lte_rrc_nonCriticalExtension_02, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_02 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CSFBParametersRequestCDMA2000_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CSFBParametersRequestCDMA2000_r8_IEs, CSFBParametersRequestCDMA2000_r8_IEs_sequence);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_02_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_02(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_02, T_criticalExtensionsFuture_02_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_02_vals[] = {
  {   0, "csfbParametersRequestCDMA2000-r8" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_02_choice[] = {
  {   0, &hf_lte_rrc_csfbParametersRequestCDMA2000_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_CSFBParametersRequestCDMA2000_r8_IEs },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_02, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_02 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_02(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_02, T_criticalExtensions_02_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t CSFBParametersRequestCDMA2000_sequence[] = {
  { &hf_lte_rrc_criticalExtensions_02, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_02 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CSFBParametersRequestCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:CSFBParametersRequestCDMA2000 ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CSFBParametersRequestCDMA2000, CSFBParametersRequestCDMA2000_sequence);

  return offset;
}


static const per_sequence_t T_measResultServCell_sequence[] = {
  { &hf_lte_rrc_rsrpResult  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RSRP_Range },
  { &hf_lte_rrc_rsrqResult  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RSRQ_Range },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_measResultServCell(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_measResultServCell, T_measResultServCell_sequence);

  return offset;
}


static const per_sequence_t CellGlobalIdEUTRA_sequence[] = {
  { &hf_lte_rrc_plmn_Identity, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PLMN_Identity },
  { &hf_lte_rrc_cellIdentity, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CellIdentity },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CellGlobalIdEUTRA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CellGlobalIdEUTRA, CellGlobalIdEUTRA_sequence);

  return offset;
}


static const per_sequence_t PLMN_IdentityList2_sequence_of[1] = {
  { &hf_lte_rrc_PLMN_IdentityList2_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PLMN_Identity },
};

static int
dissect_lte_rrc_PLMN_IdentityList2(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_PLMN_IdentityList2, PLMN_IdentityList2_sequence_of,
                                                  1, 5, FALSE);

  return offset;
}


static const per_sequence_t T_cgi_Info_sequence[] = {
  { &hf_lte_rrc_cellGlobalId, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CellGlobalIdEUTRA },
  { &hf_lte_rrc_trackingAreaCode, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_TrackingAreaCode },
  { &hf_lte_rrc_plmn_IdentityList_01, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_PLMN_IdentityList2 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_cgi_Info(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_cgi_Info, T_cgi_Info_sequence);

  return offset;
}


static const value_string lte_rrc_T_csg_MemberStatus_r9_vals[] = {
  {   0, "member" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_csg_MemberStatus_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t AdditionalSI_Info_r9_sequence[] = {
  { &hf_lte_rrc_csg_MemberStatus_r9, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_csg_MemberStatus_r9 },
  { &hf_lte_rrc_csg_Identity_r9, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_CSG_Identity },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_AdditionalSI_Info_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_AdditionalSI_Info_r9, AdditionalSI_Info_r9_sequence);

  return offset;
}


static const per_sequence_t T_measResult_sequence[] = {
  { &hf_lte_rrc_rsrpResult  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_RSRP_Range },
  { &hf_lte_rrc_rsrqResult  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_RSRQ_Range },
  { &hf_lte_rrc_additionalSI_Info_r9, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_AdditionalSI_Info_r9 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_measResult(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_measResult, T_measResult_sequence);

  return offset;
}


static const per_sequence_t MeasResultEUTRA_sequence[] = {
  { &hf_lte_rrc_physCellId_01, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhysCellId },
  { &hf_lte_rrc_cgi_Info    , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_cgi_Info },
  { &hf_lte_rrc_measResult  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_measResult },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MeasResultEUTRA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MeasResultEUTRA, MeasResultEUTRA_sequence);

  return offset;
}


static const per_sequence_t MeasResultListEUTRA_sequence_of[1] = {
  { &hf_lte_rrc_MeasResultListEUTRA_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MeasResultEUTRA },
};

static int
dissect_lte_rrc_MeasResultListEUTRA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_MeasResultListEUTRA, MeasResultListEUTRA_sequence_of,
                                                  1, maxCellReport, FALSE);

  return offset;
}


static const value_string lte_rrc_T_physCellId_vals[] = {
  {   0, "fdd" },
  {   1, "tdd" },
  { 0, NULL }
};

static const per_choice_t T_physCellId_choice[] = {
  {   0, &hf_lte_rrc_fdd         , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_PhysCellIdUTRA_FDD },
  {   1, &hf_lte_rrc_tdd         , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_PhysCellIdUTRA_TDD },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_physCellId(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_physCellId, T_physCellId_choice,
                                 NULL);

  return offset;
}



static int
dissect_lte_rrc_BIT_STRING_SIZE_28(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     28, 28, FALSE, NULL);

  return offset;
}


static const per_sequence_t CellGlobalIdUTRA_sequence[] = {
  { &hf_lte_rrc_plmn_Identity, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PLMN_Identity },
  { &hf_lte_rrc_cellIdentity_01, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_28 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CellGlobalIdUTRA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CellGlobalIdUTRA, CellGlobalIdUTRA_sequence);

  return offset;
}


static const per_sequence_t T_cgi_Info_01_sequence[] = {
  { &hf_lte_rrc_cellGlobalId_01, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CellGlobalIdUTRA },
  { &hf_lte_rrc_locationAreaCode, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_BIT_STRING_SIZE_16 },
  { &hf_lte_rrc_routingAreaCode, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_BIT_STRING_SIZE_8 },
  { &hf_lte_rrc_plmn_IdentityList_01, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_PLMN_IdentityList2 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_cgi_Info_01(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_cgi_Info_01, T_cgi_Info_01_sequence);

  return offset;
}


static const per_sequence_t T_measResult_01_sequence[] = {
  { &hf_lte_rrc_utra_RSCP   , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_INTEGER_M5_91 },
  { &hf_lte_rrc_utra_EcN0   , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_INTEGER_0_49 },
  { &hf_lte_rrc_additionalSI_Info_r9, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_AdditionalSI_Info_r9 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_measResult_01(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_measResult_01, T_measResult_01_sequence);

  return offset;
}


static const per_sequence_t MeasResultUTRA_sequence[] = {
  { &hf_lte_rrc_physCellId_05, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_physCellId },
  { &hf_lte_rrc_cgi_Info_01 , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_cgi_Info_01 },
  { &hf_lte_rrc_measResult_01, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_measResult_01 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MeasResultUTRA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MeasResultUTRA, MeasResultUTRA_sequence);

  return offset;
}


static const per_sequence_t MeasResultListUTRA_sequence_of[1] = {
  { &hf_lte_rrc_MeasResultListUTRA_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MeasResultUTRA },
};

static int
dissect_lte_rrc_MeasResultListUTRA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_MeasResultListUTRA, MeasResultListUTRA_sequence_of,
                                                  1, maxCellReport, FALSE);

  return offset;
}


static const per_sequence_t CellGlobalIdGERAN_sequence[] = {
  { &hf_lte_rrc_plmn_Identity, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PLMN_Identity },
  { &hf_lte_rrc_locationAreaCode, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_16 },
  { &hf_lte_rrc_cellIdentity_02, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_16 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CellGlobalIdGERAN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CellGlobalIdGERAN, CellGlobalIdGERAN_sequence);

  return offset;
}


static const per_sequence_t T_cgi_Info_02_sequence[] = {
  { &hf_lte_rrc_cellGlobalId_02, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CellGlobalIdGERAN },
  { &hf_lte_rrc_routingAreaCode, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_BIT_STRING_SIZE_8 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_cgi_Info_02(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_cgi_Info_02, T_cgi_Info_02_sequence);

  return offset;
}


static const per_sequence_t T_measResult_02_sequence[] = {
  { &hf_lte_rrc_rssi        , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_63 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_measResult_02(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_measResult_02, T_measResult_02_sequence);

  return offset;
}


static const per_sequence_t MeasResultGERAN_sequence[] = {
  { &hf_lte_rrc_carrierFreq , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CarrierFreqGERAN },
  { &hf_lte_rrc_physCellId  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhysCellIdGERAN },
  { &hf_lte_rrc_cgi_Info_02 , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_cgi_Info_02 },
  { &hf_lte_rrc_measResult_02, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_measResult_02 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MeasResultGERAN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MeasResultGERAN, MeasResultGERAN_sequence);

  return offset;
}


static const per_sequence_t MeasResultListGERAN_sequence_of[1] = {
  { &hf_lte_rrc_MeasResultListGERAN_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MeasResultGERAN },
};

static int
dissect_lte_rrc_MeasResultListGERAN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_MeasResultListGERAN, MeasResultListGERAN_sequence_of,
                                                  1, maxCellReport, FALSE);

  return offset;
}



static int
dissect_lte_rrc_BIT_STRING_SIZE_47(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     47, 47, FALSE, NULL);

  return offset;
}



static int
dissect_lte_rrc_BIT_STRING_SIZE_128(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     128, 128, FALSE, NULL);

  return offset;
}


static const value_string lte_rrc_CellGlobalIdCDMA2000_vals[] = {
  {   0, "cellGlobalId1XRTT" },
  {   1, "cellGlobalIdHRPD" },
  { 0, NULL }
};

static const per_choice_t CellGlobalIdCDMA2000_choice[] = {
  {   0, &hf_lte_rrc_cellGlobalId1XRTT, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_BIT_STRING_SIZE_47 },
  {   1, &hf_lte_rrc_cellGlobalIdHRPD, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_BIT_STRING_SIZE_128 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_CellGlobalIdCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_CellGlobalIdCDMA2000, CellGlobalIdCDMA2000_choice,
                                 NULL);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_32767(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 32767U, NULL, FALSE);

  return offset;
}


static const per_sequence_t T_measResult_03_sequence[] = {
  { &hf_lte_rrc_pilotPnPhase, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_INTEGER_0_32767 },
  { &hf_lte_rrc_pilotStrength, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_63 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_measResult_03(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_measResult_03, T_measResult_03_sequence);

  return offset;
}


static const per_sequence_t MeasResultCDMA2000_sequence[] = {
  { &hf_lte_rrc_physCellId_02, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhysCellIdCDMA2000 },
  { &hf_lte_rrc_cgi_Info_03 , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_CellGlobalIdCDMA2000 },
  { &hf_lte_rrc_measResult_03, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_measResult_03 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MeasResultCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MeasResultCDMA2000, MeasResultCDMA2000_sequence);

  return offset;
}


static const per_sequence_t MeasResultListCDMA2000_sequence_of[1] = {
  { &hf_lte_rrc_MeasResultListCDMA2000_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MeasResultCDMA2000 },
};

static int
dissect_lte_rrc_MeasResultListCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_MeasResultListCDMA2000, MeasResultListCDMA2000_sequence_of,
                                                  1, maxCellReport, FALSE);

  return offset;
}


static const per_sequence_t MeasResultsCDMA2000_sequence[] = {
  { &hf_lte_rrc_preRegistrationStatusHRPD, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_measResultListCDMA2000, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MeasResultListCDMA2000 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MeasResultsCDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MeasResultsCDMA2000, MeasResultsCDMA2000_sequence);

  return offset;
}


static const value_string lte_rrc_T_measResultNeighCells_01_vals[] = {
  {   0, "measResultListEUTRA" },
  {   1, "measResultListUTRA" },
  {   2, "measResultListGERAN" },
  {   3, "measResultsCDMA2000" },
  { 0, NULL }
};

static const per_choice_t T_measResultNeighCells_01_choice[] = {
  {   0, &hf_lte_rrc_measResultListEUTRA_01, ASN1_EXTENSION_ROOT    , dissect_lte_rrc_MeasResultListEUTRA },
  {   1, &hf_lte_rrc_measResultListUTRA_01, ASN1_EXTENSION_ROOT    , dissect_lte_rrc_MeasResultListUTRA },
  {   2, &hf_lte_rrc_measResultListGERAN, ASN1_EXTENSION_ROOT    , dissect_lte_rrc_MeasResultListGERAN },
  {   3, &hf_lte_rrc_measResultsCDMA2000_01, ASN1_EXTENSION_ROOT    , dissect_lte_rrc_MeasResultsCDMA2000 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_measResultNeighCells_01(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_measResultNeighCells_01, T_measResultNeighCells_01_choice,
                                 NULL);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_4095(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 4095U, NULL, FALSE);

  return offset;
}


static const per_sequence_t MeasResultForECID_r9_sequence[] = {
  { &hf_lte_rrc_ue_RxTxTimeDiffResult_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_4095 },
  { &hf_lte_rrc_currentSFN_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_10 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MeasResultForECID_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MeasResultForECID_r9, MeasResultForECID_r9_sequence);

  return offset;
}


static const per_sequence_t MeasResults_sequence[] = {
  { &hf_lte_rrc_measId      , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MeasId },
  { &hf_lte_rrc_measResultServCell, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_measResultServCell },
  { &hf_lte_rrc_measResultNeighCells_01, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_T_measResultNeighCells_01 },
  { &hf_lte_rrc_measResultForECID_r9, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_MeasResultForECID_r9 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MeasResults(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MeasResults, MeasResults_sequence);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_07_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_07(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_07, T_nonCriticalExtension_07_sequence);

  return offset;
}


static const per_sequence_t MeasurementReport_r8_IEs_sequence[] = {
  { &hf_lte_rrc_measResults , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MeasResults },
  { &hf_lte_rrc_nonCriticalExtension_09, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_07 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MeasurementReport_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MeasurementReport_r8_IEs, MeasurementReport_r8_IEs_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_10_vals[] = {
  {   0, "measurementReport-r8" },
  {   1, "spare7" },
  {   2, "spare6" },
  {   3, "spare5" },
  {   4, "spare4" },
  {   5, "spare3" },
  {   6, "spare2" },
  {   7, "spare1" },
  { 0, NULL }
};

static const per_choice_t T_c1_10_choice[] = {
  {   0, &hf_lte_rrc_measurementReport_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_MeasurementReport_r8_IEs },
  {   1, &hf_lte_rrc_spare7      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   2, &hf_lte_rrc_spare6      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   3, &hf_lte_rrc_spare5      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   4, &hf_lte_rrc_spare4      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   5, &hf_lte_rrc_spare3      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   6, &hf_lte_rrc_spare2      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   7, &hf_lte_rrc_spare1      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_10(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_10, T_c1_10_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_06_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_06(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_06, T_criticalExtensionsFuture_06_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_06_vals[] = {
  {   0, "c1" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_06_choice[] = {
  {   0, &hf_lte_rrc_c1_10       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_10 },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_06, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_06 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_06(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_06, T_criticalExtensions_06_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t MeasurementReport_sequence[] = {
  { &hf_lte_rrc_criticalExtensions_06, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_06 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MeasurementReport(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:MeasurementReport ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MeasurementReport, MeasurementReport_sequence);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_13_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_13(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_13, T_nonCriticalExtension_13_sequence);

  return offset;
}


static const per_sequence_t RRCConnectionReconfigurationComplete_r8_IEs_sequence[] = {
  { &hf_lte_rrc_nonCriticalExtension_19, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_13 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionReconfigurationComplete_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionReconfigurationComplete_r8_IEs, RRCConnectionReconfigurationComplete_r8_IEs_sequence);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_10_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_10(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_10, T_criticalExtensionsFuture_10_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_10_vals[] = {
  {   0, "rrcConnectionReconfigurationComplete-r8" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_10_choice[] = {
  {   0, &hf_lte_rrc_rrcConnectionReconfigurationComplete_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_RRCConnectionReconfigurationComplete_r8_IEs },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_10, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_10 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_10(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_10, T_criticalExtensions_10_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t RRCConnectionReconfigurationComplete_sequence[] = {
  { &hf_lte_rrc_rrc_TransactionIdentifier, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RRC_TransactionIdentifier },
  { &hf_lte_rrc_criticalExtensions_10, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_10 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionReconfigurationComplete(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:RRCConnectionReconfigurationComplete ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionReconfigurationComplete, RRCConnectionReconfigurationComplete_sequence);

  return offset;
}


static const value_string lte_rrc_T_rlf_InfoAvailable_r9_vals[] = {
  {   0, "true" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_rlf_InfoAvailable_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_15_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_15(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_15, T_nonCriticalExtension_15_sequence);

  return offset;
}


static const per_sequence_t RRCConnectionReestablishmentComplete_v920_IEs_sequence[] = {
  { &hf_lte_rrc_rlf_InfoAvailable_r9, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_rlf_InfoAvailable_r9 },
  { &hf_lte_rrc_nonCriticalExtension_22, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_15 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionReestablishmentComplete_v920_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionReestablishmentComplete_v920_IEs, RRCConnectionReestablishmentComplete_v920_IEs_sequence);

  return offset;
}


static const per_sequence_t RRCConnectionReestablishmentComplete_r8_IEs_sequence[] = {
  { &hf_lte_rrc_nonCriticalExtension_21, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_RRCConnectionReestablishmentComplete_v920_IEs },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionReestablishmentComplete_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionReestablishmentComplete_r8_IEs, RRCConnectionReestablishmentComplete_r8_IEs_sequence);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_12_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_12(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_12, T_criticalExtensionsFuture_12_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_12_vals[] = {
  {   0, "rrcConnectionReestablishmentComplete-r8" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_12_choice[] = {
  {   0, &hf_lte_rrc_rrcConnectionReestablishmentComplete_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_RRCConnectionReestablishmentComplete_r8_IEs },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_12, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_12 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_12(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_12, T_criticalExtensions_12_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t RRCConnectionReestablishmentComplete_sequence[] = {
  { &hf_lte_rrc_rrc_TransactionIdentifier, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RRC_TransactionIdentifier },
  { &hf_lte_rrc_criticalExtensions_12, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_12 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionReestablishmentComplete(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:RRCConnectionReestablishmentComplete ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionReestablishmentComplete, RRCConnectionReestablishmentComplete_sequence);

  return offset;
}


static const per_sequence_t RegisteredMME_sequence[] = {
  { &hf_lte_rrc_plmn_Identity, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_PLMN_Identity },
  { &hf_lte_rrc_mmegi       , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BIT_STRING_SIZE_16 },
  { &hf_lte_rrc_mmec        , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MMEC },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RegisteredMME(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RegisteredMME, RegisteredMME_sequence);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_20_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_20(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_20, T_nonCriticalExtension_20_sequence);

  return offset;
}


static const per_sequence_t RRCConnectionSetupComplete_r8_IEs_sequence[] = {
  { &hf_lte_rrc_selectedPLMN_Identity, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_1_6 },
  { &hf_lte_rrc_registeredMME, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_RegisteredMME },
  { &hf_lte_rrc_dedicatedInfoNAS, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_DedicatedInfoNAS },
  { &hf_lte_rrc_nonCriticalExtension_29, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_20 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionSetupComplete_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionSetupComplete_r8_IEs, RRCConnectionSetupComplete_r8_IEs_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_18_vals[] = {
  {   0, "rrcConnectionSetupComplete-r8" },
  {   1, "spare3" },
  {   2, "spare2" },
  {   3, "spare1" },
  { 0, NULL }
};

static const per_choice_t T_c1_18_choice[] = {
  {   0, &hf_lte_rrc_rrcConnectionSetupComplete_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_RRCConnectionSetupComplete_r8_IEs },
  {   1, &hf_lte_rrc_spare3      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   2, &hf_lte_rrc_spare2      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   3, &hf_lte_rrc_spare1      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_18(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_18, T_c1_18_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_19_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_19(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_19, T_criticalExtensionsFuture_19_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_19_vals[] = {
  {   0, "c1" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_19_choice[] = {
  {   0, &hf_lte_rrc_c1_18       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_18 },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_19, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_19 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_19(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_19, T_criticalExtensions_19_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t RRCConnectionSetupComplete_sequence[] = {
  { &hf_lte_rrc_rrc_TransactionIdentifier, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RRC_TransactionIdentifier },
  { &hf_lte_rrc_criticalExtensions_19, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_19 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRCConnectionSetupComplete(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:RRCConnectionSetupComplete ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRCConnectionSetupComplete, RRCConnectionSetupComplete_sequence);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_22_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_22(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_22, T_nonCriticalExtension_22_sequence);

  return offset;
}


static const per_sequence_t SecurityModeComplete_r8_IEs_sequence[] = {
  { &hf_lte_rrc_nonCriticalExtension_31, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_22 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SecurityModeComplete_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SecurityModeComplete_r8_IEs, SecurityModeComplete_r8_IEs_sequence);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_21_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_21(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_21, T_criticalExtensionsFuture_21_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_21_vals[] = {
  {   0, "securityModeComplete-r8" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_21_choice[] = {
  {   0, &hf_lte_rrc_securityModeComplete_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_SecurityModeComplete_r8_IEs },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_21, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_21 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_21(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_21, T_criticalExtensions_21_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t SecurityModeComplete_sequence[] = {
  { &hf_lte_rrc_rrc_TransactionIdentifier, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RRC_TransactionIdentifier },
  { &hf_lte_rrc_criticalExtensions_21, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_21 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SecurityModeComplete(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:SecurityModeComplete ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SecurityModeComplete, SecurityModeComplete_sequence);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_23_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_23(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_23, T_nonCriticalExtension_23_sequence);

  return offset;
}


static const per_sequence_t SecurityModeFailure_r8_IEs_sequence[] = {
  { &hf_lte_rrc_nonCriticalExtension_32, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_23 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SecurityModeFailure_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SecurityModeFailure_r8_IEs, SecurityModeFailure_r8_IEs_sequence);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_22_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_22(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_22, T_criticalExtensionsFuture_22_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_22_vals[] = {
  {   0, "securityModeFailure-r8" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_22_choice[] = {
  {   0, &hf_lte_rrc_securityModeFailure_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_SecurityModeFailure_r8_IEs },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_22, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_22 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_22(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_22, T_criticalExtensions_22_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t SecurityModeFailure_sequence[] = {
  { &hf_lte_rrc_rrc_TransactionIdentifier, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RRC_TransactionIdentifier },
  { &hf_lte_rrc_criticalExtensions_22, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_22 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SecurityModeFailure(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:SecurityModeFailure ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SecurityModeFailure, SecurityModeFailure_sequence);

  return offset;
}



static int
dissect_lte_rrc_T_ueCapabilityRAT_Container(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  tvbuff_t *ue_eutra_cap_tvb=NULL;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &ue_eutra_cap_tvb);


if(ue_eutra_cap_tvb){
	switch(lte_rrc_rat_type_value){
	case 0:
		/* eutra */
		dissect_UE_EUTRA_Capability_PDU(ue_eutra_cap_tvb,actx->pinfo, tree);
		break;
	case 1:
		/* utra */
		dissect_rrc_InterRATHandoverInfo_PDU(ue_eutra_cap_tvb, actx->pinfo, tree);
		break;
	case 2:
		/* geran-cs */
		de_ms_cm_2(ue_eutra_cap_tvb, tree, 0, 5, NULL, 0);
		de_ms_cm_3(ue_eutra_cap_tvb, tree, 5, tvb_length(ue_eutra_cap_tvb)-5, NULL, 0);
		break;
	case 3:
		/* geran-ps */
		de_gmm_ms_radio_acc_cap(ue_eutra_cap_tvb, tree, 0, tvb_length(ue_eutra_cap_tvb), NULL, 0);
		break;
	case 4:
		/* cdma2000-1XRTT */
		/* dissection of "A21 Mobile Subscription Information" could be added to packet-ansi_a.c */
		break;
	default:
		break;
	}

}


  return offset;
}


static const per_sequence_t UE_CapabilityRAT_Container_sequence[] = {
  { &hf_lte_rrc_rat_Type    , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RAT_Type },
  { &hf_lte_rrc_ueCapabilityRAT_Container, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_ueCapabilityRAT_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_UE_CapabilityRAT_Container(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  lte_rrc_rat_type_value = -1;
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_UE_CapabilityRAT_Container, UE_CapabilityRAT_Container_sequence);



  return offset;
}


static const per_sequence_t UE_CapabilityRAT_ContainerList_sequence_of[1] = {
  { &hf_lte_rrc_UE_CapabilityRAT_ContainerList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_UE_CapabilityRAT_Container },
};

static int
dissect_lte_rrc_UE_CapabilityRAT_ContainerList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_UE_CapabilityRAT_ContainerList, UE_CapabilityRAT_ContainerList_sequence_of,
                                                  0, maxRAT_Capabilities, FALSE);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_27_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_27(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_27, T_nonCriticalExtension_27_sequence);

  return offset;
}


static const per_sequence_t UECapabilityInformation_r8_IEs_sequence[] = {
  { &hf_lte_rrc_ue_CapabilityRAT_ContainerList, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_UE_CapabilityRAT_ContainerList },
  { &hf_lte_rrc_nonCriticalExtension_38, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_27 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_UECapabilityInformation_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_UECapabilityInformation_r8_IEs, UECapabilityInformation_r8_IEs_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_21_vals[] = {
  {   0, "ueCapabilityInformation-r8" },
  {   1, "spare7" },
  {   2, "spare6" },
  {   3, "spare5" },
  {   4, "spare4" },
  {   5, "spare3" },
  {   6, "spare2" },
  {   7, "spare1" },
  { 0, NULL }
};

static const per_choice_t T_c1_21_choice[] = {
  {   0, &hf_lte_rrc_ueCapabilityInformation_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_UECapabilityInformation_r8_IEs },
  {   1, &hf_lte_rrc_spare7      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   2, &hf_lte_rrc_spare6      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   3, &hf_lte_rrc_spare5      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   4, &hf_lte_rrc_spare4      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   5, &hf_lte_rrc_spare3      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   6, &hf_lte_rrc_spare2      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   7, &hf_lte_rrc_spare1      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_21(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_21, T_c1_21_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_25_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_25(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_25, T_criticalExtensionsFuture_25_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_25_vals[] = {
  {   0, "c1" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_25_choice[] = {
  {   0, &hf_lte_rrc_c1_21       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_21 },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_25, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_25 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_25(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_25, T_criticalExtensions_25_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t UECapabilityInformation_sequence[] = {
  { &hf_lte_rrc_rrc_TransactionIdentifier, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RRC_TransactionIdentifier },
  { &hf_lte_rrc_criticalExtensions_25, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_25 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_UECapabilityInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:UECapabilityInformation ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_UECapabilityInformation, UECapabilityInformation_sequence);

  return offset;
}



static int
dissect_lte_rrc_BIT_STRING_SIZE_56(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     56, 56, FALSE, NULL);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_30_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_30(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_30, T_nonCriticalExtension_30_sequence);

  return offset;
}


static const per_sequence_t ULHandoverPreparationTransfer_r8_IEs_sequence[] = {
  { &hf_lte_rrc_cdma2000_Type, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CDMA2000_Type },
  { &hf_lte_rrc_meid        , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_BIT_STRING_SIZE_56 },
  { &hf_lte_rrc_dedicatedInfo, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_DedicatedInfoCDMA2000 },
  { &hf_lte_rrc_nonCriticalExtension_41, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_30 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_ULHandoverPreparationTransfer_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_ULHandoverPreparationTransfer_r8_IEs, ULHandoverPreparationTransfer_r8_IEs_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_24_vals[] = {
  {   0, "ulHandoverPreparationTransfer-r8" },
  {   1, "spare3" },
  {   2, "spare2" },
  {   3, "spare1" },
  { 0, NULL }
};

static const per_choice_t T_c1_24_choice[] = {
  {   0, &hf_lte_rrc_ulHandoverPreparationTransfer_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_ULHandoverPreparationTransfer_r8_IEs },
  {   1, &hf_lte_rrc_spare3      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   2, &hf_lte_rrc_spare2      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   3, &hf_lte_rrc_spare1      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_24(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_24, T_c1_24_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_28_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_28(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_28, T_criticalExtensionsFuture_28_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_28_vals[] = {
  {   0, "c1" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_28_choice[] = {
  {   0, &hf_lte_rrc_c1_24       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_24 },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_28, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_28 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_28(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_28, T_criticalExtensions_28_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t ULHandoverPreparationTransfer_sequence[] = {
  { &hf_lte_rrc_criticalExtensions_28, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_28 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_ULHandoverPreparationTransfer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:ULHandoverPreparationTransfer ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_ULHandoverPreparationTransfer, ULHandoverPreparationTransfer_sequence);

  return offset;
}


static const value_string lte_rrc_T_dedicatedInfoType_01_vals[] = {
  {   0, "dedicatedInfoNAS" },
  {   1, "dedicatedInfoCDMA2000-1XRTT" },
  {   2, "dedicatedInfoCDMA2000-HRPD" },
  { 0, NULL }
};

static const per_choice_t T_dedicatedInfoType_01_choice[] = {
  {   0, &hf_lte_rrc_dedicatedInfoNAS, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_DedicatedInfoNAS },
  {   1, &hf_lte_rrc_dedicatedInfoCDMA2000_1XRTT, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_DedicatedInfoCDMA2000 },
  {   2, &hf_lte_rrc_dedicatedInfoCDMA2000_HRPD, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_DedicatedInfoCDMA2000 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_dedicatedInfoType_01(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_dedicatedInfoType_01, T_dedicatedInfoType_01_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_31_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_31(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_31, T_nonCriticalExtension_31_sequence);

  return offset;
}


static const per_sequence_t ULInformationTransfer_r8_IEs_sequence[] = {
  { &hf_lte_rrc_dedicatedInfoType_01, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_dedicatedInfoType_01 },
  { &hf_lte_rrc_nonCriticalExtension_42, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_31 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_ULInformationTransfer_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_ULInformationTransfer_r8_IEs, ULInformationTransfer_r8_IEs_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_25_vals[] = {
  {   0, "ulInformationTransfer-r8" },
  {   1, "spare3" },
  {   2, "spare2" },
  {   3, "spare1" },
  { 0, NULL }
};

static const per_choice_t T_c1_25_choice[] = {
  {   0, &hf_lte_rrc_ulInformationTransfer_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_ULInformationTransfer_r8_IEs },
  {   1, &hf_lte_rrc_spare3      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   2, &hf_lte_rrc_spare2      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   3, &hf_lte_rrc_spare1      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_25(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_25, T_c1_25_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_29_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_29(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_29, T_criticalExtensionsFuture_29_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_29_vals[] = {
  {   0, "c1" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_29_choice[] = {
  {   0, &hf_lte_rrc_c1_25       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_25 },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_29, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_29 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_29(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_29, T_criticalExtensions_29_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t ULInformationTransfer_sequence[] = {
  { &hf_lte_rrc_criticalExtensions_29, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_29 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_ULInformationTransfer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:ULInformationTransfer ");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_ULInformationTransfer, ULInformationTransfer_sequence);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_0_4294967295(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 4294967295U, NULL, FALSE);

  return offset;
}


static const per_sequence_t DRB_CountInfo_sequence[] = {
  { &hf_lte_rrc_drb_Identity, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_DRB_Identity },
  { &hf_lte_rrc_count_Uplink, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_4294967295 },
  { &hf_lte_rrc_count_Downlink, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_0_4294967295 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_DRB_CountInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_DRB_CountInfo, DRB_CountInfo_sequence);

  return offset;
}


static const per_sequence_t DRB_CountInfoList_sequence_of[1] = {
  { &hf_lte_rrc_DRB_CountInfoList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_DRB_CountInfo },
};

static int
dissect_lte_rrc_DRB_CountInfoList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_DRB_CountInfoList, DRB_CountInfoList_sequence_of,
                                                  0, maxDRB, FALSE);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_01_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_01(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_01, T_nonCriticalExtension_01_sequence);

  return offset;
}


static const per_sequence_t CounterCheckResponse_r8_IEs_sequence[] = {
  { &hf_lte_rrc_drb_CountInfoList, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_DRB_CountInfoList },
  { &hf_lte_rrc_nonCriticalExtension_01, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_01 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CounterCheckResponse_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CounterCheckResponse_r8_IEs, CounterCheckResponse_r8_IEs_sequence);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_01_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_01(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_01, T_criticalExtensionsFuture_01_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_01_vals[] = {
  {   0, "counterCheckResponse-r8" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_01_choice[] = {
  {   0, &hf_lte_rrc_counterCheckResponse_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_CounterCheckResponse_r8_IEs },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_01, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_01 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_01(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_01, T_criticalExtensions_01_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t CounterCheckResponse_sequence[] = {
  { &hf_lte_rrc_rrc_TransactionIdentifier, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RRC_TransactionIdentifier },
  { &hf_lte_rrc_criticalExtensions_01, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_01 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CounterCheckResponse(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {

/* MQ */
col_append_str(actx->pinfo->cinfo, COL_INFO, "RRC:CounterCheckResponse ");
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CounterCheckResponse, CounterCheckResponse_sequence);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_1_200(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, 200U, NULL, FALSE);

  return offset;
}


static const per_sequence_t T_rach_Report_r9_sequence[] = {
  { &hf_lte_rrc_numberOfPreamblesSent_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_1_200 },
  { &hf_lte_rrc_contentionDetected_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_rach_Report_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_rach_Report_r9, T_rach_Report_r9_sequence);

  return offset;
}


static const per_sequence_t T_measResultLastServCell_sequence[] = {
  { &hf_lte_rrc_rsrpResult  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RSRP_Range },
  { &hf_lte_rrc_rsrqResult  , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_RSRQ_Range },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_measResultLastServCell(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_measResultLastServCell, T_measResultLastServCell_sequence);

  return offset;
}


static const per_sequence_t MeasResultList2EUTRA_item_sequence[] = {
  { &hf_lte_rrc_carrierFreq_01, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ARFCN_ValueEUTRA },
  { &hf_lte_rrc_measResultList, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MeasResultListEUTRA },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MeasResultList2EUTRA_item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MeasResultList2EUTRA_item, MeasResultList2EUTRA_item_sequence);

  return offset;
}


static const per_sequence_t MeasResultList2EUTRA_sequence_of[1] = {
  { &hf_lte_rrc_MeasResultList2EUTRA_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MeasResultList2EUTRA_item },
};

static int
dissect_lte_rrc_MeasResultList2EUTRA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_MeasResultList2EUTRA, MeasResultList2EUTRA_sequence_of,
                                                  1, maxFreq, FALSE);

  return offset;
}


static const per_sequence_t MeasResultList2UTRA_item_sequence[] = {
  { &hf_lte_rrc_carrierFreq_02, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ARFCN_ValueUTRA },
  { &hf_lte_rrc_measResultList_01, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MeasResultListUTRA },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MeasResultList2UTRA_item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MeasResultList2UTRA_item, MeasResultList2UTRA_item_sequence);

  return offset;
}


static const per_sequence_t MeasResultList2UTRA_sequence_of[1] = {
  { &hf_lte_rrc_MeasResultList2UTRA_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MeasResultList2UTRA_item },
};

static int
dissect_lte_rrc_MeasResultList2UTRA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_MeasResultList2UTRA, MeasResultList2UTRA_sequence_of,
                                                  1, maxCellReport, FALSE);

  return offset;
}


static const per_sequence_t MeasResultList2CDMA2000_item_sequence[] = {
  { &hf_lte_rrc_carrierFreq_03, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CarrierFreqCDMA2000 },
  { &hf_lte_rrc_measResultList_02, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MeasResultsCDMA2000 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MeasResultList2CDMA2000_item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MeasResultList2CDMA2000_item, MeasResultList2CDMA2000_item_sequence);

  return offset;
}


static const per_sequence_t MeasResultList2CDMA2000_sequence_of[1] = {
  { &hf_lte_rrc_MeasResultList2CDMA2000_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MeasResultList2CDMA2000_item },
};

static int
dissect_lte_rrc_MeasResultList2CDMA2000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_MeasResultList2CDMA2000, MeasResultList2CDMA2000_sequence_of,
                                                  1, maxCellReport, FALSE);

  return offset;
}


static const per_sequence_t T_measResultNeighCells_sequence[] = {
  { &hf_lte_rrc_measResultListEUTRA, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_MeasResultList2EUTRA },
  { &hf_lte_rrc_measResultListUTRA, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_MeasResultList2UTRA },
  { &hf_lte_rrc_measResultListGERAN, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_MeasResultListGERAN },
  { &hf_lte_rrc_measResultsCDMA2000, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_MeasResultList2CDMA2000 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_measResultNeighCells(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_measResultNeighCells, T_measResultNeighCells_sequence);

  return offset;
}


static const per_sequence_t RLF_Report_r9_sequence[] = {
  { &hf_lte_rrc_measResultLastServCell, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_measResultLastServCell },
  { &hf_lte_rrc_measResultNeighCells, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_T_measResultNeighCells },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RLF_Report_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RLF_Report_r9, RLF_Report_r9_sequence);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_29_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_29(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_29, T_nonCriticalExtension_29_sequence);

  return offset;
}


static const per_sequence_t UEInformationResponse_r9_IEs_sequence[] = {
  { &hf_lte_rrc_rach_Report_r9, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_rach_Report_r9 },
  { &hf_lte_rrc_rlfReport_r9, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_RLF_Report_r9 },
  { &hf_lte_rrc_nonCriticalExtension_40, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_29 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_UEInformationResponse_r9_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_UEInformationResponse_r9_IEs, UEInformationResponse_r9_IEs_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_23_vals[] = {
  {   0, "ueInformationResponse-r9" },
  {   1, "spare3" },
  {   2, "spare2" },
  {   3, "spare1" },
  { 0, NULL }
};

static const per_choice_t T_c1_23_choice[] = {
  {   0, &hf_lte_rrc_ueInformationResponse_r9_01, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_UEInformationResponse_r9_IEs },
  {   1, &hf_lte_rrc_spare3      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   2, &hf_lte_rrc_spare2      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   3, &hf_lte_rrc_spare1      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_23(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_23, T_c1_23_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_27_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_27(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_27, T_criticalExtensionsFuture_27_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_27_vals[] = {
  {   0, "c1" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_27_choice[] = {
  {   0, &hf_lte_rrc_c1_23       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_23 },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_27, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_27 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_27(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_27, T_criticalExtensions_27_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t UEInformationResponse_r9_sequence[] = {
  { &hf_lte_rrc_rrc_TransactionIdentifier, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RRC_TransactionIdentifier },
  { &hf_lte_rrc_criticalExtensions_27, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_27 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_UEInformationResponse_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_UEInformationResponse_r9, UEInformationResponse_r9_sequence);

  return offset;
}


static const value_string lte_rrc_T_type_r9_vals[] = {
  {   0, "entering" },
  {   1, "leaving" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_type_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_carrierFreq_r9_vals[] = {
  {   0, "eutra-r9" },
  {   1, "utra-r9" },
  { 0, NULL }
};

static const per_choice_t T_carrierFreq_r9_choice[] = {
  {   0, &hf_lte_rrc_eutra_r9    , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_ARFCN_ValueEUTRA },
  {   1, &hf_lte_rrc_utra_r9     , ASN1_EXTENSION_ROOT    , dissect_lte_rrc_ARFCN_ValueUTRA },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_carrierFreq_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_carrierFreq_r9, T_carrierFreq_r9_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_11_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_11(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_11, T_nonCriticalExtension_11_sequence);

  return offset;
}


static const per_sequence_t ProximityIndication_r9_IEs_sequence[] = {
  { &hf_lte_rrc_type_r9     , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_type_r9 },
  { &hf_lte_rrc_carrierFreq_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_carrierFreq_r9 },
  { &hf_lte_rrc_nonCriticalExtension_15, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_11 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_ProximityIndication_r9_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_ProximityIndication_r9_IEs, ProximityIndication_r9_IEs_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_12_vals[] = {
  {   0, "proximityIndication-r9" },
  {   1, "spare3" },
  {   2, "spare2" },
  {   3, "spare1" },
  { 0, NULL }
};

static const per_choice_t T_c1_12_choice[] = {
  {   0, &hf_lte_rrc_proximityIndication_r9_01, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_ProximityIndication_r9_IEs },
  {   1, &hf_lte_rrc_spare3      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   2, &hf_lte_rrc_spare2      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   3, &hf_lte_rrc_spare1      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_12(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_12, T_c1_12_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_08_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_08(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_08, T_criticalExtensionsFuture_08_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_08_vals[] = {
  {   0, "c1" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_08_choice[] = {
  {   0, &hf_lte_rrc_c1_12       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_12 },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_08, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_08 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_08(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_08, T_criticalExtensions_08_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t ProximityIndication_r9_sequence[] = {
  { &hf_lte_rrc_criticalExtensions_08, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_08 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_ProximityIndication_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_ProximityIndication_r9, ProximityIndication_r9_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_06_vals[] = {
  {   0, "csfbParametersRequestCDMA2000" },
  {   1, "measurementReport" },
  {   2, "rrcConnectionReconfigurationComplete" },
  {   3, "rrcConnectionReestablishmentComplete" },
  {   4, "rrcConnectionSetupComplete" },
  {   5, "securityModeComplete" },
  {   6, "securityModeFailure" },
  {   7, "ueCapabilityInformation" },
  {   8, "ulHandoverPreparationTransfer" },
  {   9, "ulInformationTransfer" },
  {  10, "counterCheckResponse" },
  {  11, "ueInformationResponse-r9" },
  {  12, "proximityIndication-r9" },
  {  13, "spare3" },
  {  14, "spare2" },
  {  15, "spare1" },
  { 0, NULL }
};

static const per_choice_t T_c1_06_choice[] = {
  {   0, &hf_lte_rrc_csfbParametersRequestCDMA2000, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_CSFBParametersRequestCDMA2000 },
  {   1, &hf_lte_rrc_measurementReport, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_MeasurementReport },
  {   2, &hf_lte_rrc_rrcConnectionReconfigurationComplete, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_RRCConnectionReconfigurationComplete },
  {   3, &hf_lte_rrc_rrcConnectionReestablishmentComplete, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_RRCConnectionReestablishmentComplete },
  {   4, &hf_lte_rrc_rrcConnectionSetupComplete, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_RRCConnectionSetupComplete },
  {   5, &hf_lte_rrc_securityModeComplete, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_SecurityModeComplete },
  {   6, &hf_lte_rrc_securityModeFailure, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_SecurityModeFailure },
  {   7, &hf_lte_rrc_ueCapabilityInformation, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_UECapabilityInformation },
  {   8, &hf_lte_rrc_ulHandoverPreparationTransfer, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_ULHandoverPreparationTransfer },
  {   9, &hf_lte_rrc_ulInformationTransfer, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_ULInformationTransfer },
  {  10, &hf_lte_rrc_counterCheckResponse, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_CounterCheckResponse },
  {  11, &hf_lte_rrc_ueInformationResponse_r9, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_UEInformationResponse_r9 },
  {  12, &hf_lte_rrc_proximityIndication_r9, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_ProximityIndication_r9 },
  {  13, &hf_lte_rrc_spare3      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {  14, &hf_lte_rrc_spare2      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {  15, &hf_lte_rrc_spare1      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_06(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_06, T_c1_06_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_messageClassExtension_06_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_messageClassExtension_06(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_messageClassExtension_06, T_messageClassExtension_06_sequence);

  return offset;
}


static const value_string lte_rrc_UL_DCCH_MessageType_vals[] = {
  {   0, "c1" },
  {   1, "messageClassExtension" },
  { 0, NULL }
};

static const per_choice_t UL_DCCH_MessageType_choice[] = {
  {   0, &hf_lte_rrc_c1_06       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_06 },
  {   1, &hf_lte_rrc_messageClassExtension_06, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_messageClassExtension_06 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_UL_DCCH_MessageType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_UL_DCCH_MessageType, UL_DCCH_MessageType_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t UL_DCCH_Message_sequence[] = {
  { &hf_lte_rrc_message_07  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_UL_DCCH_MessageType },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_UL_DCCH_Message(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  actx->pinfo->link_dir = P2P_DIR_UL;

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_UL_DCCH_Message, UL_DCCH_Message_sequence);

  return offset;
}


static const value_string lte_rrc_AccessStratumRelease_vals[] = {
  {   0, "rel8" },
  {   1, "rel9" },
  {   2, "spare6" },
  {   3, "spare5" },
  {   4, "spare4" },
  {   5, "spare3" },
  {   6, "spare2" },
  {   7, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_AccessStratumRelease(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, TRUE, 0, NULL);

  return offset;
}



static int
dissect_lte_rrc_INTEGER_1_5(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, 5U, NULL, FALSE);

  return offset;
}


static const per_sequence_t T_supportedROHC_Profiles_sequence[] = {
  { &hf_lte_rrc_profile0x0001, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_profile0x0002, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_profile0x0003, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_profile0x0004, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_profile0x0006, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_profile0x0101, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_profile0x0102, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_profile0x0103, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_profile0x0104, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_supportedROHC_Profiles(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_supportedROHC_Profiles, T_supportedROHC_Profiles_sequence);

  return offset;
}


static const value_string lte_rrc_T_maxNumberROHC_ContextSessions_vals[] = {
  {   0, "cs2" },
  {   1, "cs4" },
  {   2, "cs8" },
  {   3, "cs12" },
  {   4, "cs16" },
  {   5, "cs24" },
  {   6, "cs32" },
  {   7, "cs48" },
  {   8, "cs64" },
  {   9, "cs128" },
  {  10, "cs256" },
  {  11, "cs512" },
  {  12, "cs1024" },
  {  13, "cs16384" },
  {  14, "spare2" },
  {  15, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_maxNumberROHC_ContextSessions(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t PDCP_Parameters_sequence[] = {
  { &hf_lte_rrc_supportedROHC_Profiles, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_supportedROHC_Profiles },
  { &hf_lte_rrc_maxNumberROHC_ContextSessions, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_T_maxNumberROHC_ContextSessions },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_PDCP_Parameters(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_PDCP_Parameters, PDCP_Parameters_sequence);

  return offset;
}


static const per_sequence_t PhyLayerParameters_sequence[] = {
  { &hf_lte_rrc_ue_TxAntennaSelectionSupported, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_ue_SpecificRefSigsSupported, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_PhyLayerParameters(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_PhyLayerParameters, PhyLayerParameters_sequence);

  return offset;
}


static const per_sequence_t SupportedBandEUTRA_sequence[] = {
  { &hf_lte_rrc_bandEUTRA   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_1_64 },
  { &hf_lte_rrc_halfDuplex  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SupportedBandEUTRA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SupportedBandEUTRA, SupportedBandEUTRA_sequence);

  return offset;
}


static const per_sequence_t SupportedBandListEUTRA_sequence_of[1] = {
  { &hf_lte_rrc_SupportedBandListEUTRA_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SupportedBandEUTRA },
};

static int
dissect_lte_rrc_SupportedBandListEUTRA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_SupportedBandListEUTRA, SupportedBandListEUTRA_sequence_of,
                                                  1, maxBands, FALSE);

  return offset;
}


static const per_sequence_t RF_Parameters_sequence[] = {
  { &hf_lte_rrc_supportedBandListEUTRA, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SupportedBandListEUTRA },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RF_Parameters(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RF_Parameters, RF_Parameters_sequence);

  return offset;
}


static const per_sequence_t InterFreqBandInfo_sequence[] = {
  { &hf_lte_rrc_interFreqNeedForGaps, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_InterFreqBandInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_InterFreqBandInfo, InterFreqBandInfo_sequence);

  return offset;
}


static const per_sequence_t InterFreqBandList_sequence_of[1] = {
  { &hf_lte_rrc_InterFreqBandList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_InterFreqBandInfo },
};

static int
dissect_lte_rrc_InterFreqBandList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_InterFreqBandList, InterFreqBandList_sequence_of,
                                                  1, maxBands, FALSE);

  return offset;
}


static const per_sequence_t InterRAT_BandInfo_sequence[] = {
  { &hf_lte_rrc_interRAT_NeedForGaps, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_InterRAT_BandInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_InterRAT_BandInfo, InterRAT_BandInfo_sequence);

  return offset;
}


static const per_sequence_t InterRAT_BandList_sequence_of[1] = {
  { &hf_lte_rrc_InterRAT_BandList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_InterRAT_BandInfo },
};

static int
dissect_lte_rrc_InterRAT_BandList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_InterRAT_BandList, InterRAT_BandList_sequence_of,
                                                  1, maxBands, FALSE);

  return offset;
}


static const per_sequence_t BandInfoEUTRA_sequence[] = {
  { &hf_lte_rrc_interFreqBandList, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_InterFreqBandList },
  { &hf_lte_rrc_interRAT_BandList, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_InterRAT_BandList },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_BandInfoEUTRA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_BandInfoEUTRA, BandInfoEUTRA_sequence);

  return offset;
}


static const per_sequence_t BandListEUTRA_sequence_of[1] = {
  { &hf_lte_rrc_BandListEUTRA_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BandInfoEUTRA },
};

static int
dissect_lte_rrc_BandListEUTRA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_BandListEUTRA, BandListEUTRA_sequence_of,
                                                  1, maxBands, FALSE);

  return offset;
}


static const per_sequence_t MeasParameters_sequence[] = {
  { &hf_lte_rrc_bandListEUTRA, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BandListEUTRA },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_MeasParameters(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_MeasParameters, MeasParameters_sequence);

  return offset;
}


static const value_string lte_rrc_SupportedBandUTRA_FDD_vals[] = {
  {   0, "bandI" },
  {   1, "bandII" },
  {   2, "bandIII" },
  {   3, "bandIV" },
  {   4, "bandV" },
  {   5, "bandVI" },
  {   6, "bandVII" },
  {   7, "bandVIII" },
  {   8, "bandIX" },
  {   9, "bandX" },
  {  10, "bandXI" },
  {  11, "bandXII" },
  {  12, "bandXIII" },
  {  13, "bandXIV" },
  {  14, "bandXV" },
  {  15, "bandXVI" },
  { 0, NULL }
};


static int
dissect_lte_rrc_SupportedBandUTRA_FDD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t SupportedBandListUTRA_FDD_sequence_of[1] = {
  { &hf_lte_rrc_SupportedBandListUTRA_FDD_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SupportedBandUTRA_FDD },
};

static int
dissect_lte_rrc_SupportedBandListUTRA_FDD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_SupportedBandListUTRA_FDD, SupportedBandListUTRA_FDD_sequence_of,
                                                  1, maxBands, FALSE);

  return offset;
}


static const per_sequence_t IRAT_ParametersUTRA_FDD_sequence[] = {
  { &hf_lte_rrc_supportedBandListUTRA_FDD, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SupportedBandListUTRA_FDD },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_IRAT_ParametersUTRA_FDD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_IRAT_ParametersUTRA_FDD, IRAT_ParametersUTRA_FDD_sequence);

  return offset;
}


static const value_string lte_rrc_SupportedBandUTRA_TDD128_vals[] = {
  {   0, "a" },
  {   1, "b" },
  {   2, "c" },
  {   3, "d" },
  {   4, "e" },
  {   5, "f" },
  {   6, "g" },
  {   7, "h" },
  {   8, "i" },
  {   9, "j" },
  {  10, "k" },
  {  11, "l" },
  {  12, "m" },
  {  13, "n" },
  {  14, "o" },
  {  15, "p" },
  { 0, NULL }
};


static int
dissect_lte_rrc_SupportedBandUTRA_TDD128(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t SupportedBandListUTRA_TDD128_sequence_of[1] = {
  { &hf_lte_rrc_SupportedBandListUTRA_TDD128_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SupportedBandUTRA_TDD128 },
};

static int
dissect_lte_rrc_SupportedBandListUTRA_TDD128(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_SupportedBandListUTRA_TDD128, SupportedBandListUTRA_TDD128_sequence_of,
                                                  1, maxBands, FALSE);

  return offset;
}


static const per_sequence_t IRAT_ParametersUTRA_TDD128_sequence[] = {
  { &hf_lte_rrc_supportedBandListUTRA_TDD128, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SupportedBandListUTRA_TDD128 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_IRAT_ParametersUTRA_TDD128(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_IRAT_ParametersUTRA_TDD128, IRAT_ParametersUTRA_TDD128_sequence);

  return offset;
}


static const value_string lte_rrc_SupportedBandUTRA_TDD384_vals[] = {
  {   0, "a" },
  {   1, "b" },
  {   2, "c" },
  {   3, "d" },
  {   4, "e" },
  {   5, "f" },
  {   6, "g" },
  {   7, "h" },
  {   8, "i" },
  {   9, "j" },
  {  10, "k" },
  {  11, "l" },
  {  12, "m" },
  {  13, "n" },
  {  14, "o" },
  {  15, "p" },
  { 0, NULL }
};


static int
dissect_lte_rrc_SupportedBandUTRA_TDD384(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t SupportedBandListUTRA_TDD384_sequence_of[1] = {
  { &hf_lte_rrc_SupportedBandListUTRA_TDD384_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SupportedBandUTRA_TDD384 },
};

static int
dissect_lte_rrc_SupportedBandListUTRA_TDD384(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_SupportedBandListUTRA_TDD384, SupportedBandListUTRA_TDD384_sequence_of,
                                                  1, maxBands, FALSE);

  return offset;
}


static const per_sequence_t IRAT_ParametersUTRA_TDD384_sequence[] = {
  { &hf_lte_rrc_supportedBandListUTRA_TDD384, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SupportedBandListUTRA_TDD384 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_IRAT_ParametersUTRA_TDD384(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_IRAT_ParametersUTRA_TDD384, IRAT_ParametersUTRA_TDD384_sequence);

  return offset;
}


static const value_string lte_rrc_SupportedBandUTRA_TDD768_vals[] = {
  {   0, "a" },
  {   1, "b" },
  {   2, "c" },
  {   3, "d" },
  {   4, "e" },
  {   5, "f" },
  {   6, "g" },
  {   7, "h" },
  {   8, "i" },
  {   9, "j" },
  {  10, "k" },
  {  11, "l" },
  {  12, "m" },
  {  13, "n" },
  {  14, "o" },
  {  15, "p" },
  { 0, NULL }
};


static int
dissect_lte_rrc_SupportedBandUTRA_TDD768(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t SupportedBandListUTRA_TDD768_sequence_of[1] = {
  { &hf_lte_rrc_SupportedBandListUTRA_TDD768_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SupportedBandUTRA_TDD768 },
};

static int
dissect_lte_rrc_SupportedBandListUTRA_TDD768(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_SupportedBandListUTRA_TDD768, SupportedBandListUTRA_TDD768_sequence_of,
                                                  1, maxBands, FALSE);

  return offset;
}


static const per_sequence_t IRAT_ParametersUTRA_TDD768_sequence[] = {
  { &hf_lte_rrc_supportedBandListUTRA_TDD768, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SupportedBandListUTRA_TDD768 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_IRAT_ParametersUTRA_TDD768(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_IRAT_ParametersUTRA_TDD768, IRAT_ParametersUTRA_TDD768_sequence);

  return offset;
}


static const value_string lte_rrc_SupportedBandGERAN_vals[] = {
  {   0, "gsm450" },
  {   1, "gsm480" },
  {   2, "gsm710" },
  {   3, "gsm750" },
  {   4, "gsm810" },
  {   5, "gsm850" },
  {   6, "gsm900P" },
  {   7, "gsm900E" },
  {   8, "gsm900R" },
  {   9, "gsm1800" },
  {  10, "gsm1900" },
  {  11, "spare5" },
  {  12, "spare4" },
  {  13, "spare3" },
  {  14, "spare2" },
  {  15, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_SupportedBandGERAN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t SupportedBandListGERAN_sequence_of[1] = {
  { &hf_lte_rrc_SupportedBandListGERAN_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SupportedBandGERAN },
};

static int
dissect_lte_rrc_SupportedBandListGERAN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_SupportedBandListGERAN, SupportedBandListGERAN_sequence_of,
                                                  1, maxBands, FALSE);

  return offset;
}


static const per_sequence_t IRAT_ParametersGERAN_sequence[] = {
  { &hf_lte_rrc_supportedBandListGERAN, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SupportedBandListGERAN },
  { &hf_lte_rrc_interRAT_PS_HO_ToGERAN, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_IRAT_ParametersGERAN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_IRAT_ParametersGERAN, IRAT_ParametersGERAN_sequence);

  return offset;
}


static const per_sequence_t SupportedBandListHRPD_sequence_of[1] = {
  { &hf_lte_rrc_SupportedBandListHRPD_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BandclassCDMA2000 },
};

static int
dissect_lte_rrc_SupportedBandListHRPD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_SupportedBandListHRPD, SupportedBandListHRPD_sequence_of,
                                                  1, maxCDMA_BandClass, FALSE);

  return offset;
}


static const value_string lte_rrc_T_tx_ConfigHRPD_vals[] = {
  {   0, "single" },
  {   1, "dual" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_tx_ConfigHRPD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_rx_ConfigHRPD_vals[] = {
  {   0, "single" },
  {   1, "dual" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_rx_ConfigHRPD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t IRAT_ParametersCDMA2000_HRPD_sequence[] = {
  { &hf_lte_rrc_supportedBandListHRPD, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SupportedBandListHRPD },
  { &hf_lte_rrc_tx_ConfigHRPD, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_tx_ConfigHRPD },
  { &hf_lte_rrc_rx_ConfigHRPD, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_rx_ConfigHRPD },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_IRAT_ParametersCDMA2000_HRPD(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_IRAT_ParametersCDMA2000_HRPD, IRAT_ParametersCDMA2000_HRPD_sequence);

  return offset;
}


static const per_sequence_t SupportedBandList1XRTT_sequence_of[1] = {
  { &hf_lte_rrc_SupportedBandList1XRTT_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BandclassCDMA2000 },
};

static int
dissect_lte_rrc_SupportedBandList1XRTT(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_SupportedBandList1XRTT, SupportedBandList1XRTT_sequence_of,
                                                  1, maxCDMA_BandClass, FALSE);

  return offset;
}


static const value_string lte_rrc_T_tx_Config1XRTT_vals[] = {
  {   0, "single" },
  {   1, "dual" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_tx_Config1XRTT(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_rx_Config1XRTT_vals[] = {
  {   0, "single" },
  {   1, "dual" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_rx_Config1XRTT(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t IRAT_ParametersCDMA2000_1XRTT_sequence[] = {
  { &hf_lte_rrc_supportedBandList1XRTT, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SupportedBandList1XRTT },
  { &hf_lte_rrc_tx_Config1XRTT, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_tx_Config1XRTT },
  { &hf_lte_rrc_rx_Config1XRTT, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_rx_Config1XRTT },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_IRAT_ParametersCDMA2000_1XRTT(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_IRAT_ParametersCDMA2000_1XRTT, IRAT_ParametersCDMA2000_1XRTT_sequence);

  return offset;
}


static const per_sequence_t T_interRAT_Parameters_sequence[] = {
  { &hf_lte_rrc_utraFDD     , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_IRAT_ParametersUTRA_FDD },
  { &hf_lte_rrc_utraTDD128  , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_IRAT_ParametersUTRA_TDD128 },
  { &hf_lte_rrc_utraTDD384  , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_IRAT_ParametersUTRA_TDD384 },
  { &hf_lte_rrc_utraTDD768  , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_IRAT_ParametersUTRA_TDD768 },
  { &hf_lte_rrc_geran_02    , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_IRAT_ParametersGERAN },
  { &hf_lte_rrc_cdma2000_HRPD_01, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_IRAT_ParametersCDMA2000_HRPD },
  { &hf_lte_rrc_cdma2000_1xRTT_01, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_IRAT_ParametersCDMA2000_1XRTT },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_interRAT_Parameters(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_interRAT_Parameters, T_interRAT_Parameters_sequence);

  return offset;
}


static const per_sequence_t PhyLayerParameters_v920_sequence[] = {
  { &hf_lte_rrc_enhancedDualLayerFDD_Supported_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_enhancedDualLayerTDD_Supported_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_PhyLayerParameters_v920(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_PhyLayerParameters_v920, PhyLayerParameters_v920_sequence);

  return offset;
}


static const value_string lte_rrc_T_dtm_r9_vals[] = {
  {   0, "supported" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_dtm_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_e_RedirectionGERAN_r9_vals[] = {
  {   0, "supported" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_e_RedirectionGERAN_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t IRAT_ParametersGERAN_v920_sequence[] = {
  { &hf_lte_rrc_dtm_r9      , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_dtm_r9 },
  { &hf_lte_rrc_e_RedirectionGERAN_r9, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_e_RedirectionGERAN_r9 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_IRAT_ParametersGERAN_v920(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_IRAT_ParametersGERAN_v920, IRAT_ParametersGERAN_v920_sequence);

  return offset;
}


static const value_string lte_rrc_T_e_Redirection_r9_vals[] = {
  {   0, "supported" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_e_Redirection_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t IRAT_ParametersUTRA_v920_sequence[] = {
  { &hf_lte_rrc_e_Redirection_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_e_Redirection_r9 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_IRAT_ParametersUTRA_v920(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_IRAT_ParametersUTRA_v920, IRAT_ParametersUTRA_v920_sequence);

  return offset;
}


static const value_string lte_rrc_T_e_CSFB_r9_vals[] = {
  {   0, "supported" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_e_CSFB_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string lte_rrc_T_e_CSFB_ConcPS_Mob_r9_vals[] = {
  {   0, "notSupported" },
  {   1, "supported" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_e_CSFB_ConcPS_Mob_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t IRAT_ParametersCDMA2000_1XRTT_v920_sequence[] = {
  { &hf_lte_rrc_e_CSFB_r9_01, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_e_CSFB_r9 },
  { &hf_lte_rrc_e_CSFB_ConcPS_Mob_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_e_CSFB_ConcPS_Mob_r9 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_IRAT_ParametersCDMA2000_1XRTT_v920(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_IRAT_ParametersCDMA2000_1XRTT_v920, IRAT_ParametersCDMA2000_1XRTT_v920_sequence);

  return offset;
}


static const value_string lte_rrc_T_deviceType_r9_vals[] = {
  {   0, "noBenFromBatConsumpOpt" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_deviceType_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t CSG_ProximityIndicationParameters_r9_sequence[] = {
  { &hf_lte_rrc_intraFreqProximityIndicationSupported_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_interFreqProximityIndicationSupported_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_utran_ProximityIndicationSupported_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_CSG_ProximityIndicationParameters_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_CSG_ProximityIndicationParameters_r9, CSG_ProximityIndicationParameters_r9_sequence);

  return offset;
}


static const per_sequence_t NeighCellSI_AcquisitionParameters_r9_sequence[] = {
  { &hf_lte_rrc_intraFreqSI_AcquisitionForHO_Supported_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_interFreqSI_AcquisitionForHO_Supported_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { &hf_lte_rrc_utran_SI_AcquisitionForHO_Supported_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_NeighCellSI_AcquisitionParameters_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_NeighCellSI_AcquisitionParameters_r9, NeighCellSI_AcquisitionParameters_r9_sequence);

  return offset;
}


static const per_sequence_t SON_Parameters_r9_sequence[] = {
  { &hf_lte_rrc_rach_ReportSupported_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_BOOLEAN },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_SON_Parameters_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_SON_Parameters_r9, SON_Parameters_r9_sequence);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_32_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_32(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_32, T_nonCriticalExtension_32_sequence);

  return offset;
}


static const per_sequence_t UE_EUTRA_Capability_v920_IEs_sequence[] = {
  { &hf_lte_rrc_phyLayerParameters_v920, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhyLayerParameters_v920 },
  { &hf_lte_rrc_interRAT_ParametersGERAN_v920, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_IRAT_ParametersGERAN_v920 },
  { &hf_lte_rrc_interRAT_ParametersUTRA_v920, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_IRAT_ParametersUTRA_v920 },
  { &hf_lte_rrc_interRAT_Parameters_v920, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_IRAT_ParametersCDMA2000_1XRTT_v920 },
  { &hf_lte_rrc_deviceType_r9, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_deviceType_r9 },
  { &hf_lte_rrc_csg_ProximityIndicationParameters_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CSG_ProximityIndicationParameters_r9 },
  { &hf_lte_rrc_neighCellSI_AcquisitionParameters_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_NeighCellSI_AcquisitionParameters_r9 },
  { &hf_lte_rrc_son_Parameters_r9, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SON_Parameters_r9 },
  { &hf_lte_rrc_nonCriticalExtension_44, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_32 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_UE_EUTRA_Capability_v920_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_UE_EUTRA_Capability_v920_IEs, UE_EUTRA_Capability_v920_IEs_sequence);

  return offset;
}


static const per_sequence_t UE_EUTRA_Capability_sequence[] = {
  { &hf_lte_rrc_accessStratumRelease, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_AccessStratumRelease },
  { &hf_lte_rrc_ue_Category , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_INTEGER_1_5 },
  { &hf_lte_rrc_pdcp_Parameters, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PDCP_Parameters },
  { &hf_lte_rrc_phyLayerParameters, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhyLayerParameters },
  { &hf_lte_rrc_rf_Parameters, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RF_Parameters },
  { &hf_lte_rrc_measParameters, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MeasParameters },
  { &hf_lte_rrc_featureGroupIndicators, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_BIT_STRING_SIZE_32 },
  { &hf_lte_rrc_interRAT_Parameters, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_interRAT_Parameters },
  { &hf_lte_rrc_nonCriticalExtension_43, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_UE_EUTRA_Capability_v920_IEs },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_UE_EUTRA_Capability(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_UE_EUTRA_Capability, UE_EUTRA_Capability_sequence);

  return offset;
}


static const value_string lte_rrc_T_physCellIdUTRA_vals[] = {
  {   0, "fdd" },
  {   1, "tdd" },
  { 0, NULL }
};

static const per_choice_t T_physCellIdUTRA_choice[] = {
  {   0, &hf_lte_rrc_fdd         , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_PhysCellIdUTRA_FDD },
  {   1, &hf_lte_rrc_tdd         , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_PhysCellIdUTRA_TDD },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_physCellIdUTRA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_physCellIdUTRA, T_physCellIdUTRA_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_physCellIdGERAN_sequence[] = {
  { &hf_lte_rrc_carrierFreq , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CarrierFreqGERAN },
  { &hf_lte_rrc_physCellId  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhysCellIdGERAN },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_physCellIdGERAN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_physCellIdGERAN, T_physCellIdGERAN_sequence);

  return offset;
}


static const value_string lte_rrc_CellsTriggeredList_item_vals[] = {
  {   0, "physCellIdEUTRA" },
  {   1, "physCellIdUTRA" },
  {   2, "physCellIdGERAN" },
  {   3, "physCellIdCDMA2000" },
  { 0, NULL }
};

static const per_choice_t CellsTriggeredList_item_choice[] = {
  {   0, &hf_lte_rrc_physCellIdEUTRA, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_PhysCellId },
  {   1, &hf_lte_rrc_physCellIdUTRA, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_physCellIdUTRA },
  {   2, &hf_lte_rrc_physCellIdGERAN, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_physCellIdGERAN },
  {   3, &hf_lte_rrc_physCellIdCDMA2000, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_PhysCellIdCDMA2000 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_CellsTriggeredList_item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_CellsTriggeredList_item, CellsTriggeredList_item_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t CellsTriggeredList_sequence_of[1] = {
  { &hf_lte_rrc_CellsTriggeredList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CellsTriggeredList_item },
};

static int
dissect_lte_rrc_CellsTriggeredList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_CellsTriggeredList, CellsTriggeredList_sequence_of,
                                                  1, maxCellMeas, FALSE);

  return offset;
}



static int
dissect_lte_rrc_T_handoverCommandMessage(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string_containing_pdu_new(tvb, offset, actx, tree, hf_index,
                                                                NO_BOUND, NO_BOUND, FALSE, dissect_DL_DCCH_Message_PDU);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_33_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_33(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_33, T_nonCriticalExtension_33_sequence);

  return offset;
}


static const per_sequence_t HandoverCommand_r8_IEs_sequence[] = {
  { &hf_lte_rrc_handoverCommandMessage, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_handoverCommandMessage },
  { &hf_lte_rrc_nonCriticalExtension_45, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_33 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_HandoverCommand_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_HandoverCommand_r8_IEs, HandoverCommand_r8_IEs_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_26_vals[] = {
  {   0, "handoverCommand-r8" },
  {   1, "spare7" },
  {   2, "spare6" },
  {   3, "spare5" },
  {   4, "spare4" },
  {   5, "spare3" },
  {   6, "spare2" },
  {   7, "spare1" },
  { 0, NULL }
};

static const per_choice_t T_c1_26_choice[] = {
  {   0, &hf_lte_rrc_handoverCommand_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_HandoverCommand_r8_IEs },
  {   1, &hf_lte_rrc_spare7      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   2, &hf_lte_rrc_spare6      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   3, &hf_lte_rrc_spare5      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   4, &hf_lte_rrc_spare4      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   5, &hf_lte_rrc_spare3      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   6, &hf_lte_rrc_spare2      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   7, &hf_lte_rrc_spare1      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_26(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_26, T_c1_26_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_30_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_30(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_30, T_criticalExtensionsFuture_30_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_30_vals[] = {
  {   0, "c1" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_30_choice[] = {
  {   0, &hf_lte_rrc_c1_26       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_26 },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_30, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_30 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_30(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_30, T_criticalExtensions_30_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t HandoverCommand_sequence[] = {
  { &hf_lte_rrc_criticalExtensions_30, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_30 },
  { NULL, 0, 0, NULL }
};

int
dissect_lte_rrc_HandoverCommand(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_HandoverCommand, HandoverCommand_sequence);

  return offset;
}



static int
dissect_lte_rrc_T_sourceSystemInformationBlockType1Ext(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string_containing_pdu_new(tvb, offset, actx, tree, hf_index,
                                                                NO_BOUND, NO_BOUND, FALSE, dissect_SystemInformationBlockType1_v890_IEs_PDU);

  return offset;
}


static const per_sequence_t AS_Config_sequence[] = {
  { &hf_lte_rrc_sourceMeasConfig, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MeasConfig },
  { &hf_lte_rrc_sourceRadioResourceConfig, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_RadioResourceConfigDedicated },
  { &hf_lte_rrc_sourceSecurityAlgorithmConfig, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SecurityAlgorithmConfig },
  { &hf_lte_rrc_sourceUE_Identity, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_C_RNTI },
  { &hf_lte_rrc_sourceMasterInformationBlock, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_MasterInformationBlock },
  { &hf_lte_rrc_sourceSystemInformationBlockType1, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SystemInformationBlockType1 },
  { &hf_lte_rrc_sourceSystemInformationBlockType2, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_SystemInformationBlockType2 },
  { &hf_lte_rrc_antennaInfoCommon, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_AntennaInfoCommon },
  { &hf_lte_rrc_sourceDl_CarrierFreq, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ARFCN_ValueEUTRA },
  { &hf_lte_rrc_sourceSystemInformationBlockType1Ext, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_lte_rrc_T_sourceSystemInformationBlockType1Ext },
  { &hf_lte_rrc_sourceOtherConfig_r9, ASN1_NOT_EXTENSION_ROOT, ASN1_NOT_OPTIONAL, dissect_lte_rrc_OtherConfig_r9 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_AS_Config(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_AS_Config, AS_Config_sequence);

  return offset;
}


static const value_string lte_rrc_T_ue_InactiveTime_vals[] = {
  {   0, "s1" },
  {   1, "s2" },
  {   2, "s3" },
  {   3, "s5" },
  {   4, "s7" },
  {   5, "s10" },
  {   6, "s15" },
  {   7, "s20" },
  {   8, "s25" },
  {   9, "s30" },
  {  10, "s40" },
  {  11, "s50" },
  {  12, "min1" },
  {  13, "min1s20c" },
  {  14, "min1s40" },
  {  15, "min2" },
  {  16, "min2s30" },
  {  17, "min3" },
  {  18, "min3s30" },
  {  19, "min4" },
  {  20, "min5" },
  {  21, "min6" },
  {  22, "min7" },
  {  23, "min8" },
  {  24, "min9" },
  {  25, "min10" },
  {  26, "min12" },
  {  27, "min14" },
  {  28, "min17" },
  {  29, "min20" },
  {  30, "min24" },
  {  31, "min28" },
  {  32, "min33" },
  {  33, "min38" },
  {  34, "min44" },
  {  35, "min50" },
  {  36, "hr1" },
  {  37, "hr1min30" },
  {  38, "hr2" },
  {  39, "hr2min30" },
  {  40, "hr3" },
  {  41, "hr3min30" },
  {  42, "hr4" },
  {  43, "hr5" },
  {  44, "hr6" },
  {  45, "hr8" },
  {  46, "hr10" },
  {  47, "hr13" },
  {  48, "hr16" },
  {  49, "hr20" },
  {  50, "day1" },
  {  51, "day1hr12" },
  {  52, "day2" },
  {  53, "day2hr12" },
  {  54, "day3" },
  {  55, "day4" },
  {  56, "day5" },
  {  57, "day7" },
  {  58, "day10" },
  {  59, "day14" },
  {  60, "day19" },
  {  61, "day24" },
  {  62, "day30" },
  {  63, "dayMoreThan30" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_ue_InactiveTime(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     64, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t RRM_Config_sequence[] = {
  { &hf_lte_rrc_ue_InactiveTime, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_T_ue_InactiveTime },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_RRM_Config(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_RRM_Config, RRM_Config_sequence);

  return offset;
}



static int
dissect_lte_rrc_Key_eNodeB_Star(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     256, 256, FALSE, NULL);

  return offset;
}


static const per_sequence_t AdditionalReestabInfo_sequence[] = {
  { &hf_lte_rrc_cellIdentity, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_CellIdentity },
  { &hf_lte_rrc_key_eNodeB_Star, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_Key_eNodeB_Star },
  { &hf_lte_rrc_shortMAC_I  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ShortMAC_I },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_AdditionalReestabInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_AdditionalReestabInfo, AdditionalReestabInfo_sequence);

  return offset;
}


static const per_sequence_t AdditionalReestabInfoList_sequence_of[1] = {
  { &hf_lte_rrc_AdditionalReestabInfoList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_AdditionalReestabInfo },
};

static int
dissect_lte_rrc_AdditionalReestabInfoList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_lte_rrc_AdditionalReestabInfoList, AdditionalReestabInfoList_sequence_of,
                                                  1, maxReestabInfo, FALSE);

  return offset;
}


static const per_sequence_t ReestablishmentInfo_sequence[] = {
  { &hf_lte_rrc_sourcePhysCellId, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_PhysCellId },
  { &hf_lte_rrc_targetCellShortMAC_I, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_lte_rrc_ShortMAC_I },
  { &hf_lte_rrc_additionalReestabInfoList, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_lte_rrc_AdditionalReestabInfoList },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_ReestablishmentInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_ReestablishmentInfo, ReestablishmentInfo_sequence);

  return offset;
}


static const per_sequence_t AS_Context_sequence[] = {
  { &hf_lte_rrc_reestablishmentInfo, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_ReestablishmentInfo },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_AS_Context(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_AS_Context, AS_Context_sequence);

  return offset;
}


static const value_string lte_rrc_T_ue_ConfigRelease_r9_vals[] = {
  {   0, "rel9" },
  {   1, "spare7" },
  {   2, "spare6" },
  {   3, "spare5" },
  {   4, "spare4" },
  {   5, "spare3" },
  {   6, "spare2" },
  {   7, "spare1" },
  { 0, NULL }
};


static int
dissect_lte_rrc_T_ue_ConfigRelease_r9(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_34_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_34(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_34, T_nonCriticalExtension_34_sequence);

  return offset;
}


static const per_sequence_t HandoverPreparationInformation_v920_IEs_sequence[] = {
  { &hf_lte_rrc_ue_ConfigRelease_r9, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_ue_ConfigRelease_r9 },
  { &hf_lte_rrc_nonCriticalExtension_47, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_34 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_HandoverPreparationInformation_v920_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_HandoverPreparationInformation_v920_IEs, HandoverPreparationInformation_v920_IEs_sequence);

  return offset;
}


static const per_sequence_t HandoverPreparationInformation_r8_IEs_sequence[] = {
  { &hf_lte_rrc_ue_RadioAccessCapabilityInfo, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_UE_CapabilityRAT_ContainerList },
  { &hf_lte_rrc_as_Config   , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_AS_Config },
  { &hf_lte_rrc_rrm_Config  , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_RRM_Config },
  { &hf_lte_rrc_as_Context  , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_AS_Context },
  { &hf_lte_rrc_nonCriticalExtension_46, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_HandoverPreparationInformation_v920_IEs },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_HandoverPreparationInformation_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_HandoverPreparationInformation_r8_IEs, HandoverPreparationInformation_r8_IEs_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_27_vals[] = {
  {   0, "handoverPreparationInformation-r8" },
  {   1, "spare7" },
  {   2, "spare6" },
  {   3, "spare5" },
  {   4, "spare4" },
  {   5, "spare3" },
  {   6, "spare2" },
  {   7, "spare1" },
  { 0, NULL }
};

static const per_choice_t T_c1_27_choice[] = {
  {   0, &hf_lte_rrc_handoverPreparationInformation_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_HandoverPreparationInformation_r8_IEs },
  {   1, &hf_lte_rrc_spare7      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   2, &hf_lte_rrc_spare6      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   3, &hf_lte_rrc_spare5      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   4, &hf_lte_rrc_spare4      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   5, &hf_lte_rrc_spare3      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   6, &hf_lte_rrc_spare2      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   7, &hf_lte_rrc_spare1      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_27(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_27, T_c1_27_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_31_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_31(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_31, T_criticalExtensionsFuture_31_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_31_vals[] = {
  {   0, "c1" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_31_choice[] = {
  {   0, &hf_lte_rrc_c1_27       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_27 },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_31, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_31 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_31(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_31, T_criticalExtensions_31_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t HandoverPreparationInformation_sequence[] = {
  { &hf_lte_rrc_criticalExtensions_31, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_31 },
  { NULL, 0, 0, NULL }
};

int
dissect_lte_rrc_HandoverPreparationInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_HandoverPreparationInformation, HandoverPreparationInformation_sequence);

  return offset;
}



static int
dissect_lte_rrc_T_ue_RadioAccessCapabilityInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string_containing_pdu_new(tvb, offset, actx, tree, hf_index,
                                                                NO_BOUND, NO_BOUND, FALSE, dissect_UECapabilityInformation_PDU);

  return offset;
}


static const per_sequence_t T_nonCriticalExtension_35_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_nonCriticalExtension_35(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_nonCriticalExtension_35, T_nonCriticalExtension_35_sequence);

  return offset;
}


static const per_sequence_t UERadioAccessCapabilityInformation_r8_IEs_sequence[] = {
  { &hf_lte_rrc_ue_RadioAccessCapabilityInfo_01, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_ue_RadioAccessCapabilityInfo },
  { &hf_lte_rrc_nonCriticalExtension_48, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_lte_rrc_T_nonCriticalExtension_35 },
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_UERadioAccessCapabilityInformation_r8_IEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_UERadioAccessCapabilityInformation_r8_IEs, UERadioAccessCapabilityInformation_r8_IEs_sequence);

  return offset;
}


static const value_string lte_rrc_T_c1_28_vals[] = {
  {   0, "ueRadioAccessCapabilityInformation-r8" },
  {   1, "spare7" },
  {   2, "spare6" },
  {   3, "spare5" },
  {   4, "spare4" },
  {   5, "spare3" },
  {   6, "spare2" },
  {   7, "spare1" },
  { 0, NULL }
};

static const per_choice_t T_c1_28_choice[] = {
  {   0, &hf_lte_rrc_ueRadioAccessCapabilityInformation_r8, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_UERadioAccessCapabilityInformation_r8_IEs },
  {   1, &hf_lte_rrc_spare7      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   2, &hf_lte_rrc_spare6      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   3, &hf_lte_rrc_spare5      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   4, &hf_lte_rrc_spare4      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   5, &hf_lte_rrc_spare3      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   6, &hf_lte_rrc_spare2      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  {   7, &hf_lte_rrc_spare1      , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_c1_28(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_c1_28, T_c1_28_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t T_criticalExtensionsFuture_32_sequence[] = {
  { NULL, 0, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensionsFuture_32(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_T_criticalExtensionsFuture_32, T_criticalExtensionsFuture_32_sequence);

  return offset;
}


static const value_string lte_rrc_T_criticalExtensions_32_vals[] = {
  {   0, "c1" },
  {   1, "criticalExtensionsFuture" },
  { 0, NULL }
};

static const per_choice_t T_criticalExtensions_32_choice[] = {
  {   0, &hf_lte_rrc_c1_28       , ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_c1_28 },
  {   1, &hf_lte_rrc_criticalExtensionsFuture_32, ASN1_NO_EXTENSIONS     , dissect_lte_rrc_T_criticalExtensionsFuture_32 },
  { 0, NULL, 0, NULL }
};

static int
dissect_lte_rrc_T_criticalExtensions_32(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_lte_rrc_T_criticalExtensions_32, T_criticalExtensions_32_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t UERadioAccessCapabilityInformation_sequence[] = {
  { &hf_lte_rrc_criticalExtensions_32, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_lte_rrc_T_criticalExtensions_32 },
  { NULL, 0, 0, NULL }
};

int
dissect_lte_rrc_UERadioAccessCapabilityInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_lte_rrc_UERadioAccessCapabilityInformation, UERadioAccessCapabilityInformation_sequence);

  return offset;
}

/*--- PDUs ---*/

static int dissect_BCCH_BCH_Message_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, FALSE, pinfo);
  offset = dissect_lte_rrc_BCCH_BCH_Message(tvb, offset, &asn1_ctx, tree, hf_lte_rrc_BCCH_BCH_Message_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_BCCH_DL_SCH_Message_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, FALSE, pinfo);
  offset = dissect_lte_rrc_BCCH_DL_SCH_Message(tvb, offset, &asn1_ctx, tree, hf_lte_rrc_BCCH_DL_SCH_Message_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_MCCH_Message_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, FALSE, pinfo);
  offset = dissect_lte_rrc_MCCH_Message(tvb, offset, &asn1_ctx, tree, hf_lte_rrc_MCCH_Message_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_PCCH_Message_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, FALSE, pinfo);
  offset = dissect_lte_rrc_PCCH_Message(tvb, offset, &asn1_ctx, tree, hf_lte_rrc_PCCH_Message_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_DL_CCCH_Message_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, FALSE, pinfo);
  offset = dissect_lte_rrc_DL_CCCH_Message(tvb, offset, &asn1_ctx, tree, hf_lte_rrc_DL_CCCH_Message_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_DL_DCCH_Message_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, FALSE, pinfo);
  offset = dissect_lte_rrc_DL_DCCH_Message(tvb, offset, &asn1_ctx, tree, hf_lte_rrc_DL_DCCH_Message_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UL_CCCH_Message_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, FALSE, pinfo);
  offset = dissect_lte_rrc_UL_CCCH_Message(tvb, offset, &asn1_ctx, tree, hf_lte_rrc_UL_CCCH_Message_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UL_DCCH_Message_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, FALSE, pinfo);
  offset = dissect_lte_rrc_UL_DCCH_Message(tvb, offset, &asn1_ctx, tree, hf_lte_rrc_UL_DCCH_Message_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UECapabilityInformation_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, FALSE, pinfo);
  offset = dissect_lte_rrc_UECapabilityInformation(tvb, offset, &asn1_ctx, tree, hf_lte_rrc_UECapabilityInformation_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UE_EUTRA_Capability_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, FALSE, pinfo);
  offset = dissect_lte_rrc_UE_EUTRA_Capability(tvb, offset, &asn1_ctx, tree, hf_lte_rrc_UE_EUTRA_Capability_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
int dissect_lte_rrc_HandoverCommand_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, FALSE, pinfo);
  offset = dissect_lte_rrc_HandoverCommand(tvb, offset, &asn1_ctx, tree, hf_lte_rrc_lte_rrc_HandoverCommand_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
int dissect_lte_rrc_HandoverPreparationInformation_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, FALSE, pinfo);
  offset = dissect_lte_rrc_HandoverPreparationInformation(tvb, offset, &asn1_ctx, tree, hf_lte_rrc_lte_rrc_HandoverPreparationInformation_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
int dissect_lte_rrc_UERadioAccessCapabilityInformation_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, FALSE, pinfo);
  offset = dissect_lte_rrc_UERadioAccessCapabilityInformation(tvb, offset, &asn1_ctx, tree, hf_lte_rrc_lte_rrc_UERadioAccessCapabilityInformation_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_SystemInformationBlockType1_v890_IEs_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, FALSE, pinfo);
  offset = dissect_lte_rrc_SystemInformationBlockType1_v890_IEs(tvb, offset, &asn1_ctx, tree, hf_lte_rrc_SystemInformationBlockType1_v890_IEs_PDU);
  offset += 7; offset >>= 3;
  return offset;
}


/*--- End of included file: packet-lte-rrc-fn.c ---*/
#line 68 "packet-lte-rrc-template.c"

static void
dissect_lte_rrc_DL_CCCH(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
	proto_item *ti;
	proto_tree *lte_rrc_tree;

	col_set_str(pinfo->cinfo, COL_PROTOCOL, "LTE RRC DL_CCCH");
	col_clear(pinfo->cinfo, COL_INFO);
	if (tree) {

		ti = proto_tree_add_item(tree, proto_lte_rrc, tvb, 0, -1, FALSE);
		lte_rrc_tree = proto_item_add_subtree(ti, ett_lte_rrc);
		dissect_DL_CCCH_Message_PDU(tvb, pinfo, lte_rrc_tree);
	}
}

static void
dissect_lte_rrc_DL_DCCH(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
	proto_item *ti;
	proto_tree *lte_rrc_tree;

	col_set_str(pinfo->cinfo, COL_PROTOCOL, "LTE RRC DL_DCCH");
	col_clear(pinfo->cinfo, COL_INFO);
	if (tree) {

		ti = proto_tree_add_item(tree, proto_lte_rrc, tvb, 0, -1, FALSE);
		lte_rrc_tree = proto_item_add_subtree(ti, ett_lte_rrc);
		dissect_DL_DCCH_Message_PDU(tvb, pinfo, lte_rrc_tree);
	}
}


static void
dissect_lte_rrc_UL_CCCH(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
	proto_item *ti;
	proto_tree *lte_rrc_tree;

	col_set_str(pinfo->cinfo, COL_PROTOCOL, "LTE RRC UL_CCCH");
	col_clear(pinfo->cinfo, COL_INFO);
	if (tree) {

		ti = proto_tree_add_item(tree, proto_lte_rrc, tvb, 0, -1, FALSE);
		lte_rrc_tree = proto_item_add_subtree(ti, ett_lte_rrc);
		dissect_UL_CCCH_Message_PDU(tvb, pinfo, lte_rrc_tree);
	}
}

static void
dissect_lte_rrc_UL_DCCH(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
	proto_item *ti;
	proto_tree *lte_rrc_tree;

	col_set_str(pinfo->cinfo, COL_PROTOCOL, "LTE RRC UL_DCCH");
	col_clear(pinfo->cinfo, COL_INFO);
	if (tree) {

		ti = proto_tree_add_item(tree, proto_lte_rrc, tvb, 0, -1, FALSE);
		lte_rrc_tree = proto_item_add_subtree(ti, ett_lte_rrc);
		dissect_UL_DCCH_Message_PDU(tvb, pinfo, lte_rrc_tree);
	}
}



/*--- proto_register_rrc -------------------------------------------*/
void proto_register_lte_rrc(void) {

  /* List of fields */
  static hf_register_info hf[] = {


/*--- Included file: packet-lte-rrc-hfarr.c ---*/
#line 1 "packet-lte-rrc-hfarr.c"
    { &hf_lte_rrc_BCCH_BCH_Message_PDU,
      { "BCCH-BCH-Message", "lte-rrc.BCCH_BCH_Message",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_BCCH_DL_SCH_Message_PDU,
      { "BCCH-DL-SCH-Message", "lte-rrc.BCCH_DL_SCH_Message",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_MCCH_Message_PDU,
      { "MCCH-Message", "lte-rrc.MCCH_Message",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_PCCH_Message_PDU,
      { "PCCH-Message", "lte-rrc.PCCH_Message",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_DL_CCCH_Message_PDU,
      { "DL-CCCH-Message", "lte-rrc.DL_CCCH_Message",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_DL_DCCH_Message_PDU,
      { "DL-DCCH-Message", "lte-rrc.DL_DCCH_Message",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_UL_CCCH_Message_PDU,
      { "UL-CCCH-Message", "lte-rrc.UL_CCCH_Message",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_UL_DCCH_Message_PDU,
      { "UL-DCCH-Message", "lte-rrc.UL_DCCH_Message",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_UECapabilityInformation_PDU,
      { "UECapabilityInformation", "lte-rrc.UECapabilityInformation",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_UE_EUTRA_Capability_PDU,
      { "UE-EUTRA-Capability", "lte-rrc.UE_EUTRA_Capability",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_lte_rrc_HandoverCommand_PDU,
      { "HandoverCommand", "lte-rrc.HandoverCommand",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_lte_rrc_HandoverPreparationInformation_PDU,
      { "HandoverPreparationInformation", "lte-rrc.HandoverPreparationInformation",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_lte_rrc_UERadioAccessCapabilityInformation_PDU,
      { "UERadioAccessCapabilityInformation", "lte-rrc.UERadioAccessCapabilityInformation",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_SystemInformationBlockType1_v890_IEs_PDU,
      { "SystemInformationBlockType1-v890-IEs", "lte-rrc.SystemInformationBlockType1_v890_IEs",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_message,
      { "message", "lte-rrc.message",
        FT_NONE, BASE_NONE, NULL, 0,
        "BCCH_BCH_MessageType", HFILL }},
    { &hf_lte_rrc_message_01,
      { "message", "lte-rrc.message",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_BCCH_DL_SCH_MessageType_vals), 0,
        "BCCH_DL_SCH_MessageType", HFILL }},
    { &hf_lte_rrc_c1,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_systemInformation,
      { "systemInformation", "lte-rrc.systemInformation",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_systemInformationBlockType1,
      { "systemInformationBlockType1", "lte-rrc.systemInformationBlockType1",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_messageClassExtension,
      { "messageClassExtension", "lte-rrc.messageClassExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_message_02,
      { "message", "lte-rrc.message",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_MCCH_MessageType_vals), 0,
        "MCCH_MessageType", HFILL }},
    { &hf_lte_rrc_c1_01,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_01_vals), 0,
        "T_c1_01", HFILL }},
    { &hf_lte_rrc_mbsfnAreaConfiguration_r9,
      { "mbsfnAreaConfiguration-r9", "lte-rrc.mbsfnAreaConfiguration_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_messageClassExtension_01,
      { "messageClassExtension", "lte-rrc.messageClassExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_messageClassExtension_01", HFILL }},
    { &hf_lte_rrc_message_03,
      { "message", "lte-rrc.message",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_PCCH_MessageType_vals), 0,
        "PCCH_MessageType", HFILL }},
    { &hf_lte_rrc_c1_02,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_02_vals), 0,
        "T_c1_02", HFILL }},
    { &hf_lte_rrc_paging,
      { "paging", "lte-rrc.paging",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_messageClassExtension_02,
      { "messageClassExtension", "lte-rrc.messageClassExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_messageClassExtension_02", HFILL }},
    { &hf_lte_rrc_message_04,
      { "message", "lte-rrc.message",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_DL_CCCH_MessageType_vals), 0,
        "DL_CCCH_MessageType", HFILL }},
    { &hf_lte_rrc_c1_03,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_03_vals), 0,
        "T_c1_03", HFILL }},
    { &hf_lte_rrc_rrcConnectionReestablishment,
      { "rrcConnectionReestablishment", "lte-rrc.rrcConnectionReestablishment",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_rrcConnectionReestablishmentReject,
      { "rrcConnectionReestablishmentReject", "lte-rrc.rrcConnectionReestablishmentReject",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_rrcConnectionReject,
      { "rrcConnectionReject", "lte-rrc.rrcConnectionReject",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_rrcConnectionSetup,
      { "rrcConnectionSetup", "lte-rrc.rrcConnectionSetup",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_messageClassExtension_03,
      { "messageClassExtension", "lte-rrc.messageClassExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_messageClassExtension_03", HFILL }},
    { &hf_lte_rrc_message_05,
      { "message", "lte-rrc.message",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_DL_DCCH_MessageType_vals), 0,
        "DL_DCCH_MessageType", HFILL }},
    { &hf_lte_rrc_c1_04,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_04_vals), 0,
        "T_c1_04", HFILL }},
    { &hf_lte_rrc_csfbParametersResponseCDMA2000,
      { "csfbParametersResponseCDMA2000", "lte-rrc.csfbParametersResponseCDMA2000",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_dlInformationTransfer,
      { "dlInformationTransfer", "lte-rrc.dlInformationTransfer",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_handoverFromEUTRAPreparationRequest,
      { "handoverFromEUTRAPreparationRequest", "lte-rrc.handoverFromEUTRAPreparationRequest",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_mobilityFromEUTRACommand,
      { "mobilityFromEUTRACommand", "lte-rrc.mobilityFromEUTRACommand",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_rrcConnectionReconfiguration,
      { "rrcConnectionReconfiguration", "lte-rrc.rrcConnectionReconfiguration",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_rrcConnectionRelease,
      { "rrcConnectionRelease", "lte-rrc.rrcConnectionRelease",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_securityModeCommand,
      { "securityModeCommand", "lte-rrc.securityModeCommand",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ueCapabilityEnquiry,
      { "ueCapabilityEnquiry", "lte-rrc.ueCapabilityEnquiry",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_counterCheck,
      { "counterCheck", "lte-rrc.counterCheck",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ueInformationRequest_r9,
      { "ueInformationRequest-r9", "lte-rrc.ueInformationRequest_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_spare6,
      { "spare6", "lte-rrc.spare6",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_spare5,
      { "spare5", "lte-rrc.spare5",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_spare4,
      { "spare4", "lte-rrc.spare4",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_spare3,
      { "spare3", "lte-rrc.spare3",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_spare2,
      { "spare2", "lte-rrc.spare2",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_spare1,
      { "spare1", "lte-rrc.spare1",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_messageClassExtension_04,
      { "messageClassExtension", "lte-rrc.messageClassExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_messageClassExtension_04", HFILL }},
    { &hf_lte_rrc_message_06,
      { "message", "lte-rrc.message",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_UL_CCCH_MessageType_vals), 0,
        "UL_CCCH_MessageType", HFILL }},
    { &hf_lte_rrc_c1_05,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_05_vals), 0,
        "T_c1_05", HFILL }},
    { &hf_lte_rrc_rrcConnectionReestablishmentRequest,
      { "rrcConnectionReestablishmentRequest", "lte-rrc.rrcConnectionReestablishmentRequest",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_rrcConnectionRequest,
      { "rrcConnectionRequest", "lte-rrc.rrcConnectionRequest",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_messageClassExtension_05,
      { "messageClassExtension", "lte-rrc.messageClassExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_messageClassExtension_05", HFILL }},
    { &hf_lte_rrc_message_07,
      { "message", "lte-rrc.message",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_UL_DCCH_MessageType_vals), 0,
        "UL_DCCH_MessageType", HFILL }},
    { &hf_lte_rrc_c1_06,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_06_vals), 0,
        "T_c1_06", HFILL }},
    { &hf_lte_rrc_csfbParametersRequestCDMA2000,
      { "csfbParametersRequestCDMA2000", "lte-rrc.csfbParametersRequestCDMA2000",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_measurementReport,
      { "measurementReport", "lte-rrc.measurementReport",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_rrcConnectionReconfigurationComplete,
      { "rrcConnectionReconfigurationComplete", "lte-rrc.rrcConnectionReconfigurationComplete",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_rrcConnectionReestablishmentComplete,
      { "rrcConnectionReestablishmentComplete", "lte-rrc.rrcConnectionReestablishmentComplete",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_rrcConnectionSetupComplete,
      { "rrcConnectionSetupComplete", "lte-rrc.rrcConnectionSetupComplete",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_securityModeComplete,
      { "securityModeComplete", "lte-rrc.securityModeComplete",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_securityModeFailure,
      { "securityModeFailure", "lte-rrc.securityModeFailure",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ueCapabilityInformation,
      { "ueCapabilityInformation", "lte-rrc.ueCapabilityInformation",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ulHandoverPreparationTransfer,
      { "ulHandoverPreparationTransfer", "lte-rrc.ulHandoverPreparationTransfer",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ulInformationTransfer,
      { "ulInformationTransfer", "lte-rrc.ulInformationTransfer",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_counterCheckResponse,
      { "counterCheckResponse", "lte-rrc.counterCheckResponse",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ueInformationResponse_r9,
      { "ueInformationResponse-r9", "lte-rrc.ueInformationResponse_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_proximityIndication_r9,
      { "proximityIndication-r9", "lte-rrc.proximityIndication_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_messageClassExtension_06,
      { "messageClassExtension", "lte-rrc.messageClassExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_messageClassExtension_06", HFILL }},
    { &hf_lte_rrc_rrc_TransactionIdentifier,
      { "rrc-TransactionIdentifier", "lte-rrc.rrc_TransactionIdentifier",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_criticalExtensions,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_c1_07,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_07_vals), 0,
        "T_c1_07", HFILL }},
    { &hf_lte_rrc_counterCheck_r8,
      { "counterCheck-r8", "lte-rrc.counterCheck_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "CounterCheck_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_drb_CountMSB_InfoList,
      { "drb-CountMSB-InfoList", "lte-rrc.drb_CountMSB_InfoList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nonCriticalExtension,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_DRB_CountMSB_InfoList_item,
      { "DRB-CountMSB-Info", "lte-rrc.DRB_CountMSB_Info",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_drb_Identity,
      { "drb-Identity", "lte-rrc.drb_Identity",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_countMSB_Uplink,
      { "countMSB-Uplink", "lte-rrc.countMSB_Uplink",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_33554431", HFILL }},
    { &hf_lte_rrc_countMSB_Downlink,
      { "countMSB-Downlink", "lte-rrc.countMSB_Downlink",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_33554431", HFILL }},
    { &hf_lte_rrc_criticalExtensions_01,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_01_vals), 0,
        "T_criticalExtensions_01", HFILL }},
    { &hf_lte_rrc_counterCheckResponse_r8,
      { "counterCheckResponse-r8", "lte-rrc.counterCheckResponse_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "CounterCheckResponse_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_01,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_01", HFILL }},
    { &hf_lte_rrc_drb_CountInfoList,
      { "drb-CountInfoList", "lte-rrc.drb_CountInfoList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_01,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_01", HFILL }},
    { &hf_lte_rrc_DRB_CountInfoList_item,
      { "DRB-CountInfo", "lte-rrc.DRB_CountInfo",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_count_Uplink,
      { "count-Uplink", "lte-rrc.count_Uplink",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_4294967295", HFILL }},
    { &hf_lte_rrc_count_Downlink,
      { "count-Downlink", "lte-rrc.count_Downlink",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_4294967295", HFILL }},
    { &hf_lte_rrc_criticalExtensions_02,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_02_vals), 0,
        "T_criticalExtensions_02", HFILL }},
    { &hf_lte_rrc_csfbParametersRequestCDMA2000_r8,
      { "csfbParametersRequestCDMA2000-r8", "lte-rrc.csfbParametersRequestCDMA2000_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "CSFBParametersRequestCDMA2000_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_02,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_02", HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_02,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_02", HFILL }},
    { &hf_lte_rrc_criticalExtensions_03,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_03_vals), 0,
        "T_criticalExtensions_03", HFILL }},
    { &hf_lte_rrc_csfbParametersResponseCDMA2000_r8,
      { "csfbParametersResponseCDMA2000-r8", "lte-rrc.csfbParametersResponseCDMA2000_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "CSFBParametersResponseCDMA2000_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_03,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_03", HFILL }},
    { &hf_lte_rrc_rand,
      { "rand", "lte-rrc.rand",
        FT_BYTES, BASE_NONE, NULL, 0,
        "RAND_CDMA2000", HFILL }},
    { &hf_lte_rrc_mobilityParameters,
      { "mobilityParameters", "lte-rrc.mobilityParameters",
        FT_BYTES, BASE_NONE, NULL, 0,
        "MobilityParametersCDMA2000", HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_03,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_03", HFILL }},
    { &hf_lte_rrc_criticalExtensions_04,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_04_vals), 0,
        "T_criticalExtensions_04", HFILL }},
    { &hf_lte_rrc_c1_08,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_08_vals), 0,
        "T_c1_08", HFILL }},
    { &hf_lte_rrc_dlInformationTransfer_r8,
      { "dlInformationTransfer-r8", "lte-rrc.dlInformationTransfer_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "DLInformationTransfer_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_04,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_04", HFILL }},
    { &hf_lte_rrc_dedicatedInfoType,
      { "dedicatedInfoType", "lte-rrc.dedicatedInfoType",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_dedicatedInfoType_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_dedicatedInfoNAS,
      { "dedicatedInfoNAS", "lte-rrc.dedicatedInfoNAS",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_dedicatedInfoCDMA2000_1XRTT,
      { "dedicatedInfoCDMA2000-1XRTT", "lte-rrc.dedicatedInfoCDMA2000_1XRTT",
        FT_BYTES, BASE_NONE, NULL, 0,
        "DedicatedInfoCDMA2000", HFILL }},
    { &hf_lte_rrc_dedicatedInfoCDMA2000_HRPD,
      { "dedicatedInfoCDMA2000-HRPD", "lte-rrc.dedicatedInfoCDMA2000_HRPD",
        FT_BYTES, BASE_NONE, NULL, 0,
        "DedicatedInfoCDMA2000", HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_04,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_04", HFILL }},
    { &hf_lte_rrc_criticalExtensions_05,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_05_vals), 0,
        "T_criticalExtensions_05", HFILL }},
    { &hf_lte_rrc_c1_09,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_09_vals), 0,
        "T_c1_09", HFILL }},
    { &hf_lte_rrc_handoverFromEUTRAPreparationRequest_r8,
      { "handoverFromEUTRAPreparationRequest-r8", "lte-rrc.handoverFromEUTRAPreparationRequest_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "HandoverFromEUTRAPreparationRequest_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_05,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_05", HFILL }},
    { &hf_lte_rrc_cdma2000_Type,
      { "cdma2000-Type", "lte-rrc.cdma2000_Type",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_CDMA2000_Type_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_05,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "HandoverFromEUTRAPreparationRequest_v890_IEs", HFILL }},
    { &hf_lte_rrc_lateR8NonCriticalExtension,
      { "lateR8NonCriticalExtension", "lte-rrc.lateR8NonCriticalExtension",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING", HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_06,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "HandoverFromEUTRAPreparationRequest_v920_IEs", HFILL }},
    { &hf_lte_rrc_concurrPrepCDMA2000_HRPD_r9,
      { "concurrPrepCDMA2000-HRPD-r9", "lte-rrc.concurrPrepCDMA2000_HRPD_r9",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_07,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_05", HFILL }},
    { &hf_lte_rrc_dl_Bandwidth,
      { "dl-Bandwidth", "lte-rrc.dl_Bandwidth",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_dl_Bandwidth_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_phich_Config,
      { "phich-Config", "lte-rrc.phich_Config",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_systemFrameNumber,
      { "systemFrameNumber", "lte-rrc.systemFrameNumber",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_8", HFILL }},
    { &hf_lte_rrc_spare,
      { "spare", "lte-rrc.spare",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_10", HFILL }},
    { &hf_lte_rrc_commonSF_Alloc_r9,
      { "commonSF-Alloc-r9", "lte-rrc.commonSF_Alloc_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "CommonSF_AllocPatternList_r9", HFILL }},
    { &hf_lte_rrc_commonSF_AllocPeriod_r9,
      { "commonSF-AllocPeriod-r9", "lte-rrc.commonSF_AllocPeriod_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_commonSF_AllocPeriod_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_pmch_InfoList_r9,
      { "pmch-InfoList-r9", "lte-rrc.pmch_InfoList_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_08,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_06", HFILL }},
    { &hf_lte_rrc_CommonSF_AllocPatternList_r9_item,
      { "MBSFN-SubframeConfig", "lte-rrc.MBSFN_SubframeConfig",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_criticalExtensions_06,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_06_vals), 0,
        "T_criticalExtensions_06", HFILL }},
    { &hf_lte_rrc_c1_10,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_10_vals), 0,
        "T_c1_10", HFILL }},
    { &hf_lte_rrc_measurementReport_r8,
      { "measurementReport-r8", "lte-rrc.measurementReport_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "MeasurementReport_r8_IEs", HFILL }},
    { &hf_lte_rrc_spare7,
      { "spare7", "lte-rrc.spare7",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_06,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_06", HFILL }},
    { &hf_lte_rrc_measResults,
      { "measResults", "lte-rrc.measResults",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_09,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_07", HFILL }},
    { &hf_lte_rrc_criticalExtensions_07,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_07_vals), 0,
        "T_criticalExtensions_07", HFILL }},
    { &hf_lte_rrc_c1_11,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_11_vals), 0,
        "T_c1_11", HFILL }},
    { &hf_lte_rrc_mobilityFromEUTRACommand_r8,
      { "mobilityFromEUTRACommand-r8", "lte-rrc.mobilityFromEUTRACommand_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "MobilityFromEUTRACommand_r8_IEs", HFILL }},
    { &hf_lte_rrc_mobilityFromEUTRACommand_r9,
      { "mobilityFromEUTRACommand-r9", "lte-rrc.mobilityFromEUTRACommand_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        "MobilityFromEUTRACommand_r9_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_07,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_07", HFILL }},
    { &hf_lte_rrc_cs_FallbackIndicator,
      { "cs-FallbackIndicator", "lte-rrc.cs_FallbackIndicator",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_purpose,
      { "purpose", "lte-rrc.purpose",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_purpose_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_handover,
      { "handover", "lte-rrc.handover",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_cellChangeOrder,
      { "cellChangeOrder", "lte-rrc.cellChangeOrder",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_10,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_08", HFILL }},
    { &hf_lte_rrc_purpose_01,
      { "purpose", "lte-rrc.purpose",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_purpose_01_vals), 0,
        "T_purpose_01", HFILL }},
    { &hf_lte_rrc_e_CSFB_r9,
      { "e-CSFB-r9", "lte-rrc.e_CSFB_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_11,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_09", HFILL }},
    { &hf_lte_rrc_targetRAT_Type,
      { "targetRAT-Type", "lte-rrc.targetRAT_Type",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_targetRAT_Type_vals), 0,
        "T_targetRAT_Type", HFILL }},
    { &hf_lte_rrc_targetRAT_MessageContainer,
      { "targetRAT-MessageContainer", "lte-rrc.targetRAT_MessageContainer",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING", HFILL }},
    { &hf_lte_rrc_nas_SecurityParamFromEUTRA,
      { "nas-SecurityParamFromEUTRA", "lte-rrc.nas_SecurityParamFromEUTRA",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING_SIZE_1", HFILL }},
    { &hf_lte_rrc_systemInformation_01,
      { "systemInformation", "lte-rrc.systemInformation",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_SI_OrPSI_GERAN_vals), 0,
        "SI_OrPSI_GERAN", HFILL }},
    { &hf_lte_rrc_t304,
      { "t304", "lte-rrc.t304",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_t304_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_targetRAT_Type_01,
      { "targetRAT-Type", "lte-rrc.targetRAT_Type",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_targetRAT_Type_01_vals), 0,
        "T_targetRAT_Type_01", HFILL }},
    { &hf_lte_rrc_geran,
      { "geran", "lte-rrc.geran",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_physCellId,
      { "physCellId", "lte-rrc.physCellId",
        FT_NONE, BASE_NONE, NULL, 0,
        "PhysCellIdGERAN", HFILL }},
    { &hf_lte_rrc_carrierFreq,
      { "carrierFreq", "lte-rrc.carrierFreq",
        FT_NONE, BASE_NONE, NULL, 0,
        "CarrierFreqGERAN", HFILL }},
    { &hf_lte_rrc_networkControlOrder,
      { "networkControlOrder", "lte-rrc.networkControlOrder",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_2", HFILL }},
    { &hf_lte_rrc_si,
      { "si", "lte-rrc.si",
        FT_UINT32, BASE_DEC, NULL, 0,
        "SystemInfoListGERAN", HFILL }},
    { &hf_lte_rrc_psi,
      { "psi", "lte-rrc.psi",
        FT_UINT32, BASE_DEC, NULL, 0,
        "SystemInfoListGERAN", HFILL }},
    { &hf_lte_rrc_messageContCDMA2000_1XRTT_r9,
      { "messageContCDMA2000-1XRTT-r9", "lte-rrc.messageContCDMA2000_1XRTT_r9",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING", HFILL }},
    { &hf_lte_rrc_mobilityCDMA2000_HRPD_r9,
      { "mobilityCDMA2000-HRPD-r9", "lte-rrc.mobilityCDMA2000_HRPD_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_mobilityCDMA2000_HRPD_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_messageContCDMA2000_HRPD_r9,
      { "messageContCDMA2000-HRPD-r9", "lte-rrc.messageContCDMA2000_HRPD_r9",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING", HFILL }},
    { &hf_lte_rrc_redirectCarrierCDMA2000_HRPD_r9,
      { "redirectCarrierCDMA2000-HRPD-r9", "lte-rrc.redirectCarrierCDMA2000_HRPD_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        "CarrierFreqCDMA2000", HFILL }},
    { &hf_lte_rrc_pagingRecordList,
      { "pagingRecordList", "lte-rrc.pagingRecordList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_systemInfoModification,
      { "systemInfoModification", "lte-rrc.systemInfoModification",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_systemInfoModification_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_etws_Indication,
      { "etws-Indication", "lte-rrc.etws_Indication",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_etws_Indication_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_12,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "Paging_v890_IEs", HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_13,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "Paging_v920_IEs", HFILL }},
    { &hf_lte_rrc_cmas_Indication_r9,
      { "cmas-Indication-r9", "lte-rrc.cmas_Indication_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_cmas_Indication_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_14,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_10", HFILL }},
    { &hf_lte_rrc_PagingRecordList_item,
      { "PagingRecord", "lte-rrc.PagingRecord",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ue_Identity,
      { "ue-Identity", "lte-rrc.ue_Identity",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_PagingUE_Identity_vals), 0,
        "PagingUE_Identity", HFILL }},
    { &hf_lte_rrc_cn_Domain,
      { "cn-Domain", "lte-rrc.cn_Domain",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_cn_Domain_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_s_TMSI,
      { "s-TMSI", "lte-rrc.s_TMSI",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_imsi,
      { "imsi", "lte-rrc.imsi",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_IMSI_item,
      { "IMSI-Digit", "lte-rrc.IMSI_Digit",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_criticalExtensions_08,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_08_vals), 0,
        "T_criticalExtensions_08", HFILL }},
    { &hf_lte_rrc_c1_12,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_12_vals), 0,
        "T_c1_12", HFILL }},
    { &hf_lte_rrc_proximityIndication_r9_01,
      { "proximityIndication-r9", "lte-rrc.proximityIndication_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        "ProximityIndication_r9_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_08,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_08", HFILL }},
    { &hf_lte_rrc_type_r9,
      { "type-r9", "lte-rrc.type_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_type_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_carrierFreq_r9,
      { "carrierFreq-r9", "lte-rrc.carrierFreq_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_carrierFreq_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_eutra_r9,
      { "eutra-r9", "lte-rrc.eutra_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ARFCN_ValueEUTRA", HFILL }},
    { &hf_lte_rrc_utra_r9,
      { "utra-r9", "lte-rrc.utra_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ARFCN_ValueUTRA", HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_15,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_11", HFILL }},
    { &hf_lte_rrc_criticalExtensions_09,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_09_vals), 0,
        "T_criticalExtensions_09", HFILL }},
    { &hf_lte_rrc_c1_13,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_13_vals), 0,
        "T_c1_13", HFILL }},
    { &hf_lte_rrc_rrcConnectionReconfiguration_r8,
      { "rrcConnectionReconfiguration-r8", "lte-rrc.rrcConnectionReconfiguration_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "RRCConnectionReconfiguration_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_09,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_09", HFILL }},
    { &hf_lte_rrc_measConfig,
      { "measConfig", "lte-rrc.measConfig",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_mobilityControlInfo,
      { "mobilityControlInfo", "lte-rrc.mobilityControlInfo",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_dedicatedInfoNASList,
      { "dedicatedInfoNASList", "lte-rrc.dedicatedInfoNASList",
        FT_UINT32, BASE_DEC, NULL, 0,
        "SEQUENCE_SIZE_1_maxDRB_OF_DedicatedInfoNAS", HFILL }},
    { &hf_lte_rrc_dedicatedInfoNASList_item,
      { "DedicatedInfoNAS", "lte-rrc.DedicatedInfoNAS",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_radioResourceConfigDedicated,
      { "radioResourceConfigDedicated", "lte-rrc.radioResourceConfigDedicated",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_securityConfigHO,
      { "securityConfigHO", "lte-rrc.securityConfigHO",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_16,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "RRCConnectionReconfiguration_v890_IEs", HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_17,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "RRCConnectionReconfiguration_v920_IEs", HFILL }},
    { &hf_lte_rrc_otherConfig_r9,
      { "otherConfig-r9", "lte-rrc.otherConfig_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_fullConfig_r9,
      { "fullConfig-r9", "lte-rrc.fullConfig_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_fullConfig_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_18,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_12", HFILL }},
    { &hf_lte_rrc_handoverType,
      { "handoverType", "lte-rrc.handoverType",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_handoverType_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_intraLTE,
      { "intraLTE", "lte-rrc.intraLTE",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_securityAlgorithmConfig,
      { "securityAlgorithmConfig", "lte-rrc.securityAlgorithmConfig",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_keyChangeIndicator,
      { "keyChangeIndicator", "lte-rrc.keyChangeIndicator",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_nextHopChainingCount,
      { "nextHopChainingCount", "lte-rrc.nextHopChainingCount",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_interRAT,
      { "interRAT", "lte-rrc.interRAT",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nas_SecurityParamToEUTRA,
      { "nas-SecurityParamToEUTRA", "lte-rrc.nas_SecurityParamToEUTRA",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING_SIZE_6", HFILL }},
    { &hf_lte_rrc_criticalExtensions_10,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_10_vals), 0,
        "T_criticalExtensions_10", HFILL }},
    { &hf_lte_rrc_rrcConnectionReconfigurationComplete_r8,
      { "rrcConnectionReconfigurationComplete-r8", "lte-rrc.rrcConnectionReconfigurationComplete_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "RRCConnectionReconfigurationComplete_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_10,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_10", HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_19,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_13", HFILL }},
    { &hf_lte_rrc_criticalExtensions_11,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_11_vals), 0,
        "T_criticalExtensions_11", HFILL }},
    { &hf_lte_rrc_c1_14,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_14_vals), 0,
        "T_c1_14", HFILL }},
    { &hf_lte_rrc_rrcConnectionReestablishment_r8,
      { "rrcConnectionReestablishment-r8", "lte-rrc.rrcConnectionReestablishment_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "RRCConnectionReestablishment_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_11,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_11", HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_20,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_14", HFILL }},
    { &hf_lte_rrc_criticalExtensions_12,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_12_vals), 0,
        "T_criticalExtensions_12", HFILL }},
    { &hf_lte_rrc_rrcConnectionReestablishmentComplete_r8,
      { "rrcConnectionReestablishmentComplete-r8", "lte-rrc.rrcConnectionReestablishmentComplete_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "RRCConnectionReestablishmentComplete_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_12,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_12", HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_21,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "RRCConnectionReestablishmentComplete_v920_IEs", HFILL }},
    { &hf_lte_rrc_rlf_InfoAvailable_r9,
      { "rlf-InfoAvailable-r9", "lte-rrc.rlf_InfoAvailable_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_rlf_InfoAvailable_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_22,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_15", HFILL }},
    { &hf_lte_rrc_criticalExtensions_13,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_13_vals), 0,
        "T_criticalExtensions_13", HFILL }},
    { &hf_lte_rrc_rrcConnectionReestablishmentReject_r8,
      { "rrcConnectionReestablishmentReject-r8", "lte-rrc.rrcConnectionReestablishmentReject_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "RRCConnectionReestablishmentReject_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_13,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_13", HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_23,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_16", HFILL }},
    { &hf_lte_rrc_criticalExtensions_14,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_14_vals), 0,
        "T_criticalExtensions_14", HFILL }},
    { &hf_lte_rrc_rrcConnectionReestablishmentRequest_r8,
      { "rrcConnectionReestablishmentRequest-r8", "lte-rrc.rrcConnectionReestablishmentRequest_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "RRCConnectionReestablishmentRequest_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_14,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_14", HFILL }},
    { &hf_lte_rrc_ue_Identity_01,
      { "ue-Identity", "lte-rrc.ue_Identity",
        FT_NONE, BASE_NONE, NULL, 0,
        "ReestabUE_Identity", HFILL }},
    { &hf_lte_rrc_reestablishmentCause,
      { "reestablishmentCause", "lte-rrc.reestablishmentCause",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_ReestablishmentCause_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_spare_01,
      { "spare", "lte-rrc.spare",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_2", HFILL }},
    { &hf_lte_rrc_c_RNTI,
      { "c-RNTI", "lte-rrc.c_RNTI",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_physCellId_01,
      { "physCellId", "lte-rrc.physCellId",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_shortMAC_I,
      { "shortMAC-I", "lte-rrc.shortMAC_I",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_criticalExtensions_15,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_15_vals), 0,
        "T_criticalExtensions_15", HFILL }},
    { &hf_lte_rrc_c1_15,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_15_vals), 0,
        "T_c1_15", HFILL }},
    { &hf_lte_rrc_rrcConnectionReject_r8,
      { "rrcConnectionReject-r8", "lte-rrc.rrcConnectionReject_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "RRCConnectionReject_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_15,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_15", HFILL }},
    { &hf_lte_rrc_waitTime,
      { "waitTime", "lte-rrc.waitTime",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_16", HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_24,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_17", HFILL }},
    { &hf_lte_rrc_criticalExtensions_16,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_16_vals), 0,
        "T_criticalExtensions_16", HFILL }},
    { &hf_lte_rrc_c1_16,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_16_vals), 0,
        "T_c1_16", HFILL }},
    { &hf_lte_rrc_rrcConnectionRelease_r8,
      { "rrcConnectionRelease-r8", "lte-rrc.rrcConnectionRelease_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "RRCConnectionRelease_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_16,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_16", HFILL }},
    { &hf_lte_rrc_releaseCause,
      { "releaseCause", "lte-rrc.releaseCause",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_ReleaseCause_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_redirectedCarrierInfo,
      { "redirectedCarrierInfo", "lte-rrc.redirectedCarrierInfo",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_RedirectedCarrierInfo_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_idleModeMobilityControlInfo,
      { "idleModeMobilityControlInfo", "lte-rrc.idleModeMobilityControlInfo",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_25,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "RRCConnectionRelease_v890_IEs", HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_26,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "RRCConnectionRelease_v920_IEs", HFILL }},
    { &hf_lte_rrc_cellInfoList_r9,
      { "cellInfoList-r9", "lte-rrc.cellInfoList_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_cellInfoList_r9_vals), 0,
        "T_cellInfoList_r9", HFILL }},
    { &hf_lte_rrc_geran_r9,
      { "geran-r9", "lte-rrc.geran_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "CellInfoListGERAN_r9", HFILL }},
    { &hf_lte_rrc_utra_FDD_r9,
      { "utra-FDD-r9", "lte-rrc.utra_FDD_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "CellInfoListUTRA_FDD_r9", HFILL }},
    { &hf_lte_rrc_utra_TDD_r9,
      { "utra-TDD-r9", "lte-rrc.utra_TDD_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "CellInfoListUTRA_TDD_r9", HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_27,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_18", HFILL }},
    { &hf_lte_rrc_eutra,
      { "eutra", "lte-rrc.eutra",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ARFCN_ValueEUTRA", HFILL }},
    { &hf_lte_rrc_geran_01,
      { "geran", "lte-rrc.geran",
        FT_NONE, BASE_NONE, NULL, 0,
        "CarrierFreqsGERAN", HFILL }},
    { &hf_lte_rrc_utra_FDD,
      { "utra-FDD", "lte-rrc.utra_FDD",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ARFCN_ValueUTRA", HFILL }},
    { &hf_lte_rrc_utra_TDD,
      { "utra-TDD", "lte-rrc.utra_TDD",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ARFCN_ValueUTRA", HFILL }},
    { &hf_lte_rrc_cdma2000_HRPD,
      { "cdma2000-HRPD", "lte-rrc.cdma2000_HRPD",
        FT_NONE, BASE_NONE, NULL, 0,
        "CarrierFreqCDMA2000", HFILL }},
    { &hf_lte_rrc_cdma2000_1xRTT,
      { "cdma2000-1xRTT", "lte-rrc.cdma2000_1xRTT",
        FT_NONE, BASE_NONE, NULL, 0,
        "CarrierFreqCDMA2000", HFILL }},
    { &hf_lte_rrc_freqPriorityListEUTRA,
      { "freqPriorityListEUTRA", "lte-rrc.freqPriorityListEUTRA",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_freqPriorityListGERAN,
      { "freqPriorityListGERAN", "lte-rrc.freqPriorityListGERAN",
        FT_UINT32, BASE_DEC, NULL, 0,
        "FreqsPriorityListGERAN", HFILL }},
    { &hf_lte_rrc_freqPriorityListUTRA_FDD,
      { "freqPriorityListUTRA-FDD", "lte-rrc.freqPriorityListUTRA_FDD",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_freqPriorityListUTRA_TDD,
      { "freqPriorityListUTRA-TDD", "lte-rrc.freqPriorityListUTRA_TDD",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_bandClassPriorityListHRPD,
      { "bandClassPriorityListHRPD", "lte-rrc.bandClassPriorityListHRPD",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_bandClassPriorityList1XRTT,
      { "bandClassPriorityList1XRTT", "lte-rrc.bandClassPriorityList1XRTT",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_t320,
      { "t320", "lte-rrc.t320",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_t320_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_FreqPriorityListEUTRA_item,
      { "FreqPriorityEUTRA", "lte-rrc.FreqPriorityEUTRA",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_carrierFreq_01,
      { "carrierFreq", "lte-rrc.carrierFreq",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ARFCN_ValueEUTRA", HFILL }},
    { &hf_lte_rrc_cellReselectionPriority,
      { "cellReselectionPriority", "lte-rrc.cellReselectionPriority",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_FreqsPriorityListGERAN_item,
      { "FreqsPriorityGERAN", "lte-rrc.FreqsPriorityGERAN",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_carrierFreqs,
      { "carrierFreqs", "lte-rrc.carrierFreqs",
        FT_NONE, BASE_NONE, NULL, 0,
        "CarrierFreqsGERAN", HFILL }},
    { &hf_lte_rrc_FreqPriorityListUTRA_FDD_item,
      { "FreqPriorityUTRA-FDD", "lte-rrc.FreqPriorityUTRA_FDD",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_carrierFreq_02,
      { "carrierFreq", "lte-rrc.carrierFreq",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ARFCN_ValueUTRA", HFILL }},
    { &hf_lte_rrc_FreqPriorityListUTRA_TDD_item,
      { "FreqPriorityUTRA-TDD", "lte-rrc.FreqPriorityUTRA_TDD",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_BandClassPriorityListHRPD_item,
      { "BandClassPriorityHRPD", "lte-rrc.BandClassPriorityHRPD",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_bandClass,
      { "bandClass", "lte-rrc.bandClass",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_BandclassCDMA2000_vals), 0,
        "BandclassCDMA2000", HFILL }},
    { &hf_lte_rrc_BandClassPriorityList1XRTT_item,
      { "BandClassPriority1XRTT", "lte-rrc.BandClassPriority1XRTT",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_CellInfoListGERAN_r9_item,
      { "CellInfoGERAN-r9", "lte-rrc.CellInfoGERAN_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_physCellId_r9,
      { "physCellId-r9", "lte-rrc.physCellId_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        "PhysCellIdGERAN", HFILL }},
    { &hf_lte_rrc_carrierFreq_r9_01,
      { "carrierFreq-r9", "lte-rrc.carrierFreq_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        "CarrierFreqGERAN", HFILL }},
    { &hf_lte_rrc_systemInformation_r9,
      { "systemInformation-r9", "lte-rrc.systemInformation_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "SystemInfoListGERAN", HFILL }},
    { &hf_lte_rrc_CellInfoListUTRA_FDD_r9_item,
      { "CellInfoUTRA-FDD-r9", "lte-rrc.CellInfoUTRA_FDD_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_physCellId_r9_01,
      { "physCellId-r9", "lte-rrc.physCellId_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "PhysCellIdUTRA_FDD", HFILL }},
    { &hf_lte_rrc_utra_BCCH_Container_r9,
      { "utra-BCCH-Container-r9", "lte-rrc.utra_BCCH_Container_r9",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING", HFILL }},
    { &hf_lte_rrc_CellInfoListUTRA_TDD_r9_item,
      { "CellInfoUTRA-TDD-r9", "lte-rrc.CellInfoUTRA_TDD_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_physCellId_r9_02,
      { "physCellId-r9", "lte-rrc.physCellId_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "PhysCellIdUTRA_TDD", HFILL }},
    { &hf_lte_rrc_criticalExtensions_17,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_17_vals), 0,
        "T_criticalExtensions_17", HFILL }},
    { &hf_lte_rrc_rrcConnectionRequest_r8,
      { "rrcConnectionRequest-r8", "lte-rrc.rrcConnectionRequest_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "RRCConnectionRequest_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_17,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_17", HFILL }},
    { &hf_lte_rrc_ue_Identity_02,
      { "ue-Identity", "lte-rrc.ue_Identity",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_InitialUE_Identity_vals), 0,
        "InitialUE_Identity", HFILL }},
    { &hf_lte_rrc_establishmentCause,
      { "establishmentCause", "lte-rrc.establishmentCause",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_EstablishmentCause_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_spare_02,
      { "spare", "lte-rrc.spare",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_1", HFILL }},
    { &hf_lte_rrc_randomValue,
      { "randomValue", "lte-rrc.randomValue",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_40", HFILL }},
    { &hf_lte_rrc_criticalExtensions_18,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_18_vals), 0,
        "T_criticalExtensions_18", HFILL }},
    { &hf_lte_rrc_c1_17,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_17_vals), 0,
        "T_c1_17", HFILL }},
    { &hf_lte_rrc_rrcConnectionSetup_r8,
      { "rrcConnectionSetup-r8", "lte-rrc.rrcConnectionSetup_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "RRCConnectionSetup_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_18,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_18", HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_28,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_19", HFILL }},
    { &hf_lte_rrc_criticalExtensions_19,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_19_vals), 0,
        "T_criticalExtensions_19", HFILL }},
    { &hf_lte_rrc_c1_18,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_18_vals), 0,
        "T_c1_18", HFILL }},
    { &hf_lte_rrc_rrcConnectionSetupComplete_r8,
      { "rrcConnectionSetupComplete-r8", "lte-rrc.rrcConnectionSetupComplete_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "RRCConnectionSetupComplete_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_19,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_19", HFILL }},
    { &hf_lte_rrc_selectedPLMN_Identity,
      { "selectedPLMN-Identity", "lte-rrc.selectedPLMN_Identity",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_6", HFILL }},
    { &hf_lte_rrc_registeredMME,
      { "registeredMME", "lte-rrc.registeredMME",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_29,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_20", HFILL }},
    { &hf_lte_rrc_plmn_Identity,
      { "plmn-Identity", "lte-rrc.plmn_Identity",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_mmegi,
      { "mmegi", "lte-rrc.mmegi",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_16", HFILL }},
    { &hf_lte_rrc_mmec,
      { "mmec", "lte-rrc.mmec",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_criticalExtensions_20,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_20_vals), 0,
        "T_criticalExtensions_20", HFILL }},
    { &hf_lte_rrc_c1_19,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_19_vals), 0,
        "T_c1_19", HFILL }},
    { &hf_lte_rrc_securityModeCommand_r8,
      { "securityModeCommand-r8", "lte-rrc.securityModeCommand_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "SecurityModeCommand_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_20,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_20", HFILL }},
    { &hf_lte_rrc_securityConfigSMC,
      { "securityConfigSMC", "lte-rrc.securityConfigSMC",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_30,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_21", HFILL }},
    { &hf_lte_rrc_criticalExtensions_21,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_21_vals), 0,
        "T_criticalExtensions_21", HFILL }},
    { &hf_lte_rrc_securityModeComplete_r8,
      { "securityModeComplete-r8", "lte-rrc.securityModeComplete_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "SecurityModeComplete_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_21,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_21", HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_31,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_22", HFILL }},
    { &hf_lte_rrc_criticalExtensions_22,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_22_vals), 0,
        "T_criticalExtensions_22", HFILL }},
    { &hf_lte_rrc_securityModeFailure_r8,
      { "securityModeFailure-r8", "lte-rrc.securityModeFailure_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "SecurityModeFailure_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_22,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_22", HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_32,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_23", HFILL }},
    { &hf_lte_rrc_criticalExtensions_23,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_23_vals), 0,
        "T_criticalExtensions_23", HFILL }},
    { &hf_lte_rrc_systemInformation_r8,
      { "systemInformation-r8", "lte-rrc.systemInformation_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "SystemInformation_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_23,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_23", HFILL }},
    { &hf_lte_rrc_sib_TypeAndInfo,
      { "sib-TypeAndInfo", "lte-rrc.sib_TypeAndInfo",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_sib_TypeAndInfo_item,
      { "sib-TypeAndInfo item", "lte-rrc.sib_TypeAndInfo_item",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_sib_TypeAndInfo_item_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_sib2,
      { "sib2", "lte-rrc.sib2",
        FT_NONE, BASE_NONE, NULL, 0,
        "SystemInformationBlockType2", HFILL }},
    { &hf_lte_rrc_sib3,
      { "sib3", "lte-rrc.sib3",
        FT_NONE, BASE_NONE, NULL, 0,
        "SystemInformationBlockType3", HFILL }},
    { &hf_lte_rrc_sib4,
      { "sib4", "lte-rrc.sib4",
        FT_NONE, BASE_NONE, NULL, 0,
        "SystemInformationBlockType4", HFILL }},
    { &hf_lte_rrc_sib5,
      { "sib5", "lte-rrc.sib5",
        FT_NONE, BASE_NONE, NULL, 0,
        "SystemInformationBlockType5", HFILL }},
    { &hf_lte_rrc_sib6,
      { "sib6", "lte-rrc.sib6",
        FT_NONE, BASE_NONE, NULL, 0,
        "SystemInformationBlockType6", HFILL }},
    { &hf_lte_rrc_sib7,
      { "sib7", "lte-rrc.sib7",
        FT_NONE, BASE_NONE, NULL, 0,
        "SystemInformationBlockType7", HFILL }},
    { &hf_lte_rrc_sib8,
      { "sib8", "lte-rrc.sib8",
        FT_NONE, BASE_NONE, NULL, 0,
        "SystemInformationBlockType8", HFILL }},
    { &hf_lte_rrc_sib9,
      { "sib9", "lte-rrc.sib9",
        FT_NONE, BASE_NONE, NULL, 0,
        "SystemInformationBlockType9", HFILL }},
    { &hf_lte_rrc_sib10,
      { "sib10", "lte-rrc.sib10",
        FT_NONE, BASE_NONE, NULL, 0,
        "SystemInformationBlockType10", HFILL }},
    { &hf_lte_rrc_sib11,
      { "sib11", "lte-rrc.sib11",
        FT_NONE, BASE_NONE, NULL, 0,
        "SystemInformationBlockType11", HFILL }},
    { &hf_lte_rrc_sib12_v920,
      { "sib12-v920", "lte-rrc.sib12_v920",
        FT_NONE, BASE_NONE, NULL, 0,
        "SystemInformationBlockType12_r9", HFILL }},
    { &hf_lte_rrc_sib13_v920,
      { "sib13-v920", "lte-rrc.sib13_v920",
        FT_NONE, BASE_NONE, NULL, 0,
        "SystemInformationBlockType13_r9", HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_33,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_24", HFILL }},
    { &hf_lte_rrc_cellAccessRelatedInfo,
      { "cellAccessRelatedInfo", "lte-rrc.cellAccessRelatedInfo",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_plmn_IdentityList,
      { "plmn-IdentityList", "lte-rrc.plmn_IdentityList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_trackingAreaCode,
      { "trackingAreaCode", "lte-rrc.trackingAreaCode",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_cellIdentity,
      { "cellIdentity", "lte-rrc.cellIdentity",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_cellBarred,
      { "cellBarred", "lte-rrc.cellBarred",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_cellBarred_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_intraFreqReselection,
      { "intraFreqReselection", "lte-rrc.intraFreqReselection",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_intraFreqReselection_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_csg_Indication,
      { "csg-Indication", "lte-rrc.csg_Indication",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_csg_Identity,
      { "csg-Identity", "lte-rrc.csg_Identity",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_cellSelectionInfo,
      { "cellSelectionInfo", "lte-rrc.cellSelectionInfo",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_q_RxLevMin,
      { "q-RxLevMin", "lte-rrc.q_RxLevMin",
        FT_INT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_q_RxLevMinOffset,
      { "q-RxLevMinOffset", "lte-rrc.q_RxLevMinOffset",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_8", HFILL }},
    { &hf_lte_rrc_p_Max,
      { "p-Max", "lte-rrc.p_Max",
        FT_INT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_freqBandIndicator,
      { "freqBandIndicator", "lte-rrc.freqBandIndicator",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_64", HFILL }},
    { &hf_lte_rrc_schedulingInfoList,
      { "schedulingInfoList", "lte-rrc.schedulingInfoList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_tdd_Config,
      { "tdd-Config", "lte-rrc.tdd_Config",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_si_WindowLength,
      { "si-WindowLength", "lte-rrc.si_WindowLength",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_si_WindowLength_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_systemInfoValueTag,
      { "systemInfoValueTag", "lte-rrc.systemInfoValueTag",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_31", HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_34,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "SystemInformationBlockType1_v890_IEs", HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_35,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "SystemInformationBlockType1_v920_IEs", HFILL }},
    { &hf_lte_rrc_ims_EmergencySupport_r9,
      { "ims-EmergencySupport-r9", "lte-rrc.ims_EmergencySupport_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_ims_EmergencySupport_r9_vals), 0,
        "T_ims_EmergencySupport_r9", HFILL }},
    { &hf_lte_rrc_cellSelectionInfo_v920,
      { "cellSelectionInfo-v920", "lte-rrc.cellSelectionInfo_v920",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_36,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_25", HFILL }},
    { &hf_lte_rrc_PLMN_IdentityList_item,
      { "PLMN-IdentityInfo", "lte-rrc.PLMN_IdentityInfo",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_cellReservedForOperatorUse,
      { "cellReservedForOperatorUse", "lte-rrc.cellReservedForOperatorUse",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_cellReservedForOperatorUse_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_SchedulingInfoList_item,
      { "SchedulingInfo", "lte-rrc.SchedulingInfo",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_si_Periodicity,
      { "si-Periodicity", "lte-rrc.si_Periodicity",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_si_Periodicity_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_sib_MappingInfo,
      { "sib-MappingInfo", "lte-rrc.sib_MappingInfo",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_SIB_MappingInfo_item,
      { "SIB-Type", "lte-rrc.SIB_Type",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_SIB_Type_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_q_QualMin_r9,
      { "q-QualMin-r9", "lte-rrc.q_QualMin_r9",
        FT_INT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_q_QualMinOffset_r9,
      { "q-QualMinOffset-r9", "lte-rrc.q_QualMinOffset_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_8", HFILL }},
    { &hf_lte_rrc_criticalExtensions_24,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_24_vals), 0,
        "T_criticalExtensions_24", HFILL }},
    { &hf_lte_rrc_c1_20,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_20_vals), 0,
        "T_c1_20", HFILL }},
    { &hf_lte_rrc_ueCapabilityEnquiry_r8,
      { "ueCapabilityEnquiry-r8", "lte-rrc.ueCapabilityEnquiry_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "UECapabilityEnquiry_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_24,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_24", HFILL }},
    { &hf_lte_rrc_ue_CapabilityRequest,
      { "ue-CapabilityRequest", "lte-rrc.ue_CapabilityRequest",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_37,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_26", HFILL }},
    { &hf_lte_rrc_UE_CapabilityRequest_item,
      { "RAT-Type", "lte-rrc.RAT_Type",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_RAT_Type_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_criticalExtensions_25,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_25_vals), 0,
        "T_criticalExtensions_25", HFILL }},
    { &hf_lte_rrc_c1_21,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_21_vals), 0,
        "T_c1_21", HFILL }},
    { &hf_lte_rrc_ueCapabilityInformation_r8,
      { "ueCapabilityInformation-r8", "lte-rrc.ueCapabilityInformation_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "UECapabilityInformation_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_25,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_25", HFILL }},
    { &hf_lte_rrc_ue_CapabilityRAT_ContainerList,
      { "ue-CapabilityRAT-ContainerList", "lte-rrc.ue_CapabilityRAT_ContainerList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_38,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_27", HFILL }},
    { &hf_lte_rrc_criticalExtensions_26,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_26_vals), 0,
        "T_criticalExtensions_26", HFILL }},
    { &hf_lte_rrc_c1_22,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_22_vals), 0,
        "T_c1_22", HFILL }},
    { &hf_lte_rrc_ueInformationRequest_r9_01,
      { "ueInformationRequest-r9", "lte-rrc.ueInformationRequest_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        "UEInformationRequest_r9_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_26,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_26", HFILL }},
    { &hf_lte_rrc_rach_ReportReq_r9,
      { "rach-ReportReq-r9", "lte-rrc.rach_ReportReq_r9",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_rlf_ReportReq_r9,
      { "rlf-ReportReq-r9", "lte-rrc.rlf_ReportReq_r9",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_39,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_28", HFILL }},
    { &hf_lte_rrc_criticalExtensions_27,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_27_vals), 0,
        "T_criticalExtensions_27", HFILL }},
    { &hf_lte_rrc_c1_23,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_23_vals), 0,
        "T_c1_23", HFILL }},
    { &hf_lte_rrc_ueInformationResponse_r9_01,
      { "ueInformationResponse-r9", "lte-rrc.ueInformationResponse_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        "UEInformationResponse_r9_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_27,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_27", HFILL }},
    { &hf_lte_rrc_rach_Report_r9,
      { "rach-Report-r9", "lte-rrc.rach_Report_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_rach_Report_r9", HFILL }},
    { &hf_lte_rrc_numberOfPreamblesSent_r9,
      { "numberOfPreamblesSent-r9", "lte-rrc.numberOfPreamblesSent_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_200", HFILL }},
    { &hf_lte_rrc_contentionDetected_r9,
      { "contentionDetected-r9", "lte-rrc.contentionDetected_r9",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_rlfReport_r9,
      { "rlfReport-r9", "lte-rrc.rlfReport_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        "RLF_Report_r9", HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_40,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_29", HFILL }},
    { &hf_lte_rrc_measResultLastServCell,
      { "measResultLastServCell", "lte-rrc.measResultLastServCell",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_rsrpResult,
      { "rsrpResult", "lte-rrc.rsrpResult",
        FT_UINT32, BASE_DEC, NULL, 0,
        "RSRP_Range", HFILL }},
    { &hf_lte_rrc_rsrqResult,
      { "rsrqResult", "lte-rrc.rsrqResult",
        FT_UINT32, BASE_DEC, NULL, 0,
        "RSRQ_Range", HFILL }},
    { &hf_lte_rrc_measResultNeighCells,
      { "measResultNeighCells", "lte-rrc.measResultNeighCells",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_measResultListEUTRA,
      { "measResultListEUTRA", "lte-rrc.measResultListEUTRA",
        FT_UINT32, BASE_DEC, NULL, 0,
        "MeasResultList2EUTRA", HFILL }},
    { &hf_lte_rrc_measResultListUTRA,
      { "measResultListUTRA", "lte-rrc.measResultListUTRA",
        FT_UINT32, BASE_DEC, NULL, 0,
        "MeasResultList2UTRA", HFILL }},
    { &hf_lte_rrc_measResultListGERAN,
      { "measResultListGERAN", "lte-rrc.measResultListGERAN",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_measResultsCDMA2000,
      { "measResultsCDMA2000", "lte-rrc.measResultsCDMA2000",
        FT_UINT32, BASE_DEC, NULL, 0,
        "MeasResultList2CDMA2000", HFILL }},
    { &hf_lte_rrc_MeasResultList2EUTRA_item,
      { "MeasResultList2EUTRA item", "lte-rrc.MeasResultList2EUTRA_item",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_measResultList,
      { "measResultList", "lte-rrc.measResultList",
        FT_UINT32, BASE_DEC, NULL, 0,
        "MeasResultListEUTRA", HFILL }},
    { &hf_lte_rrc_MeasResultList2UTRA_item,
      { "MeasResultList2UTRA item", "lte-rrc.MeasResultList2UTRA_item",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_measResultList_01,
      { "measResultList", "lte-rrc.measResultList",
        FT_UINT32, BASE_DEC, NULL, 0,
        "MeasResultListUTRA", HFILL }},
    { &hf_lte_rrc_MeasResultList2CDMA2000_item,
      { "MeasResultList2CDMA2000 item", "lte-rrc.MeasResultList2CDMA2000_item",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_carrierFreq_03,
      { "carrierFreq", "lte-rrc.carrierFreq",
        FT_NONE, BASE_NONE, NULL, 0,
        "CarrierFreqCDMA2000", HFILL }},
    { &hf_lte_rrc_measResultList_02,
      { "measResultList", "lte-rrc.measResultList",
        FT_NONE, BASE_NONE, NULL, 0,
        "MeasResultsCDMA2000", HFILL }},
    { &hf_lte_rrc_criticalExtensions_28,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_28_vals), 0,
        "T_criticalExtensions_28", HFILL }},
    { &hf_lte_rrc_c1_24,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_24_vals), 0,
        "T_c1_24", HFILL }},
    { &hf_lte_rrc_ulHandoverPreparationTransfer_r8,
      { "ulHandoverPreparationTransfer-r8", "lte-rrc.ulHandoverPreparationTransfer_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "ULHandoverPreparationTransfer_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_28,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_28", HFILL }},
    { &hf_lte_rrc_meid,
      { "meid", "lte-rrc.meid",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_56", HFILL }},
    { &hf_lte_rrc_dedicatedInfo,
      { "dedicatedInfo", "lte-rrc.dedicatedInfo",
        FT_BYTES, BASE_NONE, NULL, 0,
        "DedicatedInfoCDMA2000", HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_41,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_30", HFILL }},
    { &hf_lte_rrc_criticalExtensions_29,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_29_vals), 0,
        "T_criticalExtensions_29", HFILL }},
    { &hf_lte_rrc_c1_25,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_25_vals), 0,
        "T_c1_25", HFILL }},
    { &hf_lte_rrc_ulInformationTransfer_r8,
      { "ulInformationTransfer-r8", "lte-rrc.ulInformationTransfer_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "ULInformationTransfer_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_29,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_29", HFILL }},
    { &hf_lte_rrc_dedicatedInfoType_01,
      { "dedicatedInfoType", "lte-rrc.dedicatedInfoType",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_dedicatedInfoType_01_vals), 0,
        "T_dedicatedInfoType_01", HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_42,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_31", HFILL }},
    { &hf_lte_rrc_ac_BarringInfo,
      { "ac-BarringInfo", "lte-rrc.ac_BarringInfo",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ac_BarringForEmergency,
      { "ac-BarringForEmergency", "lte-rrc.ac_BarringForEmergency",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_ac_BarringForMO_Signalling,
      { "ac-BarringForMO-Signalling", "lte-rrc.ac_BarringForMO_Signalling",
        FT_NONE, BASE_NONE, NULL, 0,
        "AC_BarringConfig", HFILL }},
    { &hf_lte_rrc_ac_BarringForMO_Data,
      { "ac-BarringForMO-Data", "lte-rrc.ac_BarringForMO_Data",
        FT_NONE, BASE_NONE, NULL, 0,
        "AC_BarringConfig", HFILL }},
    { &hf_lte_rrc_radioResourceConfigCommon,
      { "radioResourceConfigCommon", "lte-rrc.radioResourceConfigCommon",
        FT_NONE, BASE_NONE, NULL, 0,
        "RadioResourceConfigCommonSIB", HFILL }},
    { &hf_lte_rrc_ue_TimersAndConstants,
      { "ue-TimersAndConstants", "lte-rrc.ue_TimersAndConstants",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_freqInfo,
      { "freqInfo", "lte-rrc.freqInfo",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ul_CarrierFreq,
      { "ul-CarrierFreq", "lte-rrc.ul_CarrierFreq",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ARFCN_ValueEUTRA", HFILL }},
    { &hf_lte_rrc_ul_Bandwidth,
      { "ul-Bandwidth", "lte-rrc.ul_Bandwidth",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_ul_Bandwidth_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_additionalSpectrumEmission,
      { "additionalSpectrumEmission", "lte-rrc.additionalSpectrumEmission",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_mbsfn_SubframeConfigList,
      { "mbsfn-SubframeConfigList", "lte-rrc.mbsfn_SubframeConfigList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_timeAlignmentTimerCommon,
      { "timeAlignmentTimerCommon", "lte-rrc.timeAlignmentTimerCommon",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_TimeAlignmentTimer_vals), 0,
        "TimeAlignmentTimer", HFILL }},
    { &hf_lte_rrc_ssac_BarringForMMTEL_Voice_r9,
      { "ssac-BarringForMMTEL-Voice-r9", "lte-rrc.ssac_BarringForMMTEL_Voice_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        "AC_BarringConfig", HFILL }},
    { &hf_lte_rrc_ssac_BarringForMMTEL_Video_r9,
      { "ssac-BarringForMMTEL-Video-r9", "lte-rrc.ssac_BarringForMMTEL_Video_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        "AC_BarringConfig", HFILL }},
    { &hf_lte_rrc_ac_BarringFactor,
      { "ac-BarringFactor", "lte-rrc.ac_BarringFactor",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_ac_BarringFactor_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ac_BarringTime,
      { "ac-BarringTime", "lte-rrc.ac_BarringTime",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_ac_BarringTime_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ac_BarringForSpecialAC,
      { "ac-BarringForSpecialAC", "lte-rrc.ac_BarringForSpecialAC",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_5", HFILL }},
    { &hf_lte_rrc_MBSFN_SubframeConfigList_item,
      { "MBSFN-SubframeConfig", "lte-rrc.MBSFN_SubframeConfig",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_cellReselectionInfoCommon,
      { "cellReselectionInfoCommon", "lte-rrc.cellReselectionInfoCommon",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_q_Hyst,
      { "q-Hyst", "lte-rrc.q_Hyst",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_q_Hyst_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_speedStateReselectionPars,
      { "speedStateReselectionPars", "lte-rrc.speedStateReselectionPars",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_mobilityStateParameters,
      { "mobilityStateParameters", "lte-rrc.mobilityStateParameters",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_q_HystSF,
      { "q-HystSF", "lte-rrc.q_HystSF",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_sf_Medium,
      { "sf-Medium", "lte-rrc.sf_Medium",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_sf_Medium_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_sf_High,
      { "sf-High", "lte-rrc.sf_High",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_sf_High_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_cellReselectionServingFreqInfo,
      { "cellReselectionServingFreqInfo", "lte-rrc.cellReselectionServingFreqInfo",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_s_NonIntraSearch,
      { "s-NonIntraSearch", "lte-rrc.s_NonIntraSearch",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ReselectionThreshold", HFILL }},
    { &hf_lte_rrc_threshServingLow,
      { "threshServingLow", "lte-rrc.threshServingLow",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ReselectionThreshold", HFILL }},
    { &hf_lte_rrc_intraFreqCellReselectionInfo,
      { "intraFreqCellReselectionInfo", "lte-rrc.intraFreqCellReselectionInfo",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_s_IntraSearch,
      { "s-IntraSearch", "lte-rrc.s_IntraSearch",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ReselectionThreshold", HFILL }},
    { &hf_lte_rrc_allowedMeasBandwidth,
      { "allowedMeasBandwidth", "lte-rrc.allowedMeasBandwidth",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_AllowedMeasBandwidth_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_presenceAntennaPort1,
      { "presenceAntennaPort1", "lte-rrc.presenceAntennaPort1",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_neighCellConfig,
      { "neighCellConfig", "lte-rrc.neighCellConfig",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_t_ReselectionEUTRA,
      { "t-ReselectionEUTRA", "lte-rrc.t_ReselectionEUTRA",
        FT_UINT32, BASE_DEC, NULL, 0,
        "T_Reselection", HFILL }},
    { &hf_lte_rrc_t_ReselectionEUTRA_SF,
      { "t-ReselectionEUTRA-SF", "lte-rrc.t_ReselectionEUTRA_SF",
        FT_NONE, BASE_NONE, NULL, 0,
        "SpeedStateScaleFactors", HFILL }},
    { &hf_lte_rrc_s_IntraSearch_v920,
      { "s-IntraSearch-v920", "lte-rrc.s_IntraSearch_v920",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_s_IntraSearchP_r9,
      { "s-IntraSearchP-r9", "lte-rrc.s_IntraSearchP_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ReselectionThreshold", HFILL }},
    { &hf_lte_rrc_s_IntraSearchQ_r9,
      { "s-IntraSearchQ-r9", "lte-rrc.s_IntraSearchQ_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ReselectionThresholdQ_r9", HFILL }},
    { &hf_lte_rrc_s_NonIntraSearch_v920,
      { "s-NonIntraSearch-v920", "lte-rrc.s_NonIntraSearch_v920",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_s_NonIntraSearchP_r9,
      { "s-NonIntraSearchP-r9", "lte-rrc.s_NonIntraSearchP_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ReselectionThreshold", HFILL }},
    { &hf_lte_rrc_s_NonIntraSearchQ_r9,
      { "s-NonIntraSearchQ-r9", "lte-rrc.s_NonIntraSearchQ_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ReselectionThresholdQ_r9", HFILL }},
    { &hf_lte_rrc_threshServingLowQ_r9,
      { "threshServingLowQ-r9", "lte-rrc.threshServingLowQ_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ReselectionThresholdQ_r9", HFILL }},
    { &hf_lte_rrc_intraFreqNeighCellList,
      { "intraFreqNeighCellList", "lte-rrc.intraFreqNeighCellList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_intraFreqBlackCellList,
      { "intraFreqBlackCellList", "lte-rrc.intraFreqBlackCellList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_csg_PhysCellIdRange,
      { "csg-PhysCellIdRange", "lte-rrc.csg_PhysCellIdRange",
        FT_NONE, BASE_NONE, NULL, 0,
        "PhysCellIdRange", HFILL }},
    { &hf_lte_rrc_IntraFreqNeighCellList_item,
      { "IntraFreqNeighCellInfo", "lte-rrc.IntraFreqNeighCellInfo",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_q_OffsetCell,
      { "q-OffsetCell", "lte-rrc.q_OffsetCell",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_Q_OffsetRange_vals), 0,
        "Q_OffsetRange", HFILL }},
    { &hf_lte_rrc_IntraFreqBlackCellList_item,
      { "PhysCellIdRange", "lte-rrc.PhysCellIdRange",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_interFreqCarrierFreqList,
      { "interFreqCarrierFreqList", "lte-rrc.interFreqCarrierFreqList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_InterFreqCarrierFreqList_item,
      { "InterFreqCarrierFreqInfo", "lte-rrc.InterFreqCarrierFreqInfo",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_dl_CarrierFreq,
      { "dl-CarrierFreq", "lte-rrc.dl_CarrierFreq",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ARFCN_ValueEUTRA", HFILL }},
    { &hf_lte_rrc_threshX_High,
      { "threshX-High", "lte-rrc.threshX_High",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ReselectionThreshold", HFILL }},
    { &hf_lte_rrc_threshX_Low,
      { "threshX-Low", "lte-rrc.threshX_Low",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ReselectionThreshold", HFILL }},
    { &hf_lte_rrc_q_OffsetFreq,
      { "q-OffsetFreq", "lte-rrc.q_OffsetFreq",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_Q_OffsetRange_vals), 0,
        "Q_OffsetRange", HFILL }},
    { &hf_lte_rrc_interFreqNeighCellList,
      { "interFreqNeighCellList", "lte-rrc.interFreqNeighCellList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_interFreqBlackCellList,
      { "interFreqBlackCellList", "lte-rrc.interFreqBlackCellList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_threshX_Q_r9,
      { "threshX-Q-r9", "lte-rrc.threshX_Q_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_threshX_HighQ_r9,
      { "threshX-HighQ-r9", "lte-rrc.threshX_HighQ_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ReselectionThresholdQ_r9", HFILL }},
    { &hf_lte_rrc_threshX_LowQ_r9,
      { "threshX-LowQ-r9", "lte-rrc.threshX_LowQ_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ReselectionThresholdQ_r9", HFILL }},
    { &hf_lte_rrc_InterFreqNeighCellList_item,
      { "InterFreqNeighCellInfo", "lte-rrc.InterFreqNeighCellInfo",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_InterFreqBlackCellList_item,
      { "PhysCellIdRange", "lte-rrc.PhysCellIdRange",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_carrierFreqListUTRA_FDD,
      { "carrierFreqListUTRA-FDD", "lte-rrc.carrierFreqListUTRA_FDD",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_carrierFreqListUTRA_TDD,
      { "carrierFreqListUTRA-TDD", "lte-rrc.carrierFreqListUTRA_TDD",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_t_ReselectionUTRA,
      { "t-ReselectionUTRA", "lte-rrc.t_ReselectionUTRA",
        FT_UINT32, BASE_DEC, NULL, 0,
        "T_Reselection", HFILL }},
    { &hf_lte_rrc_t_ReselectionUTRA_SF,
      { "t-ReselectionUTRA-SF", "lte-rrc.t_ReselectionUTRA_SF",
        FT_NONE, BASE_NONE, NULL, 0,
        "SpeedStateScaleFactors", HFILL }},
    { &hf_lte_rrc_CarrierFreqListUTRA_FDD_item,
      { "CarrierFreqUTRA-FDD", "lte-rrc.CarrierFreqUTRA_FDD",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_q_RxLevMin_01,
      { "q-RxLevMin", "lte-rrc.q_RxLevMin",
        FT_INT32, BASE_DEC, NULL, 0,
        "INTEGER_M60_M13", HFILL }},
    { &hf_lte_rrc_p_MaxUTRA,
      { "p-MaxUTRA", "lte-rrc.p_MaxUTRA",
        FT_INT32, BASE_DEC, NULL, 0,
        "INTEGER_M50_33", HFILL }},
    { &hf_lte_rrc_q_QualMin,
      { "q-QualMin", "lte-rrc.q_QualMin",
        FT_INT32, BASE_DEC, NULL, 0,
        "INTEGER_M24_0", HFILL }},
    { &hf_lte_rrc_threshX_Q_r9_01,
      { "threshX-Q-r9", "lte-rrc.threshX_Q_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_threshX_Q_r9_01", HFILL }},
    { &hf_lte_rrc_CarrierFreqListUTRA_TDD_item,
      { "CarrierFreqUTRA-TDD", "lte-rrc.CarrierFreqUTRA_TDD",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_t_ReselectionGERAN,
      { "t-ReselectionGERAN", "lte-rrc.t_ReselectionGERAN",
        FT_UINT32, BASE_DEC, NULL, 0,
        "T_Reselection", HFILL }},
    { &hf_lte_rrc_t_ReselectionGERAN_SF,
      { "t-ReselectionGERAN-SF", "lte-rrc.t_ReselectionGERAN_SF",
        FT_NONE, BASE_NONE, NULL, 0,
        "SpeedStateScaleFactors", HFILL }},
    { &hf_lte_rrc_carrierFreqsInfoList,
      { "carrierFreqsInfoList", "lte-rrc.carrierFreqsInfoList",
        FT_UINT32, BASE_DEC, NULL, 0,
        "CarrierFreqsInfoListGERAN", HFILL }},
    { &hf_lte_rrc_CarrierFreqsInfoListGERAN_item,
      { "CarrierFreqsInfoGERAN", "lte-rrc.CarrierFreqsInfoGERAN",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_commonInfo,
      { "commonInfo", "lte-rrc.commonInfo",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ncc_Permitted,
      { "ncc-Permitted", "lte-rrc.ncc_Permitted",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_8", HFILL }},
    { &hf_lte_rrc_q_RxLevMin_02,
      { "q-RxLevMin", "lte-rrc.q_RxLevMin",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_45", HFILL }},
    { &hf_lte_rrc_p_MaxGERAN,
      { "p-MaxGERAN", "lte-rrc.p_MaxGERAN",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_39", HFILL }},
    { &hf_lte_rrc_systemTimeInfo,
      { "systemTimeInfo", "lte-rrc.systemTimeInfo",
        FT_NONE, BASE_NONE, NULL, 0,
        "SystemTimeInfoCDMA2000", HFILL }},
    { &hf_lte_rrc_searchWindowSize,
      { "searchWindowSize", "lte-rrc.searchWindowSize",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_15", HFILL }},
    { &hf_lte_rrc_parametersHRPD,
      { "parametersHRPD", "lte-rrc.parametersHRPD",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_preRegistrationInfoHRPD,
      { "preRegistrationInfoHRPD", "lte-rrc.preRegistrationInfoHRPD",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_cellReselectionParametersHRPD,
      { "cellReselectionParametersHRPD", "lte-rrc.cellReselectionParametersHRPD",
        FT_NONE, BASE_NONE, NULL, 0,
        "CellReselectionParametersCDMA2000", HFILL }},
    { &hf_lte_rrc_parameters1XRTT,
      { "parameters1XRTT", "lte-rrc.parameters1XRTT",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_csfb_RegistrationParam1XRTT,
      { "csfb-RegistrationParam1XRTT", "lte-rrc.csfb_RegistrationParam1XRTT",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_longCodeState1XRTT,
      { "longCodeState1XRTT", "lte-rrc.longCodeState1XRTT",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_42", HFILL }},
    { &hf_lte_rrc_cellReselectionParameters1XRTT,
      { "cellReselectionParameters1XRTT", "lte-rrc.cellReselectionParameters1XRTT",
        FT_NONE, BASE_NONE, NULL, 0,
        "CellReselectionParametersCDMA2000", HFILL }},
    { &hf_lte_rrc_csfb_SupportForDualRxUEs_r9,
      { "csfb-SupportForDualRxUEs-r9", "lte-rrc.csfb_SupportForDualRxUEs_r9",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_cellReselectionParametersHRPD_v920,
      { "cellReselectionParametersHRPD-v920", "lte-rrc.cellReselectionParametersHRPD_v920",
        FT_NONE, BASE_NONE, NULL, 0,
        "CellReselectionParametersCDMA2000_v920", HFILL }},
    { &hf_lte_rrc_cellReselectionParameters1XRTT_v920,
      { "cellReselectionParameters1XRTT-v920", "lte-rrc.cellReselectionParameters1XRTT_v920",
        FT_NONE, BASE_NONE, NULL, 0,
        "CellReselectionParametersCDMA2000_v920", HFILL }},
    { &hf_lte_rrc_csfb_RegistrationParam1XRTT_v920,
      { "csfb-RegistrationParam1XRTT-v920", "lte-rrc.csfb_RegistrationParam1XRTT_v920",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ac_BarringConfig1XRTT_r9,
      { "ac-BarringConfig1XRTT-r9", "lte-rrc.ac_BarringConfig1XRTT_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_bandClassList,
      { "bandClassList", "lte-rrc.bandClassList",
        FT_UINT32, BASE_DEC, NULL, 0,
        "BandClassListCDMA2000", HFILL }},
    { &hf_lte_rrc_neighCellList,
      { "neighCellList", "lte-rrc.neighCellList",
        FT_UINT32, BASE_DEC, NULL, 0,
        "NeighCellListCDMA2000", HFILL }},
    { &hf_lte_rrc_t_ReselectionCDMA2000,
      { "t-ReselectionCDMA2000", "lte-rrc.t_ReselectionCDMA2000",
        FT_UINT32, BASE_DEC, NULL, 0,
        "T_Reselection", HFILL }},
    { &hf_lte_rrc_t_ReselectionCDMA2000_SF,
      { "t-ReselectionCDMA2000-SF", "lte-rrc.t_ReselectionCDMA2000_SF",
        FT_NONE, BASE_NONE, NULL, 0,
        "SpeedStateScaleFactors", HFILL }},
    { &hf_lte_rrc_neighCellList_v920,
      { "neighCellList-v920", "lte-rrc.neighCellList_v920",
        FT_UINT32, BASE_DEC, NULL, 0,
        "NeighCellListCDMA2000_v920", HFILL }},
    { &hf_lte_rrc_NeighCellListCDMA2000_item,
      { "NeighCellCDMA2000", "lte-rrc.NeighCellCDMA2000",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_neighCellsPerFreqList,
      { "neighCellsPerFreqList", "lte-rrc.neighCellsPerFreqList",
        FT_UINT32, BASE_DEC, NULL, 0,
        "NeighCellsPerBandclassListCDMA2000", HFILL }},
    { &hf_lte_rrc_NeighCellsPerBandclassListCDMA2000_item,
      { "NeighCellsPerBandclassCDMA2000", "lte-rrc.NeighCellsPerBandclassCDMA2000",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_arfcn,
      { "arfcn", "lte-rrc.arfcn",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ARFCN_ValueCDMA2000", HFILL }},
    { &hf_lte_rrc_physCellIdList,
      { "physCellIdList", "lte-rrc.physCellIdList",
        FT_UINT32, BASE_DEC, NULL, 0,
        "PhysCellIdListCDMA2000", HFILL }},
    { &hf_lte_rrc_NeighCellListCDMA2000_v920_item,
      { "NeighCellCDMA2000-v920", "lte-rrc.NeighCellCDMA2000_v920",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_neighCellsPerFreqList_v920,
      { "neighCellsPerFreqList-v920", "lte-rrc.neighCellsPerFreqList_v920",
        FT_UINT32, BASE_DEC, NULL, 0,
        "NeighCellsPerBandclassListCDMA2000_v920", HFILL }},
    { &hf_lte_rrc_NeighCellsPerBandclassListCDMA2000_v920_item,
      { "NeighCellsPerBandclassCDMA2000-v920", "lte-rrc.NeighCellsPerBandclassCDMA2000_v920",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_physCellIdList_v920,
      { "physCellIdList-v920", "lte-rrc.physCellIdList_v920",
        FT_UINT32, BASE_DEC, NULL, 0,
        "PhysCellIdListCDMA2000_v920", HFILL }},
    { &hf_lte_rrc_PhysCellIdListCDMA2000_item,
      { "PhysCellIdCDMA2000", "lte-rrc.PhysCellIdCDMA2000",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_PhysCellIdListCDMA2000_v920_item,
      { "PhysCellIdCDMA2000", "lte-rrc.PhysCellIdCDMA2000",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_BandClassListCDMA2000_item,
      { "BandClassInfoCDMA2000", "lte-rrc.BandClassInfoCDMA2000",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_threshX_High_01,
      { "threshX-High", "lte-rrc.threshX_High",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_63", HFILL }},
    { &hf_lte_rrc_threshX_Low_01,
      { "threshX-Low", "lte-rrc.threshX_Low",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_63", HFILL }},
    { &hf_lte_rrc_ac_Barring0to9_r9,
      { "ac-Barring0to9-r9", "lte-rrc.ac_Barring0to9_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_63", HFILL }},
    { &hf_lte_rrc_ac_Barring10_r9,
      { "ac-Barring10-r9", "lte-rrc.ac_Barring10_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_7", HFILL }},
    { &hf_lte_rrc_ac_Barring11_r9,
      { "ac-Barring11-r9", "lte-rrc.ac_Barring11_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_7", HFILL }},
    { &hf_lte_rrc_ac_Barring12_r9,
      { "ac-Barring12-r9", "lte-rrc.ac_Barring12_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_7", HFILL }},
    { &hf_lte_rrc_ac_Barring13_r9,
      { "ac-Barring13-r9", "lte-rrc.ac_Barring13_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_7", HFILL }},
    { &hf_lte_rrc_ac_Barring14_r9,
      { "ac-Barring14-r9", "lte-rrc.ac_Barring14_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_7", HFILL }},
    { &hf_lte_rrc_ac_Barring15_r9,
      { "ac-Barring15-r9", "lte-rrc.ac_Barring15_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_7", HFILL }},
    { &hf_lte_rrc_ac_BarringMsg_r9,
      { "ac-BarringMsg-r9", "lte-rrc.ac_BarringMsg_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_7", HFILL }},
    { &hf_lte_rrc_ac_BarringReg_r9,
      { "ac-BarringReg-r9", "lte-rrc.ac_BarringReg_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_7", HFILL }},
    { &hf_lte_rrc_ac_BarringEmg_r9,
      { "ac-BarringEmg-r9", "lte-rrc.ac_BarringEmg_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_7", HFILL }},
    { &hf_lte_rrc_hnb_Name,
      { "hnb-Name", "lte-rrc.hnb_Name",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING_SIZE_1_48", HFILL }},
    { &hf_lte_rrc_messageIdentifier,
      { "messageIdentifier", "lte-rrc.messageIdentifier",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_16", HFILL }},
    { &hf_lte_rrc_serialNumber,
      { "serialNumber", "lte-rrc.serialNumber",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_16", HFILL }},
    { &hf_lte_rrc_warningType,
      { "warningType", "lte-rrc.warningType",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING_SIZE_2", HFILL }},
    { &hf_lte_rrc_warningSecurityInfo,
      { "warningSecurityInfo", "lte-rrc.warningSecurityInfo",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING_SIZE_50", HFILL }},
    { &hf_lte_rrc_warningMessageSegmentType,
      { "warningMessageSegmentType", "lte-rrc.warningMessageSegmentType",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_warningMessageSegmentType_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_warningMessageSegmentNumber,
      { "warningMessageSegmentNumber", "lte-rrc.warningMessageSegmentNumber",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_63", HFILL }},
    { &hf_lte_rrc_warningMessageSegment,
      { "warningMessageSegment", "lte-rrc.warningMessageSegment",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING", HFILL }},
    { &hf_lte_rrc_dataCodingScheme,
      { "dataCodingScheme", "lte-rrc.dataCodingScheme",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING_SIZE_1", HFILL }},
    { &hf_lte_rrc_messageIdentifier_r9,
      { "messageIdentifier-r9", "lte-rrc.messageIdentifier_r9",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_16", HFILL }},
    { &hf_lte_rrc_serialNumber_r9,
      { "serialNumber-r9", "lte-rrc.serialNumber_r9",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_16", HFILL }},
    { &hf_lte_rrc_warningMessageSegmentType_r9,
      { "warningMessageSegmentType-r9", "lte-rrc.warningMessageSegmentType_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_warningMessageSegmentType_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_warningMessageSegmentNumber_r9,
      { "warningMessageSegmentNumber-r9", "lte-rrc.warningMessageSegmentNumber_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_63", HFILL }},
    { &hf_lte_rrc_warningMessageSegment_r9,
      { "warningMessageSegment-r9", "lte-rrc.warningMessageSegment_r9",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING", HFILL }},
    { &hf_lte_rrc_dataCodingScheme_r9,
      { "dataCodingScheme-r9", "lte-rrc.dataCodingScheme_r9",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING_SIZE_1", HFILL }},
    { &hf_lte_rrc_lateR9NonCriticalExtension,
      { "lateR9NonCriticalExtension", "lte-rrc.lateR9NonCriticalExtension",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING", HFILL }},
    { &hf_lte_rrc_mbsfn_AreaInfoList_r9,
      { "mbsfn-AreaInfoList-r9", "lte-rrc.mbsfn_AreaInfoList_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_notificationConfig_r9,
      { "notificationConfig-r9", "lte-rrc.notificationConfig_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        "MBMS_NotificationConfig_r9", HFILL }},
    { &hf_lte_rrc_antennaPortsCount,
      { "antennaPortsCount", "lte-rrc.antennaPortsCount",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_antennaPortsCount_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_transmissionMode,
      { "transmissionMode", "lte-rrc.transmissionMode",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_transmissionMode_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_codebookSubsetRestriction,
      { "codebookSubsetRestriction", "lte-rrc.codebookSubsetRestriction",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_codebookSubsetRestriction_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_n2TxAntenna_tm3,
      { "n2TxAntenna-tm3", "lte-rrc.n2TxAntenna_tm3",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_2", HFILL }},
    { &hf_lte_rrc_n4TxAntenna_tm3,
      { "n4TxAntenna-tm3", "lte-rrc.n4TxAntenna_tm3",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_4", HFILL }},
    { &hf_lte_rrc_n2TxAntenna_tm4,
      { "n2TxAntenna-tm4", "lte-rrc.n2TxAntenna_tm4",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_6", HFILL }},
    { &hf_lte_rrc_n4TxAntenna_tm4,
      { "n4TxAntenna-tm4", "lte-rrc.n4TxAntenna_tm4",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_64", HFILL }},
    { &hf_lte_rrc_n2TxAntenna_tm5,
      { "n2TxAntenna-tm5", "lte-rrc.n2TxAntenna_tm5",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_4", HFILL }},
    { &hf_lte_rrc_n4TxAntenna_tm5,
      { "n4TxAntenna-tm5", "lte-rrc.n4TxAntenna_tm5",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_16", HFILL }},
    { &hf_lte_rrc_n2TxAntenna_tm6,
      { "n2TxAntenna-tm6", "lte-rrc.n2TxAntenna_tm6",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_4", HFILL }},
    { &hf_lte_rrc_n4TxAntenna_tm6,
      { "n4TxAntenna-tm6", "lte-rrc.n4TxAntenna_tm6",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_16", HFILL }},
    { &hf_lte_rrc_ue_TransmitAntennaSelection,
      { "ue-TransmitAntennaSelection", "lte-rrc.ue_TransmitAntennaSelection",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_ue_TransmitAntennaSelection_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_release,
      { "release", "lte-rrc.release",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_setup,
      { "setup", "lte-rrc.setup",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_setup_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_codebookSubsetRestriction_v920,
      { "codebookSubsetRestriction-v920", "lte-rrc.codebookSubsetRestriction_v920",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_codebookSubsetRestriction_v920_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_n2TxAntenna_tm8_r9,
      { "n2TxAntenna-tm8-r9", "lte-rrc.n2TxAntenna_tm8_r9",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_6", HFILL }},
    { &hf_lte_rrc_n4TxAntenna_tm8_r9,
      { "n4TxAntenna-tm8-r9", "lte-rrc.n4TxAntenna_tm8_r9",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_32", HFILL }},
    { &hf_lte_rrc_cqi_ReportModeAperiodic,
      { "cqi-ReportModeAperiodic", "lte-rrc.cqi_ReportModeAperiodic",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_cqi_ReportModeAperiodic_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nomPDSCH_RS_EPRE_Offset,
      { "nomPDSCH-RS-EPRE-Offset", "lte-rrc.nomPDSCH_RS_EPRE_Offset",
        FT_INT32, BASE_DEC, NULL, 0,
        "INTEGER_M1_6", HFILL }},
    { &hf_lte_rrc_cqi_ReportPeriodic,
      { "cqi-ReportPeriodic", "lte-rrc.cqi_ReportPeriodic",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_CQI_ReportPeriodic_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_cqi_Mask_r9,
      { "cqi-Mask-r9", "lte-rrc.cqi_Mask_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_cqi_Mask_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_pmi_RI_Report_r9,
      { "pmi-RI-Report-r9", "lte-rrc.pmi_RI_Report_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_pmi_RI_Report_r9_vals), 0,
        "T_pmi_RI_Report_r9", HFILL }},
    { &hf_lte_rrc_setup_01,
      { "setup", "lte-rrc.setup",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_setup_01", HFILL }},
    { &hf_lte_rrc_cqi_PUCCH_ResourceIndex,
      { "cqi-PUCCH-ResourceIndex", "lte-rrc.cqi_PUCCH_ResourceIndex",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_1185", HFILL }},
    { &hf_lte_rrc_cqi_pmi_ConfigIndex,
      { "cqi-pmi-ConfigIndex", "lte-rrc.cqi_pmi_ConfigIndex",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_1023", HFILL }},
    { &hf_lte_rrc_cqi_FormatIndicatorPeriodic,
      { "cqi-FormatIndicatorPeriodic", "lte-rrc.cqi_FormatIndicatorPeriodic",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_cqi_FormatIndicatorPeriodic_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_widebandCQI,
      { "widebandCQI", "lte-rrc.widebandCQI",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_subbandCQI,
      { "subbandCQI", "lte-rrc.subbandCQI",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_k,
      { "k", "lte-rrc.k",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_4", HFILL }},
    { &hf_lte_rrc_ri_ConfigIndex,
      { "ri-ConfigIndex", "lte-rrc.ri_ConfigIndex",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_1023", HFILL }},
    { &hf_lte_rrc_simultaneousAckNackAndCQI,
      { "simultaneousAckNackAndCQI", "lte-rrc.simultaneousAckNackAndCQI",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_ul_SpecificParameters,
      { "ul-SpecificParameters", "lte-rrc.ul_SpecificParameters",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_priority,
      { "priority", "lte-rrc.priority",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_16", HFILL }},
    { &hf_lte_rrc_prioritisedBitRate,
      { "prioritisedBitRate", "lte-rrc.prioritisedBitRate",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_prioritisedBitRate_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_bucketSizeDuration,
      { "bucketSizeDuration", "lte-rrc.bucketSizeDuration",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_bucketSizeDuration_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_logicalChannelGroup,
      { "logicalChannelGroup", "lte-rrc.logicalChannelGroup",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_3", HFILL }},
    { &hf_lte_rrc_logicalChannelSR_Mask_r9,
      { "logicalChannelSR-Mask-r9", "lte-rrc.logicalChannelSR_Mask_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_logicalChannelSR_Mask_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ul_SCH_Config,
      { "ul-SCH-Config", "lte-rrc.ul_SCH_Config",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_maxHARQ_Tx,
      { "maxHARQ-Tx", "lte-rrc.maxHARQ_Tx",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_maxHARQ_Tx_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_periodicBSR_Timer,
      { "periodicBSR-Timer", "lte-rrc.periodicBSR_Timer",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_periodicBSR_Timer_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_retxBSR_Timer,
      { "retxBSR-Timer", "lte-rrc.retxBSR_Timer",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_retxBSR_Timer_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ttiBundling,
      { "ttiBundling", "lte-rrc.ttiBundling",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_drx_Config,
      { "drx-Config", "lte-rrc.drx_Config",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_DRX_Config_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_timeAlignmentTimerDedicated,
      { "timeAlignmentTimerDedicated", "lte-rrc.timeAlignmentTimerDedicated",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_TimeAlignmentTimer_vals), 0,
        "TimeAlignmentTimer", HFILL }},
    { &hf_lte_rrc_phr_Config,
      { "phr-Config", "lte-rrc.phr_Config",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_phr_Config_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_setup_02,
      { "setup", "lte-rrc.setup",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_setup_02", HFILL }},
    { &hf_lte_rrc_periodicPHR_Timer,
      { "periodicPHR-Timer", "lte-rrc.periodicPHR_Timer",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_periodicPHR_Timer_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_prohibitPHR_Timer,
      { "prohibitPHR-Timer", "lte-rrc.prohibitPHR_Timer",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_prohibitPHR_Timer_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_dl_PathlossChange,
      { "dl-PathlossChange", "lte-rrc.dl_PathlossChange",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_dl_PathlossChange_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_sr_ProhibitTimer_r9,
      { "sr-ProhibitTimer-r9", "lte-rrc.sr_ProhibitTimer_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_7", HFILL }},
    { &hf_lte_rrc_setup_03,
      { "setup", "lte-rrc.setup",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_setup_03", HFILL }},
    { &hf_lte_rrc_onDurationTimer,
      { "onDurationTimer", "lte-rrc.onDurationTimer",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_onDurationTimer_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_drx_InactivityTimer,
      { "drx-InactivityTimer", "lte-rrc.drx_InactivityTimer",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_drx_InactivityTimer_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_drx_RetransmissionTimer,
      { "drx-RetransmissionTimer", "lte-rrc.drx_RetransmissionTimer",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_drx_RetransmissionTimer_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_longDRX_CycleStartOffset,
      { "longDRX-CycleStartOffset", "lte-rrc.longDRX_CycleStartOffset",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_longDRX_CycleStartOffset_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_sf10,
      { "sf10", "lte-rrc.sf10",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_9", HFILL }},
    { &hf_lte_rrc_sf20,
      { "sf20", "lte-rrc.sf20",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_19", HFILL }},
    { &hf_lte_rrc_sf32,
      { "sf32", "lte-rrc.sf32",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_31", HFILL }},
    { &hf_lte_rrc_sf40,
      { "sf40", "lte-rrc.sf40",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_39", HFILL }},
    { &hf_lte_rrc_sf64,
      { "sf64", "lte-rrc.sf64",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_63", HFILL }},
    { &hf_lte_rrc_sf80,
      { "sf80", "lte-rrc.sf80",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_79", HFILL }},
    { &hf_lte_rrc_sf128,
      { "sf128", "lte-rrc.sf128",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_127", HFILL }},
    { &hf_lte_rrc_sf160,
      { "sf160", "lte-rrc.sf160",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_159", HFILL }},
    { &hf_lte_rrc_sf256,
      { "sf256", "lte-rrc.sf256",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_255", HFILL }},
    { &hf_lte_rrc_sf320,
      { "sf320", "lte-rrc.sf320",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_319", HFILL }},
    { &hf_lte_rrc_sf512,
      { "sf512", "lte-rrc.sf512",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_511", HFILL }},
    { &hf_lte_rrc_sf640,
      { "sf640", "lte-rrc.sf640",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_639", HFILL }},
    { &hf_lte_rrc_sf1024,
      { "sf1024", "lte-rrc.sf1024",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_1023", HFILL }},
    { &hf_lte_rrc_sf1280,
      { "sf1280", "lte-rrc.sf1280",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_1279", HFILL }},
    { &hf_lte_rrc_sf2048,
      { "sf2048", "lte-rrc.sf2048",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_2047", HFILL }},
    { &hf_lte_rrc_sf2560,
      { "sf2560", "lte-rrc.sf2560",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_2559", HFILL }},
    { &hf_lte_rrc_shortDRX,
      { "shortDRX", "lte-rrc.shortDRX",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_shortDRX_Cycle,
      { "shortDRX-Cycle", "lte-rrc.shortDRX_Cycle",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_shortDRX_Cycle_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_drxShortCycleTimer,
      { "drxShortCycleTimer", "lte-rrc.drxShortCycleTimer",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_16", HFILL }},
    { &hf_lte_rrc_discardTimer,
      { "discardTimer", "lte-rrc.discardTimer",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_discardTimer_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_rlc_AM,
      { "rlc-AM", "lte-rrc.rlc_AM",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_statusReportRequired,
      { "statusReportRequired", "lte-rrc.statusReportRequired",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_rlc_UM,
      { "rlc-UM", "lte-rrc.rlc_UM",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_pdcp_SN_Size,
      { "pdcp-SN-Size", "lte-rrc.pdcp_SN_Size",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_pdcp_SN_Size_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_headerCompression,
      { "headerCompression", "lte-rrc.headerCompression",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_headerCompression_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_notUsed,
      { "notUsed", "lte-rrc.notUsed",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_rohc,
      { "rohc", "lte-rrc.rohc",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_maxCID,
      { "maxCID", "lte-rrc.maxCID",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_16383", HFILL }},
    { &hf_lte_rrc_profiles,
      { "profiles", "lte-rrc.profiles",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_profile0x0001,
      { "profile0x0001", "lte-rrc.profile0x0001",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_profile0x0002,
      { "profile0x0002", "lte-rrc.profile0x0002",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_profile0x0003,
      { "profile0x0003", "lte-rrc.profile0x0003",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_profile0x0004,
      { "profile0x0004", "lte-rrc.profile0x0004",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_profile0x0006,
      { "profile0x0006", "lte-rrc.profile0x0006",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_profile0x0101,
      { "profile0x0101", "lte-rrc.profile0x0101",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_profile0x0102,
      { "profile0x0102", "lte-rrc.profile0x0102",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_profile0x0103,
      { "profile0x0103", "lte-rrc.profile0x0103",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_profile0x0104,
      { "profile0x0104", "lte-rrc.profile0x0104",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_referenceSignalPower,
      { "referenceSignalPower", "lte-rrc.referenceSignalPower",
        FT_INT32, BASE_DEC, NULL, 0,
        "INTEGER_M60_50", HFILL }},
    { &hf_lte_rrc_p_b,
      { "p-b", "lte-rrc.p_b",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_3", HFILL }},
    { &hf_lte_rrc_p_a,
      { "p-a", "lte-rrc.p_a",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_p_a_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_phich_Duration,
      { "phich-Duration", "lte-rrc.phich_Duration",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_phich_Duration_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_phich_Resource,
      { "phich-Resource", "lte-rrc.phich_Resource",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_phich_Resource_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_pdsch_ConfigDedicated,
      { "pdsch-ConfigDedicated", "lte-rrc.pdsch_ConfigDedicated",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_pucch_ConfigDedicated,
      { "pucch-ConfigDedicated", "lte-rrc.pucch_ConfigDedicated",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_pusch_ConfigDedicated,
      { "pusch-ConfigDedicated", "lte-rrc.pusch_ConfigDedicated",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_uplinkPowerControlDedicated,
      { "uplinkPowerControlDedicated", "lte-rrc.uplinkPowerControlDedicated",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_tpc_PDCCH_ConfigPUCCH,
      { "tpc-PDCCH-ConfigPUCCH", "lte-rrc.tpc_PDCCH_ConfigPUCCH",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_TPC_PDCCH_Config_vals), 0,
        "TPC_PDCCH_Config", HFILL }},
    { &hf_lte_rrc_tpc_PDCCH_ConfigPUSCH,
      { "tpc-PDCCH-ConfigPUSCH", "lte-rrc.tpc_PDCCH_ConfigPUSCH",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_TPC_PDCCH_Config_vals), 0,
        "TPC_PDCCH_Config", HFILL }},
    { &hf_lte_rrc_cqi_ReportConfig,
      { "cqi-ReportConfig", "lte-rrc.cqi_ReportConfig",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_soundingRS_UL_ConfigDedicated,
      { "soundingRS-UL-ConfigDedicated", "lte-rrc.soundingRS_UL_ConfigDedicated",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_SoundingRS_UL_ConfigDedicated_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_antennaInfo,
      { "antennaInfo", "lte-rrc.antennaInfo",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_antennaInfo_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_explicitValue,
      { "explicitValue", "lte-rrc.explicitValue",
        FT_NONE, BASE_NONE, NULL, 0,
        "AntennaInfoDedicated", HFILL }},
    { &hf_lte_rrc_defaultValue,
      { "defaultValue", "lte-rrc.defaultValue",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_schedulingRequestConfig,
      { "schedulingRequestConfig", "lte-rrc.schedulingRequestConfig",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_SchedulingRequestConfig_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_cqi_ReportConfig_v920,
      { "cqi-ReportConfig-v920", "lte-rrc.cqi_ReportConfig_v920",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_antennaInfo_v920,
      { "antennaInfo-v920", "lte-rrc.antennaInfo_v920",
        FT_NONE, BASE_NONE, NULL, 0,
        "AntennaInfoDedicated_v920", HFILL }},
    { &hf_lte_rrc_rootSequenceIndex,
      { "rootSequenceIndex", "lte-rrc.rootSequenceIndex",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_837", HFILL }},
    { &hf_lte_rrc_prach_ConfigInfo,
      { "prach-ConfigInfo", "lte-rrc.prach_ConfigInfo",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_prach_ConfigIndex,
      { "prach-ConfigIndex", "lte-rrc.prach_ConfigIndex",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_63", HFILL }},
    { &hf_lte_rrc_highSpeedFlag,
      { "highSpeedFlag", "lte-rrc.highSpeedFlag",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_zeroCorrelationZoneConfig,
      { "zeroCorrelationZoneConfig", "lte-rrc.zeroCorrelationZoneConfig",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_15", HFILL }},
    { &hf_lte_rrc_prach_FreqOffset,
      { "prach-FreqOffset", "lte-rrc.prach_FreqOffset",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_94", HFILL }},
    { &hf_lte_rrc_deltaPUCCH_Shift,
      { "deltaPUCCH-Shift", "lte-rrc.deltaPUCCH_Shift",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_deltaPUCCH_Shift_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nRB_CQI,
      { "nRB-CQI", "lte-rrc.nRB_CQI",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_98", HFILL }},
    { &hf_lte_rrc_nCS_AN,
      { "nCS-AN", "lte-rrc.nCS_AN",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_7", HFILL }},
    { &hf_lte_rrc_n1PUCCH_AN,
      { "n1PUCCH-AN", "lte-rrc.n1PUCCH_AN",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_2047", HFILL }},
    { &hf_lte_rrc_ackNackRepetition,
      { "ackNackRepetition", "lte-rrc.ackNackRepetition",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_ackNackRepetition_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_setup_04,
      { "setup", "lte-rrc.setup",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_setup_04", HFILL }},
    { &hf_lte_rrc_repetitionFactor,
      { "repetitionFactor", "lte-rrc.repetitionFactor",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_repetitionFactor_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_n1PUCCH_AN_Rep,
      { "n1PUCCH-AN-Rep", "lte-rrc.n1PUCCH_AN_Rep",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_2047", HFILL }},
    { &hf_lte_rrc_tdd_AckNackFeedbackMode,
      { "tdd-AckNackFeedbackMode", "lte-rrc.tdd_AckNackFeedbackMode",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_tdd_AckNackFeedbackMode_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_pusch_ConfigBasic,
      { "pusch-ConfigBasic", "lte-rrc.pusch_ConfigBasic",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_n_SB,
      { "n-SB", "lte-rrc.n_SB",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_4", HFILL }},
    { &hf_lte_rrc_hoppingMode,
      { "hoppingMode", "lte-rrc.hoppingMode",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_hoppingMode_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_pusch_HoppingOffset,
      { "pusch-HoppingOffset", "lte-rrc.pusch_HoppingOffset",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_98", HFILL }},
    { &hf_lte_rrc_enable64QAM,
      { "enable64QAM", "lte-rrc.enable64QAM",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_ul_ReferenceSignalsPUSCH,
      { "ul-ReferenceSignalsPUSCH", "lte-rrc.ul_ReferenceSignalsPUSCH",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_betaOffset_ACK_Index,
      { "betaOffset-ACK-Index", "lte-rrc.betaOffset_ACK_Index",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_15", HFILL }},
    { &hf_lte_rrc_betaOffset_RI_Index,
      { "betaOffset-RI-Index", "lte-rrc.betaOffset_RI_Index",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_15", HFILL }},
    { &hf_lte_rrc_betaOffset_CQI_Index,
      { "betaOffset-CQI-Index", "lte-rrc.betaOffset_CQI_Index",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_15", HFILL }},
    { &hf_lte_rrc_groupHoppingEnabled,
      { "groupHoppingEnabled", "lte-rrc.groupHoppingEnabled",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_groupAssignmentPUSCH,
      { "groupAssignmentPUSCH", "lte-rrc.groupAssignmentPUSCH",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_29", HFILL }},
    { &hf_lte_rrc_sequenceHoppingEnabled,
      { "sequenceHoppingEnabled", "lte-rrc.sequenceHoppingEnabled",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_cyclicShift,
      { "cyclicShift", "lte-rrc.cyclicShift",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_7", HFILL }},
    { &hf_lte_rrc_preambleInfo,
      { "preambleInfo", "lte-rrc.preambleInfo",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_numberOfRA_Preambles,
      { "numberOfRA-Preambles", "lte-rrc.numberOfRA_Preambles",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_numberOfRA_Preambles_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_preamblesGroupAConfig,
      { "preamblesGroupAConfig", "lte-rrc.preamblesGroupAConfig",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_sizeOfRA_PreamblesGroupA,
      { "sizeOfRA-PreamblesGroupA", "lte-rrc.sizeOfRA_PreamblesGroupA",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_sizeOfRA_PreamblesGroupA_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_messageSizeGroupA,
      { "messageSizeGroupA", "lte-rrc.messageSizeGroupA",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_messageSizeGroupA_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_messagePowerOffsetGroupB,
      { "messagePowerOffsetGroupB", "lte-rrc.messagePowerOffsetGroupB",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_messagePowerOffsetGroupB_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_powerRampingParameters,
      { "powerRampingParameters", "lte-rrc.powerRampingParameters",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_powerRampingStep,
      { "powerRampingStep", "lte-rrc.powerRampingStep",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_powerRampingStep_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_preambleInitialReceivedTargetPower,
      { "preambleInitialReceivedTargetPower", "lte-rrc.preambleInitialReceivedTargetPower",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_preambleInitialReceivedTargetPower_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ra_SupervisionInfo,
      { "ra-SupervisionInfo", "lte-rrc.ra_SupervisionInfo",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_preambleTransMax,
      { "preambleTransMax", "lte-rrc.preambleTransMax",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_preambleTransMax_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ra_ResponseWindowSize,
      { "ra-ResponseWindowSize", "lte-rrc.ra_ResponseWindowSize",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_ra_ResponseWindowSize_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_mac_ContentionResolutionTimer,
      { "mac-ContentionResolutionTimer", "lte-rrc.mac_ContentionResolutionTimer",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_mac_ContentionResolutionTimer_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_maxHARQ_Msg3Tx,
      { "maxHARQ-Msg3Tx", "lte-rrc.maxHARQ_Msg3Tx",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_8", HFILL }},
    { &hf_lte_rrc_ra_PreambleIndex,
      { "ra-PreambleIndex", "lte-rrc.ra_PreambleIndex",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_63", HFILL }},
    { &hf_lte_rrc_ra_PRACH_MaskIndex,
      { "ra-PRACH-MaskIndex", "lte-rrc.ra_PRACH_MaskIndex",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_15", HFILL }},
    { &hf_lte_rrc_rach_ConfigCommon,
      { "rach-ConfigCommon", "lte-rrc.rach_ConfigCommon",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_bcch_Config,
      { "bcch-Config", "lte-rrc.bcch_Config",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_pcch_Config,
      { "pcch-Config", "lte-rrc.pcch_Config",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_prach_Config,
      { "prach-Config", "lte-rrc.prach_Config",
        FT_NONE, BASE_NONE, NULL, 0,
        "PRACH_ConfigSIB", HFILL }},
    { &hf_lte_rrc_pdsch_ConfigCommon,
      { "pdsch-ConfigCommon", "lte-rrc.pdsch_ConfigCommon",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_pusch_ConfigCommon,
      { "pusch-ConfigCommon", "lte-rrc.pusch_ConfigCommon",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_pucch_ConfigCommon,
      { "pucch-ConfigCommon", "lte-rrc.pucch_ConfigCommon",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_soundingRS_UL_ConfigCommon,
      { "soundingRS-UL-ConfigCommon", "lte-rrc.soundingRS_UL_ConfigCommon",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_SoundingRS_UL_ConfigCommon_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_uplinkPowerControlCommon,
      { "uplinkPowerControlCommon", "lte-rrc.uplinkPowerControlCommon",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ul_CyclicPrefixLength,
      { "ul-CyclicPrefixLength", "lte-rrc.ul_CyclicPrefixLength",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_UL_CyclicPrefixLength_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_prach_Config_01,
      { "prach-Config", "lte-rrc.prach_Config",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_antennaInfoCommon,
      { "antennaInfoCommon", "lte-rrc.antennaInfoCommon",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_modificationPeriodCoeff,
      { "modificationPeriodCoeff", "lte-rrc.modificationPeriodCoeff",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_modificationPeriodCoeff_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_defaultPagingCycle,
      { "defaultPagingCycle", "lte-rrc.defaultPagingCycle",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_defaultPagingCycle_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nB,
      { "nB", "lte-rrc.nB",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_nB_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_srb_ToAddModList,
      { "srb-ToAddModList", "lte-rrc.srb_ToAddModList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_drb_ToAddModList,
      { "drb-ToAddModList", "lte-rrc.drb_ToAddModList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_drb_ToReleaseList,
      { "drb-ToReleaseList", "lte-rrc.drb_ToReleaseList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_mac_MainConfig,
      { "mac-MainConfig", "lte-rrc.mac_MainConfig",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_mac_MainConfig_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_explicitValue_01,
      { "explicitValue", "lte-rrc.explicitValue",
        FT_NONE, BASE_NONE, NULL, 0,
        "MAC_MainConfig", HFILL }},
    { &hf_lte_rrc_sps_Config,
      { "sps-Config", "lte-rrc.sps_Config",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_physicalConfigDedicated,
      { "physicalConfigDedicated", "lte-rrc.physicalConfigDedicated",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_rlf_TimersAndConstants_r9,
      { "rlf-TimersAndConstants-r9", "lte-rrc.rlf_TimersAndConstants_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_RLF_TimersAndConstants_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_SRB_ToAddModList_item,
      { "SRB-ToAddMod", "lte-rrc.SRB_ToAddMod",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_srb_Identity,
      { "srb-Identity", "lte-rrc.srb_Identity",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_2", HFILL }},
    { &hf_lte_rrc_rlc_Config,
      { "rlc-Config", "lte-rrc.rlc_Config",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_rlc_Config_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_explicitValue_02,
      { "explicitValue", "lte-rrc.explicitValue",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_RLC_Config_vals), 0,
        "RLC_Config", HFILL }},
    { &hf_lte_rrc_logicalChannelConfig,
      { "logicalChannelConfig", "lte-rrc.logicalChannelConfig",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_logicalChannelConfig_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_explicitValue_03,
      { "explicitValue", "lte-rrc.explicitValue",
        FT_NONE, BASE_NONE, NULL, 0,
        "LogicalChannelConfig", HFILL }},
    { &hf_lte_rrc_DRB_ToAddModList_item,
      { "DRB-ToAddMod", "lte-rrc.DRB_ToAddMod",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_eps_BearerIdentity,
      { "eps-BearerIdentity", "lte-rrc.eps_BearerIdentity",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_15", HFILL }},
    { &hf_lte_rrc_pdcp_Config,
      { "pdcp-Config", "lte-rrc.pdcp_Config",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_rlc_Config_01,
      { "rlc-Config", "lte-rrc.rlc_Config",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_RLC_Config_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_logicalChannelIdentity,
      { "logicalChannelIdentity", "lte-rrc.logicalChannelIdentity",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_3_10", HFILL }},
    { &hf_lte_rrc_logicalChannelConfig_01,
      { "logicalChannelConfig", "lte-rrc.logicalChannelConfig",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_DRB_ToReleaseList_item,
      { "DRB-Identity", "lte-rrc.DRB_Identity",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_am,
      { "am", "lte-rrc.am",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ul_AM_RLC,
      { "ul-AM-RLC", "lte-rrc.ul_AM_RLC",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_dl_AM_RLC,
      { "dl-AM-RLC", "lte-rrc.dl_AM_RLC",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_um_Bi_Directional,
      { "um-Bi-Directional", "lte-rrc.um_Bi_Directional",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ul_UM_RLC,
      { "ul-UM-RLC", "lte-rrc.ul_UM_RLC",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_dl_UM_RLC,
      { "dl-UM-RLC", "lte-rrc.dl_UM_RLC",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_um_Uni_Directional_UL,
      { "um-Uni-Directional-UL", "lte-rrc.um_Uni_Directional_UL",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_um_Uni_Directional_DL,
      { "um-Uni-Directional-DL", "lte-rrc.um_Uni_Directional_DL",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_t_PollRetransmit,
      { "t-PollRetransmit", "lte-rrc.t_PollRetransmit",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_PollRetransmit_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_pollPDU,
      { "pollPDU", "lte-rrc.pollPDU",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_PollPDU_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_pollByte,
      { "pollByte", "lte-rrc.pollByte",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_PollByte_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_maxRetxThreshold,
      { "maxRetxThreshold", "lte-rrc.maxRetxThreshold",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_maxRetxThreshold_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_t_Reordering,
      { "t-Reordering", "lte-rrc.t_Reordering",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_Reordering_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_t_StatusProhibit,
      { "t-StatusProhibit", "lte-rrc.t_StatusProhibit",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_StatusProhibit_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_sn_FieldLength,
      { "sn-FieldLength", "lte-rrc.sn_FieldLength",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_SN_FieldLength_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_setup_05,
      { "setup", "lte-rrc.setup",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_setup_05", HFILL }},
    { &hf_lte_rrc_t301_r9,
      { "t301-r9", "lte-rrc.t301_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_t301_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_t310_r9,
      { "t310-r9", "lte-rrc.t310_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_t310_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_n310_r9,
      { "n310-r9", "lte-rrc.n310_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_n310_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_t311_r9,
      { "t311-r9", "lte-rrc.t311_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_t311_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_n311_r9,
      { "n311-r9", "lte-rrc.n311_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_n311_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_setup_06,
      { "setup", "lte-rrc.setup",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_setup_06", HFILL }},
    { &hf_lte_rrc_sr_PUCCH_ResourceIndex,
      { "sr-PUCCH-ResourceIndex", "lte-rrc.sr_PUCCH_ResourceIndex",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_2047", HFILL }},
    { &hf_lte_rrc_sr_ConfigIndex,
      { "sr-ConfigIndex", "lte-rrc.sr_ConfigIndex",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_157", HFILL }},
    { &hf_lte_rrc_dsr_TransMax,
      { "dsr-TransMax", "lte-rrc.dsr_TransMax",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_dsr_TransMax_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_setup_07,
      { "setup", "lte-rrc.setup",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_setup_07", HFILL }},
    { &hf_lte_rrc_srs_BandwidthConfig,
      { "srs-BandwidthConfig", "lte-rrc.srs_BandwidthConfig",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_srs_BandwidthConfig_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_srs_SubframeConfig,
      { "srs-SubframeConfig", "lte-rrc.srs_SubframeConfig",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_srs_SubframeConfig_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ackNackSRS_SimultaneousTransmission,
      { "ackNackSRS-SimultaneousTransmission", "lte-rrc.ackNackSRS_SimultaneousTransmission",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_srs_MaxUpPts,
      { "srs-MaxUpPts", "lte-rrc.srs_MaxUpPts",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_srs_MaxUpPts_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_setup_08,
      { "setup", "lte-rrc.setup",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_setup_08", HFILL }},
    { &hf_lte_rrc_srs_Bandwidth,
      { "srs-Bandwidth", "lte-rrc.srs_Bandwidth",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_srs_Bandwidth_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_srs_HoppingBandwidth,
      { "srs-HoppingBandwidth", "lte-rrc.srs_HoppingBandwidth",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_srs_HoppingBandwidth_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_freqDomainPosition,
      { "freqDomainPosition", "lte-rrc.freqDomainPosition",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_23", HFILL }},
    { &hf_lte_rrc_duration,
      { "duration", "lte-rrc.duration",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_srs_ConfigIndex,
      { "srs-ConfigIndex", "lte-rrc.srs_ConfigIndex",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_1023", HFILL }},
    { &hf_lte_rrc_transmissionComb,
      { "transmissionComb", "lte-rrc.transmissionComb",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_1", HFILL }},
    { &hf_lte_rrc_cyclicShift_01,
      { "cyclicShift", "lte-rrc.cyclicShift",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_cyclicShift_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_semiPersistSchedC_RNTI,
      { "semiPersistSchedC-RNTI", "lte-rrc.semiPersistSchedC_RNTI",
        FT_BYTES, BASE_NONE, NULL, 0,
        "C_RNTI", HFILL }},
    { &hf_lte_rrc_sps_ConfigDL,
      { "sps-ConfigDL", "lte-rrc.sps_ConfigDL",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_SPS_ConfigDL_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_sps_ConfigUL,
      { "sps-ConfigUL", "lte-rrc.sps_ConfigUL",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_SPS_ConfigUL_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_setup_09,
      { "setup", "lte-rrc.setup",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_setup_09", HFILL }},
    { &hf_lte_rrc_semiPersistSchedIntervalDL,
      { "semiPersistSchedIntervalDL", "lte-rrc.semiPersistSchedIntervalDL",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_semiPersistSchedIntervalDL_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_numberOfConfSPS_Processes,
      { "numberOfConfSPS-Processes", "lte-rrc.numberOfConfSPS_Processes",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_8", HFILL }},
    { &hf_lte_rrc_n1_PUCCH_AN_PersistentList,
      { "n1-PUCCH-AN-PersistentList", "lte-rrc.n1_PUCCH_AN_PersistentList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_setup_10,
      { "setup", "lte-rrc.setup",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_setup_10", HFILL }},
    { &hf_lte_rrc_semiPersistSchedIntervalUL,
      { "semiPersistSchedIntervalUL", "lte-rrc.semiPersistSchedIntervalUL",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_semiPersistSchedIntervalUL_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_implicitReleaseAfter,
      { "implicitReleaseAfter", "lte-rrc.implicitReleaseAfter",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_implicitReleaseAfter_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_p0_Persistent,
      { "p0-Persistent", "lte-rrc.p0_Persistent",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_p0_NominalPUSCH_Persistent,
      { "p0-NominalPUSCH-Persistent", "lte-rrc.p0_NominalPUSCH_Persistent",
        FT_INT32, BASE_DEC, NULL, 0,
        "INTEGER_M126_24", HFILL }},
    { &hf_lte_rrc_p0_UE_PUSCH_Persistent,
      { "p0-UE-PUSCH-Persistent", "lte-rrc.p0_UE_PUSCH_Persistent",
        FT_INT32, BASE_DEC, NULL, 0,
        "INTEGER_M8_7", HFILL }},
    { &hf_lte_rrc_twoIntervalsConfig,
      { "twoIntervalsConfig", "lte-rrc.twoIntervalsConfig",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_twoIntervalsConfig_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_N1_PUCCH_AN_PersistentList_item,
      { "N1-PUCCH-AN-PersistentList item", "lte-rrc.N1_PUCCH_AN_PersistentList_item",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_2047", HFILL }},
    { &hf_lte_rrc_subframeAssignment,
      { "subframeAssignment", "lte-rrc.subframeAssignment",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_subframeAssignment_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_specialSubframePatterns,
      { "specialSubframePatterns", "lte-rrc.specialSubframePatterns",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_specialSubframePatterns_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_setup_11,
      { "setup", "lte-rrc.setup",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_setup_11", HFILL }},
    { &hf_lte_rrc_tpc_RNTI,
      { "tpc-RNTI", "lte-rrc.tpc_RNTI",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_16", HFILL }},
    { &hf_lte_rrc_tpc_Index,
      { "tpc-Index", "lte-rrc.tpc_Index",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_TPC_Index_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_indexOfFormat3,
      { "indexOfFormat3", "lte-rrc.indexOfFormat3",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_15", HFILL }},
    { &hf_lte_rrc_indexOfFormat3A,
      { "indexOfFormat3A", "lte-rrc.indexOfFormat3A",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_31", HFILL }},
    { &hf_lte_rrc_p0_NominalPUSCH,
      { "p0-NominalPUSCH", "lte-rrc.p0_NominalPUSCH",
        FT_INT32, BASE_DEC, NULL, 0,
        "INTEGER_M126_24", HFILL }},
    { &hf_lte_rrc_alpha,
      { "alpha", "lte-rrc.alpha",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_alpha_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_p0_NominalPUCCH,
      { "p0-NominalPUCCH", "lte-rrc.p0_NominalPUCCH",
        FT_INT32, BASE_DEC, NULL, 0,
        "INTEGER_M127_M96", HFILL }},
    { &hf_lte_rrc_deltaFList_PUCCH,
      { "deltaFList-PUCCH", "lte-rrc.deltaFList_PUCCH",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_deltaPreambleMsg3,
      { "deltaPreambleMsg3", "lte-rrc.deltaPreambleMsg3",
        FT_INT32, BASE_DEC, NULL, 0,
        "INTEGER_M1_6", HFILL }},
    { &hf_lte_rrc_p0_UE_PUSCH,
      { "p0-UE-PUSCH", "lte-rrc.p0_UE_PUSCH",
        FT_INT32, BASE_DEC, NULL, 0,
        "INTEGER_M8_7", HFILL }},
    { &hf_lte_rrc_deltaMCS_Enabled,
      { "deltaMCS-Enabled", "lte-rrc.deltaMCS_Enabled",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_deltaMCS_Enabled_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_accumulationEnabled,
      { "accumulationEnabled", "lte-rrc.accumulationEnabled",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_p0_UE_PUCCH,
      { "p0-UE-PUCCH", "lte-rrc.p0_UE_PUCCH",
        FT_INT32, BASE_DEC, NULL, 0,
        "INTEGER_M8_7", HFILL }},
    { &hf_lte_rrc_pSRS_Offset,
      { "pSRS-Offset", "lte-rrc.pSRS_Offset",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_15", HFILL }},
    { &hf_lte_rrc_filterCoefficient,
      { "filterCoefficient", "lte-rrc.filterCoefficient",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_FilterCoefficient_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_deltaF_PUCCH_Format1,
      { "deltaF-PUCCH-Format1", "lte-rrc.deltaF_PUCCH_Format1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_deltaF_PUCCH_Format1_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_deltaF_PUCCH_Format1b,
      { "deltaF-PUCCH-Format1b", "lte-rrc.deltaF_PUCCH_Format1b",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_deltaF_PUCCH_Format1b_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_deltaF_PUCCH_Format2,
      { "deltaF-PUCCH-Format2", "lte-rrc.deltaF_PUCCH_Format2",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_deltaF_PUCCH_Format2_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_deltaF_PUCCH_Format2a,
      { "deltaF-PUCCH-Format2a", "lte-rrc.deltaF_PUCCH_Format2a",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_deltaF_PUCCH_Format2a_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_deltaF_PUCCH_Format2b,
      { "deltaF-PUCCH-Format2b", "lte-rrc.deltaF_PUCCH_Format2b",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_deltaF_PUCCH_Format2b_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_cipheringAlgorithm,
      { "cipheringAlgorithm", "lte-rrc.cipheringAlgorithm",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_cipheringAlgorithm_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_integrityProtAlgorithm,
      { "integrityProtAlgorithm", "lte-rrc.integrityProtAlgorithm",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_integrityProtAlgorithm_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_arfcn_01,
      { "arfcn", "lte-rrc.arfcn",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ARFCN_ValueGERAN", HFILL }},
    { &hf_lte_rrc_bandIndicator,
      { "bandIndicator", "lte-rrc.bandIndicator",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_BandIndicatorGERAN_vals), 0,
        "BandIndicatorGERAN", HFILL }},
    { &hf_lte_rrc_startingARFCN,
      { "startingARFCN", "lte-rrc.startingARFCN",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ARFCN_ValueGERAN", HFILL }},
    { &hf_lte_rrc_followingARFCNs,
      { "followingARFCNs", "lte-rrc.followingARFCNs",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_followingARFCNs_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_explicitListOfARFCNs,
      { "explicitListOfARFCNs", "lte-rrc.explicitListOfARFCNs",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_equallySpacedARFCNs,
      { "equallySpacedARFCNs", "lte-rrc.equallySpacedARFCNs",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_arfcn_Spacing,
      { "arfcn-Spacing", "lte-rrc.arfcn_Spacing",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_8", HFILL }},
    { &hf_lte_rrc_numberOfFollowingARFCNs,
      { "numberOfFollowingARFCNs", "lte-rrc.numberOfFollowingARFCNs",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_31", HFILL }},
    { &hf_lte_rrc_variableBitMapOfARFCNs,
      { "variableBitMapOfARFCNs", "lte-rrc.variableBitMapOfARFCNs",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING_SIZE_1_16", HFILL }},
    { &hf_lte_rrc_ExplicitListOfARFCNs_item,
      { "ARFCN-ValueGERAN", "lte-rrc.ARFCN_ValueGERAN",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_CellIndexList_item,
      { "CellIndex", "lte-rrc.CellIndex",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_sid,
      { "sid", "lte-rrc.sid",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_15", HFILL }},
    { &hf_lte_rrc_nid,
      { "nid", "lte-rrc.nid",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_16", HFILL }},
    { &hf_lte_rrc_multipleSID,
      { "multipleSID", "lte-rrc.multipleSID",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_multipleNID,
      { "multipleNID", "lte-rrc.multipleNID",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_homeReg,
      { "homeReg", "lte-rrc.homeReg",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_foreignSIDReg,
      { "foreignSIDReg", "lte-rrc.foreignSIDReg",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_foreignNIDReg,
      { "foreignNIDReg", "lte-rrc.foreignNIDReg",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_parameterReg,
      { "parameterReg", "lte-rrc.parameterReg",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_powerUpReg,
      { "powerUpReg", "lte-rrc.powerUpReg",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_registrationPeriod,
      { "registrationPeriod", "lte-rrc.registrationPeriod",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_7", HFILL }},
    { &hf_lte_rrc_registrationZone,
      { "registrationZone", "lte-rrc.registrationZone",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_12", HFILL }},
    { &hf_lte_rrc_totalZone,
      { "totalZone", "lte-rrc.totalZone",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_3", HFILL }},
    { &hf_lte_rrc_zoneTimer,
      { "zoneTimer", "lte-rrc.zoneTimer",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_3", HFILL }},
    { &hf_lte_rrc_powerDownReg_r9,
      { "powerDownReg-r9", "lte-rrc.powerDownReg_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_powerDownReg_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_cellIdentity_01,
      { "cellIdentity", "lte-rrc.cellIdentity",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_28", HFILL }},
    { &hf_lte_rrc_locationAreaCode,
      { "locationAreaCode", "lte-rrc.locationAreaCode",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_16", HFILL }},
    { &hf_lte_rrc_cellIdentity_02,
      { "cellIdentity", "lte-rrc.cellIdentity",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_16", HFILL }},
    { &hf_lte_rrc_cellGlobalId1XRTT,
      { "cellGlobalId1XRTT", "lte-rrc.cellGlobalId1XRTT",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_47", HFILL }},
    { &hf_lte_rrc_cellGlobalIdHRPD,
      { "cellGlobalIdHRPD", "lte-rrc.cellGlobalIdHRPD",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_128", HFILL }},
    { &hf_lte_rrc_targetPhysCellId,
      { "targetPhysCellId", "lte-rrc.targetPhysCellId",
        FT_UINT32, BASE_DEC, NULL, 0,
        "PhysCellId", HFILL }},
    { &hf_lte_rrc_carrierFreq_04,
      { "carrierFreq", "lte-rrc.carrierFreq",
        FT_NONE, BASE_NONE, NULL, 0,
        "CarrierFreqEUTRA", HFILL }},
    { &hf_lte_rrc_carrierBandwidth,
      { "carrierBandwidth", "lte-rrc.carrierBandwidth",
        FT_NONE, BASE_NONE, NULL, 0,
        "CarrierBandwidthEUTRA", HFILL }},
    { &hf_lte_rrc_t304_01,
      { "t304", "lte-rrc.t304",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_t304_01_vals), 0,
        "T_t304_01", HFILL }},
    { &hf_lte_rrc_newUE_Identity,
      { "newUE-Identity", "lte-rrc.newUE_Identity",
        FT_BYTES, BASE_NONE, NULL, 0,
        "C_RNTI", HFILL }},
    { &hf_lte_rrc_radioResourceConfigCommon_01,
      { "radioResourceConfigCommon", "lte-rrc.radioResourceConfigCommon",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_rach_ConfigDedicated,
      { "rach-ConfigDedicated", "lte-rrc.rach_ConfigDedicated",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_dl_Bandwidth_01,
      { "dl-Bandwidth", "lte-rrc.dl_Bandwidth",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_dl_Bandwidth_01_vals), 0,
        "T_dl_Bandwidth_01", HFILL }},
    { &hf_lte_rrc_ul_Bandwidth_01,
      { "ul-Bandwidth", "lte-rrc.ul_Bandwidth",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_ul_Bandwidth_01_vals), 0,
        "T_ul_Bandwidth_01", HFILL }},
    { &hf_lte_rrc_t_Evaluation,
      { "t-Evaluation", "lte-rrc.t_Evaluation",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_t_Evaluation_vals), 0,
        "T_t_Evaluation", HFILL }},
    { &hf_lte_rrc_t_HystNormal,
      { "t-HystNormal", "lte-rrc.t_HystNormal",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_t_HystNormal_vals), 0,
        "T_t_HystNormal", HFILL }},
    { &hf_lte_rrc_n_CellChangeMedium,
      { "n-CellChangeMedium", "lte-rrc.n_CellChangeMedium",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_16", HFILL }},
    { &hf_lte_rrc_n_CellChangeHigh,
      { "n-CellChangeHigh", "lte-rrc.n_CellChangeHigh",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_16", HFILL }},
    { &hf_lte_rrc_start,
      { "start", "lte-rrc.start",
        FT_UINT32, BASE_DEC, NULL, 0,
        "PhysCellId", HFILL }},
    { &hf_lte_rrc_range,
      { "range", "lte-rrc.range",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_range_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_networkColourCode,
      { "networkColourCode", "lte-rrc.networkColourCode",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_3", HFILL }},
    { &hf_lte_rrc_baseStationColourCode,
      { "baseStationColourCode", "lte-rrc.baseStationColourCode",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_3", HFILL }},
    { &hf_lte_rrc_mcc,
      { "mcc", "lte-rrc.mcc",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_mnc,
      { "mnc", "lte-rrc.mnc",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_MCC_item,
      { "MCC-MNC-Digit", "lte-rrc.MCC_MNC_Digit",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_MNC_item,
      { "MCC-MNC-Digit", "lte-rrc.MCC_MNC_Digit",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_preRegistrationAllowed,
      { "preRegistrationAllowed", "lte-rrc.preRegistrationAllowed",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_preRegistrationZoneId,
      { "preRegistrationZoneId", "lte-rrc.preRegistrationZoneId",
        FT_UINT32, BASE_DEC, NULL, 0,
        "PreRegistrationZoneIdHRPD", HFILL }},
    { &hf_lte_rrc_secondaryPreRegistrationZoneIdList,
      { "secondaryPreRegistrationZoneIdList", "lte-rrc.secondaryPreRegistrationZoneIdList",
        FT_UINT32, BASE_DEC, NULL, 0,
        "SecondaryPreRegistrationZoneIdListHRPD", HFILL }},
    { &hf_lte_rrc_SecondaryPreRegistrationZoneIdListHRPD_item,
      { "PreRegistrationZoneIdHRPD", "lte-rrc.PreRegistrationZoneIdHRPD",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_sf_Medium_01,
      { "sf-Medium", "lte-rrc.sf_Medium",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_sf_Medium_01_vals), 0,
        "T_sf_Medium_01", HFILL }},
    { &hf_lte_rrc_sf_High_01,
      { "sf-High", "lte-rrc.sf_High",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_sf_High_01_vals), 0,
        "T_sf_High_01", HFILL }},
    { &hf_lte_rrc_SystemInfoListGERAN_item,
      { "SystemInfoListGERAN item", "lte-rrc.SystemInfoListGERAN_item",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING_SIZE_1_23", HFILL }},
    { &hf_lte_rrc_cdma_EUTRA_Synchronisation,
      { "cdma-EUTRA-Synchronisation", "lte-rrc.cdma_EUTRA_Synchronisation",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_cdma_SystemTime,
      { "cdma-SystemTime", "lte-rrc.cdma_SystemTime",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_cdma_SystemTime_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_synchronousSystemTime,
      { "synchronousSystemTime", "lte-rrc.synchronousSystemTime",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_39", HFILL }},
    { &hf_lte_rrc_asynchronousSystemTime,
      { "asynchronousSystemTime", "lte-rrc.asynchronousSystemTime",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_49", HFILL }},
    { &hf_lte_rrc_measObjectToRemoveList,
      { "measObjectToRemoveList", "lte-rrc.measObjectToRemoveList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_measObjectToAddModList,
      { "measObjectToAddModList", "lte-rrc.measObjectToAddModList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_reportConfigToRemoveList,
      { "reportConfigToRemoveList", "lte-rrc.reportConfigToRemoveList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_reportConfigToAddModList,
      { "reportConfigToAddModList", "lte-rrc.reportConfigToAddModList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_measIdToRemoveList,
      { "measIdToRemoveList", "lte-rrc.measIdToRemoveList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_measIdToAddModList,
      { "measIdToAddModList", "lte-rrc.measIdToAddModList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_quantityConfig,
      { "quantityConfig", "lte-rrc.quantityConfig",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_measGapConfig,
      { "measGapConfig", "lte-rrc.measGapConfig",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_MeasGapConfig_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_s_Measure,
      { "s-Measure", "lte-rrc.s_Measure",
        FT_UINT32, BASE_DEC, NULL, 0,
        "RSRP_Range", HFILL }},
    { &hf_lte_rrc_speedStatePars,
      { "speedStatePars", "lte-rrc.speedStatePars",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_speedStatePars_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_setup_12,
      { "setup", "lte-rrc.setup",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_setup_12", HFILL }},
    { &hf_lte_rrc_timeToTrigger_SF,
      { "timeToTrigger-SF", "lte-rrc.timeToTrigger_SF",
        FT_NONE, BASE_NONE, NULL, 0,
        "SpeedStateScaleFactors", HFILL }},
    { &hf_lte_rrc_MeasIdToRemoveList_item,
      { "MeasId", "lte-rrc.MeasId",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_MeasObjectToRemoveList_item,
      { "MeasObjectId", "lte-rrc.MeasObjectId",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ReportConfigToRemoveList_item,
      { "ReportConfigId", "lte-rrc.ReportConfigId",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_setup_13,
      { "setup", "lte-rrc.setup",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_setup_13", HFILL }},
    { &hf_lte_rrc_gapOffset,
      { "gapOffset", "lte-rrc.gapOffset",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_gapOffset_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_gp0,
      { "gp0", "lte-rrc.gp0",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_39", HFILL }},
    { &hf_lte_rrc_gp1,
      { "gp1", "lte-rrc.gp1",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_79", HFILL }},
    { &hf_lte_rrc_MeasIdToAddModList_item,
      { "MeasIdToAddMod", "lte-rrc.MeasIdToAddMod",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_measId,
      { "measId", "lte-rrc.measId",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_measObjectId,
      { "measObjectId", "lte-rrc.measObjectId",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_reportConfigId,
      { "reportConfigId", "lte-rrc.reportConfigId",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_offsetFreq,
      { "offsetFreq", "lte-rrc.offsetFreq",
        FT_INT32, BASE_DEC, NULL, 0,
        "Q_OffsetRangeInterRAT", HFILL }},
    { &hf_lte_rrc_cellsToRemoveList,
      { "cellsToRemoveList", "lte-rrc.cellsToRemoveList",
        FT_UINT32, BASE_DEC, NULL, 0,
        "CellIndexList", HFILL }},
    { &hf_lte_rrc_cellsToAddModList,
      { "cellsToAddModList", "lte-rrc.cellsToAddModList",
        FT_UINT32, BASE_DEC, NULL, 0,
        "CellsToAddModListCDMA2000", HFILL }},
    { &hf_lte_rrc_cellForWhichToReportCGI,
      { "cellForWhichToReportCGI", "lte-rrc.cellForWhichToReportCGI",
        FT_UINT32, BASE_DEC, NULL, 0,
        "PhysCellIdCDMA2000", HFILL }},
    { &hf_lte_rrc_CellsToAddModListCDMA2000_item,
      { "CellsToAddModCDMA2000", "lte-rrc.CellsToAddModCDMA2000",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_cellIndex,
      { "cellIndex", "lte-rrc.cellIndex",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_maxCellMeas", HFILL }},
    { &hf_lte_rrc_physCellId_02,
      { "physCellId", "lte-rrc.physCellId",
        FT_UINT32, BASE_DEC, NULL, 0,
        "PhysCellIdCDMA2000", HFILL }},
    { &hf_lte_rrc_offsetFreq_01,
      { "offsetFreq", "lte-rrc.offsetFreq",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_Q_OffsetRange_vals), 0,
        "Q_OffsetRange", HFILL }},
    { &hf_lte_rrc_cellsToAddModList_01,
      { "cellsToAddModList", "lte-rrc.cellsToAddModList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_blackCellsToRemoveList,
      { "blackCellsToRemoveList", "lte-rrc.blackCellsToRemoveList",
        FT_UINT32, BASE_DEC, NULL, 0,
        "CellIndexList", HFILL }},
    { &hf_lte_rrc_blackCellsToAddModList,
      { "blackCellsToAddModList", "lte-rrc.blackCellsToAddModList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_cellForWhichToReportCGI_01,
      { "cellForWhichToReportCGI", "lte-rrc.cellForWhichToReportCGI",
        FT_UINT32, BASE_DEC, NULL, 0,
        "PhysCellId", HFILL }},
    { &hf_lte_rrc_CellsToAddModList_item,
      { "CellsToAddMod", "lte-rrc.CellsToAddMod",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_cellIndividualOffset,
      { "cellIndividualOffset", "lte-rrc.cellIndividualOffset",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_Q_OffsetRange_vals), 0,
        "Q_OffsetRange", HFILL }},
    { &hf_lte_rrc_BlackCellsToAddModList_item,
      { "BlackCellsToAddMod", "lte-rrc.BlackCellsToAddMod",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_physCellIdRange,
      { "physCellIdRange", "lte-rrc.physCellIdRange",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_cellForWhichToReportCGI_02,
      { "cellForWhichToReportCGI", "lte-rrc.cellForWhichToReportCGI",
        FT_NONE, BASE_NONE, NULL, 0,
        "PhysCellIdGERAN", HFILL }},
    { &hf_lte_rrc_MeasObjectToAddModList_item,
      { "MeasObjectToAddMod", "lte-rrc.MeasObjectToAddMod",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_measObject,
      { "measObject", "lte-rrc.measObject",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_measObject_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_measObjectEUTRA,
      { "measObjectEUTRA", "lte-rrc.measObjectEUTRA",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_measObjectUTRA,
      { "measObjectUTRA", "lte-rrc.measObjectUTRA",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_measObjectGERAN,
      { "measObjectGERAN", "lte-rrc.measObjectGERAN",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_measObjectCDMA2000,
      { "measObjectCDMA2000", "lte-rrc.measObjectCDMA2000",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_cellsToAddModList_02,
      { "cellsToAddModList", "lte-rrc.cellsToAddModList",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_cellsToAddModList_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_cellsToAddModListUTRA_FDD,
      { "cellsToAddModListUTRA-FDD", "lte-rrc.cellsToAddModListUTRA_FDD",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_cellsToAddModListUTRA_TDD,
      { "cellsToAddModListUTRA-TDD", "lte-rrc.cellsToAddModListUTRA_TDD",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_cellForWhichToReportCGI_03,
      { "cellForWhichToReportCGI", "lte-rrc.cellForWhichToReportCGI",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_cellForWhichToReportCGI_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_utra_FDD_01,
      { "utra-FDD", "lte-rrc.utra_FDD",
        FT_UINT32, BASE_DEC, NULL, 0,
        "PhysCellIdUTRA_FDD", HFILL }},
    { &hf_lte_rrc_utra_TDD_01,
      { "utra-TDD", "lte-rrc.utra_TDD",
        FT_UINT32, BASE_DEC, NULL, 0,
        "PhysCellIdUTRA_TDD", HFILL }},
    { &hf_lte_rrc_CellsToAddModListUTRA_FDD_item,
      { "CellsToAddModUTRA-FDD", "lte-rrc.CellsToAddModUTRA_FDD",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_physCellId_03,
      { "physCellId", "lte-rrc.physCellId",
        FT_UINT32, BASE_DEC, NULL, 0,
        "PhysCellIdUTRA_FDD", HFILL }},
    { &hf_lte_rrc_CellsToAddModListUTRA_TDD_item,
      { "CellsToAddModUTRA-TDD", "lte-rrc.CellsToAddModUTRA_TDD",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_physCellId_04,
      { "physCellId", "lte-rrc.physCellId",
        FT_UINT32, BASE_DEC, NULL, 0,
        "PhysCellIdUTRA_TDD", HFILL }},
    { &hf_lte_rrc_measResultServCell,
      { "measResultServCell", "lte-rrc.measResultServCell",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_measResultNeighCells_01,
      { "measResultNeighCells", "lte-rrc.measResultNeighCells",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_measResultNeighCells_01_vals), 0,
        "T_measResultNeighCells_01", HFILL }},
    { &hf_lte_rrc_measResultListEUTRA_01,
      { "measResultListEUTRA", "lte-rrc.measResultListEUTRA",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_measResultListUTRA_01,
      { "measResultListUTRA", "lte-rrc.measResultListUTRA",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_measResultsCDMA2000_01,
      { "measResultsCDMA2000", "lte-rrc.measResultsCDMA2000",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_measResultForECID_r9,
      { "measResultForECID-r9", "lte-rrc.measResultForECID_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_MeasResultListEUTRA_item,
      { "MeasResultEUTRA", "lte-rrc.MeasResultEUTRA",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_cgi_Info,
      { "cgi-Info", "lte-rrc.cgi_Info",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_cellGlobalId,
      { "cellGlobalId", "lte-rrc.cellGlobalId",
        FT_NONE, BASE_NONE, NULL, 0,
        "CellGlobalIdEUTRA", HFILL }},
    { &hf_lte_rrc_plmn_IdentityList_01,
      { "plmn-IdentityList", "lte-rrc.plmn_IdentityList",
        FT_UINT32, BASE_DEC, NULL, 0,
        "PLMN_IdentityList2", HFILL }},
    { &hf_lte_rrc_measResult,
      { "measResult", "lte-rrc.measResult",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_additionalSI_Info_r9,
      { "additionalSI-Info-r9", "lte-rrc.additionalSI_Info_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_MeasResultListUTRA_item,
      { "MeasResultUTRA", "lte-rrc.MeasResultUTRA",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_physCellId_05,
      { "physCellId", "lte-rrc.physCellId",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_physCellId_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_fdd,
      { "fdd", "lte-rrc.fdd",
        FT_UINT32, BASE_DEC, NULL, 0,
        "PhysCellIdUTRA_FDD", HFILL }},
    { &hf_lte_rrc_tdd,
      { "tdd", "lte-rrc.tdd",
        FT_UINT32, BASE_DEC, NULL, 0,
        "PhysCellIdUTRA_TDD", HFILL }},
    { &hf_lte_rrc_cgi_Info_01,
      { "cgi-Info", "lte-rrc.cgi_Info",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_cgi_Info_01", HFILL }},
    { &hf_lte_rrc_cellGlobalId_01,
      { "cellGlobalId", "lte-rrc.cellGlobalId",
        FT_NONE, BASE_NONE, NULL, 0,
        "CellGlobalIdUTRA", HFILL }},
    { &hf_lte_rrc_routingAreaCode,
      { "routingAreaCode", "lte-rrc.routingAreaCode",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_8", HFILL }},
    { &hf_lte_rrc_measResult_01,
      { "measResult", "lte-rrc.measResult",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_measResult_01", HFILL }},
    { &hf_lte_rrc_utra_RSCP,
      { "utra-RSCP", "lte-rrc.utra_RSCP",
        FT_INT32, BASE_DEC, NULL, 0,
        "INTEGER_M5_91", HFILL }},
    { &hf_lte_rrc_utra_EcN0,
      { "utra-EcN0", "lte-rrc.utra_EcN0",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_49", HFILL }},
    { &hf_lte_rrc_MeasResultListGERAN_item,
      { "MeasResultGERAN", "lte-rrc.MeasResultGERAN",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_cgi_Info_02,
      { "cgi-Info", "lte-rrc.cgi_Info",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_cgi_Info_02", HFILL }},
    { &hf_lte_rrc_cellGlobalId_02,
      { "cellGlobalId", "lte-rrc.cellGlobalId",
        FT_NONE, BASE_NONE, NULL, 0,
        "CellGlobalIdGERAN", HFILL }},
    { &hf_lte_rrc_measResult_02,
      { "measResult", "lte-rrc.measResult",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_measResult_02", HFILL }},
    { &hf_lte_rrc_rssi,
      { "rssi", "lte-rrc.rssi",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_63", HFILL }},
    { &hf_lte_rrc_preRegistrationStatusHRPD,
      { "preRegistrationStatusHRPD", "lte-rrc.preRegistrationStatusHRPD",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_measResultListCDMA2000,
      { "measResultListCDMA2000", "lte-rrc.measResultListCDMA2000",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_MeasResultListCDMA2000_item,
      { "MeasResultCDMA2000", "lte-rrc.MeasResultCDMA2000",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_cgi_Info_03,
      { "cgi-Info", "lte-rrc.cgi_Info",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_CellGlobalIdCDMA2000_vals), 0,
        "CellGlobalIdCDMA2000", HFILL }},
    { &hf_lte_rrc_measResult_03,
      { "measResult", "lte-rrc.measResult",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_measResult_03", HFILL }},
    { &hf_lte_rrc_pilotPnPhase,
      { "pilotPnPhase", "lte-rrc.pilotPnPhase",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_32767", HFILL }},
    { &hf_lte_rrc_pilotStrength,
      { "pilotStrength", "lte-rrc.pilotStrength",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_63", HFILL }},
    { &hf_lte_rrc_ue_RxTxTimeDiffResult_r9,
      { "ue-RxTxTimeDiffResult-r9", "lte-rrc.ue_RxTxTimeDiffResult_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_4095", HFILL }},
    { &hf_lte_rrc_currentSFN_r9,
      { "currentSFN-r9", "lte-rrc.currentSFN_r9",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_10", HFILL }},
    { &hf_lte_rrc_PLMN_IdentityList2_item,
      { "PLMN-Identity", "lte-rrc.PLMN_Identity",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_csg_MemberStatus_r9,
      { "csg-MemberStatus-r9", "lte-rrc.csg_MemberStatus_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_csg_MemberStatus_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_csg_Identity_r9,
      { "csg-Identity-r9", "lte-rrc.csg_Identity_r9",
        FT_BYTES, BASE_NONE, NULL, 0,
        "CSG_Identity", HFILL }},
    { &hf_lte_rrc_quantityConfigEUTRA,
      { "quantityConfigEUTRA", "lte-rrc.quantityConfigEUTRA",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_quantityConfigUTRA,
      { "quantityConfigUTRA", "lte-rrc.quantityConfigUTRA",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_quantityConfigGERAN,
      { "quantityConfigGERAN", "lte-rrc.quantityConfigGERAN",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_quantityConfigCDMA2000,
      { "quantityConfigCDMA2000", "lte-rrc.quantityConfigCDMA2000",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_filterCoefficientRSRP,
      { "filterCoefficientRSRP", "lte-rrc.filterCoefficientRSRP",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_FilterCoefficient_vals), 0,
        "FilterCoefficient", HFILL }},
    { &hf_lte_rrc_filterCoefficientRSRQ,
      { "filterCoefficientRSRQ", "lte-rrc.filterCoefficientRSRQ",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_FilterCoefficient_vals), 0,
        "FilterCoefficient", HFILL }},
    { &hf_lte_rrc_measQuantityUTRA_FDD,
      { "measQuantityUTRA-FDD", "lte-rrc.measQuantityUTRA_FDD",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_measQuantityUTRA_FDD_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_measQuantityUTRA_TDD,
      { "measQuantityUTRA-TDD", "lte-rrc.measQuantityUTRA_TDD",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_measQuantityUTRA_TDD_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_measQuantityGERAN,
      { "measQuantityGERAN", "lte-rrc.measQuantityGERAN",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_measQuantityGERAN_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_measQuantityCDMA2000,
      { "measQuantityCDMA2000", "lte-rrc.measQuantityCDMA2000",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_measQuantityCDMA2000_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_triggerType,
      { "triggerType", "lte-rrc.triggerType",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_triggerType_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_event,
      { "event", "lte-rrc.event",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_eventId,
      { "eventId", "lte-rrc.eventId",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_eventId_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_eventA1,
      { "eventA1", "lte-rrc.eventA1",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_a1_Threshold,
      { "a1-Threshold", "lte-rrc.a1_Threshold",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_ThresholdEUTRA_vals), 0,
        "ThresholdEUTRA", HFILL }},
    { &hf_lte_rrc_eventA2,
      { "eventA2", "lte-rrc.eventA2",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_a2_Threshold,
      { "a2-Threshold", "lte-rrc.a2_Threshold",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_ThresholdEUTRA_vals), 0,
        "ThresholdEUTRA", HFILL }},
    { &hf_lte_rrc_eventA3,
      { "eventA3", "lte-rrc.eventA3",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_a3_Offset,
      { "a3-Offset", "lte-rrc.a3_Offset",
        FT_INT32, BASE_DEC, NULL, 0,
        "INTEGER_M30_30", HFILL }},
    { &hf_lte_rrc_reportOnLeave,
      { "reportOnLeave", "lte-rrc.reportOnLeave",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_eventA4,
      { "eventA4", "lte-rrc.eventA4",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_a4_Threshold,
      { "a4-Threshold", "lte-rrc.a4_Threshold",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_ThresholdEUTRA_vals), 0,
        "ThresholdEUTRA", HFILL }},
    { &hf_lte_rrc_eventA5,
      { "eventA5", "lte-rrc.eventA5",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_a5_Threshold1,
      { "a5-Threshold1", "lte-rrc.a5_Threshold1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_ThresholdEUTRA_vals), 0,
        "ThresholdEUTRA", HFILL }},
    { &hf_lte_rrc_a5_Threshold2,
      { "a5-Threshold2", "lte-rrc.a5_Threshold2",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_ThresholdEUTRA_vals), 0,
        "ThresholdEUTRA", HFILL }},
    { &hf_lte_rrc_hysteresis,
      { "hysteresis", "lte-rrc.hysteresis",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_timeToTrigger,
      { "timeToTrigger", "lte-rrc.timeToTrigger",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_TimeToTrigger_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_periodical,
      { "periodical", "lte-rrc.periodical",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_purpose_02,
      { "purpose", "lte-rrc.purpose",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_purpose_02_vals), 0,
        "T_purpose_02", HFILL }},
    { &hf_lte_rrc_triggerQuantity,
      { "triggerQuantity", "lte-rrc.triggerQuantity",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_triggerQuantity_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_reportQuantity,
      { "reportQuantity", "lte-rrc.reportQuantity",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_reportQuantity_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_maxReportCells,
      { "maxReportCells", "lte-rrc.maxReportCells",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_maxCellReport", HFILL }},
    { &hf_lte_rrc_reportInterval,
      { "reportInterval", "lte-rrc.reportInterval",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_ReportInterval_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_reportAmount,
      { "reportAmount", "lte-rrc.reportAmount",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_reportAmount_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_si_RequestForHO_r9,
      { "si-RequestForHO-r9", "lte-rrc.si_RequestForHO_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_si_RequestForHO_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ue_RxTxTimeDiffPeriodical_r9,
      { "ue-RxTxTimeDiffPeriodical-r9", "lte-rrc.ue_RxTxTimeDiffPeriodical_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_ue_RxTxTimeDiffPeriodical_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_threshold_RSRP,
      { "threshold-RSRP", "lte-rrc.threshold_RSRP",
        FT_UINT32, BASE_DEC, NULL, 0,
        "RSRP_Range", HFILL }},
    { &hf_lte_rrc_threshold_RSRQ,
      { "threshold-RSRQ", "lte-rrc.threshold_RSRQ",
        FT_UINT32, BASE_DEC, NULL, 0,
        "RSRQ_Range", HFILL }},
    { &hf_lte_rrc_triggerType_01,
      { "triggerType", "lte-rrc.triggerType",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_triggerType_01_vals), 0,
        "T_triggerType_01", HFILL }},
    { &hf_lte_rrc_event_01,
      { "event", "lte-rrc.event",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_event_01", HFILL }},
    { &hf_lte_rrc_eventId_01,
      { "eventId", "lte-rrc.eventId",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_eventId_01_vals), 0,
        "T_eventId_01", HFILL }},
    { &hf_lte_rrc_eventB1,
      { "eventB1", "lte-rrc.eventB1",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_b1_Threshold,
      { "b1-Threshold", "lte-rrc.b1_Threshold",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_b1_Threshold_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_b1_ThresholdUTRA,
      { "b1-ThresholdUTRA", "lte-rrc.b1_ThresholdUTRA",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_ThresholdUTRA_vals), 0,
        "ThresholdUTRA", HFILL }},
    { &hf_lte_rrc_b1_ThresholdGERAN,
      { "b1-ThresholdGERAN", "lte-rrc.b1_ThresholdGERAN",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ThresholdGERAN", HFILL }},
    { &hf_lte_rrc_b1_ThresholdCDMA2000,
      { "b1-ThresholdCDMA2000", "lte-rrc.b1_ThresholdCDMA2000",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ThresholdCDMA2000", HFILL }},
    { &hf_lte_rrc_eventB2,
      { "eventB2", "lte-rrc.eventB2",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_b2_Threshold1,
      { "b2-Threshold1", "lte-rrc.b2_Threshold1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_ThresholdEUTRA_vals), 0,
        "ThresholdEUTRA", HFILL }},
    { &hf_lte_rrc_b2_Threshold2,
      { "b2-Threshold2", "lte-rrc.b2_Threshold2",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_b2_Threshold2_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_b2_Threshold2UTRA,
      { "b2-Threshold2UTRA", "lte-rrc.b2_Threshold2UTRA",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_ThresholdUTRA_vals), 0,
        "ThresholdUTRA", HFILL }},
    { &hf_lte_rrc_b2_Threshold2GERAN,
      { "b2-Threshold2GERAN", "lte-rrc.b2_Threshold2GERAN",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ThresholdGERAN", HFILL }},
    { &hf_lte_rrc_b2_Threshold2CDMA2000,
      { "b2-Threshold2CDMA2000", "lte-rrc.b2_Threshold2CDMA2000",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ThresholdCDMA2000", HFILL }},
    { &hf_lte_rrc_periodical_01,
      { "periodical", "lte-rrc.periodical",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_periodical_01", HFILL }},
    { &hf_lte_rrc_purpose_03,
      { "purpose", "lte-rrc.purpose",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_purpose_03_vals), 0,
        "T_purpose_03", HFILL }},
    { &hf_lte_rrc_reportAmount_01,
      { "reportAmount", "lte-rrc.reportAmount",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_reportAmount_01_vals), 0,
        "T_reportAmount_01", HFILL }},
    { &hf_lte_rrc_si_RequestForHO_r9_01,
      { "si-RequestForHO-r9", "lte-rrc.si_RequestForHO_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_si_RequestForHO_r9_01_vals), 0,
        "T_si_RequestForHO_r9_01", HFILL }},
    { &hf_lte_rrc_ReportConfigToAddModList_item,
      { "ReportConfigToAddMod", "lte-rrc.ReportConfigToAddMod",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_reportConfig,
      { "reportConfig", "lte-rrc.reportConfig",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_reportConfig_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_reportConfigEUTRA,
      { "reportConfigEUTRA", "lte-rrc.reportConfigEUTRA",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_reportConfigInterRAT,
      { "reportConfigInterRAT", "lte-rrc.reportConfigInterRAT",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_reportProximityConfig_r9,
      { "reportProximityConfig-r9", "lte-rrc.reportProximityConfig_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_proximityIndicationEUTRA_r9,
      { "proximityIndicationEUTRA-r9", "lte-rrc.proximityIndicationEUTRA_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_proximityIndicationEUTRA_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_proximityIndicationUTRA_r9,
      { "proximityIndicationUTRA-r9", "lte-rrc.proximityIndicationUTRA_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_proximityIndicationUTRA_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_m_TMSI,
      { "m-TMSI", "lte-rrc.m_TMSI",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_32", HFILL }},
    { &hf_lte_rrc_UE_CapabilityRAT_ContainerList_item,
      { "UE-CapabilityRAT-Container", "lte-rrc.UE_CapabilityRAT_Container",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_rat_Type,
      { "rat-Type", "lte-rrc.rat_Type",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_RAT_Type_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ueCapabilityRAT_Container,
      { "ueCapabilityRAT-Container", "lte-rrc.ueCapabilityRAT_Container",
        FT_BYTES, BASE_NONE, NULL, 0,
        "T_ueCapabilityRAT_Container", HFILL }},
    { &hf_lte_rrc_accessStratumRelease,
      { "accessStratumRelease", "lte-rrc.accessStratumRelease",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_AccessStratumRelease_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ue_Category,
      { "ue-Category", "lte-rrc.ue_Category",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_5", HFILL }},
    { &hf_lte_rrc_pdcp_Parameters,
      { "pdcp-Parameters", "lte-rrc.pdcp_Parameters",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_phyLayerParameters,
      { "phyLayerParameters", "lte-rrc.phyLayerParameters",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_rf_Parameters,
      { "rf-Parameters", "lte-rrc.rf_Parameters",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_measParameters,
      { "measParameters", "lte-rrc.measParameters",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_featureGroupIndicators,
      { "featureGroupIndicators", "lte-rrc.featureGroupIndicators",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_32", HFILL }},
    { &hf_lte_rrc_interRAT_Parameters,
      { "interRAT-Parameters", "lte-rrc.interRAT_Parameters",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_interRAT_Parameters", HFILL }},
    { &hf_lte_rrc_utraFDD,
      { "utraFDD", "lte-rrc.utraFDD",
        FT_NONE, BASE_NONE, NULL, 0,
        "IRAT_ParametersUTRA_FDD", HFILL }},
    { &hf_lte_rrc_utraTDD128,
      { "utraTDD128", "lte-rrc.utraTDD128",
        FT_NONE, BASE_NONE, NULL, 0,
        "IRAT_ParametersUTRA_TDD128", HFILL }},
    { &hf_lte_rrc_utraTDD384,
      { "utraTDD384", "lte-rrc.utraTDD384",
        FT_NONE, BASE_NONE, NULL, 0,
        "IRAT_ParametersUTRA_TDD384", HFILL }},
    { &hf_lte_rrc_utraTDD768,
      { "utraTDD768", "lte-rrc.utraTDD768",
        FT_NONE, BASE_NONE, NULL, 0,
        "IRAT_ParametersUTRA_TDD768", HFILL }},
    { &hf_lte_rrc_geran_02,
      { "geran", "lte-rrc.geran",
        FT_NONE, BASE_NONE, NULL, 0,
        "IRAT_ParametersGERAN", HFILL }},
    { &hf_lte_rrc_cdma2000_HRPD_01,
      { "cdma2000-HRPD", "lte-rrc.cdma2000_HRPD",
        FT_NONE, BASE_NONE, NULL, 0,
        "IRAT_ParametersCDMA2000_HRPD", HFILL }},
    { &hf_lte_rrc_cdma2000_1xRTT_01,
      { "cdma2000-1xRTT", "lte-rrc.cdma2000_1xRTT",
        FT_NONE, BASE_NONE, NULL, 0,
        "IRAT_ParametersCDMA2000_1XRTT", HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_43,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "UE_EUTRA_Capability_v920_IEs", HFILL }},
    { &hf_lte_rrc_phyLayerParameters_v920,
      { "phyLayerParameters-v920", "lte-rrc.phyLayerParameters_v920",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_interRAT_ParametersGERAN_v920,
      { "interRAT-ParametersGERAN-v920", "lte-rrc.interRAT_ParametersGERAN_v920",
        FT_NONE, BASE_NONE, NULL, 0,
        "IRAT_ParametersGERAN_v920", HFILL }},
    { &hf_lte_rrc_interRAT_ParametersUTRA_v920,
      { "interRAT-ParametersUTRA-v920", "lte-rrc.interRAT_ParametersUTRA_v920",
        FT_NONE, BASE_NONE, NULL, 0,
        "IRAT_ParametersUTRA_v920", HFILL }},
    { &hf_lte_rrc_interRAT_Parameters_v920,
      { "interRAT-Parameters-v920", "lte-rrc.interRAT_Parameters_v920",
        FT_NONE, BASE_NONE, NULL, 0,
        "IRAT_ParametersCDMA2000_1XRTT_v920", HFILL }},
    { &hf_lte_rrc_deviceType_r9,
      { "deviceType-r9", "lte-rrc.deviceType_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_deviceType_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_csg_ProximityIndicationParameters_r9,
      { "csg-ProximityIndicationParameters-r9", "lte-rrc.csg_ProximityIndicationParameters_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_neighCellSI_AcquisitionParameters_r9,
      { "neighCellSI-AcquisitionParameters-r9", "lte-rrc.neighCellSI_AcquisitionParameters_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_son_Parameters_r9,
      { "son-Parameters-r9", "lte-rrc.son_Parameters_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_44,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_32", HFILL }},
    { &hf_lte_rrc_supportedROHC_Profiles,
      { "supportedROHC-Profiles", "lte-rrc.supportedROHC_Profiles",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_maxNumberROHC_ContextSessions,
      { "maxNumberROHC-ContextSessions", "lte-rrc.maxNumberROHC_ContextSessions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_maxNumberROHC_ContextSessions_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ue_TxAntennaSelectionSupported,
      { "ue-TxAntennaSelectionSupported", "lte-rrc.ue_TxAntennaSelectionSupported",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_ue_SpecificRefSigsSupported,
      { "ue-SpecificRefSigsSupported", "lte-rrc.ue_SpecificRefSigsSupported",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_enhancedDualLayerFDD_Supported_r9,
      { "enhancedDualLayerFDD-Supported-r9", "lte-rrc.enhancedDualLayerFDD_Supported_r9",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_enhancedDualLayerTDD_Supported_r9,
      { "enhancedDualLayerTDD-Supported-r9", "lte-rrc.enhancedDualLayerTDD_Supported_r9",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_supportedBandListEUTRA,
      { "supportedBandListEUTRA", "lte-rrc.supportedBandListEUTRA",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_SupportedBandListEUTRA_item,
      { "SupportedBandEUTRA", "lte-rrc.SupportedBandEUTRA",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_bandEUTRA,
      { "bandEUTRA", "lte-rrc.bandEUTRA",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_64", HFILL }},
    { &hf_lte_rrc_halfDuplex,
      { "halfDuplex", "lte-rrc.halfDuplex",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_bandListEUTRA,
      { "bandListEUTRA", "lte-rrc.bandListEUTRA",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_BandListEUTRA_item,
      { "BandInfoEUTRA", "lte-rrc.BandInfoEUTRA",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_interFreqBandList,
      { "interFreqBandList", "lte-rrc.interFreqBandList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_interRAT_BandList,
      { "interRAT-BandList", "lte-rrc.interRAT_BandList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_InterFreqBandList_item,
      { "InterFreqBandInfo", "lte-rrc.InterFreqBandInfo",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_interFreqNeedForGaps,
      { "interFreqNeedForGaps", "lte-rrc.interFreqNeedForGaps",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_InterRAT_BandList_item,
      { "InterRAT-BandInfo", "lte-rrc.InterRAT_BandInfo",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_interRAT_NeedForGaps,
      { "interRAT-NeedForGaps", "lte-rrc.interRAT_NeedForGaps",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_supportedBandListUTRA_FDD,
      { "supportedBandListUTRA-FDD", "lte-rrc.supportedBandListUTRA_FDD",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_e_Redirection_r9,
      { "e-Redirection-r9", "lte-rrc.e_Redirection_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_e_Redirection_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_SupportedBandListUTRA_FDD_item,
      { "SupportedBandUTRA-FDD", "lte-rrc.SupportedBandUTRA_FDD",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_SupportedBandUTRA_FDD_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_supportedBandListUTRA_TDD128,
      { "supportedBandListUTRA-TDD128", "lte-rrc.supportedBandListUTRA_TDD128",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_SupportedBandListUTRA_TDD128_item,
      { "SupportedBandUTRA-TDD128", "lte-rrc.SupportedBandUTRA_TDD128",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_SupportedBandUTRA_TDD128_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_supportedBandListUTRA_TDD384,
      { "supportedBandListUTRA-TDD384", "lte-rrc.supportedBandListUTRA_TDD384",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_SupportedBandListUTRA_TDD384_item,
      { "SupportedBandUTRA-TDD384", "lte-rrc.SupportedBandUTRA_TDD384",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_SupportedBandUTRA_TDD384_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_supportedBandListUTRA_TDD768,
      { "supportedBandListUTRA-TDD768", "lte-rrc.supportedBandListUTRA_TDD768",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_SupportedBandListUTRA_TDD768_item,
      { "SupportedBandUTRA-TDD768", "lte-rrc.SupportedBandUTRA_TDD768",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_SupportedBandUTRA_TDD768_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_supportedBandListGERAN,
      { "supportedBandListGERAN", "lte-rrc.supportedBandListGERAN",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_interRAT_PS_HO_ToGERAN,
      { "interRAT-PS-HO-ToGERAN", "lte-rrc.interRAT_PS_HO_ToGERAN",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_dtm_r9,
      { "dtm-r9", "lte-rrc.dtm_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_dtm_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_e_RedirectionGERAN_r9,
      { "e-RedirectionGERAN-r9", "lte-rrc.e_RedirectionGERAN_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_e_RedirectionGERAN_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_SupportedBandListGERAN_item,
      { "SupportedBandGERAN", "lte-rrc.SupportedBandGERAN",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_SupportedBandGERAN_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_supportedBandListHRPD,
      { "supportedBandListHRPD", "lte-rrc.supportedBandListHRPD",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_tx_ConfigHRPD,
      { "tx-ConfigHRPD", "lte-rrc.tx_ConfigHRPD",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_tx_ConfigHRPD_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_rx_ConfigHRPD,
      { "rx-ConfigHRPD", "lte-rrc.rx_ConfigHRPD",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_rx_ConfigHRPD_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_SupportedBandListHRPD_item,
      { "BandclassCDMA2000", "lte-rrc.BandclassCDMA2000",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_BandclassCDMA2000_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_supportedBandList1XRTT,
      { "supportedBandList1XRTT", "lte-rrc.supportedBandList1XRTT",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_tx_Config1XRTT,
      { "tx-Config1XRTT", "lte-rrc.tx_Config1XRTT",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_tx_Config1XRTT_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_rx_Config1XRTT,
      { "rx-Config1XRTT", "lte-rrc.rx_Config1XRTT",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_rx_Config1XRTT_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_e_CSFB_r9_01,
      { "e-CSFB-r9", "lte-rrc.e_CSFB_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_e_CSFB_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_e_CSFB_ConcPS_Mob_r9,
      { "e-CSFB-ConcPS-Mob-r9", "lte-rrc.e_CSFB_ConcPS_Mob_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_e_CSFB_ConcPS_Mob_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_SupportedBandList1XRTT_item,
      { "BandclassCDMA2000", "lte-rrc.BandclassCDMA2000",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_BandclassCDMA2000_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_intraFreqProximityIndicationSupported_r9,
      { "intraFreqProximityIndicationSupported-r9", "lte-rrc.intraFreqProximityIndicationSupported_r9",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_interFreqProximityIndicationSupported_r9,
      { "interFreqProximityIndicationSupported-r9", "lte-rrc.interFreqProximityIndicationSupported_r9",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_utran_ProximityIndicationSupported_r9,
      { "utran-ProximityIndicationSupported-r9", "lte-rrc.utran_ProximityIndicationSupported_r9",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_intraFreqSI_AcquisitionForHO_Supported_r9,
      { "intraFreqSI-AcquisitionForHO-Supported-r9", "lte-rrc.intraFreqSI_AcquisitionForHO_Supported_r9",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_interFreqSI_AcquisitionForHO_Supported_r9,
      { "interFreqSI-AcquisitionForHO-Supported-r9", "lte-rrc.interFreqSI_AcquisitionForHO_Supported_r9",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_utran_SI_AcquisitionForHO_Supported_r9,
      { "utran-SI-AcquisitionForHO-Supported-r9", "lte-rrc.utran_SI_AcquisitionForHO_Supported_r9",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_rach_ReportSupported_r9,
      { "rach-ReportSupported-r9", "lte-rrc.rach_ReportSupported_r9",
        FT_BOOLEAN, BASE_NONE, NULL, 0,
        "BOOLEAN", HFILL }},
    { &hf_lte_rrc_t300,
      { "t300", "lte-rrc.t300",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_t300_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_t301,
      { "t301", "lte-rrc.t301",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_t301_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_t310,
      { "t310", "lte-rrc.t310",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_t310_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_n310,
      { "n310", "lte-rrc.n310",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_n310_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_t311,
      { "t311", "lte-rrc.t311",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_t311_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_n311,
      { "n311", "lte-rrc.n311",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_n311_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_notificationRepetitionCoeff_r9,
      { "notificationRepetitionCoeff-r9", "lte-rrc.notificationRepetitionCoeff_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_notificationRepetitionCoeff_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_notificationOffset_r9,
      { "notificationOffset-r9", "lte-rrc.notificationOffset_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_10", HFILL }},
    { &hf_lte_rrc_notificationSF_Index_r9,
      { "notificationSF-Index-r9", "lte-rrc.notificationSF_Index_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_6", HFILL }},
    { &hf_lte_rrc_MBSFN_AreaInfoList_r9_item,
      { "MBSFN-AreaInfo-r9", "lte-rrc.MBSFN_AreaInfo_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_mbsfn_AreaId_r9,
      { "mbsfn-AreaId-r9", "lte-rrc.mbsfn_AreaId_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_255", HFILL }},
    { &hf_lte_rrc_non_MBSFNregionLength,
      { "non-MBSFNregionLength", "lte-rrc.non_MBSFNregionLength",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_non_MBSFNregionLength_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_notificationIndicator_r9,
      { "notificationIndicator-r9", "lte-rrc.notificationIndicator_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_7", HFILL }},
    { &hf_lte_rrc_mcch_Config_r9,
      { "mcch-Config-r9", "lte-rrc.mcch_Config_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_mcch_RepetitionPeriod_r9,
      { "mcch-RepetitionPeriod-r9", "lte-rrc.mcch_RepetitionPeriod_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_mcch_RepetitionPeriod_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_mcch_Offset_r9,
      { "mcch-Offset-r9", "lte-rrc.mcch_Offset_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_10", HFILL }},
    { &hf_lte_rrc_mcch_ModificationPeriod_r9,
      { "mcch-ModificationPeriod-r9", "lte-rrc.mcch_ModificationPeriod_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_mcch_ModificationPeriod_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_sf_AllocInfo_r9,
      { "sf-AllocInfo-r9", "lte-rrc.sf_AllocInfo_r9",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_6", HFILL }},
    { &hf_lte_rrc_signallingMCS_r9,
      { "signallingMCS-r9", "lte-rrc.signallingMCS_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_signallingMCS_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_radioframeAllocationPeriod,
      { "radioframeAllocationPeriod", "lte-rrc.radioframeAllocationPeriod",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_radioframeAllocationPeriod_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_radioframeAllocationOffset,
      { "radioframeAllocationOffset", "lte-rrc.radioframeAllocationOffset",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_7", HFILL }},
    { &hf_lte_rrc_subframeAllocation,
      { "subframeAllocation", "lte-rrc.subframeAllocation",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_subframeAllocation_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_oneFrame,
      { "oneFrame", "lte-rrc.oneFrame",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_6", HFILL }},
    { &hf_lte_rrc_fourFrames,
      { "fourFrames", "lte-rrc.fourFrames",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_24", HFILL }},
    { &hf_lte_rrc_PMCH_InfoList_r9_item,
      { "PMCH-Info-r9", "lte-rrc.PMCH_Info_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_pmch_Config_r9,
      { "pmch-Config-r9", "lte-rrc.pmch_Config_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_mbms_SessionInfoList_r9,
      { "mbms-SessionInfoList-r9", "lte-rrc.mbms_SessionInfoList_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_MBMS_SessionInfoList_r9_item,
      { "MBMS-SessionInfo-r9", "lte-rrc.MBMS_SessionInfo_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_tmgi_r9,
      { "tmgi-r9", "lte-rrc.tmgi_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_sessionId_r9,
      { "sessionId-r9", "lte-rrc.sessionId_r9",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING_SIZE_1", HFILL }},
    { &hf_lte_rrc_logicalChannelIdentity_r9,
      { "logicalChannelIdentity-r9", "lte-rrc.logicalChannelIdentity_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_maxSessionPerPMCH_1", HFILL }},
    { &hf_lte_rrc_sf_AllocEnd_r9,
      { "sf-AllocEnd-r9", "lte-rrc.sf_AllocEnd_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_1535", HFILL }},
    { &hf_lte_rrc_dataMCS_r9,
      { "dataMCS-r9", "lte-rrc.dataMCS_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_28", HFILL }},
    { &hf_lte_rrc_mch_SchedulingPeriod_r9,
      { "mch-SchedulingPeriod-r9", "lte-rrc.mch_SchedulingPeriod_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_mch_SchedulingPeriod_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_plmn_Id_r9,
      { "plmn-Id-r9", "lte-rrc.plmn_Id_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_plmn_Id_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_plmn_Index_r9,
      { "plmn-Index-r9", "lte-rrc.plmn_Index_r9",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_6", HFILL }},
    { &hf_lte_rrc_explicitValue_r9,
      { "explicitValue-r9", "lte-rrc.explicitValue_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        "PLMN_Identity", HFILL }},
    { &hf_lte_rrc_serviceId_r9,
      { "serviceId-r9", "lte-rrc.serviceId_r9",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING_SIZE_3", HFILL }},
    { &hf_lte_rrc_CellsTriggeredList_item,
      { "CellsTriggeredList item", "lte-rrc.CellsTriggeredList_item",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_CellsTriggeredList_item_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_physCellIdEUTRA,
      { "physCellIdEUTRA", "lte-rrc.physCellIdEUTRA",
        FT_UINT32, BASE_DEC, NULL, 0,
        "PhysCellId", HFILL }},
    { &hf_lte_rrc_physCellIdUTRA,
      { "physCellIdUTRA", "lte-rrc.physCellIdUTRA",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_physCellIdUTRA_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_physCellIdGERAN,
      { "physCellIdGERAN", "lte-rrc.physCellIdGERAN",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_physCellIdCDMA2000,
      { "physCellIdCDMA2000", "lte-rrc.physCellIdCDMA2000",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_criticalExtensions_30,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_30_vals), 0,
        "T_criticalExtensions_30", HFILL }},
    { &hf_lte_rrc_c1_26,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_26_vals), 0,
        "T_c1_26", HFILL }},
    { &hf_lte_rrc_handoverCommand_r8,
      { "handoverCommand-r8", "lte-rrc.handoverCommand_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "HandoverCommand_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_30,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_30", HFILL }},
    { &hf_lte_rrc_handoverCommandMessage,
      { "handoverCommandMessage", "lte-rrc.handoverCommandMessage",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_45,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_33", HFILL }},
    { &hf_lte_rrc_criticalExtensions_31,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_31_vals), 0,
        "T_criticalExtensions_31", HFILL }},
    { &hf_lte_rrc_c1_27,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_27_vals), 0,
        "T_c1_27", HFILL }},
    { &hf_lte_rrc_handoverPreparationInformation_r8,
      { "handoverPreparationInformation-r8", "lte-rrc.handoverPreparationInformation_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "HandoverPreparationInformation_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_31,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_31", HFILL }},
    { &hf_lte_rrc_ue_RadioAccessCapabilityInfo,
      { "ue-RadioAccessCapabilityInfo", "lte-rrc.ue_RadioAccessCapabilityInfo",
        FT_UINT32, BASE_DEC, NULL, 0,
        "UE_CapabilityRAT_ContainerList", HFILL }},
    { &hf_lte_rrc_as_Config,
      { "as-Config", "lte-rrc.as_Config",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_rrm_Config,
      { "rrm-Config", "lte-rrc.rrm_Config",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_as_Context,
      { "as-Context", "lte-rrc.as_Context",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_46,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "HandoverPreparationInformation_v920_IEs", HFILL }},
    { &hf_lte_rrc_ue_ConfigRelease_r9,
      { "ue-ConfigRelease-r9", "lte-rrc.ue_ConfigRelease_r9",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_ue_ConfigRelease_r9_vals), 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_47,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_34", HFILL }},
    { &hf_lte_rrc_criticalExtensions_32,
      { "criticalExtensions", "lte-rrc.criticalExtensions",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_criticalExtensions_32_vals), 0,
        "T_criticalExtensions_32", HFILL }},
    { &hf_lte_rrc_c1_28,
      { "c1", "lte-rrc.c1",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_c1_28_vals), 0,
        "T_c1_28", HFILL }},
    { &hf_lte_rrc_ueRadioAccessCapabilityInformation_r8,
      { "ueRadioAccessCapabilityInformation-r8", "lte-rrc.ueRadioAccessCapabilityInformation_r8",
        FT_NONE, BASE_NONE, NULL, 0,
        "UERadioAccessCapabilityInformation_r8_IEs", HFILL }},
    { &hf_lte_rrc_criticalExtensionsFuture_32,
      { "criticalExtensionsFuture", "lte-rrc.criticalExtensionsFuture",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_criticalExtensionsFuture_32", HFILL }},
    { &hf_lte_rrc_ue_RadioAccessCapabilityInfo_01,
      { "ue-RadioAccessCapabilityInfo", "lte-rrc.ue_RadioAccessCapabilityInfo",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_nonCriticalExtension_48,
      { "nonCriticalExtension", "lte-rrc.nonCriticalExtension",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_nonCriticalExtension_35", HFILL }},
    { &hf_lte_rrc_sourceMeasConfig,
      { "sourceMeasConfig", "lte-rrc.sourceMeasConfig",
        FT_NONE, BASE_NONE, NULL, 0,
        "MeasConfig", HFILL }},
    { &hf_lte_rrc_sourceRadioResourceConfig,
      { "sourceRadioResourceConfig", "lte-rrc.sourceRadioResourceConfig",
        FT_NONE, BASE_NONE, NULL, 0,
        "RadioResourceConfigDedicated", HFILL }},
    { &hf_lte_rrc_sourceSecurityAlgorithmConfig,
      { "sourceSecurityAlgorithmConfig", "lte-rrc.sourceSecurityAlgorithmConfig",
        FT_NONE, BASE_NONE, NULL, 0,
        "SecurityAlgorithmConfig", HFILL }},
    { &hf_lte_rrc_sourceUE_Identity,
      { "sourceUE-Identity", "lte-rrc.sourceUE_Identity",
        FT_BYTES, BASE_NONE, NULL, 0,
        "C_RNTI", HFILL }},
    { &hf_lte_rrc_sourceMasterInformationBlock,
      { "sourceMasterInformationBlock", "lte-rrc.sourceMasterInformationBlock",
        FT_NONE, BASE_NONE, NULL, 0,
        "MasterInformationBlock", HFILL }},
    { &hf_lte_rrc_sourceSystemInformationBlockType1,
      { "sourceSystemInformationBlockType1", "lte-rrc.sourceSystemInformationBlockType1",
        FT_NONE, BASE_NONE, NULL, 0,
        "SystemInformationBlockType1", HFILL }},
    { &hf_lte_rrc_sourceSystemInformationBlockType2,
      { "sourceSystemInformationBlockType2", "lte-rrc.sourceSystemInformationBlockType2",
        FT_NONE, BASE_NONE, NULL, 0,
        "SystemInformationBlockType2", HFILL }},
    { &hf_lte_rrc_sourceDl_CarrierFreq,
      { "sourceDl-CarrierFreq", "lte-rrc.sourceDl_CarrierFreq",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ARFCN_ValueEUTRA", HFILL }},
    { &hf_lte_rrc_sourceSystemInformationBlockType1Ext,
      { "sourceSystemInformationBlockType1Ext", "lte-rrc.sourceSystemInformationBlockType1Ext",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_sourceOtherConfig_r9,
      { "sourceOtherConfig-r9", "lte-rrc.sourceOtherConfig_r9",
        FT_NONE, BASE_NONE, NULL, 0,
        "OtherConfig_r9", HFILL }},
    { &hf_lte_rrc_reestablishmentInfo,
      { "reestablishmentInfo", "lte-rrc.reestablishmentInfo",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_sourcePhysCellId,
      { "sourcePhysCellId", "lte-rrc.sourcePhysCellId",
        FT_UINT32, BASE_DEC, NULL, 0,
        "PhysCellId", HFILL }},
    { &hf_lte_rrc_targetCellShortMAC_I,
      { "targetCellShortMAC-I", "lte-rrc.targetCellShortMAC_I",
        FT_BYTES, BASE_NONE, NULL, 0,
        "ShortMAC_I", HFILL }},
    { &hf_lte_rrc_additionalReestabInfoList,
      { "additionalReestabInfoList", "lte-rrc.additionalReestabInfoList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_AdditionalReestabInfoList_item,
      { "AdditionalReestabInfo", "lte-rrc.AdditionalReestabInfo",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_key_eNodeB_Star,
      { "key-eNodeB-Star", "lte-rrc.key_eNodeB_Star",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_lte_rrc_ue_InactiveTime,
      { "ue-InactiveTime", "lte-rrc.ue_InactiveTime",
        FT_UINT32, BASE_DEC, VALS(lte_rrc_T_ue_InactiveTime_vals), 0,
        NULL, HFILL }},

/*--- End of included file: packet-lte-rrc-hfarr.c ---*/
#line 143 "packet-lte-rrc-template.c"
  };

  /* List of subtrees */
  static gint *ett[] = {
		  &ett_lte_rrc,

/*--- Included file: packet-lte-rrc-ettarr.c ---*/
#line 1 "packet-lte-rrc-ettarr.c"
    &ett_lte_rrc_BCCH_BCH_Message,
    &ett_lte_rrc_BCCH_DL_SCH_Message,
    &ett_lte_rrc_BCCH_DL_SCH_MessageType,
    &ett_lte_rrc_T_c1,
    &ett_lte_rrc_T_messageClassExtension,
    &ett_lte_rrc_MCCH_Message,
    &ett_lte_rrc_MCCH_MessageType,
    &ett_lte_rrc_T_c1_01,
    &ett_lte_rrc_T_messageClassExtension_01,
    &ett_lte_rrc_PCCH_Message,
    &ett_lte_rrc_PCCH_MessageType,
    &ett_lte_rrc_T_c1_02,
    &ett_lte_rrc_T_messageClassExtension_02,
    &ett_lte_rrc_DL_CCCH_Message,
    &ett_lte_rrc_DL_CCCH_MessageType,
    &ett_lte_rrc_T_c1_03,
    &ett_lte_rrc_T_messageClassExtension_03,
    &ett_lte_rrc_DL_DCCH_Message,
    &ett_lte_rrc_DL_DCCH_MessageType,
    &ett_lte_rrc_T_c1_04,
    &ett_lte_rrc_T_messageClassExtension_04,
    &ett_lte_rrc_UL_CCCH_Message,
    &ett_lte_rrc_UL_CCCH_MessageType,
    &ett_lte_rrc_T_c1_05,
    &ett_lte_rrc_T_messageClassExtension_05,
    &ett_lte_rrc_UL_DCCH_Message,
    &ett_lte_rrc_UL_DCCH_MessageType,
    &ett_lte_rrc_T_c1_06,
    &ett_lte_rrc_T_messageClassExtension_06,
    &ett_lte_rrc_CounterCheck,
    &ett_lte_rrc_T_criticalExtensions,
    &ett_lte_rrc_T_c1_07,
    &ett_lte_rrc_T_criticalExtensionsFuture,
    &ett_lte_rrc_CounterCheck_r8_IEs,
    &ett_lte_rrc_T_nonCriticalExtension,
    &ett_lte_rrc_DRB_CountMSB_InfoList,
    &ett_lte_rrc_DRB_CountMSB_Info,
    &ett_lte_rrc_CounterCheckResponse,
    &ett_lte_rrc_T_criticalExtensions_01,
    &ett_lte_rrc_T_criticalExtensionsFuture_01,
    &ett_lte_rrc_CounterCheckResponse_r8_IEs,
    &ett_lte_rrc_T_nonCriticalExtension_01,
    &ett_lte_rrc_DRB_CountInfoList,
    &ett_lte_rrc_DRB_CountInfo,
    &ett_lte_rrc_CSFBParametersRequestCDMA2000,
    &ett_lte_rrc_T_criticalExtensions_02,
    &ett_lte_rrc_T_criticalExtensionsFuture_02,
    &ett_lte_rrc_CSFBParametersRequestCDMA2000_r8_IEs,
    &ett_lte_rrc_T_nonCriticalExtension_02,
    &ett_lte_rrc_CSFBParametersResponseCDMA2000,
    &ett_lte_rrc_T_criticalExtensions_03,
    &ett_lte_rrc_T_criticalExtensionsFuture_03,
    &ett_lte_rrc_CSFBParametersResponseCDMA2000_r8_IEs,
    &ett_lte_rrc_T_nonCriticalExtension_03,
    &ett_lte_rrc_DLInformationTransfer,
    &ett_lte_rrc_T_criticalExtensions_04,
    &ett_lte_rrc_T_c1_08,
    &ett_lte_rrc_T_criticalExtensionsFuture_04,
    &ett_lte_rrc_DLInformationTransfer_r8_IEs,
    &ett_lte_rrc_T_dedicatedInfoType,
    &ett_lte_rrc_T_nonCriticalExtension_04,
    &ett_lte_rrc_HandoverFromEUTRAPreparationRequest,
    &ett_lte_rrc_T_criticalExtensions_05,
    &ett_lte_rrc_T_c1_09,
    &ett_lte_rrc_T_criticalExtensionsFuture_05,
    &ett_lte_rrc_HandoverFromEUTRAPreparationRequest_r8_IEs,
    &ett_lte_rrc_HandoverFromEUTRAPreparationRequest_v890_IEs,
    &ett_lte_rrc_HandoverFromEUTRAPreparationRequest_v920_IEs,
    &ett_lte_rrc_T_nonCriticalExtension_05,
    &ett_lte_rrc_MasterInformationBlock,
    &ett_lte_rrc_MBSFNAreaConfiguration_r9,
    &ett_lte_rrc_T_nonCriticalExtension_06,
    &ett_lte_rrc_CommonSF_AllocPatternList_r9,
    &ett_lte_rrc_MeasurementReport,
    &ett_lte_rrc_T_criticalExtensions_06,
    &ett_lte_rrc_T_c1_10,
    &ett_lte_rrc_T_criticalExtensionsFuture_06,
    &ett_lte_rrc_MeasurementReport_r8_IEs,
    &ett_lte_rrc_T_nonCriticalExtension_07,
    &ett_lte_rrc_MobilityFromEUTRACommand,
    &ett_lte_rrc_T_criticalExtensions_07,
    &ett_lte_rrc_T_c1_11,
    &ett_lte_rrc_T_criticalExtensionsFuture_07,
    &ett_lte_rrc_MobilityFromEUTRACommand_r8_IEs,
    &ett_lte_rrc_T_purpose,
    &ett_lte_rrc_T_nonCriticalExtension_08,
    &ett_lte_rrc_MobilityFromEUTRACommand_r9_IEs,
    &ett_lte_rrc_T_purpose_01,
    &ett_lte_rrc_T_nonCriticalExtension_09,
    &ett_lte_rrc_Handover,
    &ett_lte_rrc_CellChangeOrder,
    &ett_lte_rrc_T_targetRAT_Type_01,
    &ett_lte_rrc_T_geran,
    &ett_lte_rrc_SI_OrPSI_GERAN,
    &ett_lte_rrc_E_CSFB_r9,
    &ett_lte_rrc_Paging,
    &ett_lte_rrc_Paging_v890_IEs,
    &ett_lte_rrc_Paging_v920_IEs,
    &ett_lte_rrc_T_nonCriticalExtension_10,
    &ett_lte_rrc_PagingRecordList,
    &ett_lte_rrc_PagingRecord,
    &ett_lte_rrc_PagingUE_Identity,
    &ett_lte_rrc_IMSI,
    &ett_lte_rrc_ProximityIndication_r9,
    &ett_lte_rrc_T_criticalExtensions_08,
    &ett_lte_rrc_T_c1_12,
    &ett_lte_rrc_T_criticalExtensionsFuture_08,
    &ett_lte_rrc_ProximityIndication_r9_IEs,
    &ett_lte_rrc_T_carrierFreq_r9,
    &ett_lte_rrc_T_nonCriticalExtension_11,
    &ett_lte_rrc_RRCConnectionReconfiguration,
    &ett_lte_rrc_T_criticalExtensions_09,
    &ett_lte_rrc_T_c1_13,
    &ett_lte_rrc_T_criticalExtensionsFuture_09,
    &ett_lte_rrc_RRCConnectionReconfiguration_r8_IEs,
    &ett_lte_rrc_SEQUENCE_SIZE_1_maxDRB_OF_DedicatedInfoNAS,
    &ett_lte_rrc_RRCConnectionReconfiguration_v890_IEs,
    &ett_lte_rrc_RRCConnectionReconfiguration_v920_IEs,
    &ett_lte_rrc_T_nonCriticalExtension_12,
    &ett_lte_rrc_SecurityConfigHO,
    &ett_lte_rrc_T_handoverType,
    &ett_lte_rrc_T_intraLTE,
    &ett_lte_rrc_T_interRAT,
    &ett_lte_rrc_RRCConnectionReconfigurationComplete,
    &ett_lte_rrc_T_criticalExtensions_10,
    &ett_lte_rrc_T_criticalExtensionsFuture_10,
    &ett_lte_rrc_RRCConnectionReconfigurationComplete_r8_IEs,
    &ett_lte_rrc_T_nonCriticalExtension_13,
    &ett_lte_rrc_RRCConnectionReestablishment,
    &ett_lte_rrc_T_criticalExtensions_11,
    &ett_lte_rrc_T_c1_14,
    &ett_lte_rrc_T_criticalExtensionsFuture_11,
    &ett_lte_rrc_RRCConnectionReestablishment_r8_IEs,
    &ett_lte_rrc_T_nonCriticalExtension_14,
    &ett_lte_rrc_RRCConnectionReestablishmentComplete,
    &ett_lte_rrc_T_criticalExtensions_12,
    &ett_lte_rrc_T_criticalExtensionsFuture_12,
    &ett_lte_rrc_RRCConnectionReestablishmentComplete_r8_IEs,
    &ett_lte_rrc_RRCConnectionReestablishmentComplete_v920_IEs,
    &ett_lte_rrc_T_nonCriticalExtension_15,
    &ett_lte_rrc_RRCConnectionReestablishmentReject,
    &ett_lte_rrc_T_criticalExtensions_13,
    &ett_lte_rrc_T_criticalExtensionsFuture_13,
    &ett_lte_rrc_RRCConnectionReestablishmentReject_r8_IEs,
    &ett_lte_rrc_T_nonCriticalExtension_16,
    &ett_lte_rrc_RRCConnectionReestablishmentRequest,
    &ett_lte_rrc_T_criticalExtensions_14,
    &ett_lte_rrc_T_criticalExtensionsFuture_14,
    &ett_lte_rrc_RRCConnectionReestablishmentRequest_r8_IEs,
    &ett_lte_rrc_ReestabUE_Identity,
    &ett_lte_rrc_RRCConnectionReject,
    &ett_lte_rrc_T_criticalExtensions_15,
    &ett_lte_rrc_T_c1_15,
    &ett_lte_rrc_T_criticalExtensionsFuture_15,
    &ett_lte_rrc_RRCConnectionReject_r8_IEs,
    &ett_lte_rrc_T_nonCriticalExtension_17,
    &ett_lte_rrc_RRCConnectionRelease,
    &ett_lte_rrc_T_criticalExtensions_16,
    &ett_lte_rrc_T_c1_16,
    &ett_lte_rrc_T_criticalExtensionsFuture_16,
    &ett_lte_rrc_RRCConnectionRelease_r8_IEs,
    &ett_lte_rrc_RRCConnectionRelease_v890_IEs,
    &ett_lte_rrc_RRCConnectionRelease_v920_IEs,
    &ett_lte_rrc_T_cellInfoList_r9,
    &ett_lte_rrc_T_nonCriticalExtension_18,
    &ett_lte_rrc_RedirectedCarrierInfo,
    &ett_lte_rrc_IdleModeMobilityControlInfo,
    &ett_lte_rrc_FreqPriorityListEUTRA,
    &ett_lte_rrc_FreqPriorityEUTRA,
    &ett_lte_rrc_FreqsPriorityListGERAN,
    &ett_lte_rrc_FreqsPriorityGERAN,
    &ett_lte_rrc_FreqPriorityListUTRA_FDD,
    &ett_lte_rrc_FreqPriorityUTRA_FDD,
    &ett_lte_rrc_FreqPriorityListUTRA_TDD,
    &ett_lte_rrc_FreqPriorityUTRA_TDD,
    &ett_lte_rrc_BandClassPriorityListHRPD,
    &ett_lte_rrc_BandClassPriorityHRPD,
    &ett_lte_rrc_BandClassPriorityList1XRTT,
    &ett_lte_rrc_BandClassPriority1XRTT,
    &ett_lte_rrc_CellInfoListGERAN_r9,
    &ett_lte_rrc_CellInfoGERAN_r9,
    &ett_lte_rrc_CellInfoListUTRA_FDD_r9,
    &ett_lte_rrc_CellInfoUTRA_FDD_r9,
    &ett_lte_rrc_CellInfoListUTRA_TDD_r9,
    &ett_lte_rrc_CellInfoUTRA_TDD_r9,
    &ett_lte_rrc_RRCConnectionRequest,
    &ett_lte_rrc_T_criticalExtensions_17,
    &ett_lte_rrc_T_criticalExtensionsFuture_17,
    &ett_lte_rrc_RRCConnectionRequest_r8_IEs,
    &ett_lte_rrc_InitialUE_Identity,
    &ett_lte_rrc_RRCConnectionSetup,
    &ett_lte_rrc_T_criticalExtensions_18,
    &ett_lte_rrc_T_c1_17,
    &ett_lte_rrc_T_criticalExtensionsFuture_18,
    &ett_lte_rrc_RRCConnectionSetup_r8_IEs,
    &ett_lte_rrc_T_nonCriticalExtension_19,
    &ett_lte_rrc_RRCConnectionSetupComplete,
    &ett_lte_rrc_T_criticalExtensions_19,
    &ett_lte_rrc_T_c1_18,
    &ett_lte_rrc_T_criticalExtensionsFuture_19,
    &ett_lte_rrc_RRCConnectionSetupComplete_r8_IEs,
    &ett_lte_rrc_T_nonCriticalExtension_20,
    &ett_lte_rrc_RegisteredMME,
    &ett_lte_rrc_SecurityModeCommand,
    &ett_lte_rrc_T_criticalExtensions_20,
    &ett_lte_rrc_T_c1_19,
    &ett_lte_rrc_T_criticalExtensionsFuture_20,
    &ett_lte_rrc_SecurityModeCommand_r8_IEs,
    &ett_lte_rrc_T_nonCriticalExtension_21,
    &ett_lte_rrc_SecurityConfigSMC,
    &ett_lte_rrc_SecurityModeComplete,
    &ett_lte_rrc_T_criticalExtensions_21,
    &ett_lte_rrc_T_criticalExtensionsFuture_21,
    &ett_lte_rrc_SecurityModeComplete_r8_IEs,
    &ett_lte_rrc_T_nonCriticalExtension_22,
    &ett_lte_rrc_SecurityModeFailure,
    &ett_lte_rrc_T_criticalExtensions_22,
    &ett_lte_rrc_T_criticalExtensionsFuture_22,
    &ett_lte_rrc_SecurityModeFailure_r8_IEs,
    &ett_lte_rrc_T_nonCriticalExtension_23,
    &ett_lte_rrc_SystemInformation,
    &ett_lte_rrc_T_criticalExtensions_23,
    &ett_lte_rrc_T_criticalExtensionsFuture_23,
    &ett_lte_rrc_SystemInformation_r8_IEs,
    &ett_lte_rrc_T_sib_TypeAndInfo,
    &ett_lte_rrc_T_sib_TypeAndInfo_item,
    &ett_lte_rrc_T_nonCriticalExtension_24,
    &ett_lte_rrc_SystemInformationBlockType1,
    &ett_lte_rrc_T_cellAccessRelatedInfo,
    &ett_lte_rrc_T_cellSelectionInfo,
    &ett_lte_rrc_SystemInformationBlockType1_v890_IEs,
    &ett_lte_rrc_SystemInformationBlockType1_v920_IEs,
    &ett_lte_rrc_T_nonCriticalExtension_25,
    &ett_lte_rrc_PLMN_IdentityList,
    &ett_lte_rrc_PLMN_IdentityInfo,
    &ett_lte_rrc_SchedulingInfoList,
    &ett_lte_rrc_SchedulingInfo,
    &ett_lte_rrc_SIB_MappingInfo,
    &ett_lte_rrc_CellSelectionInfo_v920,
    &ett_lte_rrc_UECapabilityEnquiry,
    &ett_lte_rrc_T_criticalExtensions_24,
    &ett_lte_rrc_T_c1_20,
    &ett_lte_rrc_T_criticalExtensionsFuture_24,
    &ett_lte_rrc_UECapabilityEnquiry_r8_IEs,
    &ett_lte_rrc_T_nonCriticalExtension_26,
    &ett_lte_rrc_UE_CapabilityRequest,
    &ett_lte_rrc_UECapabilityInformation,
    &ett_lte_rrc_T_criticalExtensions_25,
    &ett_lte_rrc_T_c1_21,
    &ett_lte_rrc_T_criticalExtensionsFuture_25,
    &ett_lte_rrc_UECapabilityInformation_r8_IEs,
    &ett_lte_rrc_T_nonCriticalExtension_27,
    &ett_lte_rrc_UEInformationRequest_r9,
    &ett_lte_rrc_T_criticalExtensions_26,
    &ett_lte_rrc_T_c1_22,
    &ett_lte_rrc_T_criticalExtensionsFuture_26,
    &ett_lte_rrc_UEInformationRequest_r9_IEs,
    &ett_lte_rrc_T_nonCriticalExtension_28,
    &ett_lte_rrc_UEInformationResponse_r9,
    &ett_lte_rrc_T_criticalExtensions_27,
    &ett_lte_rrc_T_c1_23,
    &ett_lte_rrc_T_criticalExtensionsFuture_27,
    &ett_lte_rrc_UEInformationResponse_r9_IEs,
    &ett_lte_rrc_T_rach_Report_r9,
    &ett_lte_rrc_T_nonCriticalExtension_29,
    &ett_lte_rrc_RLF_Report_r9,
    &ett_lte_rrc_T_measResultLastServCell,
    &ett_lte_rrc_T_measResultNeighCells,
    &ett_lte_rrc_MeasResultList2EUTRA,
    &ett_lte_rrc_MeasResultList2EUTRA_item,
    &ett_lte_rrc_MeasResultList2UTRA,
    &ett_lte_rrc_MeasResultList2UTRA_item,
    &ett_lte_rrc_MeasResultList2CDMA2000,
    &ett_lte_rrc_MeasResultList2CDMA2000_item,
    &ett_lte_rrc_ULHandoverPreparationTransfer,
    &ett_lte_rrc_T_criticalExtensions_28,
    &ett_lte_rrc_T_c1_24,
    &ett_lte_rrc_T_criticalExtensionsFuture_28,
    &ett_lte_rrc_ULHandoverPreparationTransfer_r8_IEs,
    &ett_lte_rrc_T_nonCriticalExtension_30,
    &ett_lte_rrc_ULInformationTransfer,
    &ett_lte_rrc_T_criticalExtensions_29,
    &ett_lte_rrc_T_c1_25,
    &ett_lte_rrc_T_criticalExtensionsFuture_29,
    &ett_lte_rrc_ULInformationTransfer_r8_IEs,
    &ett_lte_rrc_T_dedicatedInfoType_01,
    &ett_lte_rrc_T_nonCriticalExtension_31,
    &ett_lte_rrc_SystemInformationBlockType2,
    &ett_lte_rrc_T_ac_BarringInfo,
    &ett_lte_rrc_T_freqInfo,
    &ett_lte_rrc_AC_BarringConfig,
    &ett_lte_rrc_MBSFN_SubframeConfigList,
    &ett_lte_rrc_SystemInformationBlockType3,
    &ett_lte_rrc_T_cellReselectionInfoCommon,
    &ett_lte_rrc_T_speedStateReselectionPars,
    &ett_lte_rrc_T_q_HystSF,
    &ett_lte_rrc_T_cellReselectionServingFreqInfo,
    &ett_lte_rrc_T_intraFreqCellReselectionInfo,
    &ett_lte_rrc_T_s_IntraSearch_v920,
    &ett_lte_rrc_T_s_NonIntraSearch_v920,
    &ett_lte_rrc_SystemInformationBlockType4,
    &ett_lte_rrc_IntraFreqNeighCellList,
    &ett_lte_rrc_IntraFreqNeighCellInfo,
    &ett_lte_rrc_IntraFreqBlackCellList,
    &ett_lte_rrc_SystemInformationBlockType5,
    &ett_lte_rrc_InterFreqCarrierFreqList,
    &ett_lte_rrc_InterFreqCarrierFreqInfo,
    &ett_lte_rrc_T_threshX_Q_r9,
    &ett_lte_rrc_InterFreqNeighCellList,
    &ett_lte_rrc_InterFreqNeighCellInfo,
    &ett_lte_rrc_InterFreqBlackCellList,
    &ett_lte_rrc_SystemInformationBlockType6,
    &ett_lte_rrc_CarrierFreqListUTRA_FDD,
    &ett_lte_rrc_CarrierFreqUTRA_FDD,
    &ett_lte_rrc_T_threshX_Q_r9_01,
    &ett_lte_rrc_CarrierFreqListUTRA_TDD,
    &ett_lte_rrc_CarrierFreqUTRA_TDD,
    &ett_lte_rrc_SystemInformationBlockType7,
    &ett_lte_rrc_CarrierFreqsInfoListGERAN,
    &ett_lte_rrc_CarrierFreqsInfoGERAN,
    &ett_lte_rrc_T_commonInfo,
    &ett_lte_rrc_SystemInformationBlockType8,
    &ett_lte_rrc_T_parametersHRPD,
    &ett_lte_rrc_T_parameters1XRTT,
    &ett_lte_rrc_CellReselectionParametersCDMA2000,
    &ett_lte_rrc_CellReselectionParametersCDMA2000_v920,
    &ett_lte_rrc_NeighCellListCDMA2000,
    &ett_lte_rrc_NeighCellCDMA2000,
    &ett_lte_rrc_NeighCellsPerBandclassListCDMA2000,
    &ett_lte_rrc_NeighCellsPerBandclassCDMA2000,
    &ett_lte_rrc_NeighCellListCDMA2000_v920,
    &ett_lte_rrc_NeighCellCDMA2000_v920,
    &ett_lte_rrc_NeighCellsPerBandclassListCDMA2000_v920,
    &ett_lte_rrc_NeighCellsPerBandclassCDMA2000_v920,
    &ett_lte_rrc_PhysCellIdListCDMA2000,
    &ett_lte_rrc_PhysCellIdListCDMA2000_v920,
    &ett_lte_rrc_BandClassListCDMA2000,
    &ett_lte_rrc_BandClassInfoCDMA2000,
    &ett_lte_rrc_AC_BarringConfig1XRTT_r9,
    &ett_lte_rrc_SystemInformationBlockType9,
    &ett_lte_rrc_SystemInformationBlockType10,
    &ett_lte_rrc_SystemInformationBlockType11,
    &ett_lte_rrc_SystemInformationBlockType12_r9,
    &ett_lte_rrc_SystemInformationBlockType13_r9,
    &ett_lte_rrc_AntennaInfoCommon,
    &ett_lte_rrc_AntennaInfoDedicated,
    &ett_lte_rrc_T_codebookSubsetRestriction,
    &ett_lte_rrc_T_ue_TransmitAntennaSelection,
    &ett_lte_rrc_AntennaInfoDedicated_v920,
    &ett_lte_rrc_T_codebookSubsetRestriction_v920,
    &ett_lte_rrc_CQI_ReportConfig,
    &ett_lte_rrc_CQI_ReportConfig_v920,
    &ett_lte_rrc_CQI_ReportPeriodic,
    &ett_lte_rrc_T_setup_01,
    &ett_lte_rrc_T_cqi_FormatIndicatorPeriodic,
    &ett_lte_rrc_T_subbandCQI,
    &ett_lte_rrc_LogicalChannelConfig,
    &ett_lte_rrc_T_ul_SpecificParameters,
    &ett_lte_rrc_MAC_MainConfig,
    &ett_lte_rrc_T_ul_SCH_Config,
    &ett_lte_rrc_T_phr_Config,
    &ett_lte_rrc_T_setup_02,
    &ett_lte_rrc_DRX_Config,
    &ett_lte_rrc_T_setup_03,
    &ett_lte_rrc_T_longDRX_CycleStartOffset,
    &ett_lte_rrc_T_shortDRX,
    &ett_lte_rrc_PDCP_Config,
    &ett_lte_rrc_T_rlc_AM,
    &ett_lte_rrc_T_rlc_UM,
    &ett_lte_rrc_T_headerCompression,
    &ett_lte_rrc_T_rohc,
    &ett_lte_rrc_T_profiles,
    &ett_lte_rrc_PDSCH_ConfigCommon,
    &ett_lte_rrc_PDSCH_ConfigDedicated,
    &ett_lte_rrc_PHICH_Config,
    &ett_lte_rrc_PhysicalConfigDedicated,
    &ett_lte_rrc_T_antennaInfo,
    &ett_lte_rrc_PRACH_ConfigSIB,
    &ett_lte_rrc_PRACH_Config,
    &ett_lte_rrc_PRACH_ConfigInfo,
    &ett_lte_rrc_PUCCH_ConfigCommon,
    &ett_lte_rrc_PUCCH_ConfigDedicated,
    &ett_lte_rrc_T_ackNackRepetition,
    &ett_lte_rrc_T_setup_04,
    &ett_lte_rrc_PUSCH_ConfigCommon,
    &ett_lte_rrc_T_pusch_ConfigBasic,
    &ett_lte_rrc_PUSCH_ConfigDedicated,
    &ett_lte_rrc_UL_ReferenceSignalsPUSCH,
    &ett_lte_rrc_RACH_ConfigCommon,
    &ett_lte_rrc_T_preambleInfo,
    &ett_lte_rrc_T_preamblesGroupAConfig,
    &ett_lte_rrc_T_powerRampingParameters,
    &ett_lte_rrc_T_ra_SupervisionInfo,
    &ett_lte_rrc_RACH_ConfigDedicated,
    &ett_lte_rrc_RadioResourceConfigCommonSIB,
    &ett_lte_rrc_RadioResourceConfigCommon,
    &ett_lte_rrc_BCCH_Config,
    &ett_lte_rrc_PCCH_Config,
    &ett_lte_rrc_RadioResourceConfigDedicated,
    &ett_lte_rrc_T_mac_MainConfig,
    &ett_lte_rrc_SRB_ToAddModList,
    &ett_lte_rrc_SRB_ToAddMod,
    &ett_lte_rrc_T_rlc_Config,
    &ett_lte_rrc_T_logicalChannelConfig,
    &ett_lte_rrc_DRB_ToAddModList,
    &ett_lte_rrc_DRB_ToAddMod,
    &ett_lte_rrc_DRB_ToReleaseList,
    &ett_lte_rrc_RLC_Config,
    &ett_lte_rrc_T_am,
    &ett_lte_rrc_T_um_Bi_Directional,
    &ett_lte_rrc_T_um_Uni_Directional_UL,
    &ett_lte_rrc_T_um_Uni_Directional_DL,
    &ett_lte_rrc_UL_AM_RLC,
    &ett_lte_rrc_DL_AM_RLC,
    &ett_lte_rrc_UL_UM_RLC,
    &ett_lte_rrc_DL_UM_RLC,
    &ett_lte_rrc_RLF_TimersAndConstants_r9,
    &ett_lte_rrc_T_setup_05,
    &ett_lte_rrc_SchedulingRequestConfig,
    &ett_lte_rrc_T_setup_06,
    &ett_lte_rrc_SoundingRS_UL_ConfigCommon,
    &ett_lte_rrc_T_setup_07,
    &ett_lte_rrc_SoundingRS_UL_ConfigDedicated,
    &ett_lte_rrc_T_setup_08,
    &ett_lte_rrc_SPS_Config,
    &ett_lte_rrc_SPS_ConfigDL,
    &ett_lte_rrc_T_setup_09,
    &ett_lte_rrc_SPS_ConfigUL,
    &ett_lte_rrc_T_setup_10,
    &ett_lte_rrc_T_p0_Persistent,
    &ett_lte_rrc_N1_PUCCH_AN_PersistentList,
    &ett_lte_rrc_TDD_Config,
    &ett_lte_rrc_TPC_PDCCH_Config,
    &ett_lte_rrc_T_setup_11,
    &ett_lte_rrc_TPC_Index,
    &ett_lte_rrc_UplinkPowerControlCommon,
    &ett_lte_rrc_UplinkPowerControlDedicated,
    &ett_lte_rrc_DeltaFList_PUCCH,
    &ett_lte_rrc_SecurityAlgorithmConfig,
    &ett_lte_rrc_CarrierFreqCDMA2000,
    &ett_lte_rrc_CarrierFreqGERAN,
    &ett_lte_rrc_CarrierFreqsGERAN,
    &ett_lte_rrc_T_followingARFCNs,
    &ett_lte_rrc_T_equallySpacedARFCNs,
    &ett_lte_rrc_ExplicitListOfARFCNs,
    &ett_lte_rrc_CellIndexList,
    &ett_lte_rrc_CSFB_RegistrationParam1XRTT,
    &ett_lte_rrc_CSFB_RegistrationParam1XRTT_v920,
    &ett_lte_rrc_CellGlobalIdEUTRA,
    &ett_lte_rrc_CellGlobalIdUTRA,
    &ett_lte_rrc_CellGlobalIdGERAN,
    &ett_lte_rrc_CellGlobalIdCDMA2000,
    &ett_lte_rrc_MobilityControlInfo,
    &ett_lte_rrc_CarrierBandwidthEUTRA,
    &ett_lte_rrc_CarrierFreqEUTRA,
    &ett_lte_rrc_MobilityStateParameters,
    &ett_lte_rrc_PhysCellIdRange,
    &ett_lte_rrc_PhysCellIdGERAN,
    &ett_lte_rrc_PLMN_Identity,
    &ett_lte_rrc_MCC,
    &ett_lte_rrc_MNC,
    &ett_lte_rrc_PreRegistrationInfoHRPD,
    &ett_lte_rrc_SecondaryPreRegistrationZoneIdListHRPD,
    &ett_lte_rrc_SpeedStateScaleFactors,
    &ett_lte_rrc_SystemInfoListGERAN,
    &ett_lte_rrc_SystemTimeInfoCDMA2000,
    &ett_lte_rrc_T_cdma_SystemTime,
    &ett_lte_rrc_MeasConfig,
    &ett_lte_rrc_T_speedStatePars,
    &ett_lte_rrc_T_setup_12,
    &ett_lte_rrc_MeasIdToRemoveList,
    &ett_lte_rrc_MeasObjectToRemoveList,
    &ett_lte_rrc_ReportConfigToRemoveList,
    &ett_lte_rrc_MeasGapConfig,
    &ett_lte_rrc_T_setup_13,
    &ett_lte_rrc_T_gapOffset,
    &ett_lte_rrc_MeasIdToAddModList,
    &ett_lte_rrc_MeasIdToAddMod,
    &ett_lte_rrc_MeasObjectCDMA2000,
    &ett_lte_rrc_CellsToAddModListCDMA2000,
    &ett_lte_rrc_CellsToAddModCDMA2000,
    &ett_lte_rrc_MeasObjectEUTRA,
    &ett_lte_rrc_CellsToAddModList,
    &ett_lte_rrc_CellsToAddMod,
    &ett_lte_rrc_BlackCellsToAddModList,
    &ett_lte_rrc_BlackCellsToAddMod,
    &ett_lte_rrc_MeasObjectGERAN,
    &ett_lte_rrc_MeasObjectToAddModList,
    &ett_lte_rrc_MeasObjectToAddMod,
    &ett_lte_rrc_T_measObject,
    &ett_lte_rrc_MeasObjectUTRA,
    &ett_lte_rrc_T_cellsToAddModList,
    &ett_lte_rrc_T_cellForWhichToReportCGI,
    &ett_lte_rrc_CellsToAddModListUTRA_FDD,
    &ett_lte_rrc_CellsToAddModUTRA_FDD,
    &ett_lte_rrc_CellsToAddModListUTRA_TDD,
    &ett_lte_rrc_CellsToAddModUTRA_TDD,
    &ett_lte_rrc_MeasResults,
    &ett_lte_rrc_T_measResultServCell,
    &ett_lte_rrc_T_measResultNeighCells_01,
    &ett_lte_rrc_MeasResultListEUTRA,
    &ett_lte_rrc_MeasResultEUTRA,
    &ett_lte_rrc_T_cgi_Info,
    &ett_lte_rrc_T_measResult,
    &ett_lte_rrc_MeasResultListUTRA,
    &ett_lte_rrc_MeasResultUTRA,
    &ett_lte_rrc_T_physCellId,
    &ett_lte_rrc_T_cgi_Info_01,
    &ett_lte_rrc_T_measResult_01,
    &ett_lte_rrc_MeasResultListGERAN,
    &ett_lte_rrc_MeasResultGERAN,
    &ett_lte_rrc_T_cgi_Info_02,
    &ett_lte_rrc_T_measResult_02,
    &ett_lte_rrc_MeasResultsCDMA2000,
    &ett_lte_rrc_MeasResultListCDMA2000,
    &ett_lte_rrc_MeasResultCDMA2000,
    &ett_lte_rrc_T_measResult_03,
    &ett_lte_rrc_MeasResultForECID_r9,
    &ett_lte_rrc_PLMN_IdentityList2,
    &ett_lte_rrc_AdditionalSI_Info_r9,
    &ett_lte_rrc_QuantityConfig,
    &ett_lte_rrc_QuantityConfigEUTRA,
    &ett_lte_rrc_QuantityConfigUTRA,
    &ett_lte_rrc_QuantityConfigGERAN,
    &ett_lte_rrc_QuantityConfigCDMA2000,
    &ett_lte_rrc_ReportConfigEUTRA,
    &ett_lte_rrc_T_triggerType,
    &ett_lte_rrc_T_event,
    &ett_lte_rrc_T_eventId,
    &ett_lte_rrc_T_eventA1,
    &ett_lte_rrc_T_eventA2,
    &ett_lte_rrc_T_eventA3,
    &ett_lte_rrc_T_eventA4,
    &ett_lte_rrc_T_eventA5,
    &ett_lte_rrc_T_periodical,
    &ett_lte_rrc_ThresholdEUTRA,
    &ett_lte_rrc_ReportConfigInterRAT,
    &ett_lte_rrc_T_triggerType_01,
    &ett_lte_rrc_T_event_01,
    &ett_lte_rrc_T_eventId_01,
    &ett_lte_rrc_T_eventB1,
    &ett_lte_rrc_T_b1_Threshold,
    &ett_lte_rrc_T_eventB2,
    &ett_lte_rrc_T_b2_Threshold2,
    &ett_lte_rrc_T_periodical_01,
    &ett_lte_rrc_ThresholdUTRA,
    &ett_lte_rrc_ReportConfigToAddModList,
    &ett_lte_rrc_ReportConfigToAddMod,
    &ett_lte_rrc_T_reportConfig,
    &ett_lte_rrc_OtherConfig_r9,
    &ett_lte_rrc_ReportProximityConfig_r9,
    &ett_lte_rrc_S_TMSI,
    &ett_lte_rrc_UE_CapabilityRAT_ContainerList,
    &ett_lte_rrc_UE_CapabilityRAT_Container,
    &ett_lte_rrc_UE_EUTRA_Capability,
    &ett_lte_rrc_T_interRAT_Parameters,
    &ett_lte_rrc_UE_EUTRA_Capability_v920_IEs,
    &ett_lte_rrc_T_nonCriticalExtension_32,
    &ett_lte_rrc_PDCP_Parameters,
    &ett_lte_rrc_T_supportedROHC_Profiles,
    &ett_lte_rrc_PhyLayerParameters,
    &ett_lte_rrc_PhyLayerParameters_v920,
    &ett_lte_rrc_RF_Parameters,
    &ett_lte_rrc_SupportedBandListEUTRA,
    &ett_lte_rrc_SupportedBandEUTRA,
    &ett_lte_rrc_MeasParameters,
    &ett_lte_rrc_BandListEUTRA,
    &ett_lte_rrc_BandInfoEUTRA,
    &ett_lte_rrc_InterFreqBandList,
    &ett_lte_rrc_InterFreqBandInfo,
    &ett_lte_rrc_InterRAT_BandList,
    &ett_lte_rrc_InterRAT_BandInfo,
    &ett_lte_rrc_IRAT_ParametersUTRA_FDD,
    &ett_lte_rrc_IRAT_ParametersUTRA_v920,
    &ett_lte_rrc_SupportedBandListUTRA_FDD,
    &ett_lte_rrc_IRAT_ParametersUTRA_TDD128,
    &ett_lte_rrc_SupportedBandListUTRA_TDD128,
    &ett_lte_rrc_IRAT_ParametersUTRA_TDD384,
    &ett_lte_rrc_SupportedBandListUTRA_TDD384,
    &ett_lte_rrc_IRAT_ParametersUTRA_TDD768,
    &ett_lte_rrc_SupportedBandListUTRA_TDD768,
    &ett_lte_rrc_IRAT_ParametersGERAN,
    &ett_lte_rrc_IRAT_ParametersGERAN_v920,
    &ett_lte_rrc_SupportedBandListGERAN,
    &ett_lte_rrc_IRAT_ParametersCDMA2000_HRPD,
    &ett_lte_rrc_SupportedBandListHRPD,
    &ett_lte_rrc_IRAT_ParametersCDMA2000_1XRTT,
    &ett_lte_rrc_IRAT_ParametersCDMA2000_1XRTT_v920,
    &ett_lte_rrc_SupportedBandList1XRTT,
    &ett_lte_rrc_CSG_ProximityIndicationParameters_r9,
    &ett_lte_rrc_NeighCellSI_AcquisitionParameters_r9,
    &ett_lte_rrc_SON_Parameters_r9,
    &ett_lte_rrc_UE_TimersAndConstants,
    &ett_lte_rrc_MBMS_NotificationConfig_r9,
    &ett_lte_rrc_MBSFN_AreaInfoList_r9,
    &ett_lte_rrc_MBSFN_AreaInfo_r9,
    &ett_lte_rrc_T_mcch_Config_r9,
    &ett_lte_rrc_MBSFN_SubframeConfig,
    &ett_lte_rrc_T_subframeAllocation,
    &ett_lte_rrc_PMCH_InfoList_r9,
    &ett_lte_rrc_PMCH_Info_r9,
    &ett_lte_rrc_MBMS_SessionInfoList_r9,
    &ett_lte_rrc_MBMS_SessionInfo_r9,
    &ett_lte_rrc_PMCH_Config_r9,
    &ett_lte_rrc_TMGI_r9,
    &ett_lte_rrc_T_plmn_Id_r9,
    &ett_lte_rrc_CellsTriggeredList,
    &ett_lte_rrc_CellsTriggeredList_item,
    &ett_lte_rrc_T_physCellIdUTRA,
    &ett_lte_rrc_T_physCellIdGERAN,
    &ett_lte_rrc_HandoverCommand,
    &ett_lte_rrc_T_criticalExtensions_30,
    &ett_lte_rrc_T_c1_26,
    &ett_lte_rrc_T_criticalExtensionsFuture_30,
    &ett_lte_rrc_HandoverCommand_r8_IEs,
    &ett_lte_rrc_T_nonCriticalExtension_33,
    &ett_lte_rrc_HandoverPreparationInformation,
    &ett_lte_rrc_T_criticalExtensions_31,
    &ett_lte_rrc_T_c1_27,
    &ett_lte_rrc_T_criticalExtensionsFuture_31,
    &ett_lte_rrc_HandoverPreparationInformation_r8_IEs,
    &ett_lte_rrc_HandoverPreparationInformation_v920_IEs,
    &ett_lte_rrc_T_nonCriticalExtension_34,
    &ett_lte_rrc_UERadioAccessCapabilityInformation,
    &ett_lte_rrc_T_criticalExtensions_32,
    &ett_lte_rrc_T_c1_28,
    &ett_lte_rrc_T_criticalExtensionsFuture_32,
    &ett_lte_rrc_UERadioAccessCapabilityInformation_r8_IEs,
    &ett_lte_rrc_T_nonCriticalExtension_35,
    &ett_lte_rrc_AS_Config,
    &ett_lte_rrc_AS_Context,
    &ett_lte_rrc_ReestablishmentInfo,
    &ett_lte_rrc_AdditionalReestabInfoList,
    &ett_lte_rrc_AdditionalReestabInfo,
    &ett_lte_rrc_RRM_Config,

/*--- End of included file: packet-lte-rrc-ettarr.c ---*/
#line 149 "packet-lte-rrc-template.c"
  };


  /* Register protocol */
  proto_lte_rrc = proto_register_protocol(PNAME, PSNAME, PFNAME);

  /* These entry points will first create an lte_rrc root node */
  register_dissector("lte_rrc.dl_ccch", dissect_lte_rrc_DL_CCCH, proto_lte_rrc);
  register_dissector("lte_rrc.dl_dcch", dissect_lte_rrc_DL_DCCH, proto_lte_rrc);
  register_dissector("lte_rrc.ul_ccch", dissect_lte_rrc_UL_CCCH, proto_lte_rrc);
  register_dissector("lte_rrc.ul_dcch", dissect_lte_rrc_UL_DCCH, proto_lte_rrc);

  /* Register fields and subtrees */
  proto_register_field_array(proto_lte_rrc, hf, array_length(hf));
  proto_register_subtree_array(ett, array_length(ett));

  /* Register the dissectors defined in lte-rrc.conf */

/*--- Included file: packet-lte-rrc-dis-reg.c ---*/
#line 1 "packet-lte-rrc-dis-reg.c"
  new_register_dissector("lte-rrc.bcch.bch", dissect_BCCH_BCH_Message_PDU, proto_lte_rrc);
  new_register_dissector("lte-rrc.bcch.dl.sch", dissect_BCCH_DL_SCH_Message_PDU, proto_lte_rrc);
  new_register_dissector("lte-rrc.mcch", dissect_MCCH_Message_PDU, proto_lte_rrc);
  new_register_dissector("lte-rrc.pcch", dissect_PCCH_Message_PDU, proto_lte_rrc);
  new_register_dissector("lte-rrc.dl.ccch", dissect_DL_CCCH_Message_PDU, proto_lte_rrc);
  new_register_dissector("lte-rrc.dl.dcch", dissect_DL_DCCH_Message_PDU, proto_lte_rrc);
  new_register_dissector("lte-rrc.ul.ccch", dissect_UL_CCCH_Message_PDU, proto_lte_rrc);
  new_register_dissector("lte-rrc.ul.dcch", dissect_UL_DCCH_Message_PDU, proto_lte_rrc);
  new_register_dissector("lte-rrc.ue_cap_info", dissect_UECapabilityInformation_PDU, proto_lte_rrc);
  new_register_dissector("lte-rrc.ue_eutra_cap", dissect_UE_EUTRA_Capability_PDU, proto_lte_rrc);


/*--- End of included file: packet-lte-rrc-dis-reg.c ---*/
#line 167 "packet-lte-rrc-template.c"

}


/*--- proto_reg_handoff_rrc ---------------------------------------*/
void
proto_reg_handoff_lte_rrc(void)
{
	static dissector_handle_t lte_rrc_dl_ccch_handle;

	lte_rrc_dl_ccch_handle = find_dissector("lte_rrc.dl_ccch");
	dissector_add_handle("udp.port", lte_rrc_dl_ccch_handle);
	nas_eps_handle = find_dissector("nas-eps");

	/* MQ 08-18-2010 */
        UL_DCCH_handle = create_dissector_handle(dissect_UL_DCCH_Message_PDU, proto_lte_rrc);
        dissector_add("udp.port", 7867 , UL_DCCH_handle);

}


