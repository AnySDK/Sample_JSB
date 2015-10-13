#ifndef __autoanysdkbindings_h__
#define __autoanysdkbindings_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_anysdk_framework_PluginProtocol_class;
extern JSObject *jsb_anysdk_framework_PluginProtocol_prototype;

bool js_autoanysdkbindings_PluginProtocol_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_autoanysdkbindings_PluginProtocol_finalize(JSContext *cx, JSObject *obj);
void js_register_autoanysdkbindings_PluginProtocol(JSContext *cx, JSObject *global);
void register_all_autoanysdkbindings(JSContext* cx, JSObject* obj);
bool js_autoanysdkbindings_PluginProtocol_isFunctionSupported(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_PluginProtocol_getPluginName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_PluginProtocol_getPluginVersion(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_PluginProtocol_setPluginName(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_PluginProtocol_getSDKVersion(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_PluginProtocol_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_anysdk_framework_PluginFactory_class;
extern JSObject *jsb_anysdk_framework_PluginFactory_prototype;

bool js_autoanysdkbindings_PluginFactory_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_autoanysdkbindings_PluginFactory_finalize(JSContext *cx, JSObject *obj);
void js_register_autoanysdkbindings_PluginFactory(JSContext *cx, JSObject *global);
void register_all_autoanysdkbindings(JSContext* cx, JSObject* obj);
bool js_autoanysdkbindings_PluginFactory_purgeFactory(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_PluginFactory_getInstance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_anysdk_framework_PluginManager_class;
extern JSObject *jsb_anysdk_framework_PluginManager_prototype;

bool js_autoanysdkbindings_PluginManager_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_autoanysdkbindings_PluginManager_finalize(JSContext *cx, JSObject *obj);
void js_register_autoanysdkbindings_PluginManager(JSContext *cx, JSObject *global);
void register_all_autoanysdkbindings(JSContext* cx, JSObject* obj);
bool js_autoanysdkbindings_PluginManager_unloadPlugin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_PluginManager_loadPlugin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_PluginManager_end(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_PluginManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_anysdk_framework_ProtocolIAP_class;
extern JSObject *jsb_anysdk_framework_ProtocolIAP_prototype;

bool js_autoanysdkbindings_ProtocolIAP_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_autoanysdkbindings_ProtocolIAP_finalize(JSContext *cx, JSObject *obj);
void js_register_autoanysdkbindings_ProtocolIAP(JSContext *cx, JSObject *global);
void register_all_autoanysdkbindings(JSContext* cx, JSObject* obj);
bool js_autoanysdkbindings_ProtocolIAP_getPluginId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_ProtocolIAP_getOrderId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_ProtocolIAP_resetPayState(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_anysdk_framework_ProtocolAnalytics_class;
extern JSObject *jsb_anysdk_framework_ProtocolAnalytics_prototype;

bool js_autoanysdkbindings_ProtocolAnalytics_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_autoanysdkbindings_ProtocolAnalytics_finalize(JSContext *cx, JSObject *obj);
void js_register_autoanysdkbindings_ProtocolAnalytics(JSContext *cx, JSObject *global);
void register_all_autoanysdkbindings(JSContext* cx, JSObject* obj);
bool js_autoanysdkbindings_ProtocolAnalytics_logTimedEventBegin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_ProtocolAnalytics_logError(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_ProtocolAnalytics_setCaptureUncaughtException(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_ProtocolAnalytics_setSessionContinueMillis(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_ProtocolAnalytics_startSession(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_ProtocolAnalytics_stopSession(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_ProtocolAnalytics_logTimedEventEnd(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_anysdk_framework_ProtocolAds_class;
extern JSObject *jsb_anysdk_framework_ProtocolAds_prototype;

bool js_autoanysdkbindings_ProtocolAds_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_autoanysdkbindings_ProtocolAds_finalize(JSContext *cx, JSObject *obj);
void js_register_autoanysdkbindings_ProtocolAds(JSContext *cx, JSObject *global);
void register_all_autoanysdkbindings(JSContext* cx, JSObject* obj);
bool js_autoanysdkbindings_ProtocolAds_showAds(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_ProtocolAds_hideAds(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_ProtocolAds_preloadAds(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_ProtocolAds_queryPoints(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_ProtocolAds_spendPoints(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_ProtocolAds_isAdTypeSupported(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_anysdk_framework_ProtocolSocial_class;
extern JSObject *jsb_anysdk_framework_ProtocolSocial_prototype;

bool js_autoanysdkbindings_ProtocolSocial_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_autoanysdkbindings_ProtocolSocial_finalize(JSContext *cx, JSObject *obj);
void js_register_autoanysdkbindings_ProtocolSocial(JSContext *cx, JSObject *global);
void register_all_autoanysdkbindings(JSContext* cx, JSObject* obj);
bool js_autoanysdkbindings_ProtocolSocial_showLeaderboard(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_ProtocolSocial_signOut(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_ProtocolSocial_showAchievements(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_ProtocolSocial_signIn(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_ProtocolSocial_submitScore(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_anysdk_framework_ProtocolUser_class;
extern JSObject *jsb_anysdk_framework_ProtocolUser_prototype;

bool js_autoanysdkbindings_ProtocolUser_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_autoanysdkbindings_ProtocolUser_finalize(JSContext *cx, JSObject *obj);
void js_register_autoanysdkbindings_ProtocolUser(JSContext *cx, JSObject *global);
void register_all_autoanysdkbindings(JSContext* cx, JSObject* obj);
bool js_autoanysdkbindings_ProtocolUser_isLogined(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_ProtocolUser_getUserID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_ProtocolUser_login(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_ProtocolUser_getPluginId(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_anysdk_framework_ProtocolPush_class;
extern JSObject *jsb_anysdk_framework_ProtocolPush_prototype;

bool js_autoanysdkbindings_ProtocolPush_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_autoanysdkbindings_ProtocolPush_finalize(JSContext *cx, JSObject *obj);
void js_register_autoanysdkbindings_ProtocolPush(JSContext *cx, JSObject *global);
void register_all_autoanysdkbindings(JSContext* cx, JSObject* obj);
bool js_autoanysdkbindings_ProtocolPush_startPush(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_ProtocolPush_closePush(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_ProtocolPush_delAlias(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_ProtocolPush_setAlias(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_anysdk_framework_ProtocolCrash_class;
extern JSObject *jsb_anysdk_framework_ProtocolCrash_prototype;

bool js_autoanysdkbindings_ProtocolCrash_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_autoanysdkbindings_ProtocolCrash_finalize(JSContext *cx, JSObject *obj);
void js_register_autoanysdkbindings_ProtocolCrash(JSContext *cx, JSObject *global);
void register_all_autoanysdkbindings(JSContext* cx, JSObject* obj);
bool js_autoanysdkbindings_ProtocolCrash_setUserIdentifier(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_ProtocolCrash_reportException(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_ProtocolCrash_leaveBreadcrumb(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_anysdk_framework_ProtocolREC_class;
extern JSObject *jsb_anysdk_framework_ProtocolREC_prototype;

bool js_autoanysdkbindings_ProtocolREC_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_autoanysdkbindings_ProtocolREC_finalize(JSContext *cx, JSObject *obj);
void js_register_autoanysdkbindings_ProtocolREC(JSContext *cx, JSObject *global);
void register_all_autoanysdkbindings(JSContext* cx, JSObject* obj);
bool js_autoanysdkbindings_ProtocolREC_startRecording(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_ProtocolREC_stopRecording(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_anysdk_framework_ProtocolCustom_class;
extern JSObject *jsb_anysdk_framework_ProtocolCustom_prototype;

bool js_autoanysdkbindings_ProtocolCustom_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_autoanysdkbindings_ProtocolCustom_finalize(JSContext *cx, JSObject *obj);
void js_register_autoanysdkbindings_ProtocolCustom(JSContext *cx, JSObject *global);
void register_all_autoanysdkbindings(JSContext* cx, JSObject* obj);


extern JSClass  *jsb_anysdk_framework_AgentManager_class;
extern JSObject *jsb_anysdk_framework_AgentManager_prototype;

bool js_autoanysdkbindings_AgentManager_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_autoanysdkbindings_AgentManager_finalize(JSContext *cx, JSObject *obj);
void js_register_autoanysdkbindings_AgentManager(JSContext *cx, JSObject *global);
void register_all_autoanysdkbindings(JSContext* cx, JSObject* obj);
bool js_autoanysdkbindings_AgentManager_getSocialPlugin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_AgentManager_unloadALLPlugin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_AgentManager_loadALLPlugin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_AgentManager_unloadAllPlugins(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_AgentManager_loadAllPlugins(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_AgentManager_getCustomParam(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_AgentManager_getUserPlugin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_AgentManager_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_AgentManager_getAdsPlugin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_AgentManager_getPushPlugin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_AgentManager_getSharePlugin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_AgentManager_getAnalyticsPlugin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_AgentManager_getCrashPlugin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_AgentManager_getCustomPlugin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_AgentManager_getRECPlugin(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_AgentManager_getChannelId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_AgentManager_end(JSContext *cx, uint32_t argc, jsval *vp);
bool js_autoanysdkbindings_AgentManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp);
#endif

