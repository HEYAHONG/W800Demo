
cmake_minimum_required(VERSION 3.10)

include(${CMAKE_CURRENT_SOURCE_DIR}/main.cmake)

if(NOT DEFINED PROJECT_NAME)
	set(PROJECT_NAME w800)
endif()

#设置编译工具链及选项
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/toolchain.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/option.cmake)

project(${PROJECT_NAME} C CXX ASM)

#设置SDK所在目录
set(SDK_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/wm_sdk_w800)

#设置链接脚本
set(CMAKE_EXE_LINKER_FLAGS " ${CMAKE_EXE_LINKER_FLAGS} \
		-T${SDK_ROOT}/ld/w800/gcc_csky.ld \
        -Wl,-ckmap=${PROJECT_NAME}.map -Wl,--gc-sections -Wl,-zmax-page-size=1024 -Wl,--whole-archive " )



#SDK头文件
list(APPEND SDK_INCLUDE_DIRS
${SDK_ROOT}/include
${SDK_ROOT}/include/app
${SDK_ROOT}/include/arch/xt804
${SDK_ROOT}/include/arch/xt804/csi_core
${SDK_ROOT}/include/arch/xt804/csi_dsp
${SDK_ROOT}/include/driver
${SDK_ROOT}/include/net
${SDK_ROOT}/include/os
${SDK_ROOT}/include/platform
${SDK_ROOT}/include/wifi
${SDK_ROOT}/include/bt

${SDK_ROOT}/platform/common/params
${SDK_ROOT}/platform/inc
${SDK_ROOT}/platform/sys

${SDK_ROOT}/src/app/libcoap/include
${SDK_ROOT}/src/app/wm_atcmd
${SDK_ROOT}/src/app/dhcpserver
${SDK_ROOT}/src/app/dnsserver
${SDK_ROOT}/src/app/web
${SDK_ROOT}/src/app/cloud
${SDK_ROOT}/src/app/cJSON
${SDK_ROOT}/src/app/rmms
${SDK_ROOT}/src/app/ntp
${SDK_ROOT}/src/app/httpclient
${SDK_ROOT}/src/app/oneshotconfig
${SDK_ROOT}/src/app/iperf
${SDK_ROOT}/src/app/mqtt
${SDK_ROOT}/src/app/ping
${SDK_ROOT}/src/app/polarssl/include
${SDK_ROOT}/src/app/mDNS/mDNSPosix
${SDK_ROOT}/src/app/mDNS/mDNSCore
${SDK_ROOT}/src/app/ota
${SDK_ROOT}/src/app/libwebsockets-2.1-stable
${SDK_ROOT}/src/app/fatfs
${SDK_ROOT}/src/app/mbedtls/include
${SDK_ROOT}/src/app/mbedtls/ports
${SDK_ROOT}/src/network/api2.0.3
${SDK_ROOT}/src/network/lwip2.0.3/include
${SDK_ROOT}/src/os/rtos/include

${SDK_ROOT}/demo
#nimble host
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/include
${SDK_ROOT}/src/bt/blehost/nimble/host/include
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/include
${SDK_ROOT}/src/bt/blehost/nimble/host/porting/w800/include
${SDK_ROOT}/src/bt/blehost/nimble/host/services/gap/include
${SDK_ROOT}/src/bt/blehost/nimble/host/services/gatt/include
${SDK_ROOT}/src/bt/blehost/nimble/host/services/bas/include
${SDK_ROOT}/src/bt/blehost/nimble/host/services/dis/include
${SDK_ROOT}/src/bt/blehost/nimble/host/store/config/include
${SDK_ROOT}/src/bt/blehost/nimble/host/store/ram/include
${SDK_ROOT}/src/bt/blehost/nimble/host/util/include
${SDK_ROOT}/src/bt/blehost/nimble/include
${SDK_ROOT}/src/bt/blehost/nimble/transport/uart/include
${SDK_ROOT}/src/bt/blehost/porting/w800/include
#br_edr bt host
${SDK_ROOT}/src/bt/host
${SDK_ROOT}/src/bt/host/main
${SDK_ROOT}/src/bt/host/include
${SDK_ROOT}/src/bt/host/stack
${SDK_ROOT}/src/bt/host/stack/include
${SDK_ROOT}/src/bt/host/gki/wm
${SDK_ROOT}/src/bt/host/gki/common
${SDK_ROOT}/src/bt/host/vnd/include
${SDK_ROOT}/src/bt/host/bta/include
${SDK_ROOT}/src/bt/host/osi/include
${SDK_ROOT}/src/bt/host/hci/include
${SDK_ROOT}/src/bt/host/btif/include
${SDK_ROOT}/src/bt/host/embdrv/sbc/encoder/include
${SDK_ROOT}/src/bt/host/embdrv/sbc/decoder/include
${SDK_ROOT}/src/bt/host/btcore/include
)


