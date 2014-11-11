//for plugin type
var Plugin_type = {
    kPluginAds:1,
    kPluginAnalytics:2,
    kPluginIAP:3,
    kPluginShare:4,
    kPluginUser:5,
    kPluginSocial:6,
    kPluginPush:7
};	//plugin type

//for ads
var AdsResultCode = {
    kAdsReceived:0,           	/**< enum the callback: the ad is received is at center. */
    kAdsShown:1,                  /**< enum the callback: the advertisement dismissed. */
    kAdsDismissed:2,             /**< enum the callback: the advertisement dismissed. */
    kPointsSpendSucceed:3,       /**< enum the callback: the points spend succeed. */
    kPointsSpendFailed:4,        /**< enum the callback: the points spend failed. */
    kNetworkError:5,              /**< enum the callback of Network error at center. */
    kUnknownError:6,              /**< enum the callback of Unknown error. */
    kOfferWallOnPointsChanged:7   /**< enum the callback of Changing the point of offerwall. */
};	//ads result code

var AdsPos = {
    kPosCenter:0,			/**< enum the toolbar is at center. */
    kPosTop:1,				/**< enum the toolbar is at top. */
    kPosTopLeft:2,			/**< enum the toolbar is at topleft. */
    kPosTopRight:3,			/**< enum the toolbar is at topright. */
    kPosBottom:4,				/**< enum the toolbar is at bottom. */
    kPosBottomLeft:5,			/**< enum the toolbar is at bottomleft. */
    kPosBottomRight:6 		/**< enum the toolbar is at bottomright. */
};	//ads pos

var AdsType = {
	AD_TYPE_BANNER:0,		/**< enum value is banner ads . */
	AD_TYPE_FULLSCREEN:1,	/**< enum value is fullscreen ads . */
	AD_TYPE_MOREAPP:2,		/**< enum value is moreapp ads . */
	AD_TYPE_OFFERWALL:3	/**< enum value is offerwall ads . */
};	//ads type

//for pay result code
var PayResultCode = {
    kPaySuccess:0,		/**< enum value is callback of succeeding in paying . */
    kPayFail:1,			/**< enum value is callback of failing to pay . */
    kPayCancel:2,		/**< enum value is callback of canceling to pay . */
    kPayNetworkError:3,	/**< enum value is callback of network error . */
    kPayProductionInforIncomplete:4,	/**< enum value is callback of incompleting info . */
	kPayInitSuccess:5,	/**< enum value is callback of succeeding in initing sdk . */
	kPayInitFail:6,		/**< enum value is callback of failing to init sdk . */
	kPayNowPaying:7 	/**< enum value is callback of paying now . */
};

// for push action result code
var PushActionResultCode = {
	kPushReceiveMessage:0	/**value is callback of Receiving Message . */
};

// for share result code
var ShareResultCode = {
    kShareSuccess:0,	/**< enum value is callback of failing to sharing . */
    kShareFail:1,		/**< enum value is callback of failing to share . */
    kShareCancel:2,		/**< enum value is callback of canceling to share . */
    kShareNetworkError:3	/**< enum value is callback of network error . */
};

//for social ret code
var SocialRetCode = {
	// code for leaderboard feature
	kScoreSubmitSucceed:1,		/**< enum value is callback of succeeding in submiting. */
    kScoreSubmitfail:2,			/**< enum value is callback of failing to submit . */
    // code for achievement feature
    kAchUnlockSucceed:3,		/**< enum value is callback of succeeding in unlocking. */
    kAchUnlockFail:4,			/**< enum value is callback of failing to  unlock. */
    kSocialSignInSucceed:5,		/**< enum value is callback of succeeding to login. */
    kSocialSignInFail:6,		/**< enum value is callback of failing to  login. */
    kSocialSignOutSucceed:7,	/**< enum value is callback of succeeding to login. */
    kSocialSignOutFail:8		/**< enum value is callback of failing to  login. */
};

// for user action result code
var UserActionResultCode = {
	kInitSuccess:0,		/**< enum value is callback of succeeding in initing sdk. */
	kInitFail:1,		/**< enum  value is callback of failing to init sdk. */
    kLoginSuccess:2,	/**< enum value is callback of succeeding in login.*/
    kLoginNetworkError:3,	/**< enum value is callback of network error*/
    kLoginNoNeed:4,		/**< enum value is callback of no need login.*/
    kLoginFail:5,		/**< enum value is callback of failing to login. */
    kLoginCancel:6,		/**< enum value is callback of canceling to login. */
    kLogoutSuccess:7,	/**< enum value is callback of succeeding in logout. */
    kLogoutFail:8,		/**< enum value is callback of failing to logout. */
    kPlatformEnter:9,	/**< enum value is callback after enter platform. */
    kPlatformBack:10,	/**< enum value is callback after exit antiAddiction. */
    kPausePage:11,		/**< enum value is callback after exit pause page. */
    kExitPage:12,		/**< enum value is callback after exit exit page. */
    kAntiAddictionQuery:13,	/**< enum value is callback after querying antiAddiction. */
    kRealNameRegister:14,	/**< enum value is callback after registering realname. */
    kAccountSwitchSuccess:15,	/**< enum alue is callback of succeeding in switching account. */
    kAccountSwitchFail:16	/**< enum value is callback of failing to switch account. */
};

//for toolBar place
var ToolBarPlace = {
    kToolBarTopLeft:1,		/**< enum the toolbar is at topleft. */
    kToolBarTopRight:2,		/**< enum the toolbar is at topright. */
    kToolBarMidLeft:3,		/**< enum the toolbar is at midleft. */
    kToolBarMidRight:4,		/**< enum the toolbar is at midright. */
    kToolBarBottomLeft:5,	/**< enum the toolbar is at bottomleft. */
    kToolBarBottomRight:6	/**< enum the toolbar is at bottomright. */
};

