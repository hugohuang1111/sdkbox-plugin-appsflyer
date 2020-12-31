#pragma once

#include <string>
#include <vector>

namespace sdkbox {
namespace bb {
namespace plugin {

    class AppsFlyer {
    public:
        static void init();
        static void setListener(const std::function<void(const std::string& evt, const std::string& json)>& listener);
        static void setAppID(const std::string& appID);
        static void setDevKey(const std::string& devKey);
        static void setDebug(bool b);
        static void setAdditionalData(const std::string& json);
        static void getAppsFlyerUID(const std::function<void(const std::string& appsflyerID)>& cb);
        static void setCustomerUserID(const std::string& userID);
        static void anonymizeUser(bool b);
        static void collectASA(bool b);
        static void waitForATTUserAuthorizationWithTimeoutInterval(int seconds);
        static void stop();
        static void start();
        static void logEvent(const std::string& evt, const std::string& json);
        static void useReceiptValidationSandbox(bool b);

        /*
         * validateAndLogInAppPurchase param need a json string, like follow sample.
         *
         * Android Params Sample:
         * {
             "publicKey": "xxx",
             "signature": "xxx",
             "purchaseData": "xxx",
             "price": "xxx",
             "currency": "xxx",
             "parameters": {
                 "k1": "v1",
                 "k2": "v2"
             }
         }
         *
         * iOS Params Sample:
         * {
             "productIdentifier": "xxx",
             "transactionId": "xxx",
             "price": "xxx",
             "currency": "xxx",
             "parameters": {
                 "k1": "v1",
                 "k2": "v2"
             }
         * }
         *
         */
        static void validateAndLogInAppPurchase(const std::string& purchaseJson);
        static void setMinTimeBetweenSessions(int seconds);
        static void setResolveDeepLinkURLs(const std::vector<std::string>& urls);

        static void setImeiData(const std::string& data);
        static void setAndroidIdData(const std::string& data);
        static void setCollectIMEI(bool b);
        static void setCollectAndroidID(bool b);
        static void setCollectOaid(bool b);

    public:

        // In app event names constants
        static const std::string AFEventLevelAchieved             ; // @"af_level_achieved"
        static const std::string AFEventAddPaymentInfo            ; // @"af_add_payment_info"
        static const std::string AFEventAddToCart                 ; // @"af_add_to_cart"
        static const std::string AFEventAddToWishlist             ; // @"af_add_to_wishlist"
        static const std::string AFEventCompleteRegistration      ; // @"af_complete_registration"
        static const std::string AFEventTutorial_completion       ; // @"af_tutorial_completion"
        static const std::string AFEventInitiatedCheckout         ; // @"af_initiated_checkout"
        static const std::string AFEventPurchase                  ; // @"af_purchase"
        static const std::string AFEventRate                      ; // @"af_rate"
        static const std::string AFEventSearch                    ; // @"af_search"
        static const std::string AFEventSpentCredits              ; // @"af_spent_credits"
        static const std::string AFEventAchievementUnlocked       ; // @"af_achievement_unlocked"
        static const std::string AFEventContentView               ; // @"af_content_view"
        static const std::string AFEventListView                  ; // @"af_list_view"
        static const std::string AFEventTravelBooking             ; // @"af_travel_booking"
        static const std::string AFEventShare                     ; // @"af_share"
        static const std::string AFEventInvite                    ; // @"af_invite"
        static const std::string AFEventLogin                     ; // @"af_login"
        static const std::string AFEventReEngage                  ; // @"af_re_engage"
        static const std::string AFEventUpdate                    ; // @"af_update"
        static const std::string AFEventOpenedFromPushNotification  ; // @"af_opened_from_push_notification"
        static const std::string AFEventLocation                  ; // @"af_location_coordinates"
        static const std::string AFEventCustomerSegment           ; // @"af_customer_segment"

        static const std::string AFEventSubscribe                 ; // @"af_subscribe"
        static const std::string AFEventStartTrial                ; // @"af_start_trial"
        static const std::string AFEventAdClick                   ; // @"af_ad_click"
        static const std::string AFEventAdView                    ; // @"af_ad_view"