list(APPEND SDK_SRCS



#demo
${SDK_ROOT}/demo/wm_master_spi_demo.c
${SDK_ROOT}/demo/wm_wps_demo.c
${SDK_ROOT}/demo/wm_fatfs_demo.c
${SDK_ROOT}/demo/wm_socket_client_demo.c
${SDK_ROOT}/demo/wm_pwm_demo.c
${SDK_ROOT}/demo/wm_timer_demo.c
${SDK_ROOT}/demo/wm_http_demo.c
${SDK_ROOT}/demo/wm_slave_spi_demo.c
${SDK_ROOT}/demo/wm_ntp_demo.c
${SDK_ROOT}/demo/wm_i2c_demo.c
${SDK_ROOT}/demo/console/wm_demo_console_task.c
${SDK_ROOT}/demo/console/wm_demo_console_task.c
${SDK_ROOT}/demo/wm_gpio_demo.c
${SDK_ROOT}/demo/wm_rsa_demo.c
${SDK_ROOT}/demo/wm_crypt_hard_demo.c
${SDK_ROOT}/demo/wm_wps_demo.c
${SDK_ROOT}/demo/wm_socket_client_demo.c
${SDK_ROOT}/demo/wm_dsp_demo.c
${SDK_ROOT}/demo/wm_scan_demo.c
${SDK_ROOT}/demo/wm_master_spi_demo.c
${SDK_ROOT}/demo/wm_i2s_demo.c
${SDK_ROOT}/demo/wm_pwm_demo.c
${SDK_ROOT}/demo/wm_iperf_auto_demo.c
${SDK_ROOT}/demo/wm_uart_demo.c
${SDK_ROOT}/demo/wm_scan_demo.c
${SDK_ROOT}/demo/wm_sck_server_demo.c
${SDK_ROOT}/demo/wm_mcast_demo.c
${SDK_ROOT}/demo/wm_adc_demo.c
${SDK_ROOT}/demo/wm_udp_demo.c
${SDK_ROOT}/demo/wm_i2c_demo.c
${SDK_ROOT}/demo/wm_websockets_demo.c
${SDK_ROOT}/demo/wm_flash_demo.c
${SDK_ROOT}/demo/wm_apsta_demo.c
${SDK_ROOT}/demo/wm_crypt_demo.c
${SDK_ROOT}/demo/wm_sck_server_demo.c
${SDK_ROOT}/demo/wm_sdio_host_demo.c
${SDK_ROOT}/demo/wm_mqtt_demo.c
${SDK_ROOT}/demo/wm_mbedtls_demo.c
${SDK_ROOT}/demo/wm_touchsensor_demo.c
${SDK_ROOT}/demo/wm_ssl_server_demo.c
${SDK_ROOT}/demo/wm_websockets_demo.c
${SDK_ROOT}/demo/wm_rsa_demo.c
${SDK_ROOT}/demo/wm_ssl_server_demo.c
${SDK_ROOT}/demo/wm_mcast_demo.c
${SDK_ROOT}/demo/wm_pmu_demo.c
${SDK_ROOT}/demo/wm_http_demo.c
${SDK_ROOT}/demo/wm_crypt_hard_demo.c
${SDK_ROOT}/demo/wm_apsta_demo.c
${SDK_ROOT}/demo/wm_connect_net_demo.c
${SDK_ROOT}/demo/wm_fatfs_demo.c
${SDK_ROOT}/demo/wm_uart_demo.c
${SDK_ROOT}/demo/wm_softap_demo.c
${SDK_ROOT}/demo/wm_sck_client_demo.c
${SDK_ROOT}/demo/wm_dsp_demo.c
${SDK_ROOT}/demo/wm_iperf_auto_demo.c
${SDK_ROOT}/demo/wm_gpio_demo.c
${SDK_ROOT}/demo/wm_udp_demo.c
${SDK_ROOT}/demo/wm_sck_client_demo.c
${SDK_ROOT}/demo/wm_ntp_demo.c
${SDK_ROOT}/demo/wm_socket_server_demo.c
${SDK_ROOT}/demo/wm_connect_net_demo.c
${SDK_ROOT}/demo/wm_rtc_demo.c
${SDK_ROOT}/demo/wm_flash_demo.c
${SDK_ROOT}/demo/wm_slave_spi_demo.c
${SDK_ROOT}/demo/wm_timer_demo.c
${SDK_ROOT}/demo/wm_i2s_demo.c
${SDK_ROOT}/demo/wm_sdio_host_demo.c
${SDK_ROOT}/demo/wm_pmu_demo.c
${SDK_ROOT}/demo/wm_softap_demo.c
${SDK_ROOT}/demo/wm_7816_demo.c
${SDK_ROOT}/demo/wm_https_demo.c
${SDK_ROOT}/demo/wm_socket_server_demo.c
${SDK_ROOT}/demo/wm_crypt_demo.c
${SDK_ROOT}/demo/wm_mbedtls_demo.c
${SDK_ROOT}/demo/wm_touchsensor_demo.c
${SDK_ROOT}/demo/wm_https_demo.c
${SDK_ROOT}/demo/wm_7816_demo.c
${SDK_ROOT}/demo/wm_rtc_demo.c
${SDK_ROOT}/demo/wm_adc_demo.c
${SDK_ROOT}/demo/wm_mqtt_demo.c

#app

${SDK_ROOT}/src/app/ping/ping.c
${SDK_ROOT}/src/app/ping/ping.c
${SDK_ROOT}/src/app/btapp/wm_ble_uart_if.c
${SDK_ROOT}/src/app/btapp/wm_ble_server_wifi_app.c
${SDK_ROOT}/src/app/btapp/wm_ble_client_api_demo.c
${SDK_ROOT}/src/app/btapp/wm_ble_server_demo_prof.c
${SDK_ROOT}/src/app/btapp/wm_audio_sink.c
${SDK_ROOT}/src/app/btapp/wm_ble_client_api_multi_conn_demo.c
${SDK_ROOT}/src/app/btapp/wm_hfp_hsp_client.c
${SDK_ROOT}/src/app/btapp/wm_ble_server_wifi_prof.c
${SDK_ROOT}/src/app/btapp/wm_ble_client.c
${SDK_ROOT}/src/app/btapp/wm_ble_server_wifi_prof.c
${SDK_ROOT}/src/app/btapp/wm_bt_spp_server.c
${SDK_ROOT}/src/app/btapp/wm_ble_server.c
${SDK_ROOT}/src/app/btapp/wm_bt_spp_server.c
${SDK_ROOT}/src/app/btapp/wm_bt_app.c
${SDK_ROOT}/src/app/btapp/wm_bt_spp_client.c
${SDK_ROOT}/src/app/btapp/wm_bt_util.c
${SDK_ROOT}/src/app/btapp/wm_ble_uart_if.c
${SDK_ROOT}/src/app/btapp/wm_ble_server_api_demo.c
${SDK_ROOT}/src/app/btapp/wm_ble_server_wifi_app.c
${SDK_ROOT}/src/app/btapp/wm_audio_sink.c
${SDK_ROOT}/src/app/btapp/wm_ble_server_api_demo.c
${SDK_ROOT}/src/app/btapp/wm_ble_client_demo.c
${SDK_ROOT}/src/app/btapp/wm_ble_server.c
${SDK_ROOT}/src/app/btapp/wm_bt_util.c
${SDK_ROOT}/src/app/btapp/wm_bt_spp_client.c
${SDK_ROOT}/src/app/btapp/wm_ble_client_demo.c
${SDK_ROOT}/src/app/btapp/wm_bt_app.c
${SDK_ROOT}/src/app/btapp/wm_hfp_hsp_client.c
${SDK_ROOT}/src/app/btapp/wm_ble_client_api_demo.c
${SDK_ROOT}/src/app/btapp/wm_ble_client.c
${SDK_ROOT}/src/app/btapp/wm_ble_gap.c
${SDK_ROOT}/src/app/btapp/wm_ble_server_demo_prof.c
${SDK_ROOT}/src/app/btapp/wm_ble_client_api_multi_conn_demo.c
${SDK_ROOT}/src/app/btapp/wm_ble_gap.c
${SDK_ROOT}/src/app/polarssl/library/polarssl_debug.c
${SDK_ROOT}/src/app/polarssl/library/cipher.c
${SDK_ROOT}/src/app/polarssl/library/arc4.c
${SDK_ROOT}/src/app/polarssl/library/polarssl_bignum.c
${SDK_ROOT}/src/app/polarssl/library/error.c
${SDK_ROOT}/src/app/polarssl/library/pem.c
${SDK_ROOT}/src/app/polarssl/library/md_wrap.c
${SDK_ROOT}/src/app/polarssl/library/rsa.c
${SDK_ROOT}/src/app/polarssl/library/md.c
${SDK_ROOT}/src/app/polarssl/library/polarssl_sha1.c
${SDK_ROOT}/src/app/polarssl/library/ssl_tls.c
${SDK_ROOT}/src/app/polarssl/library/md.c
${SDK_ROOT}/src/app/polarssl/library/polarssl_md5.c
${SDK_ROOT}/src/app/polarssl/library/x509parse.c
${SDK_ROOT}/src/app/polarssl/library/polarssl_bignum.c
${SDK_ROOT}/src/app/polarssl/library/polarssl_debug.c
${SDK_ROOT}/src/app/polarssl/library/polarssl_md5.c
${SDK_ROOT}/src/app/polarssl/library/ssl_cli.c
${SDK_ROOT}/src/app/polarssl/library/rsa.c
${SDK_ROOT}/src/app/polarssl/library/base64.c
${SDK_ROOT}/src/app/polarssl/library/error.c
${SDK_ROOT}/src/app/polarssl/library/cipher.c
${SDK_ROOT}/src/app/polarssl/library/pem.c
${SDK_ROOT}/src/app/polarssl/library/md_wrap.c
${SDK_ROOT}/src/app/polarssl/library/asn1parse.c
${SDK_ROOT}/src/app/polarssl/library/ssl_cli.c
${SDK_ROOT}/src/app/polarssl/library/ssl_tls.c
${SDK_ROOT}/src/app/polarssl/library/polarssl_sha1.c
${SDK_ROOT}/src/app/polarssl/library/x509parse.c
${SDK_ROOT}/src/app/polarssl/library/cipher_wrap.c
${SDK_ROOT}/src/app/polarssl/library/arc4.c
${SDK_ROOT}/src/app/polarssl/library/cipher_wrap.c
${SDK_ROOT}/src/app/polarssl/library/base64.c
${SDK_ROOT}/src/app/polarssl/library/asn1parse.c
${SDK_ROOT}/src/app/httpclient/HTTPClientString.c
${SDK_ROOT}/src/app/httpclient/HTTPClientAuth.c
${SDK_ROOT}/src/app/httpclient/HTTPClient.c
${SDK_ROOT}/src/app/httpclient/HTTPClientString.c
${SDK_ROOT}/src/app/httpclient/HTTPClientWrapper.c
${SDK_ROOT}/src/app/httpclient/HTTPClientWrapper.c
${SDK_ROOT}/src/app/httpclient/HTTPClientAuth.c
${SDK_ROOT}/src/app/httpclient/wm_httpclient_task.c
${SDK_ROOT}/src/app/httpclient/wm_httpclient_task.c
${SDK_ROOT}/src/app/httpclient/HTTPClient.c
${SDK_ROOT}/src/app/ota/wm_http_fwup.c
${SDK_ROOT}/src/app/ota/wm_http_fwup.c
${SDK_ROOT}/src/app/ota/wm_socket_fwup.c
${SDK_ROOT}/src/app/ota/wm_socket_fwup.c
${SDK_ROOT}/src/app/dnsserver/dns_server.c
${SDK_ROOT}/src/app/dnsserver/dns_server.c
${SDK_ROOT}/src/app/wm_atcmd/wm_uart_task.c
${SDK_ROOT}/src/app/wm_atcmd/wm_cmdp.c
${SDK_ROOT}/src/app/wm_atcmd/wm_uart_task.c
${SDK_ROOT}/src/app/wm_atcmd/wm_cmdp_hostif.c
${SDK_ROOT}/src/app/wm_atcmd/wm_hspi_task.c
${SDK_ROOT}/src/app/wm_atcmd/wm_rmms.c
${SDK_ROOT}/src/app/wm_atcmd/wm_cmdp_hostif.c
${SDK_ROOT}/src/app/wm_atcmd/wm_cmdp_ri.c
${SDK_ROOT}/src/app/wm_atcmd/wm_cmdp_ri.c
${SDK_ROOT}/src/app/wm_atcmd/wm_rmms.c
${SDK_ROOT}/src/app/wm_atcmd/wm_hspi_task.c
${SDK_ROOT}/src/app/wm_atcmd/wm_cmdp.c
${SDK_ROOT}/src/app/web/httpd.c
${SDK_ROOT}/src/app/web/web.c
${SDK_ROOT}/src/app/web/web.c
${SDK_ROOT}/src/app/web/httpd.c
${SDK_ROOT}/src/app/web/fs.c
${SDK_ROOT}/src/app/web/fs.c
${SDK_ROOT}/src/app/bleapp/wm_bt_storage.c
${SDK_ROOT}/src/app/bleapp/wm_ble_uart_if.c
${SDK_ROOT}/src/app/bleapp/wm_ble_client_peer_manager.c
${SDK_ROOT}/src/app/bleapp/wm_ble_server_wifi_app.c
${SDK_ROOT}/src/app/bleapp/wm_ble_client_api_demo.c
${SDK_ROOT}/src/app/bleapp/wm_ble_client_api_multi_conn_demo.c
${SDK_ROOT}/src/app/bleapp/wm_ble_server_wifi_prof.c
${SDK_ROOT}/src/app/bleapp/wm_ble_server_wifi_prof.c
${SDK_ROOT}/src/app/bleapp/wm_bt_app.c
${SDK_ROOT}/src/app/bleapp/wm_bt_util.c
${SDK_ROOT}/src/app/bleapp/wm_ble_client_util.c
${SDK_ROOT}/src/app/bleapp/wm_ble_uart_if.c
${SDK_ROOT}/src/app/bleapp/wm_ble_server_api_demo.c
${SDK_ROOT}/src/app/bleapp/wm_ble_server_wifi_app.c
${SDK_ROOT}/src/app/bleapp/wm_ble_client_util.c
${SDK_ROOT}/src/app/bleapp/wm_ble_server_api_demo.c
${SDK_ROOT}/src/app/bleapp/wm_bt_util.c
${SDK_ROOT}/src/app/bleapp/wm_bt_storage.c
${SDK_ROOT}/src/app/bleapp/wm_bt_app.c
${SDK_ROOT}/src/app/bleapp/wm_ble_client_api_demo.c
${SDK_ROOT}/src/app/bleapp/wm_ble_gap.c
${SDK_ROOT}/src/app/bleapp/wm_ble_client_api_multi_conn_demo.c
${SDK_ROOT}/src/app/bleapp/wm_ble_client_peer_manager.c
${SDK_ROOT}/src/app/bleapp/wm_ble_gap.c
${SDK_ROOT}/src/app/libcoap/str.c
${SDK_ROOT}/src/app/libcoap/str.c
${SDK_ROOT}/src/app/mqtt/libemqtt.c
${SDK_ROOT}/src/app/mqtt/libemqtt.c
${SDK_ROOT}/src/app/ntp/ntp_client.c
${SDK_ROOT}/src/app/ntp/ntp_client.c
${SDK_ROOT}/src/app/mbedtls/ports/timing_alt.c
${SDK_ROOT}/src/app/mbedtls/ports/net_alt.c
${SDK_ROOT}/src/app/mbedtls/ports/md5_alt.c
${SDK_ROOT}/src/app/mbedtls/ports/hardware_alt.c
${SDK_ROOT}/src/app/mbedtls/ports/des_alt.c
${SDK_ROOT}/src/app/mbedtls/ports/des_alt.c
${SDK_ROOT}/src/app/mbedtls/ports/md5_alt.c
${SDK_ROOT}/src/app/mbedtls/ports/timing_alt.c
${SDK_ROOT}/src/app/mbedtls/ports/hardware_alt.c
${SDK_ROOT}/src/app/mbedtls/ports/sha1_alt.c
${SDK_ROOT}/src/app/mbedtls/ports/sha1_alt.c
${SDK_ROOT}/src/app/mbedtls/ports/arc4_alt.c
${SDK_ROOT}/src/app/mbedtls/ports/net_alt.c
${SDK_ROOT}/src/app/mbedtls/ports/aes_alt.c
${SDK_ROOT}/src/app/mbedtls/ports/arc4_alt.c
${SDK_ROOT}/src/app/mbedtls/ports/aes_alt.c
${SDK_ROOT}/src/app/mbedtls/library/debug.c
${SDK_ROOT}/src/app/mbedtls/library/pkcs5.c
${SDK_ROOT}/src/app/mbedtls/library/x509.c
${SDK_ROOT}/src/app/mbedtls/library/memory_buffer_alloc.c
${SDK_ROOT}/src/app/mbedtls/library/ssl_srv.c
${SDK_ROOT}/src/app/mbedtls/library/asn1write.c
${SDK_ROOT}/src/app/mbedtls/library/platform.c
${SDK_ROOT}/src/app/mbedtls/library/ecdsa.c
${SDK_ROOT}/src/app/mbedtls/library/ripemd160.c
${SDK_ROOT}/src/app/mbedtls/library/blowfish.c
${SDK_ROOT}/src/app/mbedtls/library/sha512.c
${SDK_ROOT}/src/app/mbedtls/library/ssl_cookie.c
${SDK_ROOT}/src/app/mbedtls/library/ssl_ciphersuites.c
${SDK_ROOT}/src/app/mbedtls/library/xtea.c
${SDK_ROOT}/src/app/mbedtls/library/padlock.c
${SDK_ROOT}/src/app/mbedtls/library/x509_create.c
${SDK_ROOT}/src/app/mbedtls/library/x509_csr.c
${SDK_ROOT}/src/app/mbedtls/library/rsa_internal.c
${SDK_ROOT}/src/app/mbedtls/library/x509_crt.c
${SDK_ROOT}/src/app/mbedtls/library/pkwrite.c
${SDK_ROOT}/src/app/mbedtls/library/ssl_cookie.c
${SDK_ROOT}/src/app/mbedtls/library/camellia.c
${SDK_ROOT}/src/app/mbedtls/library/ssl_ticket.c
${SDK_ROOT}/src/app/mbedtls/library/cipher.c
${SDK_ROOT}/src/app/mbedtls/library/arc4.c
${SDK_ROOT}/src/app/mbedtls/library/certs.c
${SDK_ROOT}/src/app/mbedtls/library/sha512.c
${SDK_ROOT}/src/app/mbedtls/library/error.c
${SDK_ROOT}/src/app/mbedtls/library/pem.c
${SDK_ROOT}/src/app/mbedtls/library/x509_crl.c
${SDK_ROOT}/src/app/mbedtls/library/blowfish.c
${SDK_ROOT}/src/app/mbedtls/library/entropy_poll.c
${SDK_ROOT}/src/app/mbedtls/library/ssl_cache.c
${SDK_ROOT}/src/app/mbedtls/library/cmac.c
${SDK_ROOT}/src/app/mbedtls/library/ecp.c
${SDK_ROOT}/src/app/mbedtls/library/ecdh.c
${SDK_ROOT}/src/app/mbedtls/library/md_wrap.c
${SDK_ROOT}/src/app/mbedtls/library/ccm.c
${SDK_ROOT}/src/app/mbedtls/library/ripemd160.c
${SDK_ROOT}/src/app/mbedtls/library/version.c
${SDK_ROOT}/src/app/mbedtls/library/bignum.c
${SDK_ROOT}/src/app/mbedtls/library/rsa.c
${SDK_ROOT}/src/app/mbedtls/library/threading.c
${SDK_ROOT}/src/app/mbedtls/library/x509.c
${SDK_ROOT}/src/app/mbedtls/library/platform.c
${SDK_ROOT}/src/app/mbedtls/library/des.c
${SDK_ROOT}/src/app/mbedtls/library/ecdh.c
${SDK_ROOT}/src/app/mbedtls/library/pk.c
${SDK_ROOT}/src/app/mbedtls/library/xtea.c
${SDK_ROOT}/src/app/mbedtls/library/ecjpake.c
${SDK_ROOT}/src/app/mbedtls/library/pk.c
${SDK_ROOT}/src/app/mbedtls/library/padlock.c
${SDK_ROOT}/src/app/mbedtls/library/hmac_drbg.c
${SDK_ROOT}/src/app/mbedtls/library/md.c
${SDK_ROOT}/src/app/mbedtls/library/version_features.c
${SDK_ROOT}/src/app/mbedtls/library/des.c
${SDK_ROOT}/src/app/mbedtls/library/x509write_crt.c
${SDK_ROOT}/src/app/mbedtls/library/entropy_poll.c
${SDK_ROOT}/src/app/mbedtls/library/ssl_tls.c
${SDK_ROOT}/src/app/mbedtls/library/x509_crt.c
${SDK_ROOT}/src/app/mbedtls/library/ecp_curves.c
${SDK_ROOT}/src/app/mbedtls/library/md.c
${SDK_ROOT}/src/app/mbedtls/library/x509write_csr.c
${SDK_ROOT}/src/app/mbedtls/library/md5.c
${SDK_ROOT}/src/app/mbedtls/library/net_sockets.c
${SDK_ROOT}/src/app/mbedtls/library/oid.c
${SDK_ROOT}/src/app/mbedtls/library/sha256.c
${SDK_ROOT}/src/app/mbedtls/library/md5.c
${SDK_ROOT}/src/app/mbedtls/library/ssl_cli.c
${SDK_ROOT}/src/app/mbedtls/library/dhm.c
${SDK_ROOT}/src/app/mbedtls/library/rsa.c
${SDK_ROOT}/src/app/mbedtls/library/version.c
${SDK_ROOT}/src/app/mbedtls/library/base64.c
${SDK_ROOT}/src/app/mbedtls/library/version_features.c
${SDK_ROOT}/src/app/mbedtls/library/error.c
${SDK_ROOT}/src/app/mbedtls/library/ecp_curves.c
${SDK_ROOT}/src/app/mbedtls/library/pkcs5.c
${SDK_ROOT}/src/app/mbedtls/library/havege.c
${SDK_ROOT}/src/app/mbedtls/library/cipher.c
${SDK_ROOT}/src/app/mbedtls/library/asn1write.c
${SDK_ROOT}/src/app/mbedtls/library/havege.c
${SDK_ROOT}/src/app/mbedtls/library/rsa_internal.c
${SDK_ROOT}/src/app/mbedtls/library/pem.c
${SDK_ROOT}/src/app/mbedtls/library/ctr_drbg.c
${SDK_ROOT}/src/app/mbedtls/library/sha1.c
${SDK_ROOT}/src/app/mbedtls/library/bignum.c
${SDK_ROOT}/src/app/mbedtls/library/gcm.c
${SDK_ROOT}/src/app/mbedtls/library/md_wrap.c
${SDK_ROOT}/src/app/mbedtls/library/pkcs12.c
${SDK_ROOT}/src/app/mbedtls/library/aesni.c
${SDK_ROOT}/src/app/mbedtls/library/ccm.c
${SDK_ROOT}/src/app/mbedtls/library/oid.c
${SDK_ROOT}/src/app/mbedtls/library/pkparse.c
${SDK_ROOT}/src/app/mbedtls/library/ecjpake.c
${SDK_ROOT}/src/app/mbedtls/library/asn1parse.c
${SDK_ROOT}/src/app/mbedtls/library/camellia.c
${SDK_ROOT}/src/app/mbedtls/library/sha1.c
${SDK_ROOT}/src/app/mbedtls/library/gcm.c
${SDK_ROOT}/src/app/mbedtls/library/ssl_cli.c
${SDK_ROOT}/src/app/mbedtls/library/ssl_ticket.c
${SDK_ROOT}/src/app/mbedtls/library/certs.c
${SDK_ROOT}/src/app/mbedtls/library/md4.c
${SDK_ROOT}/src/app/mbedtls/library/ssl_tls.c
${SDK_ROOT}/src/app/mbedtls/library/entropy.c
${SDK_ROOT}/src/app/mbedtls/library/aes.c
${SDK_ROOT}/src/app/mbedtls/library/hmac_drbg.c
${SDK_ROOT}/src/app/mbedtls/library/aesni.c
${SDK_ROOT}/src/app/mbedtls/library/x509_crl.c
${SDK_ROOT}/src/app/mbedtls/library/pk_wrap.c
${SDK_ROOT}/src/app/mbedtls/library/x509write_csr.c
${SDK_ROOT}/src/app/mbedtls/library/ssl_cache.c
${SDK_ROOT}/src/app/mbedtls/library/dhm.c
${SDK_ROOT}/src/app/mbedtls/library/cmac.c
${SDK_ROOT}/src/app/mbedtls/library/cipher_wrap.c
${SDK_ROOT}/src/app/mbedtls/library/pkparse.c
${SDK_ROOT}/src/app/mbedtls/library/x509_create.c
${SDK_ROOT}/src/app/mbedtls/library/pk_wrap.c
${SDK_ROOT}/src/app/mbedtls/library/arc4.c
${SDK_ROOT}/src/app/mbedtls/library/cipher_wrap.c
${SDK_ROOT}/src/app/mbedtls/library/pkcs12.c
${SDK_ROOT}/src/app/mbedtls/library/memory_buffer_alloc.c
${SDK_ROOT}/src/app/mbedtls/library/net_sockets.c
${SDK_ROOT}/src/app/mbedtls/library/pkcs11.c
${SDK_ROOT}/src/app/mbedtls/library/ecdsa.c
${SDK_ROOT}/src/app/mbedtls/library/ctr_drbg.c
${SDK_ROOT}/src/app/mbedtls/library/md4.c
${SDK_ROOT}/src/app/mbedtls/library/timing.c
${SDK_ROOT}/src/app/mbedtls/library/md2.c
${SDK_ROOT}/src/app/mbedtls/library/debug.c
${SDK_ROOT}/src/app/mbedtls/library/base64.c
${SDK_ROOT}/src/app/mbedtls/library/ssl_srv.c
${SDK_ROOT}/src/app/mbedtls/library/pkwrite.c
${SDK_ROOT}/src/app/mbedtls/library/sha256.c
${SDK_ROOT}/src/app/mbedtls/library/ecp.c
${SDK_ROOT}/src/app/mbedtls/library/md2.c
${SDK_ROOT}/src/app/mbedtls/library/threading.c
${SDK_ROOT}/src/app/mbedtls/library/pkcs11.c
${SDK_ROOT}/src/app/mbedtls/library/aes.c
${SDK_ROOT}/src/app/mbedtls/library/x509_csr.c
${SDK_ROOT}/src/app/mbedtls/library/timing.c
${SDK_ROOT}/src/app/mbedtls/library/x509write_crt.c
${SDK_ROOT}/src/app/mbedtls/library/ssl_ciphersuites.c
${SDK_ROOT}/src/app/mbedtls/library/entropy.c
${SDK_ROOT}/src/app/mbedtls/library/asn1parse.c
${SDK_ROOT}/src/app/oneshotconfig/wm_oneshot_lsd.c
${SDK_ROOT}/src/app/oneshotconfig/wm_wifi_oneshot.c
${SDK_ROOT}/src/app/oneshotconfig/wm_wifi_oneshot.c
${SDK_ROOT}/src/app/oneshotconfig/wm_oneshot_lsd.c
${SDK_ROOT}/src/app/oneshotconfig/wm_oneshot_airkiss.c
${SDK_ROOT}/src/app/oneshotconfig/wm_oneshot_airkiss.c
${SDK_ROOT}/src/app/mDNS/mDNSPosix/mDNSPosix.c
${SDK_ROOT}/src/app/mDNS/mDNSPosix/mDNSPosix.c
${SDK_ROOT}/src/app/mDNS/mDNSCore/mDNS.c
${SDK_ROOT}/src/app/mDNS/mDNSCore/mDNS.c
${SDK_ROOT}/src/app/dhcpserver/dhcp_server.c
${SDK_ROOT}/src/app/dhcpserver/dhcp_server.c
${SDK_ROOT}/src/app/fatfs/diskio.c
${SDK_ROOT}/src/app/fatfs/ffsystem.c
${SDK_ROOT}/src/app/fatfs/ff.c
${SDK_ROOT}/src/app/fatfs/diskio.c
${SDK_ROOT}/src/app/fatfs/ffsystem.c
${SDK_ROOT}/src/app/fatfs/ffunicode.c
${SDK_ROOT}/src/app/fatfs/ff.c
${SDK_ROOT}/src/app/fatfs/ffunicode.c
${SDK_ROOT}/src/app/sslserver/wm_ssl_server.c
${SDK_ROOT}/src/app/sslserver/wm_ssl_server.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/output.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/lws-plat-wm.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/output.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/header.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/client-parser.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/ssl-client.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/base64-decode.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/context.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/libwebsockets.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/context.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/ssl.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/service.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/client.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/ssl.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/base64-decode.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/client.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/handshake.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/pollfd.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/parsers.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/pollfd.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/client-parser.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/handshake.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/service.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/client-handshake.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/parsers.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/client-handshake.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/ssl-client.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/libwebsockets.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/header.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/lws-plat-wm.c
${SDK_ROOT}/src/app/cJSON/cJSON.c
${SDK_ROOT}/src/app/cJSON/cJSON.c
${SDK_ROOT}/src/app/iperf/iperf_udp.c
${SDK_ROOT}/src/app/iperf/iperf_timer.c
${SDK_ROOT}/src/app/iperf/iperf_locale.c
${SDK_ROOT}/src/app/iperf/iperf_error.c
${SDK_ROOT}/src/app/iperf/iperf_main.c
${SDK_ROOT}/src/app/iperf/iperf_udp.c
${SDK_ROOT}/src/app/iperf/iperf_units.c
${SDK_ROOT}/src/app/iperf/iperf_locale.c
${SDK_ROOT}/src/app/iperf/iperf_net.c
${SDK_ROOT}/src/app/iperf/iperf_client_api.c
${SDK_ROOT}/src/app/iperf/tcp_info.c
${SDK_ROOT}/src/app/iperf/iperf_api.c
${SDK_ROOT}/src/app/iperf/iperf_error.c
${SDK_ROOT}/src/app/iperf/iperf_api.c
${SDK_ROOT}/src/app/iperf/iperf_tcp.c
${SDK_ROOT}/src/app/iperf/iperf_main.c
${SDK_ROOT}/src/app/iperf/iperf_util.c
${SDK_ROOT}/src/app/iperf/tcp_window_size.c
${SDK_ROOT}/src/app/iperf/iperf_server_api.c
${SDK_ROOT}/src/app/iperf/wm_perf.c
${SDK_ROOT}/src/app/iperf/wm_perf.c
${SDK_ROOT}/src/app/iperf/iperf_client_api.c
${SDK_ROOT}/src/app/iperf/iperf_units.c
${SDK_ROOT}/src/app/iperf/iperf_server_api.c
${SDK_ROOT}/src/app/iperf/tcp_info.c
${SDK_ROOT}/src/app/iperf/iperf_timer.c
${SDK_ROOT}/src/app/iperf/iperf_net.c
${SDK_ROOT}/src/app/iperf/tcp_window_size.c
${SDK_ROOT}/src/app/iperf/iperf_tcp.c
${SDK_ROOT}/src/app/iperf/iperf_util.c

#common
${SDK_ROOT}/platform/common/crypto/wm_crypto_hard_mbed.c
${SDK_ROOT}/platform/common/crypto/wm_crypto_hard_mbed.c
${SDK_ROOT}/platform/common/crypto/wm_crypto_hard.c
${SDK_ROOT}/platform/common/crypto/wm_crypto_hard.c
${SDK_ROOT}/platform/common/params/wm_param.c
${SDK_ROOT}/platform/common/params/wm_param.c
${SDK_ROOT}/platform/common/utils/utils.c
${SDK_ROOT}/platform/common/utils/utils.c
${SDK_ROOT}/platform/common/mem/wm_mem.c
${SDK_ROOT}/platform/common/mem/wm_mem.c
${SDK_ROOT}/platform/common/task/wm_wl_mbox.c
${SDK_ROOT}/platform/common/task/wm_wl_mbox.c
${SDK_ROOT}/platform/common/task/wm_wl_timers.c
${SDK_ROOT}/platform/common/task/wm_wl_timers.c
${SDK_ROOT}/platform/common/task/wm_wl_task.c
${SDK_ROOT}/platform/common/task/wm_wl_task.c
${SDK_ROOT}/platform/common/fwup/wm_fwup.c
${SDK_ROOT}/platform/common/fwup/wm_fwup.c

#drivers
${SDK_ROOT}/platform/drivers/io/wm_io.c
${SDK_ROOT}/platform/drivers/io/wm_io.c
${SDK_ROOT}/platform/drivers/7816/wm_7816.c
${SDK_ROOT}/platform/drivers/7816/wm_7816.c
${SDK_ROOT}/platform/drivers/flash/wm_fls.c
${SDK_ROOT}/platform/drivers/flash/wm_fls_gd25qxx.c
${SDK_ROOT}/platform/drivers/flash/wm_fls.c
${SDK_ROOT}/platform/drivers/flash/wm_fls_gd25qxx.c
${SDK_ROOT}/platform/drivers/dma/wm_dma.c
${SDK_ROOT}/platform/drivers/dma/wm_dma.c
${SDK_ROOT}/platform/drivers/sasc/wm_sasc.c
${SDK_ROOT}/platform/drivers/sasc/wm_sasc.c
${SDK_ROOT}/platform/drivers/lcd/wm_lcd.c
${SDK_ROOT}/platform/drivers/lcd/wm_lcd.c
${SDK_ROOT}/platform/drivers/uart/wm_uart.c
${SDK_ROOT}/platform/drivers/uart/wm_uart.c
${SDK_ROOT}/platform/drivers/i2c/wm_i2c.c
${SDK_ROOT}/platform/drivers/i2c/wm_i2c.c
${SDK_ROOT}/platform/drivers/pwm/wm_pwm.c
${SDK_ROOT}/platform/drivers/pwm/wm_pwm.c
${SDK_ROOT}/platform/drivers/i2s/wm_i2s.c
${SDK_ROOT}/platform/drivers/i2s/wm_i2s.c
${SDK_ROOT}/platform/drivers/hspi/wm_hspi.c
${SDK_ROOT}/platform/drivers/hspi/wm_hspi.c
${SDK_ROOT}/platform/drivers/rtc/wm_rtc.c
${SDK_ROOT}/platform/drivers/rtc/wm_rtc.c
${SDK_ROOT}/platform/drivers/sdio_host/wm_sdio_host.c
${SDK_ROOT}/platform/drivers/sdio_host/wm_sdio_host.c
${SDK_ROOT}/platform/drivers/internalflash/wm_internal_fls.c
${SDK_ROOT}/platform/drivers/internalflash/wm_internal_fls.c
${SDK_ROOT}/platform/drivers/touchsensor/wm_touchsensor.c
${SDK_ROOT}/platform/drivers/touchsensor/wm_touchsensor.c
${SDK_ROOT}/platform/drivers/irq/wm_irq.c
${SDK_ROOT}/platform/drivers/irq/wm_irq.c
${SDK_ROOT}/platform/drivers/psram/wm_psram.c
${SDK_ROOT}/platform/drivers/psram/wm_psram.c
${SDK_ROOT}/platform/drivers/efuse/wm_efuse.c
${SDK_ROOT}/platform/drivers/efuse/wm_efuse.c
${SDK_ROOT}/platform/drivers/adc/wm_adc.c
${SDK_ROOT}/platform/drivers/adc/wm_adc.c
${SDK_ROOT}/platform/drivers/pmu/wm_pmu.c
${SDK_ROOT}/platform/drivers/pmu/wm_pmu.c
${SDK_ROOT}/platform/drivers/cpu/wm_cpu.c
${SDK_ROOT}/platform/drivers/cpu/wm_cpu.c
${SDK_ROOT}/platform/drivers/spi/wm_hostspi.c
${SDK_ROOT}/platform/drivers/spi/wm_hostspi.c
${SDK_ROOT}/platform/drivers/watchdog/wm_watchdog.c
${SDK_ROOT}/platform/drivers/watchdog/wm_watchdog.c
${SDK_ROOT}/platform/drivers/timer/wm_timer.c
${SDK_ROOT}/platform/drivers/timer/wm_timer.c
${SDK_ROOT}/platform/drivers/gpio/wm_gpio_afsel.c
${SDK_ROOT}/platform/drivers/gpio/wm_gpio.c
${SDK_ROOT}/platform/drivers/gpio/wm_gpio.c
${SDK_ROOT}/platform/drivers/gpio/wm_gpio_afsel.c

#network
${SDK_ROOT}/src/network/api2.0.3/tls_sockets.c
${SDK_ROOT}/src/network/api2.0.3/tls_netconn.c
${SDK_ROOT}/src/network/api2.0.3/tls_netconn.c
${SDK_ROOT}/src/network/api2.0.3/tls_sockets.c
${SDK_ROOT}/src/network/lwip2.0.3/core/pbuf.c
${SDK_ROOT}/src/network/lwip2.0.3/core/stats.c
${SDK_ROOT}/src/network/lwip2.0.3/core/udp.c
${SDK_ROOT}/src/network/lwip2.0.3/core/tcp.c
${SDK_ROOT}/src/network/lwip2.0.3/core/sys.c
${SDK_ROOT}/src/network/lwip2.0.3/core/memp.c
${SDK_ROOT}/src/network/lwip2.0.3/core/tcp_in.c
${SDK_ROOT}/src/network/lwip2.0.3/core/netif.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ip.c
${SDK_ROOT}/src/network/lwip2.0.3/core/alg.c
${SDK_ROOT}/src/network/lwip2.0.3/core/def.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv4/dhcp.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv4/igmp.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv4/dhcp.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv4/icmp.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv4/etharp.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv4/etharp.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv4/ip4.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv4/ip4_frag.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv4/igmp.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv4/autoip.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv4/ip4.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv4/ip4_frag.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv4/ip4_addr.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv4/ip4_addr.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv4/autoip.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv4/icmp.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv6/ethip6.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv6/nd6.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv6/dhcp6.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv6/ethip6.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv6/mld6.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv6/mld6.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv6/icmp6.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv6/nd6.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv6/ip6_frag.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv6/inet6.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv6/ip6.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv6/ip6_addr.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv6/inet6.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv6/ip6.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv6/dhcp6.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv6/icmp6.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv6/ip6_addr.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ipv6/ip6_frag.c
${SDK_ROOT}/src/network/lwip2.0.3/core/netif.c
${SDK_ROOT}/src/network/lwip2.0.3/core/mem.c
${SDK_ROOT}/src/network/lwip2.0.3/core/init.c
${SDK_ROOT}/src/network/lwip2.0.3/core/mem.c
${SDK_ROOT}/src/network/lwip2.0.3/core/tcp_out.c
${SDK_ROOT}/src/network/lwip2.0.3/core/tcp_out.c
${SDK_ROOT}/src/network/lwip2.0.3/core/pbuf.c
${SDK_ROOT}/src/network/lwip2.0.3/core/memp.c
${SDK_ROOT}/src/network/lwip2.0.3/core/sys.c
${SDK_ROOT}/src/network/lwip2.0.3/core/tcp_in.c
${SDK_ROOT}/src/network/lwip2.0.3/core/alg.c
${SDK_ROOT}/src/network/lwip2.0.3/core/raw.c
${SDK_ROOT}/src/network/lwip2.0.3/core/timeouts.c
${SDK_ROOT}/src/network/lwip2.0.3/core/inet_chksum.c
${SDK_ROOT}/src/network/lwip2.0.3/core/raw.c
${SDK_ROOT}/src/network/lwip2.0.3/core/udp.c
${SDK_ROOT}/src/network/lwip2.0.3/core/inet_chksum.c
${SDK_ROOT}/src/network/lwip2.0.3/core/dns.c
${SDK_ROOT}/src/network/lwip2.0.3/core/init.c
${SDK_ROOT}/src/network/lwip2.0.3/core/tcp.c
${SDK_ROOT}/src/network/lwip2.0.3/core/def.c
${SDK_ROOT}/src/network/lwip2.0.3/core/ip.c
${SDK_ROOT}/src/network/lwip2.0.3/core/stats.c
${SDK_ROOT}/src/network/lwip2.0.3/core/timeouts.c
${SDK_ROOT}/src/network/lwip2.0.3/core/dns.c
${SDK_ROOT}/src/network/lwip2.0.3/netif/lowpan6.c
${SDK_ROOT}/src/network/lwip2.0.3/netif/lowpan6.c
${SDK_ROOT}/src/network/lwip2.0.3/netif/ethernetif.c
${SDK_ROOT}/src/network/lwip2.0.3/netif/ethernet.c
${SDK_ROOT}/src/network/lwip2.0.3/netif/ethernetif.c
${SDK_ROOT}/src/network/lwip2.0.3/netif/ethernet.c
${SDK_ROOT}/src/network/lwip2.0.3/netif/wm_ethernet.c
${SDK_ROOT}/src/network/lwip2.0.3/netif/wm_ethernet.c
${SDK_ROOT}/src/network/lwip2.0.3/netif/slipif.c
${SDK_ROOT}/src/network/lwip2.0.3/netif/slipif.c
${SDK_ROOT}/src/network/lwip2.0.3/sys_arch.c
${SDK_ROOT}/src/network/lwip2.0.3/sys_arch.c
${SDK_ROOT}/src/network/lwip2.0.3/api/err.c
${SDK_ROOT}/src/network/lwip2.0.3/api/netbuf.c
${SDK_ROOT}/src/network/lwip2.0.3/api/api_lib.c
${SDK_ROOT}/src/network/lwip2.0.3/api/api_msg.c
${SDK_ROOT}/src/network/lwip2.0.3/api/netdb.c
${SDK_ROOT}/src/network/lwip2.0.3/api/sockets.c
${SDK_ROOT}/src/network/lwip2.0.3/api/netdb.c
${SDK_ROOT}/src/network/lwip2.0.3/api/api_msg.c
${SDK_ROOT}/src/network/lwip2.0.3/api/tcpip.c
${SDK_ROOT}/src/network/lwip2.0.3/api/netifapi.c
${SDK_ROOT}/src/network/lwip2.0.3/api/api_lib.c
${SDK_ROOT}/src/network/lwip2.0.3/api/netbuf.c
${SDK_ROOT}/src/network/lwip2.0.3/api/netifapi.c
${SDK_ROOT}/src/network/lwip2.0.3/api/tcpip.c
${SDK_ROOT}/src/network/lwip2.0.3/api/err.c
${SDK_ROOT}/src/network/lwip2.0.3/api/sockets.c

#sys
${SDK_ROOT}/platform/sys/wm_main.c
${SDK_ROOT}/platform/sys/tls_sys.c

#blehost
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/hmac_prng.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/bleutils.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/ctr_prng.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/cbc_mode.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/cmac_mode.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/ecc_dh.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/ecc_dh.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/ecc_platform_specific.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/ccm_mode.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/aes_encrypt.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/ctr_prng.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/ccm_mode.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/ctr_mode.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/ecc_dsa.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/hmac.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/aes_decrypt.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/aes_decrypt.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/cbc_mode.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/sha256.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/ctr_mode.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/ecc_dsa.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/cmac_mode.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/hmac_prng.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/aes_encrypt.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/ecc_platform_specific.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/ecc.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/bleutils.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/ecc.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/hmac.c
${SDK_ROOT}/src/bt/blehost/ext/tinycrypt/src/sha256.c
${SDK_ROOT}/src/bt/blehost/porting/w800/src/endian.c
${SDK_ROOT}/src/bt/blehost/porting/w800/src/npl_os_freertos.c
${SDK_ROOT}/src/bt/blehost/porting/w800/src/nimble_port_freertos.c
${SDK_ROOT}/src/bt/blehost/porting/w800/src/os_mempool.c
${SDK_ROOT}/src/bt/blehost/porting/w800/src/os_mbuf.c
${SDK_ROOT}/src/bt/blehost/porting/w800/src/mem.c
${SDK_ROOT}/src/bt/blehost/porting/w800/src/nimble_port.c
${SDK_ROOT}/src/bt/blehost/porting/w800/src/os_mempool.c
${SDK_ROOT}/src/bt/blehost/porting/w800/src/nimble_port.c
${SDK_ROOT}/src/bt/blehost/porting/w800/src/mem.c
${SDK_ROOT}/src/bt/blehost/porting/w800/src/os_msys_init.c
${SDK_ROOT}/src/bt/blehost/porting/w800/src/os_msys_init.c
${SDK_ROOT}/src/bt/blehost/porting/w800/src/tls_nimble.c
${SDK_ROOT}/src/bt/blehost/porting/w800/src/tls_nimble.c
${SDK_ROOT}/src/bt/blehost/porting/w800/src/nimble_port_freertos.c
${SDK_ROOT}/src/bt/blehost/porting/w800/src/os_mbuf.c
${SDK_ROOT}/src/bt/blehost/porting/w800/src/endian.c
${SDK_ROOT}/src/bt/blehost/porting/w800/src/npl_os_freertos.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_eddystone.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_sm_alg.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_sm_cmd.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_shutdown.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_flow.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_hci_util.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_gattc.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_uuid.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_cfg.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_l2cap_sig_cmd.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_mqueue.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_stop.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_store_util.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_sm_lgcy.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_sm_cmd.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_hci_evt.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_att_svr.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_cfg.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_gap.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_att_svr.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_gattc.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_conn.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_hci.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_att_cmd.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_conn.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_misc.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_sm.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_log.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_att_cmd.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_gatts_lcl.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_log.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_gatts_lcl.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_adv.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_eddystone.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_gap.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_uuid.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_hci_evt.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_startup.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_id.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_sm_lgcy.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_l2cap.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_mbuf.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_mbuf.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_sm.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_sm_sc.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_startup.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_mqueue.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_periodic_sync.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_misc.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_l2cap_sig_cmd.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_monitor.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_att.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_id.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_periodic_sync.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_hci_cmd.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_hci_util.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_pvcy.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_hci.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_ibeacon.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_att_clt.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_store.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_sm_sc.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_ibeacon.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_att.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_gatts.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_att_clt.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_l2cap_sig.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_atomic.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_sm_alg.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_pvcy.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_l2cap.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_l2cap_coc.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_shutdown.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_atomic.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_stop.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_adv.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_store.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_l2cap_coc.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_store_util.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_monitor.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_l2cap_sig.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_flow.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_gatts.c
${SDK_ROOT}/src/bt/blehost/nimble/host/src/ble_hs_hci_cmd.c
${SDK_ROOT}/src/bt/blehost/nimble/host/services/gatt/src/ble_svc_gatt.c
${SDK_ROOT}/src/bt/blehost/nimble/host/services/gatt/src/ble_svc_gatt.c
${SDK_ROOT}/src/bt/blehost/nimble/host/services/gap/src/ble_svc_gap.c
${SDK_ROOT}/src/bt/blehost/nimble/host/services/gap/src/ble_svc_gap.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/settings.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/light_model.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/friend.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/nodes.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/adv.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/model_srv.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/beacon.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/mesh.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/crypto.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/cfg_cli.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/proxy.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/mesh.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/model_cli.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/light_model.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/health_srv.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/model_srv.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/cfg_srv.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/testing.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/health_cli.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/settings.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/crypto.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/friend.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/shell.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/prov.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/adv.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/transport.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/access.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/access.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/lpn.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/prov.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/cfg_cli.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/glue.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/model_cli.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/cfg_srv.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/health_srv.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/nodes.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/net.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/beacon.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/proxy.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/health_cli.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/glue.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/transport.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/testing.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/lpn.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/shell.c
${SDK_ROOT}/src/bt/blehost/nimble/host/mesh/src/net.c
${SDK_ROOT}/src/bt/blehost/nimble/host/store/ram/src/ble_store_ram.c
${SDK_ROOT}/src/bt/blehost/nimble/host/store/ram/src/ble_store_ram.c
${SDK_ROOT}/src/bt/blehost/nimble/host/store/config/src/ble_store_nvram.c
${SDK_ROOT}/src/bt/blehost/nimble/host/store/config/src/ble_store_config.c
${SDK_ROOT}/src/bt/blehost/nimble/host/store/config/src/ble_store_nvram.c
${SDK_ROOT}/src/bt/blehost/nimble/host/store/config/src/ble_store_config.c
${SDK_ROOT}/src/bt/blehost/nimble/host/util/src/addr.c
${SDK_ROOT}/src/bt/blehost/nimble/host/util/src/addr.c
${SDK_ROOT}/src/bt/blehost/nimble/transport/uart/src/ble_hci_uart.c
${SDK_ROOT}/src/bt/blehost/nimble/transport/uart/src/ble_hci_uart.c

#RTOS
${SDK_ROOT}/src/os/rtos/wm_osal_rtos.c
${SDK_ROOT}/src/os/rtos/ports/xt804/port.c
${SDK_ROOT}/src/os/rtos/ports/xt804/cpu_task_sw.S
${SDK_ROOT}/src/os/rtos/source/croutine.c
${SDK_ROOT}/src/os/rtos/source/heap_2.c
${SDK_ROOT}/src/os/rtos/source/queue.c
${SDK_ROOT}/src/os/rtos/source/rtostimers.c
${SDK_ROOT}/src/os/rtos/source/list.c
${SDK_ROOT}/src/os/rtos/source/croutine.c
${SDK_ROOT}/src/os/rtos/source/heap_2.c
${SDK_ROOT}/src/os/rtos/source/tasks.c
${SDK_ROOT}/src/os/rtos/source/heap_3.c
${SDK_ROOT}/src/os/rtos/source/list.c
${SDK_ROOT}/src/os/rtos/source/tasks.c
${SDK_ROOT}/src/os/rtos/source/queue.c
${SDK_ROOT}/src/os/rtos/source/rtostimers.c
${SDK_ROOT}/src/os/rtos/source/heap_3.c
${SDK_ROOT}/src/os/rtos/wm_osal_rtos.c

)

