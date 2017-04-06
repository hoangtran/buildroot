/*SH0
*******************************************************************************
**                                                                           **
**         Copyright (c) 2009 - 2012 Quantenna Communications, Inc.          **
**                                                                           **
**  File        : qcsapi_driver.c                                            **
**  Description :                                                            **
**                                                                           **
*******************************************************************************
**                                                                           **
**  Redistribution and use in source and binary forms, with or without       **
**  modification, are permitted provided that the following conditions       **
**  are met:                                                                 **
**  1. Redistributions of source code must retain the above copyright        **
**     notice, this list of conditions and the following disclaimer.         **
**  2. Redistributions in binary form must reproduce the above copyright     **
**     notice, this list of conditions and the following disclaimer in the   **
**     documentation and/or other materials provided with the distribution.  **
**  3. The name of the author may not be used to endorse or promote products **
**     derived from this software without specific prior written permission. **
**                                                                           **
**  Alternatively, this software may be distributed under the terms of the   **
**  GNU General Public License ("GPL") version 2, or (at your option) any    **
**  later version as published by the Free Software Foundation.              **
**                                                                           **
**  In the case this software is distributed under the GPL license,          **
**  you should have received a copy of the GNU General Public License        **
**  along with this software; if not, write to the Free Software             **
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA  **
**                                                                           **
**  THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR       **
**  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES**
**  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  **
**  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,         **
**  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT **
**  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,**
**  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    **
**  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT      **
**  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF **
**  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.        **
**                                                                           **
*******************************************************************************
EH0*/

#include <stdio.h>

#include "qcsapi.h"
#include "qcsapi_driver.h"

