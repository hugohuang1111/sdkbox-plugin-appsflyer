#include "./json.hpp"
#include "PluginAppsFlyer.h"
#include "Bridge.hpp"
#include "Msg.hpp"

namespace sdkbox {
namespace bb {
namespace plugin {

// In app event names constants
const std::string AppsFlyer::AFEventLevelAchieved             = "af_level_achieved";
const std::string AppsFlyer::AFEventAddPaymentInfo            = "af_add_payment_info";
const std::string AppsFlyer::AFEventAddToCart                 = "af_add_to_cart";
const std::string AppsFlyer::AFEventAddToWishlist             = "af_add_to_wishlist";
const std::string AppsFlyer::AFEventCompleteRegistration      = "af_complete_registration";
const std::string AppsFlyer::AFEventTutorial_completion       = "af_tutorial_completion";
const std::string AppsFlyer::AFEventInitiatedCheckout         = "af_initiated_checkout";
const std::string AppsFlyer::AFEventPurchase                  = "af_purchase";
const std::string AppsFlyer::AFEventRate                      = "af_rate";
const std::string AppsFlyer::AFEventSearch                    = "af_search";
const std::string AppsFlyer::AFEventSpentCredits              = "af_spent_credits";
const std::string AppsFlyer::AFEventAchievementUnlocked       = "af_achievement_unlocked";
const std::string AppsFlyer::AFEventContentView               = "af_content_view";
const std::string AppsFlyer::AFEventListView                  = "af_list_view";
const std::string AppsFlyer::AFEventTravelBooking             = "af_travel_booking";
const std::string AppsFlyer::AFEventShare                     = "af_share";
const std::string AppsFlyer::AFEventInvite                    = "af_invite";
const std::string AppsFlyer::AFEventLogin                     = "af_login";
const std::string AppsFlyer::AFEventReEngage                  = "af_re_engage";
const std::string AppsFlyer::AFEventUpdate                    = "af_update";
const std::string AppsFlyer::AFEventOpenedFromPushNotification  = "af_opened_from_push_notification";
const std::string AppsFlyer::AFEventLocation                  = "af_location_coordinates";
const std::string AppsFlyer::AFEventCustomerSegment           = "af_customer_segment";

const std::string AppsFlyer::AFEventSubscribe                 = "af_subscribe";
const std::string AppsFlyer::AFEventStartTrial                = "af_start_trial";
const std::string AppsFlyer::AFEventAdClick                   = "af_ad_click";
const std::string AppsFlyer::AFEventAdView                    = "af_ad_view";