        // In app event parameter names
        static const std::string AFEventParamContent                 ; // @"af_content"
        static const std::string AFEventParamAchievenmentId          ; // @"af_achievement_id"
        static const std::string AFEventParamLevel                   ; // @"af_level"
        static const std::string AFEventParamScore                   ; // @"af_score"
        static const std::string AFEventParamSuccess                 ; // @"af_success"
        static const std::string AFEventParamPrice                   ; // @"af_price"
        static const std::string AFEventParamContentType             ; // @"af_content_type"
        static const std::string AFEventParamContentId               ; // @"af_content_id"
        static const std::string AFEventParamContentList             ; // @"af_content_list"
        static const std::string AFEventParamCurrency                ; // @"af_currency"
        static const std::string AFEventParamQuantity                ; // @"af_quantity"
        static const std::string AFEventParamRegistrationMethod      ; // @"af_registration_method"
        static const std::string AFEventParamPaymentInfoAvailable    ; // @"af_payment_info_available"
        static const std::string AFEventParamMaxRatingValue          ; // @"af_max_rating_value"
        static const std::string AFEventParamRatingValue             ; // @"af_rating_value"
        static const std::string AFEventParamSearchString            ; // @"af_search_string"
        static const std::string AFEventParamDateA                   ; // @"af_date_a"
        static const std::string AFEventParamDateB                   ; // @"af_date_b"
        static const std::string AFEventParamDestinationA            ; // @"af_destination_a"
        static const std::string AFEventParamDestinationB            ; // @"af_destination_b"
        static const std::string AFEventParamDescription             ; // @"af_description"
        static const std::string AFEventParamClass                   ; // @"af_class"
        static const std::string AFEventParamEventStart              ; // @"af_event_start"
        static const std::string AFEventParamEventEnd                ; // @"af_event_end"
        static const std::string AFEventParamLat                     ; // @"af_lat"
        static const std::string AFEventParamLong                    ; // @"af_long"
        static const std::string AFEventParamCustomerUserId          ; // @"af_customer_user_id"
        static const std::string AFEventParamValidated               ; // @"af_validated"
        static const std::string AFEventParamRevenue                 ; // @"af_revenue"
        static const std::string AFEventProjectedParamRevenue        ; // @"af_projected_revenue"
        static const std::string AFEventParamReceiptId               ; // @"af_receipt_id"
        static const std::string AFEventParamTutorialId              ; // @"af_tutorial_id"
        static const std::string AFEventParamVirtualCurrencyName     ; // @"af_virtual_currency_name"
        static const std::string AFEventParamDeepLink                ; // @"af_deep_link"
        static const std::string AFEventParamOldVersion              ; // @"af_old_version"
        static const std::string AFEventParamNewVersion              ; // @"af_new_version"
        static const std::string AFEventParamReviewText              ; // @"af_review_text"
        static const std::string AFEventParamCouponCode              ; // @"af_coupon_code"
        static const std::string AFEventParamOrderId                 ; // @"af_order_id"
        static const std::string AFEventParam1                       ; // @"af_param_1"
        static const std::string AFEventParam2                       ; // @"af_param_2"
        static const std::string AFEventParam3                       ; // @"af_param_3"
        static const std::string AFEventParam4                       ; // @"af_param_4"
        static const std::string AFEventParam5                       ; // @"af_param_5"
        static const std::string AFEventParam6                       ; // @"af_param_6"
        static const std::string AFEventParam7                       ; // @"af_param_7"
        static const std::string AFEventParam8                       ; // @"af_param_8"
        static const std::string AFEventParam9                       ; // @"af_param_9"
        static const std::string AFEventParam10                      ; // @"af_param_10"

        static const std::string AFEventParamDepartingDepartureDate   ; // @"af_departing_departure_date"
        static const std::string AFEventParamReturningDepartureDate   ; // @"af_returning_departure_date"
        static const std::string AFEventParamDestinationList          ; // @"af_destination_list"  //array of string
        static const std::string AFEventParamCity                     ; // @"af_city"
        static const std::string AFEventParamRegion                   ; // @"af_region"
        static const std::string AFEventParamCountry                  ; // @"af_country"

        static const std::string AFEventParamDepartingArrivalDate     ; // @"af_departing_arrival_date"
        static const std::string AFEventParamReturningArrivalDate     ; // @"af_returning_arrival_date"
        static const std::string AFEventParamSuggestedDestinations    ; // @"af_suggested_destinations" //array of string
        static const std::string AFEventParamTravelStart              ; // @"af_travel_start"
        static const std::string AFEventParamTravelEnd                ; // @"af_travel_end"
        static const std::string AFEventParamNumAdults                ; // @"af_num_adults"
        static const std::string AFEventParamNumChildren              ; // @"af_num_children"
        static const std::string AFEventParamNumInfants               ; // @"af_num_infants"
        static const std::string AFEventParamSuggestedHotels          ; // @"af_suggested_hotels" //array of string

        static const std::string AFEventParamUserScore                ; // @"af_user_score"
        static const std::string AFEventParamHotelScore               ; // @"af_hotel_score"
        static const std::string AFEventParamPurchaseCurrency         ; // @"af_purchase_currency"

        static const std::string AFEventParamPreferredStarRatings     ; // @"af_preferred_star_ratings"    //array of int (basically a tuple (min,max) but we'll use array of int and instruct the developer to use two values)

        static const std::string AFEventParamPreferredPriceRange      ; // @"af_preferred_price_range"    //array of int (basically a tuple (min,max) but we'll use array of int and instruct the developer to use two values)
        static const std::string AFEventParamPreferredNeighborhoods   ; // @"af_preferred_neighborhoods" //array of string
        static const std::string AFEventParamPreferredNumStops        ; // @"af_preferred_num_stops"

        static const std::string AFEventParamAdRevenueAdType               ; // @"af_adrev_ad_type"
        static const std::string AFEventParamAdRevenueNetworkName          ; // @"af_adrev_network_name"
        static const std::string AFEventParamAdRevenuePlacementId          ; // @"af_adrev_placement_id"
        static const std::string AFEventParamAdRevenueAdSize               ; // @"af_adrev_ad_size"
        static const std::string AFEventParamAdRevenueMediatedNetworkName  ; // @"af_adrev_mediated_network_name"
        
    };

}
}
}
