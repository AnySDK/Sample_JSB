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
    kAdsReceived:10000,           	/**< enum the callback: the ad is received is at center. */
    kAdsShown:10001,                  /**< enum the callback: the advertisement dismissed. */
    kAdsDismissed:10002,             /**< enum the callback: the advertisement dismissed. */
    kPointsSpendSucceed:10003,       /**< enum the callback: the points spend succeed. */
    kPointsSpendFailed:10004,        /**< enum the callback: the points spend failed. */
    kNetworkError:10005,              /**< enum the callback of Network error at center. */
    kUnknownError:10006,              /**< enum the callback of Unknown error. */
    kOfferWallOnPointsChanged:10007   /**< enum the callback of Changing the point of offerwall. */
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
    kPaySuccess:30000,		/**< enum value is callback of succeeding in paying . */
    kPayFail:30001,			/**< enum value is callback of failing to pay . */
    kPayCancel:30002,		/**< enum value is callback of canceling to pay . */
    kPayNetworkError:30003,	/**< enum value is callback of network error . */
    kPayProductionInforIncomplete:30004,	/**< enum value is callback of incompleting info . */
	kPayInitSuccess:30005,	/**< enum value is callback of succeeding in initing sdk . */
	kPayInitFail:30006,		/**< enum value is callback of failing to init sdk . */
	kPayNowPaying:30007 	/**< enum value is callback of paying now . */
};

// for push action result code
var PushActionResultCode = {
	kPushReceiveMessage:70000	/**value is callback of Receiving Message . */
};

// for share result code
var ShareResultCode = {
    kShareSuccess:40000,	/**< enum value is callback of failing to sharing . */
    kShareFail:40001,		/**< enum value is callback of failing to share . */
    kShareCancel:40002,		/**< enum value is callback of canceling to share . */
    kShareNetworkError:40003	/**< enum value is callback of network error . */
};

//for social ret code
var SocialRetCode = {
	// code for leaderboard feature
	kScoreSubmitSucceed:60001,		/**< enum value is callback of succeeding in submiting. */
    kScoreSubmitfail:60002,			/**< enum value is callback of failing to submit . */
    // code for achievement feature
    kAchUnlockSucceed:60003,		/**< enum value is callback of succeeding in unlocking. */
    kAchUnlockFail:60004,			/**< enum value is callback of failing to  unlock. */
    kSocialSignInSucceed:60005,		/**< enum value is callback of succeeding to login. */
    kSocialSignInFail:60006,		/**< enum value is callback of failing to  login. */
    kSocialSignOutSucceed:60007,	/**< enum value is callback of succeeding to login. */
    kSocialSignOutFail:60008		/**< enum value is callback of failing to  login. */
};

// for user action result code
var UserActionResultCode = {
	kInitSuccess:50000,		/**< enum value is callback of succeeding in initing sdk. */
	kInitFail:50001,		/**< enum  value is callback of failing to init sdk. */
    kLoginSuccess:50002,	/**< enum value is callback of succeeding in login.*/
    kLoginNetworkError:50003,	/**< enum value is callback of network error*/
    kLoginNoNeed:50004,		/**< enum value is callback of no need login.*/
    kLoginFail:50005,		/**< enum value is callback of failing to login. */
    kLoginCancel:50006,		/**< enum value is callback of canceling to login. */
    kLogoutSuccess:50007,	/**< enum value is callback of succeeding in logout. */
    kLogoutFail:50008,		/**< enum value is callback of failing to logout. */
    kPlatformEnter:50009,	/**< enum value is callback after enter platform. */
    kPlatformBack:50010,	/**< enum value is callback after exit antiAddiction. */
    kPausePage:50011,		/**< enum value is callback after exit pause page. */
    kExitPage:50012,		/**< enum value is callback after exit exit page. */
    kAntiAddictionQuery:50013,	/**< enum value is callback after querying antiAddiction. */
    kRealNameRegister:50014,	/**< enum value is callback after registering realname. */
    kAccountSwitchSuccess:50015,	/**< enum alue is callback of succeeding in switching account. */
    kAccountSwitchFail:50016,	/**< enum value is callback of failing to switch account. */
    kOpenShop:50017            /**< enum value is callback of open the shop. */
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

//for analytics
var AccountType = {
    ANONYMOUS:0,
    REGISTED:1,
    SINA_WEIBO:2,
    TENCENT_WEIBO:3,
    QQ:4,
    QQ_WEIBO:5,
    ND91:6
};

var AccountOperate = {
    LOGIN:0,
    LOGOUT:1,
    REGISTER:2
};

var AccountGender = {
    MALE:0,
    FEMALE:1,
    UNKNOWN:2
};

var TaskType = {
    GUIDE_LINE:0,
    MAIN_LINE:1,
    BRANCH_LINE:2,
    DAILY:3,
    ACTIVITY:4,
    OTHER:5
};
//end analytics