static const qcsapi_entry qcsapi_entry_table[] =
{
	{ e_qcsapi_errno_get_message,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_store_ipaddr,
 	  e_qcsapi_set_system_value,
 	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{
	  e_qcsapi_get_stored_ipaddr,
	  e_qcsapi_get_api_without_ifname_parameter,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_interface_enable,
 	  e_qcsapi_set_api,
 	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_interface_get_BSSID,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_mac_addr
	},
	{ e_qcsapi_interface_get_mac_addr,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_mac_addr
	},
	{ e_qcsapi_interface_set_mac_addr,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_mac_addr
	},
	{ e_qcsapi_interface_get_counter,
	  e_qcsapi_get_api,
	  e_qcsapi_counter,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_interface_get_counter64,
	  e_qcsapi_get_api,
	  e_qcsapi_counter,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_pm_get_counter,
	  e_qcsapi_get_api,
	  e_qcsapi_counter,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_pm_get_elapsed_time,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_flash_image_update,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_firmware_get_version,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_system_get_time_since_start,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_get_system_status,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_get_random_seed,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_nosuch_specific_parameter
	},
	{ e_qcsapi_set_random_seed,
	  e_qcsapi_set_system_value,
	  e_qcsapi_none,
	  e_qcsapi_nosuch_specific_parameter
	},
	{ e_qcsapi_led_get,
	  e_qcsapi_get_system_value,
	  e_qcsapi_LED,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_led_set,
	  e_qcsapi_set_system_value,
	  e_qcsapi_LED,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_led_pwm_enable,
	  e_qcsapi_set_system_value,
	  e_qcsapi_LED,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_led_brightness,
	  e_qcsapi_set_system_value,
	  e_qcsapi_LED,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_gpio_get_config,
	  e_qcsapi_get_system_value,
	  e_qcsapi_LED,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_gpio_set_config,
	  e_qcsapi_set_system_value,
	  e_qcsapi_LED,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_gpio_enable_wps_push_button,
	  e_qcsapi_set_system_value,
	  e_qcsapi_LED,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_file_path_get_config,
	  e_qcsapi_get_system_value,
	  e_qcsapi_file_path_config,
	  e_qcsapi_string
	},
	{ e_qcsapi_file_path_set_config,
	  e_qcsapi_set_system_value,
	  e_qcsapi_file_path_config,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_wifi_macaddr,
	  e_qcsapi_set_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_create_restricted_bss,
	  e_qcsapi_set_api_without_parameter,
	  e_qcsapi_none,
	  e_qcsapi_nosuch_specific_parameter
	},
	{ e_qcsapi_wifi_create_bss,
	  e_qcsapi_set_api_without_parameter,
	  e_qcsapi_none,
	  e_qcsapi_nosuch_specific_parameter
	},
	{ e_qcsapi_wifi_remove_bss,
	  e_qcsapi_set_api_without_parameter,
	  e_qcsapi_none,
	  e_qcsapi_nosuch_specific_parameter
	},
	{ e_qcsapi_wifi_get_primary_interface,
	  e_qcsapi_get_api_without_ifname_parameter,
	  e_qcsapi_none,
	  e_qcsapi_nosuch_specific_parameter
	},
	{ e_qcsapi_wifi_get_interface_by_index,
	  e_qcsapi_get_api_without_ifname,
	  e_qcsapi_index,
	  e_qcsapi_nosuch_specific_parameter
	},
	{ e_qcsapi_wifi_get_mode,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_wifi_mode
	},
	{ e_qcsapi_wifi_set_mode,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_wifi_mode
	},
	{ e_qcsapi_wifi_get_phy_mode,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_wifi_mode
	},
	{ e_qcsapi_wifi_set_phy_mode,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_wifi_mode
	},
	{ e_qcsapi_wifi_reload_in_mode,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_wifi_mode
	},
	{ e_qcsapi_wifi_rfenable,
	  e_qcsapi_set_system_value,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_rfstatus,
	  e_qcsapi_get_api_without_ifname,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_startprod,
	  e_qcsapi_get_api_without_ifname_parameter,
	  e_qcsapi_none,
	  e_qcsapi_none
	},
	{ e_qcsapi_wifi_get_freq_bands,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_bw,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_bw,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_24g_bw,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_24g_bw,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_BSSID,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_mac_addr
	},
	{ e_qcsapi_wifi_get_config_BSSID,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_mac_addr
	},
	{ e_qcsapi_wifi_ssid_get_bssid,
	  e_qcsapi_get_api,
	  e_qcsapi_select_SSID,
	  e_qcsapi_mac_addr
	},
	{ e_qcsapi_wifi_ssid_set_bssid,
	  e_qcsapi_set_api,
	  e_qcsapi_select_SSID,
	  e_qcsapi_mac_addr
	},
	{ e_qcsapi_wifi_get_SSID,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_SSID_param
	},
	{ e_qcsapi_wifi_set_SSID,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_SSID_param
	},
	{ e_qcsapi_wifi_get_channel,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_channel,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_auto_channel,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_none
	},
	{ e_qcsapi_wifi_set_auto_channel,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_standard,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_dtim,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_dtim,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_assoc_limit,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_assoc_limit,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_bss_assoc_limit,
	  e_qcsapi_get_api_without_ifname,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_bss_assoc_limit,
	  e_qcsapi_set_api_without_ifname,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_interface_get_status,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_interface_set_ip4,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_interface_get_ip4,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_list_channels,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_supp_chans,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_mode_switch,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_noise,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_rssi_by_chain,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_avg_snr,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_option,
	  e_qcsapi_get_api,
	  e_qcsapi_option,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_set_option,
	  e_qcsapi_set_api,
	  e_qcsapi_option,
	  e_qcsapi_integer
	},
	{ e_qcsapi_get_board_parameter,
	  e_qcsapi_get_system_value,
	  e_qcsapi_board_parameter,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_rates,
	  e_qcsapi_get_api,
	  e_qcsapi_rates,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_rates,
	  e_qcsapi_set_api,
	  e_qcsapi_rates,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_max_bitrate,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_max_bitrate,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_beacon_type,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_beacon_type,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_beacon_interval,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_beacon_interval,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_list_regulatory_regions,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_regulatory_tx_power,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_configured_tx_power,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_regulatory_channel,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_regulatory_region,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_regulatory_region,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_overwrite_country_code,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_list_regulatory_channels,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_list_regulatory_bands,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_regulatory_db_version,
	  e_qcsapi_get_api_without_ifname,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_regulatory_tx_power_cap,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_restore_regulatory_tx_power,
	  e_qcsapi_set_api_without_parameter,
	  e_qcsapi_none,
	  e_qcsapi_none
	},
	{ e_qcsapi_wifi_get_chan_pri_inactive,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_none
	},
	{ e_qcsapi_wifi_set_chan_pri_inactive,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_chan_disabled,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_chan_disabled,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_chan_usable,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_tx_power,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_tx_power,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_tx_power_ext,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_tx_power_ext,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_chan_power_table,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_chan_power_table,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_bw_power,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_bw_power,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_bf_power,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_bf_power,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_power_selection,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_power_selection,
	  e_qcsapi_set_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_carrier_interference,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_congestion_idx,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_supported_tx_power_levels,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_current_tx_power_level,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_current_tx_power_level,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_power_constraint,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_power_constraint,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_tpc_interval,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_tpc_interval,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_assoc_records,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_list_DFS_channels,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_is_channel_DFS,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_DFS_alt_channel,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_set_DFS_alt_channel,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_set_DFS_reentry,
	  e_qcsapi_set_api_without_parameter,
	  e_qcsapi_none,
	  e_qcsapi_none
	},
	{ e_qcsapi_wifi_get_scs_cce_channels,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_dfs_cce_channels,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_csw_records,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_none,
	},
	{ e_qcsapi_wifi_get_radar_status,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_none,
	},
	{ e_qcsapi_wifi_get_WEP_encryption_level,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_WPA_encryption_modes,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_WPA_encryption_modes,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_WPA_authentication_mode,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_WPA_authentication_mode,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_interworking,
          e_qcsapi_get_api,
          e_qcsapi_none,
          e_qcsapi_string
        },
	{ e_qcsapi_wifi_set_interworking,
          e_qcsapi_set_api,
          e_qcsapi_none,
          e_qcsapi_string
        },
	{ e_qcsapi_wifi_get_80211u_params,
          e_qcsapi_get_api,
          e_qcsapi_none,
          e_qcsapi_string
        },
	{ e_qcsapi_wifi_set_80211u_params,
          e_qcsapi_set_api,
          e_qcsapi_none,
          e_qcsapi_string
        },
	{ e_qcsapi_security_get_nai_realms,
          e_qcsapi_get_api,
          e_qcsapi_none,
          e_qcsapi_string
        },
	{ e_qcsapi_security_add_nai_realm,
          e_qcsapi_set_api,
          e_qcsapi_none,
          e_qcsapi_string
        },
	{ e_qcsapi_security_del_nai_realm,
          e_qcsapi_set_api,
          e_qcsapi_none,
          e_qcsapi_string
        },
	{ e_qcsapi_security_add_roaming_consortium,
          e_qcsapi_set_api,
          e_qcsapi_none,
          e_qcsapi_string
        },
	{ e_qcsapi_security_del_roaming_consortium,
          e_qcsapi_set_api,
          e_qcsapi_none,
          e_qcsapi_string
        },
	{ e_qcsapi_security_get_roaming_consortium,
          e_qcsapi_get_api,
          e_qcsapi_none,
          e_qcsapi_string
        },
	{ e_qcsapi_security_get_venue_name,
          e_qcsapi_get_api,
          e_qcsapi_none,
          e_qcsapi_string
        },
	{ e_qcsapi_security_add_venue_name,
          e_qcsapi_set_api,
          e_qcsapi_none,
          e_qcsapi_string
        },
	{ e_qcsapi_security_del_venue_name,
          e_qcsapi_set_api,
          e_qcsapi_none,
          e_qcsapi_string
        },
	{ e_qcsapi_security_get_oper_friendly_name,
          e_qcsapi_get_api,
          e_qcsapi_none,
          e_qcsapi_string
        },
	{ e_qcsapi_security_add_oper_friendly_name,
          e_qcsapi_set_api,
          e_qcsapi_none,
          e_qcsapi_string
        },
	{ e_qcsapi_security_del_oper_friendly_name,
          e_qcsapi_set_api,
          e_qcsapi_none,
          e_qcsapi_string
        },
	{ e_qcsapi_security_get_hs20_conn_capab,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_security_add_hs20_conn_capab,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_security_del_hs20_conn_capab,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},

	{ e_qcsapi_security_add_hs20_icon,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_security_get_hs20_icon,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_security_del_hs20_icon,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},

	{ e_qcsapi_security_add_osu_server_uri,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_security_get_osu_server_uri,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_security_del_osu_server_uri,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},

	{ e_qcsapi_security_add_osu_server_param,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_security_get_osu_server_param,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_security_del_osu_server_param,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},

	{ e_qcsapi_wifi_get_hs20_status,
          e_qcsapi_get_api,
          e_qcsapi_none,
          e_qcsapi_string
        },
	{ e_qcsapi_wifi_set_hs20_status,
          e_qcsapi_set_api,
          e_qcsapi_none,
          e_qcsapi_string
        },
	{ e_qcsapi_wifi_get_proxy_arp,
          e_qcsapi_get_api,
          e_qcsapi_none,
          e_qcsapi_string
        },
	{ e_qcsapi_wifi_set_proxy_arp,
          e_qcsapi_set_api,
          e_qcsapi_none,
          e_qcsapi_string
        },
	{ e_qcsapi_wifi_get_l2_ext_filter,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_l2_ext_filter,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_hs20_params,
          e_qcsapi_get_api,
          e_qcsapi_none,
          e_qcsapi_string
        },
	{ e_qcsapi_wifi_set_hs20_params,
          e_qcsapi_set_api,
          e_qcsapi_none,
          e_qcsapi_string
        },
	{ e_qcsapi_remove_11u_param,
          e_qcsapi_set_api,
          e_qcsapi_none,
          e_qcsapi_string
        },
	{ e_qcsapi_remove_hs20_param,
          e_qcsapi_set_api,
          e_qcsapi_none,
          e_qcsapi_string
        },
	{ e_qcsapi_wifi_get_IEEE11i_encryption_modes,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_IEEE11i_encryption_modes,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_IEEE11i_authentication_mode,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_IEEE11i_authentication_mode,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_michael_errcnt,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_pre_shared_key,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_pre_shared_key,
	  e_qcsapi_set_api,
	  e_qcsapi_index,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_add_radius_auth_server_cfg,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_del_radius_auth_server_cfg,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_radius_auth_server_cfg,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_add_radius_acct_server_cfg,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_del_radius_acct_server_cfg,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_radius_acct_server_cfg,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_radius_acct_interim_interval,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_radius_acct_interim_interval,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_eap_own_ip_addr,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_eap_own_ip_addr,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_psk_auth_failures,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_key_passphrase,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_key_passphrase,
	  e_qcsapi_set_api,
	  e_qcsapi_index,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_group_key_interval,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_group_key_interval,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_pairwise_key_interval,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_pairwise_key_interval,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_pmf,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_pmf,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_mac_address_filtering,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_set_mac_address_filtering,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_is_mac_address_authorized,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_mac_addr
	},
	{ e_qcsapi_wifi_get_authorized_mac_addresses,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_denied_mac_addresses,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_authorize_mac_address,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_mac_addr
	},
	{ e_qcsapi_wifi_deny_mac_address,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_mac_addr
	},
	{ e_qcsapi_wifi_remove_mac_address,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_mac_addr
	},
	{ e_qcsapi_wifi_add_temp_acl_macaddr,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_mac_addr
	},
	{ e_qcsapi_wifi_del_temp_acl_macaddr,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_mac_addr
	},
	{ e_qcsapi_wifi_clear_mac_address_filters,
	  e_qcsapi_set_api_without_parameter,
	  e_qcsapi_none,
	  e_qcsapi_nosuch_specific_parameter
	},
	{ e_qcsapi_wifi_set_mac_address_reserve,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_nosuch_specific_parameter
	},
	{ e_qcsapi_wifi_get_mac_address_reserve,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_nosuch_specific_parameter
	},
	{ e_qcsapi_wifi_clear_mac_address_reserve,
	  e_qcsapi_set_api_without_parameter,
	  e_qcsapi_none,
	  e_qcsapi_nosuch_specific_parameter
	},
	{ e_qcsapi_wifi_backoff_fail_max,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_backoff_timeout,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_count_associations,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_associated_device_mac_addr,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_mac_addr
	},
	{ e_qcsapi_wifi_get_associated_device_ip_addr,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_link_quality,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_rssi_per_association,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_rssi_in_dbm_per_association,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_snr_per_association,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_hw_noise_per_association,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_rx_bytes_per_association,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_tx_bytes_per_association,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_rx_packets_per_association,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_tx_packets_per_association,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_tx_err_packets_per_association,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_bw_per_association,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_tx_phy_rate_per_association,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_rx_phy_rate_per_association,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_tx_mcs_per_association,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_rx_mcs_per_association,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_achievable_tx_phy_rate_per_association,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_achievable_rx_phy_rate_per_association,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_auth_enc_per_association,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_tput_caps,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_nosuch_specific_parameter
	},
	{ e_qcsapi_wifi_get_connection_mode,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_vendor_per_association,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_max_mimo,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_node_counter,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_node_param,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_node_stats,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_max_queued,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wps_registrar_report_button_press,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wps_registrar_report_pin,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wps_registrar_get_pp_devname,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wps_registrar_set_pp_devname,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wps_enrollee_report_button_press,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wps_enrollee_report_pin,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wps_enrollee_generate_pin,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wps_get_ap_pin,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wps_set_ap_pin,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wps_save_ap_pin,
	  e_qcsapi_set_api_without_parameter,
	  e_qcsapi_none,
	  e_qcsapi_nosuch_specific_parameter
	},
	{ e_qcsapi_wps_enable_ap_pin,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wps_get_sta_pin,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wps_configure_ap,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wps_get_state,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wps_get_configured_state,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wps_set_configured_state,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wps_get_runtime_state,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wps_get_allow_pbc_overlap_status,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wps_allow_pbc_overlap,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wps_get_param,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_dwell_times,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_dwell_times,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_bgscan_dwell_times,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_bgscan_dwell_times,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_start_scan,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_cancel_scan,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_scan_status,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_cac_status,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_wait_scan_completes,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_set_scan_chk_inv,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_scan_chk_inv,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_update_bss_cfg,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_SSID_create_SSID,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_SSID_param
	},
	{ e_qcsapi_SSID_remove_SSID,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_SSID_param
	},
	{ e_qcsapi_SSID_verify_SSID,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_SSID_param
	},
	{ e_qcsapi_SSID_rename_SSID,
	  e_qcsapi_set_api,
	  e_qcsapi_select_SSID,
	  e_qcsapi_SSID_param
	},
	{ e_qcsapi_SSID_get_SSID_list,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_associate,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_SSID_param
	},
	{ e_qcsapi_wifi_associate_noscan,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_SSID_param
	},
	{ e_qcsapi_SSID_get_protocol,
	  e_qcsapi_get_api,
	  e_qcsapi_select_SSID,
	  e_qcsapi_string
	},
	{ e_qcsapi_SSID_set_protocol,
	  e_qcsapi_set_api,
	  e_qcsapi_select_SSID,
	  e_qcsapi_string
	},
	{ e_qcsapi_SSID_get_encryption_modes,
	  e_qcsapi_get_api,
	  e_qcsapi_select_SSID,
	  e_qcsapi_string
	},
	{ e_qcsapi_SSID_set_encryption_modes,
	  e_qcsapi_set_api,
	  e_qcsapi_select_SSID,
	  e_qcsapi_string
	},
	{ e_qcsapi_SSID_get_group_encryption,
	  e_qcsapi_get_api,
	  e_qcsapi_select_SSID,
	  e_qcsapi_string
	},
	{ e_qcsapi_SSID_set_group_encryption,
	  e_qcsapi_set_api,
	  e_qcsapi_select_SSID,
	  e_qcsapi_string
	},
	{ e_qcsapi_SSID_get_authentication_mode,
	  e_qcsapi_get_api,
	  e_qcsapi_select_SSID,
	  e_qcsapi_string
	},
	{ e_qcsapi_SSID_set_authentication_mode,
	  e_qcsapi_set_api,
	  e_qcsapi_select_SSID,
	  e_qcsapi_string
	},
	{ e_qcsapi_SSID_get_pre_shared_key,
	  e_qcsapi_get_api,
	  e_qcsapi_SSID_index,
	  e_qcsapi_string
	},
	{ e_qcsapi_SSID_set_pre_shared_key,
	  e_qcsapi_get_api,
	  e_qcsapi_SSID_index,
	  e_qcsapi_string
	},
	{ e_qcsapi_SSID_get_key_passphrase,
	  e_qcsapi_get_api,
	  e_qcsapi_SSID_index,
	  e_qcsapi_string
	},
	{ e_qcsapi_SSID_set_key_passphrase,
	  e_qcsapi_get_api,
	  e_qcsapi_SSID_index,
	  e_qcsapi_string
	},
	{ e_qcsapi_SSID_get_pmf,
	  e_qcsapi_get_api,
	  e_qcsapi_select_SSID,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_SSID_set_pmf,
	  e_qcsapi_get_api,
	  e_qcsapi_select_SSID,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_SSID_get_wps_SSID,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_SSID_param
	},
	{ e_qcsapi_wifi_vlan_config,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_show_vlan_config,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_br_vlan_promisc,
	  e_qcsapi_set_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_add_multicast,
	  e_qcsapi_set_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_del_multicast,
	  e_qcsapi_set_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_get_multicast_list,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_add_ipff,
	  e_qcsapi_set_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_del_ipff,
	  e_qcsapi_set_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_get_ipff,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_start_cca,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_disable_wps,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_disassociate,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_results_AP_scan,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_count_APs_scanned,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_properties_AP,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_mcs_rate,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_mcs_rate,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_service_control,
	  e_qcsapi_set_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string,
	},
	{ e_qcsapi_wfa_cert,
	  e_qcsapi_set_system_value,
	  e_qcsapi_none,
	  e_qcsapi_integer,
	},
	{ e_qcsapi_wifi_enable_scs,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_scs_switch_channel,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_scs_verbose,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_scs_smpl_enable,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_scs_active_chan_list,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_scs_active_chan_list,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_scs_smpl_dwell_time,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_scs_smpl_intv,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_scs_smpl_intv,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_scs_smpl_type,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_scs_intf_detect_intv,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_scs_thrshld,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_scs_report_only,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_scs_status,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_scs_report_stat,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_scs_cca_intf_smth_fctr,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_scs_chan_mtrc_mrgn,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_scs_nac_monitor_mode,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_scs_dfs_reentry_request,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_scs_cca_intf,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_scs_param,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_scs_stats,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_scs_burst_enable,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_scs_burst_window,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_scs_burst_thresh,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_scs_burst_pause,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_scs_burst_switch,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_start_ocac,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_stop_ocac,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_ocac_status,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_ocac_threshold,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_ocac_dwell_time,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_ocac_duration,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_ocac_cac_time,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_ocac_report_only,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_start_dfs_s_radio,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_stop_dfs_s_radio,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_dfs_s_radio_status,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_dfs_s_radio_availability,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_dfs_s_radio_threshold,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_dfs_s_radio_dwell_time,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_dfs_s_radio_duration,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_dfs_s_radio_cac_time,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_dfs_s_radio_report_only,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_dfs_s_radio_wea_duration,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_dfs_s_radio_wea_cac_time,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_dfs_s_radio_wea_dwell_time,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_ap_isolate,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_set_ap_isolate,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_power_save,
	  e_qcsapi_get_api_without_ifname_parameter,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_qpm_level,
	  e_qcsapi_get_api_without_ifname_parameter,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_time_associated_per_association,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_wds_add_peer,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_mac_addr
	},
	{ e_qcsapi_wifi_wds_remove_peer,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_mac_addr
	},
	{ e_qcsapi_wifi_wds_get_peer_address,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_wds_get_psk,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_nosuch_specific_parameter
	},
	{ e_qcsapi_wifi_wds_set_psk,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_nosuch_specific_parameter
	},
	{ e_qcsapi_wifi_wds_set_mode,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_wds_get_mode,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_qos_get_param,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_qos_set_param,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_wmm_ac_map,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_set_wmm_ac_map,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_dscp_8021p_map,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_set_dscp_8021p_map,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_dscp_ac_map,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_set_dscp_ac_map,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_ac_agg_hold_time,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_set_ac_agg_hold_time,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_set_qos_map,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_del_qos_map,
	  e_qcsapi_set_api_without_parameter,
	  e_qcsapi_none,
	  e_qcsapi_nosuch_specific_parameter
	},
	{ e_qcsapi_wifi_get_qos_map,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_send_qos_map_conf,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_mac_addr
	},
	{ e_qcsapi_wifi_get_dscp_tid_map,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_priority,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_set_priority,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_airfair,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_set_airfair,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_config_get_parameter,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_config_update_parameter,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_config_get_ssid_parameter,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_config_update_ssid_parameter,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_get_qfdr_parameter,
	  e_qcsapi_get_api_without_ifname,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_set_qfdr_parameter,
	  e_qcsapi_set_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_get_qfdr_state,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_bootcfg_get_parameter,
	  e_qcsapi_get_api_without_ifname,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_bootcfg_update_parameter,
	  e_qcsapi_set_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_bootcfg_commit,
	  e_qcsapi_get_api_without_ifname,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_vendor_fix,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_get_interface_stats,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_get_phy_stats,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_wps_set_access_control,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_wps_get_access_control,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_non_wps_set_pp_enable,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_non_wps_get_pp_enable,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_wps_cancel,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_none
	},
	{
	  e_qcsapi_wps_set_pbc_in_srcm,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{
	  e_qcsapi_wps_get_pbc_in_srcm,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_wps_timeout,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{
	  e_qcsapi_wps_on_hidden_ssid,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{
	  e_qcsapi_wps_on_hidden_ssid_status,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_wps_upnp_enable,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{
	  e_qcsapi_wps_upnp_status,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_none
	},
	{
	  e_qcsapi_wps_registrar_set_dfl_pbc_bss,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_wps_registrar_get_dfl_pbc_bss,
	  e_qcsapi_get_api_without_ifname_parameter,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_wps_set_dfl_pbc_bss,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_wps_get_dfl_pbc_bss,
	  e_qcsapi_get_api_without_ifname_parameter,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_wifi_get_wpa_status,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_wifi_get_auth_state,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_wifi_get_disconn_info,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_wifi_reset_disconn_info,
	  e_qcsapi_set_api_without_parameter,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_wifi_get_pairing_id,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_wifi_set_pairing_id,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_wifi_get_pairing_enable,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_wifi_set_pairing_enable,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_rts_threshold,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_rts_threshold,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{
	  e_qcsapi_wifi_set_txqos_sched_tbl,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_wifi_get_txqos_sched_tbl,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_wps_set_param,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_reset_all_stats,
	  e_qcsapi_set_api,
	  e_qcsapi_index,
	  e_qcsapi_integer
	},
	{
	  e_qcsapi_eth_phy_power_off,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_aspm_l1,
	  e_qcsapi_set_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_l1,
	  e_qcsapi_set_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_test_traffic,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_get_temperature,
	  e_qcsapi_get_api_without_ifname_parameter,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_telnet_enable,
	  e_qcsapi_set_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_restore_default_config,
	  e_qcsapi_get_api_without_ifname_parameter,
	  e_qcsapi_none,
	  e_qcsapi_nosuch_specific_parameter
	},
	{ e_qcsapi_run_script,
	  e_qcsapi_get_api_without_ifname_parameter,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_qtm,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_nosuch_specific_parameter
	},
	{ e_qcsapi_set_accept_oui_filter,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_mac_addr
	},
	{ e_qcsapi_get_accept_oui_filter,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_get_swfeat_list,
	  e_qcsapi_get_api_without_ifname_parameter,
	  e_qcsapi_none,
	  e_qcsapi_nosuch_specific_parameter
	},
	{ e_qcsapi_wifi_set_vht,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_vht,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_calcmd_check_rfic_health,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_calcmd_set_test_mode,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_calcmd_show_test_packet,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_calcmd_send_test_packet,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_calcmd_stop_test_packet,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_calcmd_send_dc_cw_signal,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_calcmd_stop_dc_cw_signal,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_calcmd_get_test_mode_antenna_sel,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_calcmd_get_test_mode_mcs,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_calcmd_get_test_mode_bw,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_calcmd_get_tx_power,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_calcmd_set_tx_power,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_calcmd_get_test_mode_rssi,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_calcmd_set_mac_filter,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_calcmd_get_antenna_count,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_calcmd_clear_counter,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_calcmd_get_info,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_set_soc_macaddr,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_disable_dfs_channels,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_get_carrier_id,
	  e_qcsapi_get_api_without_ifname_parameter,
	  e_qcsapi_none,
	  e_qcsapi_nosuch_specific_parameter
	},
	{ e_qcsapi_set_carrier_id,
	  e_qcsapi_get_api_without_ifname_parameter,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_enable_tdls,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_enable_tdls_over_qhop,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_tdls_status,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_tdls_params,
	  e_qcsapi_set_api,
	  e_qcsapi_tdls_params,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_tdls_params,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_tdls_operate,
	  e_qcsapi_set_api,
	  e_qcsapi_tdls_oper,
	  e_qcsapi_string
	},
	{ e_qcsapi_get_spinor_jedecid,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_get_custom_value,
	  e_qcsapi_get_api_without_ifname,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_set_custom_value,
	  e_qcsapi_set_api_without_ifname,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_get_vco_lock_detect_mode,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_set_vco_lock_detect_mode,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_mlme_stats_per_mac,
	  e_qcsapi_get_api_without_ifname_parameter,
	  e_qcsapi_none,
	  e_qcsapi_string,
	},
	{ e_qcsapi_wifi_get_mlme_stats_per_association,
	  e_qcsapi_get_api,
	  e_qcsapi_index,
	  e_qcsapi_string,
	},
	{ e_qcsapi_wifi_get_mlme_stats_macs_list,
	  e_qcsapi_get_api_without_ifname_parameter,
	  e_qcsapi_none,
	  e_qcsapi_string,
	},
	{
	  e_qcsapi_get_nss_cap,
	  e_qcsapi_get_api,
	  e_qcsapi_modulation,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_set_nss_cap,
	  e_qcsapi_set_api,
	  e_qcsapi_modulation,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_get_rx_nss_cap,
	  e_qcsapi_get_api,
	  e_qcsapi_modulation,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_set_rx_nss_cap,
	  e_qcsapi_set_api,
	  e_qcsapi_modulation,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_get_security_defer_mode,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{
	  e_qcsapi_set_security_defer_mode,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{
	  e_qcsapi_apply_security_config,
	  e_qcsapi_set_api_without_parameter,
	  e_qcsapi_none,
	  e_qcsapi_none,
	},
	{ e_qcsapi_wifi_set_intra_bss_isolate,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_intra_bss_isolate,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_bss_isolate,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_bss_isolate,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wowlan_host_state,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wowlan_match_type,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wowlan_L2_type,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wowlan_udp_port,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wowlan_pattern,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wowlan_get_host_state,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wowlan_get_match_type,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wowlan_get_L2_type,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wowlan_get_udp_port,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wowlan_get_pattern,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_extender_params,
	  e_qcsapi_set_api,
	  e_qcsapi_extender_params,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_extender_status,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_update_autochan_params,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_autochan_params,
	  e_qcsapi_set_api,
	  e_qcsapi_autochan_params,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_autochan_params,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_enable_bgscan,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_bgscan_status,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_get_uboot_info,
	  e_qcsapi_get_api_without_ifname_parameter,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_disassoc_reason,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_is_startprod_done,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_disassociate_sta,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_mac_addr
	},
	{ e_qcsapi_wifi_reassociate,
	  e_qcsapi_set_api_without_parameter,
	  e_qcsapi_none,
	  e_qcsapi_nosuch_specific_parameter
	},
	{ e_qcsapi_get_bb_param,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_set_bb_param,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_tx_amsdu,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_set_tx_amsdu,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_set_scan_buf_max_size,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_scan_buf_max_size,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_scan_table_max_len,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_scan_table_max_len,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_enable_mu,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_enable_mu,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_mu_use_precode,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_mu_use_precode,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_mu_use_eq,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_mu_use_eq,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_mu_groups,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_send_file,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_get_emac_switch,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_set_emac_switch,
	  e_qcsapi_set_system_value,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_eth_dscp_map,
	  e_qcsapi_set_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_set_optim_stats,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_pref_band,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_pref_band,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_set_sys_time,
	  e_qcsapi_set_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_get_sys_time,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_get_eth_info,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_verify_repeater_mode,
	  e_qcsapi_get_api_without_ifname,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_ap_interface_name,
	  e_qcsapi_set_api_without_ifname,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_ap_interface_name,
	  e_qcsapi_get_api_without_ifname,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_block_bss,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_block_bss,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_txba_disable,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_txba_disable,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_rxba_decline,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_rxba_decline,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_txburst,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_txburst,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_sec_chan,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_set_sec_chan,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_set_vap_default_state,
	  e_qcsapi_set_api_without_ifname,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_vap_default_state,
	  e_qcsapi_get_api_without_ifname,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_vap_state,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_vap_state,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_txrx_airtime,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_qwe_command,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_get_client_mac_list,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_get_core_dump_size,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_get_core_dump,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_sample_all_clients,
	  e_qcsapi_set_api_without_parameter,
	  e_qcsapi_none,
	  e_qcsapi_none
	},
	{ e_qcsapi_wifi_get_per_assoc_data,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_tx_chains,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_tx_chains,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_get_wifi_ready,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_get_cca_stats,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_get_ep_status,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_set_igmp_snooping_state,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_get_igmp_snooping_state,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_set_max_bcast_pps,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	},
	{ e_qcsapi_wifi_set_SSID_group_id,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_SSID_group_id,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_SSID_assoc_reserve,
	  e_qcsapi_set_api_without_ifname,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_SSID_assoc_reserve,
	  e_qcsapi_get_api_without_ifname,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_set_scs_leavedfs_chan_mtrc_mrgn,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_set_max_boot_cac_duration,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_remove_mac_address_ext,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_mac_addr
	},
	{ e_qcsapi_wifi_authorize_mac_address_ext,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_mac_addr
	},
	{ e_qcsapi_wifi_deny_mac_address_ext,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_mac_addr
	},
	{ e_qcsapi_set_log_level,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string,
	},
	{ e_qcsapi_get_log_level,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string,
	},
	{ e_qcsapi_set_remote_logging,
	  e_qcsapi_set_api_without_ifname,
	  e_qcsapi_none,
	  e_qcsapi_string,
	},
	{ e_qcsapi_set_console,
	  e_qcsapi_set_api_without_ifname,
	  e_qcsapi_none,
	  e_qcsapi_string,
	},
	{ e_qcsapi_get_vopt,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string,
	},
	{ e_qcsapi_set_vopt,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string,
	},
	{ e_qcsapi_get_app_core_dump,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_threshold_of_neighborhood_type,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_threshold_of_neighborhood_type,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_neighborhood_type,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_wifi_get_parameter,
	  e_qcsapi_get_api,
	  e_qcsapi_wifi_parameter,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_set_parameter,
	  e_qcsapi_set_api,
	  e_qcsapi_wifi_parameter,
	  e_qcsapi_integer
	},
	{ e_qcsapi_do_system_action,
	  e_qcsapi_set_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_is_weather_channel,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_set_br_isolate,
	  e_qcsapi_set_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{
	  e_qcsapi_wifi_get_br_isolate,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_tx_max_amsdu,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_set_tx_max_amsdu,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_show_access_points,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_nac_mon_mode,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_none
	},
	{ e_qcsapi_wifi_get_nac_mon_mode,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_nac_stats,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_ieee80211r,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_ieee80211r,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_set_11r_mobility_domain,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_11r_mobility_domain,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_11r_nas_id,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_11r_nas_id,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_11r_ft_over_ds,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_11r_ft_over_ds,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_get_device_mode,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_set_report_flood_interval,
	  e_qcsapi_set_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_get_report_flood_interval,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_btm_cap,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_set_btm_cap,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_set_rm_neigh_report,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_rm_neigh_report,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_add_11r_neighbour,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_del_11r_neighbour,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_get_11r_neighbour,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_wifi_set_11r_r1_key_holder,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_wifi_get_11r_r1_key_holder,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_get_pd_voltage_level,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{
	  e_qcsapi_reload_security_config,
	  e_qcsapi_set_api_without_parameter,
	  e_qcsapi_none,
	  e_qcsapi_none,
	},
	{ e_qcsapi_get_icac_status,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_integer
	},
	{ e_qcsapi_enable_emac_sdp,
	  e_qcsapi_set_system_value,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_set_bss_rxchan,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_mac_addr
	},
	{ e_qcsapi_set_unknown_dest_discover_intval,
	  e_qcsapi_set_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_get_unknown_dest_discover_intval,
	  e_qcsapi_get_api,
	  e_qcsapi_none,
	  e_qcsapi_unsigned_int
	},
	{ e_qcsapi_set_3addr_br_config,
	  e_qcsapi_set_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
	{ e_qcsapi_get_3addr_br_config,
	  e_qcsapi_get_system_value,
	  e_qcsapi_none,
	  e_qcsapi_string
	},
};

static const unsigned int	sizeof_entry_table = sizeof( qcsapi_entry_table ) / sizeof( qcsapi_entry_table[ 0 ] );


const struct qcsapi_entry *
entry_point_enum_to_table_entry( qcsapi_entry_point this_entry_point )
{
	int			 	 found_entry = 0;
	unsigned int		 	 iter;
	const struct qcsapi_entry	*retaddr = NULL;

	for (iter = 0; iter < sizeof_entry_table && found_entry == 0; iter++)
	{
		if (qcsapi_entry_table[ iter ].e_entry_point == this_entry_point )
		{
			found_entry = 1;
			retaddr = &qcsapi_entry_table[ iter ];
		}
	}

	return( retaddr );
}

/* returns 1 if successful; 0 if failure */

int
lookup_generic_parameter_type( qcsapi_entry_point qcsapi_selection, qcsapi_generic_parameter_type *p_generic_parameter_type )
{
	int		retval = 0;
	int		found_entry = 0;
	unsigned int	iter;

	for (iter = 0; iter < sizeof_entry_table; iter++)
	{
		if (qcsapi_entry_table[ iter ].e_entry_point == qcsapi_selection)
		{
			*p_generic_parameter_type = qcsapi_entry_table[ iter ].e_generic_param_type;
			found_entry = 1;
		}
	}

	if (found_entry)
	  retval = 1;

	return( retval );
}