        // In app event parameter names
const std::string AppsFlyer::AFEventParamContent                 = "af_content";
const std::string AppsFlyer::AFEventParamAchievenmentId          = "af_achievement_id";
const std::string AppsFlyer::AFEventParamLevel                   = "af_level";
const std::string AppsFlyer::AFEventParamScore                   = "af_score";
const std::string AppsFlyer::AFEventParamSuccess                 = "af_success";
const std::string AppsFlyer::AFEventParamPrice                   = "af_price";
const std::string AppsFlyer::AFEventParamContentType             = "af_content_type";
const std::string AppsFlyer::AFEventParamContentId               = "af_content_id";
const std::string AppsFlyer::AFEventParamContentList             = "af_content_list";
const std::string AppsFlyer::AFEventParamCurrency                = "af_currency";
const std::string AppsFlyer::AFEventParamQuantity                = "af_quantity";
const std::string AppsFlyer::AFEventParamRegistrationMethod      = "af_registration_method";
const std::string AppsFlyer::AFEventParamPaymentInfoAvailable    = "af_payment_info_available";
const std::string AppsFlyer::AFEventParamMaxRatingValue          = "af_max_rating_value";
const std::string AppsFlyer::AFEventParamRatingValue             = "af_rating_value";
const std::string AppsFlyer::AFEventParamSearchString            = "af_search_string";
const std::string AppsFlyer::AFEventParamDateA                   = "af_date_a";
const std::string AppsFlyer::AFEventParamDateB                   = "af_date_b";
const std::string AppsFlyer::AFEventParamDestinationA            = "af_destination_a";
const std::string AppsFlyer::AFEventParamDestinationB            = "af_destination_b";
const std::string AppsFlyer::AFEventParamDescription             = "af_description";
const std::string AppsFlyer::AFEventParamClass                   = "af_class";
const std::string AppsFlyer::AFEventParamEventStart              = "af_event_start";
const std::string AppsFlyer::AFEventParamEventEnd                = "af_event_end";
const std::string AppsFlyer::AFEventParamLat                     = "af_lat";
const std::string AppsFlyer::AFEventParamLong                    = "af_long";
const std::string AppsFlyer::AFEventParamCustomerUserId          = "af_customer_user_id";
const std::string AppsFlyer::AFEventParamValidated               = "af_validated";
const std::string AppsFlyer::AFEventParamRevenue                 = "af_revenue";
const std::string AppsFlyer::AFEventProjectedParamRevenue        = "af_projected_revenue";
const std::string AppsFlyer::AFEventParamReceiptId               = "af_receipt_id";
const std::string AppsFlyer::AFEventParamTutorialId              = "af_tutorial_id";
const std::string AppsFlyer::AFEventParamVirtualCurrencyName     = "af_virtual_currency_name";
const std::string AppsFlyer::AFEventParamDeepLink                = "af_deep_link";
const std::string AppsFlyer::AFEventParamOldVersion              = "af_old_version";
const std::string AppsFlyer::AFEventParamNewVersion              = "af_new_version";
const std::string AppsFlyer::AFEventParamReviewText              = "af_review_text";
const std::string AppsFlyer::AFEventParamCouponCode              = "af_coupon_code";
const std::string AppsFlyer::AFEventParamOrderId                 = "af_order_id";
const std::string AppsFlyer::AFEventParam1                       = "af_param_1";
const std::string AppsFlyer::AFEventParam2                       = "af_param_2";
const std::string AppsFlyer::AFEventParam3                       = "af_param_3";
const std::string AppsFlyer::AFEventParam4                       = "af_param_4";
const std::string AppsFlyer::AFEventParam5                       = "af_param_5";
const std::string AppsFlyer::AFEventParam6                       = "af_param_6";
const std::string AppsFlyer::AFEventParam7                       = "af_param_7";
const std::string AppsFlyer::AFEventParam8                       = "af_param_8";
const std::string AppsFlyer::AFEventParam9                       = "af_param_9";
const std::string AppsFlyer::AFEventParam10                      = "af_param_10";

const std::string AppsFlyer::AFEventParamDepartingDepartureDate   = "af_departing_departure_date";
const std::string AppsFlyer::AFEventParamReturningDepartureDate   = "af_returning_departure_date";
const std::string AppsFlyer::AFEventParamDestinationList          = "af_destination_list";  //array of string
const std::string AppsFlyer::AFEventParamCity                     = "af_city";
const std::string AppsFlyer::AFEventParamRegion                   = "af_region";
const std::string AppsFlyer::AFEventParamCountry                  = "af_country";


const std::string AppsFlyer::AFEventParamDepartingArrivalDate     = "af_departing_arrival_date";
const std::string AppsFlyer::AFEventParamReturningArrivalDate     = "af_returning_arrival_date";
const std::string AppsFlyer::AFEventParamSuggestedDestinations    = "af_suggested_destinations"; //array of string
const std::string AppsFlyer::AFEventParamTravelStart              = "af_travel_start";
const std::string AppsFlyer::AFEventParamTravelEnd                = "af_travel_end";
const std::string AppsFlyer::AFEventParamNumAdults                = "af_num_adults";
const std::string AppsFlyer::AFEventParamNumChildren              = "af_num_children";
const std::string AppsFlyer::AFEventParamNumInfants               = "af_num_infants";
const std::string AppsFlyer::AFEventParamSuggestedHotels          = "af_suggested_hotels"; //array of string

const std::string AppsFlyer::AFEventParamUserScore                = "af_user_score";
const std::string AppsFlyer::AFEventParamHotelScore               = "af_hotel_score";
const std::string AppsFlyer::AFEventParamPurchaseCurrency         = "af_purchase_currency";

const std::string AppsFlyer::AFEventParamPreferredStarRatings     = "af_preferred_star_ratings";    //array of int (basically a tuple (min,max) but we'll use array of int and instruct the developer to use two values)

const std::string AppsFlyer::AFEventParamPreferredPriceRange      = "af_preferred_price_range";    //array of int (basically a tuple (min,max) but we'll use array of int and instruct the developer to use two values)
const std::string AppsFlyer::AFEventParamPreferredNeighborhoods   = "af_preferred_neighborhoods"; //array of string
const std::string AppsFlyer::AFEventParamPreferredNumStops        = "af_preferred_num_stops";

const std::string AppsFlyer::AFEventParamAdRevenueAdType               = "af_adrev_ad_type";
const std::string AppsFlyer::AFEventParamAdRevenueNetworkName          = "af_adrev_network_name";
const std::string AppsFlyer::AFEventParamAdRevenuePlacementId          = "af_adrev_placement_id";
const std::string AppsFlyer::AFEventParamAdRevenueAdSize               = "af_adrev_ad_size";
const std::string AppsFlyer::AFEventParamAdRevenueMediatedNetworkName  = "af_adrev_mediated_network_name";


void AppsFlyer::init() {
    sdkbox::bb::Bridge::init();

#ifdef ANDROID
    sdkbox::bb::Bridge::addPlugin("AppsFlyer", "com.sdkbox.bb.bridge.plugin.appsflyer.PluginAppsFlyer");
#elif __APPLE__
    sdkbox::bb::Bridge::addPlugin("AppsFlyer", "BBPluginAppsFlyer");
#else
    #error "Unknown support platform"
#endif
}

void AppsFlyer::setListener(const std::function<void(const std::string& evt, const std::string& json)>& listener) {
    sdkbox::bb::Bridge::onRecv([=](const Msg& msg) {
        auto pluginName = msg.getPlugin();
        auto valEvt = msg.getValue(0);
        if (0 != pluginName.compare("AppsFlyer")) {
            return ;
        }
        listener(valEvt.stringValue(), msg.getValue(1).stringValue());
    });
}

void AppsFlyer::setAppID(const std::string& appID) {
    sdkbox::bb::Msg msg = sdkbox::bb::Msg("AppsFlyer", "setAppID");
    msg.pushValue(appID);
    sdkbox::bb::Bridge::send(msg);
}

void AppsFlyer::setDevKey(const std::string& devKey) {
    sdkbox::bb::Msg msg = sdkbox::bb::Msg("AppsFlyer", "setDevKey");
    msg.pushValue(devKey);
    sdkbox::bb::Bridge::send(msg);
}

void AppsFlyer::setDebug(bool b) {
    sdkbox::bb::Msg msg = sdkbox::bb::Msg("AppsFlyer", "setDebug");
    msg.pushValue(b);
    sdkbox::bb::Bridge::send(msg);
}

void AppsFlyer::setAdditionalData(const std::string& json) {
    sdkbox::bb::Msg msg = sdkbox::bb::Msg("AppsFlyer", "setAdditionalData");
    msg.pushValue(json);
    sdkbox::bb::Bridge::send(msg);
}

void AppsFlyer::getAppsFlyerUID(const std::function<void(const std::string& appsflyerID)>& cb) {
    sdkbox::bb::Msg msg = sdkbox::bb::Msg("AppsFlyer", "getAppsFlyerUID");
    sdkbox::bb::Bridge::send(msg, [&](const Msg& rMsg) {
        std::string appsflyerID = rMsg.getValue(0).stringValue();
        cb(appsflyerID);
    });
}

void AppsFlyer::setCustomerUserID(const std::string& userID) {
    sdkbox::bb::Msg msg = sdkbox::bb::Msg("AppsFlyer", "setCustomerUserID");
    msg.pushValue(userID);
    sdkbox::bb::Bridge::send(msg);
}

void AppsFlyer::anonymizeUser(bool b) {
    sdkbox::bb::Msg msg = sdkbox::bb::Msg("AppsFlyer", "anonymizeUser");
    msg.pushValue(b);
    sdkbox::bb::Bridge::send(msg);
}

void AppsFlyer::collectASA(bool b) {
#ifdef __APPLE__
    sdkbox::bb::Msg msg = sdkbox::bb::Msg("AppsFlyer", "collectASA");
    msg.pushValue(b);
    sdkbox::bb::Bridge::send(msg);
#endif
}

void AppsFlyer::waitForATTUserAuthorizationWithTimeoutInterval(int seconds) {
#ifdef __APPLE__
    sdkbox::bb::Msg msg = sdkbox::bb::Msg("AppsFlyer", "waitForATTUserAuthorizationWithTimeoutInterval");
    msg.pushValue(seconds);
    sdkbox::bb::Bridge::send(msg);
#endif
}

void AppsFlyer::stop() {
    sdkbox::bb::Msg msg = sdkbox::bb::Msg("AppsFlyer", "stop");
    sdkbox::bb::Bridge::send(msg);
}

void AppsFlyer::start() {
    sdkbox::bb::Msg msg = sdkbox::bb::Msg("AppsFlyer", "start");
    sdkbox::bb::Bridge::send(msg);
}

void AppsFlyer::logEvent(const std::string& evt, const std::string& json) {
    sdkbox::bb::Msg msg = sdkbox::bb::Msg("AppsFlyer", "logEvent");
    msg.pushValue(evt);
    msg.pushValue(json);
    sdkbox::bb::Bridge::send(msg);
}

void AppsFlyer::useReceiptValidationSandbox(bool b) {
#ifdef __APPLE__
    sdkbox::bb::Msg msg = sdkbox::bb::Msg("AppsFlyer", "useReceiptValidationSandbox");
    msg.pushValue(b);
    sdkbox::bb::Bridge::send(msg);
#endif
}

void AppsFlyer::validateAndLogInAppPurchase(const std::string& purchaseJson) {
    sdkbox::bb::Msg msg = sdkbox::bb::Msg("AppsFlyer", "validateAndLogInAppPurchase");
    msg.pushValue(purchaseJson);
    sdkbox::bb::Bridge::send(msg);
}

void AppsFlyer::setMinTimeBetweenSessions(int seconds) {
    sdkbox::bb::Msg msg = sdkbox::bb::Msg("AppsFlyer", "setMinTimeBetweenSessions");
    msg.pushValue(seconds);
    sdkbox::bb::Bridge::send(msg);
}

void AppsFlyer::setResolveDeepLinkURLs(const std::vector<std::string>& urls) {
    sdkbox::bb::Msg msg = sdkbox::bb::Msg("AppsFlyer", "setResolveDeepLinkURLs");
    nlohmann::json j;
    for (auto it = urls.begin(); it != urls.end(); ++it) {
        j.push_back(*it);
    }
    msg.pushValue(j.dump());
    sdkbox::bb::Bridge::send(msg);
}

void AppsFlyer::setImeiData(const std::string& data) {
#ifdef ANDROID
    sdkbox::bb::Msg msg = sdkbox::bb::Msg("AppsFlyer", "setImeiData");
    msg.pushValue(data);
    sdkbox::bb::Bridge::send(msg);
#endif
}

void AppsFlyer::setAndroidIdData(const std::string& data) {
#ifdef ANDROID
    sdkbox::bb::Msg msg = sdkbox::bb::Msg("AppsFlyer", "setAndroidIdData");
    msg.pushValue(data);
    sdkbox::bb::Bridge::send(msg);
#endif
}

void AppsFlyer::setCollectIMEI(bool b) {
#ifdef ANDROID
    sdkbox::bb::Msg msg = sdkbox::bb::Msg("AppsFlyer", "setCollectIMEI");
    msg.pushValue(b);
    sdkbox::bb::Bridge::send(msg);
#endif
}

void AppsFlyer::setCollectAndroidID(bool b) {
#ifdef ANDROID
    sdkbox::bb::Msg msg = sdkbox::bb::Msg("AppsFlyer", "setCollectAndroidID");
    msg.pushValue(b);
    sdkbox::bb::Bridge::send(msg);
#endif
}

void AppsFlyer::setCollectOaid(bool b) {
#ifdef ANDROID
    sdkbox::bb::Msg msg = sdkbox::bb::Msg("AppsFlyer", "setCollectOaid");
    msg.pushValue(b);
    sdkbox::bb::Bridge::send(msg);
#endif
}



}
}
}
