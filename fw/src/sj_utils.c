/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#include "fw/src/sj_uart.h"
#include "fw/src/device_config.h"

#ifndef CS_DISABLE_JS

#ifdef MG_ENABLE_SSL
enum v7_err fill_ssl_connect_opts(struct v7 *v7, v7_val_t opts, int force_ssl,
                                  struct mg_connect_opts *copts) {
  enum v7_err rcode = V7_OK;

  v7_val_t v_use_ssl = v7_get(v7, opts, "use_ssl", ~0);
  v7_val_t v_ca_cert = v7_get(v7, opts, "ssl_ca_cert", ~0);
  v7_val_t v_cert = v7_get(v7, opts, "ssl_cert", ~0);
  v7_val_t v_server_name = v7_get(v7, opts, "ssl_server_name", ~0);

  if (!v7_is_undefined(v_ca_cert) && !v7_is_string(v_ca_cert)) {
    rcode = v7_throwf(v7, "TypeError", "ssl_ca_cert must be a string");
    goto clean;
  }
  if (!v7_is_undefined(v_cert) && !v7_is_string(v_cert)) {
    rcode = v7_throwf(v7, "TypeError", "ssl_cert must be a string");
    goto clean;
  }
  if (!v7_is_undefined(v_server_name) && !v7_is_string(v_server_name)) {
    rcode = v7_throwf(v7, "TypeError", "ssl_server_name must be a string");
    goto clean;
  }

  copts->ssl_ca_cert = v7_get_cstring(v7, &v_ca_cert);
  copts->ssl_cert = v7_get_cstring(v7, &v_cert);
  copts->ssl_server_name = v7_get_cstring(v7, &v_server_name);

  if ((force_ssl ||
       (v7_is_boolean(v_use_ssl) && v7_get_bool(v7, v_use_ssl) != 0)) &&
      copts->ssl_ca_cert == NULL) {
    /* Defaults to configuration */
    copts->ssl_ca_cert = get_cfg()->tls.ca_file;
  }

clean:
  return rcode;
}
#endif /* MG_ENABLE_SSL */

#endif /* CS_DISABLE_JS */
