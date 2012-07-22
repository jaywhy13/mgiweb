
Fridge = function(){};
Fridge.fbu = null;
Fridge.status = 'none'; // login status: none, unknown (not connected), or connected
Fridge.authResponse = null;

Fridge.fbAsyncInit = function() {
  FB.init({
    appId: Drupal.settings.fridge.client_id,
    xfbml: true,
    oauth: true
  });

  if (Drupal.settings.fridge.client_id) {
    // Use FB.Event to detect Connect login/logout.
    FB.Event.subscribe('auth.authResponseChange', Fridge.authResponseChange);

    FB.getLoginStatus(function(response) {
      Fridge.authResponse = response.authResponse;
      Fridge.status = response.status;
      if (response.status == 'connected') {
        Fridge.handleLoginStatus(response.authResponse.userID);
      }
      else {
        Fridge.handleLoginStatus(0);
      }
      // Use FB.Event to detect Connect login/logout.
      //FB.Event.subscribe('auth.authResponseChange', Fridge.authResponseChange);

      // Notify third-parties.
      jQuery.event.trigger('fridge_login_status', response);

      if (response.status != Drupal.settings.fridge.status) {
        // Spoof a session change event.
        Fridge.authResponseChange(response);
      }
    });
  }
  else {
    Fridge.handleLoginStatus(0);
    // Use FB.Event to detect Connect login/logout.
    //FB.Event.subscribe('auth.authResponseChange', Fridge.authResponseChange);
  }

  // Notify third parties that global FB is now initialized.
  jQuery.event.trigger('fridge_init');

};


// Facebook pseudo-event handlers.
Fridge.authResponseChange = function(response) {
  Fridge.authResponse = response.authResponse;
  Fridge.status = response.status;
  if (response.status == 'connected') {
    Fridge.handleLoginStatus(response.authResponse.userID);
  }
  else {
    Fridge.handleLoginStatus(0);
  }
  if (response.status != Drupal.settings.fridge.status) {
    Fridge.ajaxEvent('session_change', {});
  }
};

/**
 * Called when we first learn the currently logged in user's Facebook ID.
 *
 * Responsible for showing/hiding markup not intended for the current
 * user.  Some sites will choose to render pages with fridge_connected and
 * fridge_not_connected classes, rather than reload pages when users
 * connect/disconnect.
 *
 * Also supports fridge_status_none (getLoginStatus does not return),
 * fridge_status_unknown (not connected), and fridge_status_connected
 * (connected).
 */
Fridge.handleLoginStatus = function(fbu, context) {
  if (context || fbu != Fridge.fbu) {
    if (fbu) {
      Fridge.fbu = fbu;
      // Show markup intended only for connected users.
      jQuery('.fridge_not_connected', context).hide();
      jQuery('.fridge_connected', context).show();
    }
    else {
      Fridge.fbu = null;
      // Show markup intended only for not connected users.
      jQuery('.fridge_connected', context).hide();
      jQuery('.fridge_not_connected', context).show();
    }
  }

  // Show or hide content based on status.
  var states = ['none', 'unknown', 'connected'];
  for (var i = states.length-1; i >= 0; --i){
    if (Fridge.status != states[i]) {
      jQuery('.fridge_status_' + states[i]).hide();
    }
  }
  jQuery('.fridge_status_' + Fridge.status).show();
};

// Helper to pass events via AJAX.
// A list of javascript functions to be evaluated is returned.
Fridge.ajaxEvent = function(event_type, request_data) {
  if (Drupal.settings.fridge.ajax_event_url) {

    if (Fridge.status == 'connected') {
      request_data.signed_request = Fridge.authResponse.signedRequest;
      request_data.access_token = FB.getAccessToken();
    }
    //request_data.fbu = Fridge.fbu; // redundant, signed request contains this
    request_data.status = Fridge.status;
    request_data.app_id = Drupal.settings.fridge.client_id;

    jQuery.ajax({
      url: Drupal.settings.fridge.ajax_event_url + '/' + event_type,
      data : request_data,
      type: 'POST',
      dataType: 'json',
      success: function(js_array, textStatus, XMLHttpRequest) {
        if (js_array.length > 0) {
          for (var i = 0; i < js_array.length; i++) {
            eval(js_array[i]);
          }
        }
      },
      error: function(jqXHR, textStatus, errorThrown) {
        // Unexpected error (i.e. ajax did not return json-encoded data).
        var headers = jqXHR.getAllResponseHeaders(); // debug info.
        var responseText = jqXHR.responseText; // debug info.
        debugger;
        // @TODO: handle error, but how?
      }
    });
  }
};



/**
 * Drupal behaviors hook.
 *
 * Called when page is loaded, or content added via javascript.
 */
(function ($) {
  Drupal.behaviors.fridge = {
    attach : function(context) {
      if (typeof(FB) == 'undefined' && typeof(window.fbAsyncInit) == 'undefined') {
        // No other modules have initialed Facebook's javascript, so we can.

        $('body').append('<div id="fb-root"></div>'); // Facebook recommends this tag.

        window.fbAsyncInit = Fridge.fbAsyncInit;

        // http://developers.facebook.com/docs/reference/javascript/
        var e = document.createElement('script'); e.async = true;
        e.src = document.location.protocol + '//connect.facebook.net/en_US/all.js';
        document.getElementById('fb-root').appendChild(e);
        Drupal.settings.fridge.fridge_initialized = 1;
      }
      else {
        if (Drupal.settings.fridge && Drupal.settings.fridge.fridge_initialized) {
          // Render any XFBML markup that may have been added by AJAX,
          // if we are the module that initialized the facebook
          // javascript.
          $(context).each(function() {
            var elem = $(this).get(0);
            FB.XFBML.parse(elem);
          });
          Fridge.handleLoginStatus(Fridge.fbu, context);
        }
      }
    }
  };

})(jQuery);