#使用源代码编译的库文件
add_library(SDK_SOURCE_LIB STATIC ${SDK_SRCS})

#预先编译的库文件
list(APPEND SDK_PRECOMPILED_LIBS 
${SDK_ROOT}/lib/w800/libwlan.a 
${SDK_ROOT}/lib/w800/libbtcontroller.a 
${SDK_ROOT}/lib/w800/libdsp.a    
${SDK_ROOT}/lib/w800/libwmarch.a  
)

#添加SimpleMQTTGateWayStack库
add_subdirectory(lib/SimpleMQTTGateWayStack/lib)

#添加MQTT移植
file(GLOB  PAHO_PORT_C_FILES lib/MQTT/*.c)
list(APPEND PAHO_SRCS
${PAHO_MQTTPACKET_C_FILES}
${PAHO_PORT_C_FILES}
)
add_library(PAHO_MQTT STATIC ${PAHO_SRCS})
target_include_directories(PAHO_MQTT
PUBLIC lib/MQTT/
)
target_compile_definitions(PAHO_MQTT
PUBLIC MQTTCLIENT_PLATFORM_HEADER=MQTTFreeRTOS_LWIP.h MQTT_TASK
)
target_link_libraries(PAHO_MQTT SMGS)



if(NOT DEFINED MAIN_SRCS)
	set(MAIN_SRCS ${SDK_ROOT}/app/main.c )
endif()



list(APPEND MAIN_SRCS

)

#Kconfig(使用Kconfig进行配置)
option(USE_KCONFIG "use kconfig" OFF)

if(${USE_KCONFIG})

    add_definitions(" -DUSE_KCONFIG=1 ")

    find_program(PYTHON
               NAMES python3 python python2
               REQUIRED
               )
    message("python path: ${PYTHON}")
    #安装依赖
    execute_process(COMMAND ${PYTHON} -m pip install -r  ${CMAKE_CURRENT_SOURCE_DIR}/requirement.txt
                      RESULT_VARIABLE PYTHON_INSTALL_RESULT)
    if(PYTHON_INSTALL_RESULT EQUAL 0)
    message("install from requirement.txt success")
    else()
    message(FATAL_ERROR "install from requirement.txt error")
    endif()

    #生成config.h
    add_custom_command(OUTPUT config.h
                    COMMAND ${PYTHON} -m genconfig --header-path config.h
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    )


    if(CMAKE_HOST_WIN32)
        #menuconfig 目标(windows)
        add_custom_target(menuconfig cmd.exe /C start cmd.exe /c ${PYTHON} -m menuconfig
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                  USES_TERMINAL
                  )
    else()
        #menuconfig 目标(非windows)
        add_custom_target(menuconfig  ${PYTHON} -m menuconfig
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                  USES_TERMINAL
                  )
    endif()

    #将config.h添加至MAIN_SRCS
    list(APPEND MAIN_SRCS
         config.h )


endif()


if(NOT DEFINED MAIN_INCLUDE_DIRS)
	set(MAIN_INCLUDE_DIRS ./)
endif()

list(APPEND  MAIN_INCLUDE_DIRS  ${SDK_INCLUDE_DIRS})




#设置头文件
include_directories(${MAIN_INCLUDE_DIRS})

#设置宏定义
add_definitions(" -DNIMBLE_FTR=1 -DWM_SWD_ENABLE=1 ")

#添加可执行文件
add_executable(${PROJECT_NAME} ${MAIN_SRCS})
target_link_libraries(${PROJECT_NAME} SDK_SOURCE_LIB  ${SDK_PRECOMPILED_LIBS} "-Wl,--no-whole-archive" PAHO_MQTT )

#生成bin文件
add_custom_target(${PROJECT_NAME}.bin ALL
				 COMMAND ${CMAKE_OBJCOPY} --output-target=binary  ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
				 DEPENDS ${PROJECT_NAME}
				 )

#准备wm_tool
find_program(WM_TOOL
               NAMES wm_tool
               PATHS ${SDK_ROOT}/tools/w800/ ${CMAKE_BINARY_DIR}/
               NO_CACHE
               )
if(NOT EXISTS ${WM_TOOL})
    message("wm_tool is not found,try to compile!")
    #使用C编译器编译
    find_program(CC NAMES cc gcc REQUIRED)
    message("cc path: ${CC}")
    execute_process(COMMAND ${CC} -pthread ${SDK_ROOT}/tools/w800/wm_tool.c  -o ${CMAKE_BINARY_DIR}/wm_tool)
    find_program(WM_TOOL
               NAMES wm_tool
               PATHS  ${CMAKE_BINARY_DIR}/ ${SDK_ROOT}/tools/w800/
               NO_CACHE
               REQUIRED
               )
    message("wm_tool path: ${WM_TOOL}" )
else()
    message("wm_tool path: ${WM_TOOL}" )
endif()


set(GREATE_IMG_STEP1_FLAGS  -b ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.bin  -fc 0 -it 1 -ih 80D0000 -ra 80D0400 -ua 8010000 -nh 0 -un 0 -vs G01.00.02  -o ${PROJECT_NAME})
set(GREATE_IMG_STEP2_FLAGS  -b ${SDK_ROOT}/tools/w800/w800_secboot.bin -fc 0 -it 0 -ih 8002000 -ra 8002400 -ua 8010000 -nh 80D0000 -un 0 -o w800_secboot)
set(GREATE_IMG_STEP3_FLAGS  -b ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.img  -fc 1 -it 1 -ih 80D0000 -ra 80D0400 -ua 8010000 -nh 0 -un 0 -vs G01.00.02 -o ${PROJECT_NAME})
set(GREATE_IMG_STEP4_FLAGS  -b ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.img  -sb  w800_secboot.img -fc 1 -it 1 -ih 80D0000 -ra 80D0400 -ua 8010000 -nh 0 -un 0 -vs G01.00.02  -o ${PROJECT_NAME})

#生成其它镜像文件（包括fls文件）
add_custom_target(${PROJECT_NAME}.fls ALL
				 COMMAND ${WM_TOOL} ${GREATE_IMG_STEP1_FLAGS} 
				 COMMAND ${WM_TOOL} ${GREATE_IMG_STEP2_FLAGS}
				 COMMAND ${WM_TOOL} ${GREATE_IMG_STEP3_FLAGS} 
				 COMMAND ${WM_TOOL} ${GREATE_IMG_STEP4_FLAGS}
				 DEPENDS ${PROJECT_NAME}.bin
				 )


##默认的烧录串口
##环境变量
if(NOT DEFINED ENV{WM_PORT})
    set(ENV{WM_PORT} ttyUSB0)
endif()

#flash目标
add_custom_target(flash
                   COMMAND ${WM_TOOL} -c $ENV{WM_PORT} -eo all -dl ${PROJECT_NAME}.fls
                   DEPENDS ${PROJECT_NAME}.fls
                  )
#run目标                  
add_custom_target(run
                   COMMAND ${WM_TOOL} -c $ENV{WM_PORT} -eo all -dl ${PROJECT_NAME}.fls -sl str -ws 115200
                   DEPENDS ${PROJECT_NAME}.fls
                  )

