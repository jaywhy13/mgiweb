
FridgeConnectAdmin = function(){};

FridgeConnectAdmin.loginStatusHandler = function(event, response) {
  //debugger;
  jQuery('.fridge_connect_admin_status').hide();
  jQuery('.fridge_connect_admin_status_' + response.status).show();
};

FridgeConnectAdmin.initHandler = function(event, response) {
  //debugger;
  jQuery('.fridge_connect_admin_status').hide();

  // The status_none text will be hidded if getLoginStatus returns.
  jQuery('.fridge_connect_admin_status_none').show();
};

/**
 * Drupal behaviors hook.
 *
 * Called when page is loaded, or content added via javascript.
 */
(function ($) {
  Drupal.behaviors.fb_connect_admin = {
    attach : function(context) {
      // Respond to our jquery pseudo-events
      jQuery(document).bind('fridge_login_status', FridgeConnectAdmin.loginStatusHandler);
      jQuery(document).bind('fridge_init', FridgeConnectAdmin.initHandler);

      jQuery('.fridge_connect_admin_status').hide();
      jQuery('.fridge_connect_admin_status_no_js').show();

    }
  };

})(jQuery);
