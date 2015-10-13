#include "autoanysdkbindings.hpp"
#include "cocos2d_specifics.hpp"
#include "AgentManager.h"
#include "PluginProtocol.h"
#include "ProtocolPush.h"
#include "PluginFactory.h"
#include "ProtocolAds.h"
#include "PluginManager.h"
#include "ProtocolAnalytics.h"
#include "ProtocolSocial.h"
#include "ProtocolIAP.h"
#include "ProtocolUser.h"
#include "ProtocolCustom.h"
#include "ProtocolREC.h"
#include "ProtocolCrash.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    JSObject* global = ScriptingCore::getInstance()->getGlobalObject();
	isNewValid = JS_GetProperty(cx, global, "initializing", &initializing) && JSVAL_TO_BOOLEAN(initializing);
	if (isNewValid)
	{
		TypeTest<T> t;
		js_type_class_t *typeClass = nullptr;
		std::string typeName = t.s_name();
		auto typeMapIter = _js_global_type_map.find(typeName);
		CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
		typeClass = typeMapIter->second;
		CCASSERT(typeClass, "The value is null.");

		JSObject *_tmp = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));
		return true;
	}

    JS_ReportError(cx, "Don't use `new cc.XXX`, please use `cc.XXX.create` instead! ");
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	return false;
}

static bool js_is_native_obj(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
	vp.set(BOOLEAN_TO_JSVAL(true));
	return true;	
}
JSClass  *jsb_anysdk_framework_PluginProtocol_class;
JSObject *jsb_anysdk_framework_PluginProtocol_prototype;

bool js_autoanysdkbindings_PluginProtocol_getPluginName(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginProtocol* cobj = (anysdk::framework::PluginProtocol *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_PluginProtocol_getPluginName : Invalid Native Object");
	if (argc == 0) {
		const char* ret = cobj->getPluginName();
		jsval jsret = JSVAL_NULL;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_PluginProtocol_getPluginName : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool js_autoanysdkbindings_PluginProtocol_isFunctionSupported(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::PluginProtocol* cobj = (anysdk::framework::PluginProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_PluginProtocol_isFunctionSupported : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_PluginProtocol_isFunctionSupported : Error processing arguments");
        bool ret = cobj->isFunctionSupported(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }
    
    JS_ReportError(cx, "js_autoanysdkbindings_PluginProtocol_isFunctionSupported : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool js_autoanysdkbindings_PluginProtocol_getPluginVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginProtocol* cobj = (anysdk::framework::PluginProtocol *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_PluginProtocol_getPluginVersion : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getPluginVersion();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_PluginProtocol_getPluginVersion : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autoanysdkbindings_PluginProtocol_setPluginName(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginProtocol* cobj = (anysdk::framework::PluginProtocol *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_PluginProtocol_setPluginName : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_PluginProtocol_setPluginName : Error processing arguments");
		cobj->setPluginName(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_PluginProtocol_setPluginName : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_autoanysdkbindings_PluginProtocol_getSDKVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginProtocol* cobj = (anysdk::framework::PluginProtocol *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_PluginProtocol_getSDKVersion : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getSDKVersion();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_PluginProtocol_getSDKVersion : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autoanysdkbindings_PluginProtocol_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("\n********** \n setDebugMode was deprecated.\n**********");
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginProtocol* cobj = (anysdk::framework::PluginProtocol *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_PluginProtocol_setDebugMode : Invalid Native Object");
	if (argc == 1) {
		bool arg0;
		arg0 = JS::ToBoolean(JS::RootedValue(cx, argv[0]));
		JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_PluginProtocol_setDebugMode : Error processing arguments");
		cobj->setDebugMode(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_PluginProtocol_setDebugMode : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}


void js_anysdk_framework_PluginProtocol_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PluginProtocol)", obj);
}

void js_register_autoanysdkbindings_PluginProtocol(JSContext *cx, JSObject *global) {
	jsb_anysdk_framework_PluginProtocol_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_anysdk_framework_PluginProtocol_class->name = "PluginProtocol";
	jsb_anysdk_framework_PluginProtocol_class->addProperty = JS_PropertyStub;
	jsb_anysdk_framework_PluginProtocol_class->delProperty = JS_DeletePropertyStub;
	jsb_anysdk_framework_PluginProtocol_class->getProperty = JS_PropertyStub;
	jsb_anysdk_framework_PluginProtocol_class->setProperty = JS_StrictPropertyStub;
	jsb_anysdk_framework_PluginProtocol_class->enumerate = JS_EnumerateStub;
	jsb_anysdk_framework_PluginProtocol_class->resolve = JS_ResolveStub;
	jsb_anysdk_framework_PluginProtocol_class->convert = JS_ConvertStub;
	jsb_anysdk_framework_PluginProtocol_class->finalize = js_anysdk_framework_PluginProtocol_finalize;
	jsb_anysdk_framework_PluginProtocol_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
        JS_FN("isFunctionSupported", js_autoanysdkbindings_PluginProtocol_isFunctionSupported, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPluginName", js_autoanysdkbindings_PluginProtocol_getPluginName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPluginVersion", js_autoanysdkbindings_PluginProtocol_getPluginVersion, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setPluginName", js_autoanysdkbindings_PluginProtocol_setPluginName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getSDKVersion", js_autoanysdkbindings_PluginProtocol_getSDKVersion, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setDebugMode", js_autoanysdkbindings_PluginProtocol_setDebugMode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_anysdk_framework_PluginProtocol_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_anysdk_framework_PluginProtocol_class,
		dummy_constructor<anysdk::framework::PluginProtocol>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "PluginProtocol", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<anysdk::framework::PluginProtocol> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_anysdk_framework_PluginProtocol_class;
		p->proto = jsb_anysdk_framework_PluginProtocol_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_anysdk_framework_PluginFactory_class;
JSObject *jsb_anysdk_framework_PluginFactory_prototype;

bool js_autoanysdkbindings_PluginFactory_purgeFactory(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		anysdk::framework::PluginFactory::purgeFactory();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	JS_ReportError(cx, "js_autoanysdkbindings_PluginFactory_purgeFactory : wrong number of arguments");
	return false;
}

bool js_autoanysdkbindings_PluginFactory_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		anysdk::framework::PluginFactory* ret = anysdk::framework::PluginFactory::getInstance();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<anysdk::framework::PluginFactory>(cx, (anysdk::framework::PluginFactory*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_autoanysdkbindings_PluginFactory_getInstance : wrong number of arguments");
	return false;
}



void js_anysdk_framework_PluginFactory_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PluginFactory)", obj);
}

void js_register_autoanysdkbindings_PluginFactory(JSContext *cx, JSObject *global) {
	jsb_anysdk_framework_PluginFactory_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_anysdk_framework_PluginFactory_class->name = "PluginFactory";
	jsb_anysdk_framework_PluginFactory_class->addProperty = JS_PropertyStub;
	jsb_anysdk_framework_PluginFactory_class->delProperty = JS_DeletePropertyStub;
	jsb_anysdk_framework_PluginFactory_class->getProperty = JS_PropertyStub;
	jsb_anysdk_framework_PluginFactory_class->setProperty = JS_StrictPropertyStub;
	jsb_anysdk_framework_PluginFactory_class->enumerate = JS_EnumerateStub;
	jsb_anysdk_framework_PluginFactory_class->resolve = JS_ResolveStub;
	jsb_anysdk_framework_PluginFactory_class->convert = JS_ConvertStub;
	jsb_anysdk_framework_PluginFactory_class->finalize = js_anysdk_framework_PluginFactory_finalize;
	jsb_anysdk_framework_PluginFactory_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("purgeFactory", js_autoanysdkbindings_PluginFactory_purgeFactory, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getInstance", js_autoanysdkbindings_PluginFactory_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_anysdk_framework_PluginFactory_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_anysdk_framework_PluginFactory_class,
		dummy_constructor<anysdk::framework::PluginFactory>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "PluginFactory", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<anysdk::framework::PluginFactory> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_anysdk_framework_PluginFactory_class;
		p->proto = jsb_anysdk_framework_PluginFactory_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_anysdk_framework_PluginManager_class;
JSObject *jsb_anysdk_framework_PluginManager_prototype;

bool js_autoanysdkbindings_PluginManager_unloadPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginManager* cobj = (anysdk::framework::PluginManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_PluginManager_unloadPlugin : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_PluginManager_unloadPlugin : Error processing arguments");
		cobj->unloadPlugin(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	if (argc == 2) {
		const char* arg0;
		int arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_PluginManager_unloadPlugin : Error processing arguments");
		cobj->unloadPlugin(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_PluginManager_unloadPlugin : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_autoanysdkbindings_PluginManager_loadPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginManager* cobj = (anysdk::framework::PluginManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_PluginManager_loadPlugin : Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		int arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_PluginManager_loadPlugin : Error processing arguments");
		anysdk::framework::PluginProtocol* ret = cobj->loadPlugin(arg0, arg1);
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<anysdk::framework::PluginProtocol>(cx, (anysdk::framework::PluginProtocol*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_PluginManager_loadPlugin : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_autoanysdkbindings_PluginManager_end(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		anysdk::framework::PluginManager::end();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	JS_ReportError(cx, "js_autoanysdkbindings_PluginManager_end : wrong number of arguments");
	return false;
}

bool js_autoanysdkbindings_PluginManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		anysdk::framework::PluginManager* ret = anysdk::framework::PluginManager::getInstance();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<anysdk::framework::PluginManager>(cx, (anysdk::framework::PluginManager*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_autoanysdkbindings_PluginManager_getInstance : wrong number of arguments");
	return false;
}



void js_anysdk_framework_PluginManager_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PluginManager)", obj);
}

void js_register_autoanysdkbindings_PluginManager(JSContext *cx, JSObject *global) {
	jsb_anysdk_framework_PluginManager_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_anysdk_framework_PluginManager_class->name = "PluginManager";
	jsb_anysdk_framework_PluginManager_class->addProperty = JS_PropertyStub;
	jsb_anysdk_framework_PluginManager_class->delProperty = JS_DeletePropertyStub;
	jsb_anysdk_framework_PluginManager_class->getProperty = JS_PropertyStub;
	jsb_anysdk_framework_PluginManager_class->setProperty = JS_StrictPropertyStub;
	jsb_anysdk_framework_PluginManager_class->enumerate = JS_EnumerateStub;
	jsb_anysdk_framework_PluginManager_class->resolve = JS_ResolveStub;
	jsb_anysdk_framework_PluginManager_class->convert = JS_ConvertStub;
	jsb_anysdk_framework_PluginManager_class->finalize = js_anysdk_framework_PluginManager_finalize;
	jsb_anysdk_framework_PluginManager_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("unloadPlugin", js_autoanysdkbindings_PluginManager_unloadPlugin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("loadPlugin", js_autoanysdkbindings_PluginManager_loadPlugin, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("end", js_autoanysdkbindings_PluginManager_end, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getInstance", js_autoanysdkbindings_PluginManager_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_anysdk_framework_PluginManager_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_anysdk_framework_PluginManager_class,
		dummy_constructor<anysdk::framework::PluginManager>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "PluginManager", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<anysdk::framework::PluginManager> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_anysdk_framework_PluginManager_class;
		p->proto = jsb_anysdk_framework_PluginManager_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_anysdk_framework_ProtocolIAP_class;
JSObject *jsb_anysdk_framework_ProtocolIAP_prototype;

bool js_autoanysdkbindings_ProtocolIAP_getPluginId(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolIAP* cobj = (anysdk::framework::ProtocolIAP *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolIAP_getPluginId : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getPluginId();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolIAP_getPluginId : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autoanysdkbindings_ProtocolIAP_getOrderId(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolIAP* cobj = (anysdk::framework::ProtocolIAP *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolIAP_getOrderId : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getOrderId();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolIAP_getOrderId : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autoanysdkbindings_ProtocolIAP_resetPayState(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		anysdk::framework::ProtocolIAP::resetPayState();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolIAP_resetPayState : wrong number of arguments");
	return false;
}


extern JSObject *jsb_anysdk_framework_PluginProtocol_prototype;

void js_anysdk_framework_ProtocolIAP_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolIAP)", obj);
}

void js_register_autoanysdkbindings_ProtocolIAP(JSContext *cx, JSObject *global) {
	jsb_anysdk_framework_ProtocolIAP_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_anysdk_framework_ProtocolIAP_class->name = "ProtocolIAP";
	jsb_anysdk_framework_ProtocolIAP_class->addProperty = JS_PropertyStub;
	jsb_anysdk_framework_ProtocolIAP_class->delProperty = JS_DeletePropertyStub;
	jsb_anysdk_framework_ProtocolIAP_class->getProperty = JS_PropertyStub;
	jsb_anysdk_framework_ProtocolIAP_class->setProperty = JS_StrictPropertyStub;
	jsb_anysdk_framework_ProtocolIAP_class->enumerate = JS_EnumerateStub;
	jsb_anysdk_framework_ProtocolIAP_class->resolve = JS_ResolveStub;
	jsb_anysdk_framework_ProtocolIAP_class->convert = JS_ConvertStub;
	jsb_anysdk_framework_ProtocolIAP_class->finalize = js_anysdk_framework_ProtocolIAP_finalize;
	jsb_anysdk_framework_ProtocolIAP_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getPluginId", js_autoanysdkbindings_ProtocolIAP_getPluginId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getOrderId", js_autoanysdkbindings_ProtocolIAP_getOrderId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("resetPayState", js_autoanysdkbindings_ProtocolIAP_resetPayState, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_anysdk_framework_ProtocolIAP_prototype = JS_InitClass(
		cx, global,
		jsb_anysdk_framework_PluginProtocol_prototype,
		jsb_anysdk_framework_ProtocolIAP_class,
		dummy_constructor<anysdk::framework::ProtocolIAP>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "ProtocolIAP", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<anysdk::framework::ProtocolIAP> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_anysdk_framework_ProtocolIAP_class;
		p->proto = jsb_anysdk_framework_ProtocolIAP_prototype;
		p->parentProto = jsb_anysdk_framework_PluginProtocol_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_anysdk_framework_ProtocolAnalytics_class;
JSObject *jsb_anysdk_framework_ProtocolAnalytics_prototype;

bool js_autoanysdkbindings_ProtocolAnalytics_logTimedEventBegin(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolAnalytics* cobj = (anysdk::framework::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolAnalytics_logTimedEventBegin : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_ProtocolAnalytics_logTimedEventBegin : Error processing arguments");
		cobj->logTimedEventBegin(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolAnalytics_logTimedEventBegin : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_autoanysdkbindings_ProtocolAnalytics_logError(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolAnalytics* cobj = (anysdk::framework::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolAnalytics_logError : Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		const char* arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_ProtocolAnalytics_logError : Error processing arguments");
		cobj->logError(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolAnalytics_logError : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}
bool js_autoanysdkbindings_ProtocolAnalytics_setCaptureUncaughtException(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolAnalytics* cobj = (anysdk::framework::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolAnalytics_setCaptureUncaughtException : Invalid Native Object");
	if (argc == 1) {
		bool arg0;
		arg0 = JS::ToBoolean(JS::RootedValue(cx, argv[0]));
		JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_ProtocolAnalytics_setCaptureUncaughtException : Error processing arguments");
		cobj->setCaptureUncaughtException(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolAnalytics_setCaptureUncaughtException : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_autoanysdkbindings_ProtocolAnalytics_setSessionContinueMillis(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolAnalytics* cobj = (anysdk::framework::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolAnalytics_setSessionContinueMillis : Invalid Native Object");
	if (argc == 1) {
		long arg0;
		ok &= jsval_to_long(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_ProtocolAnalytics_setSessionContinueMillis : Error processing arguments");
		cobj->setSessionContinueMillis(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolAnalytics_setSessionContinueMillis : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_autoanysdkbindings_ProtocolAnalytics_startSession(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolAnalytics* cobj = (anysdk::framework::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolAnalytics_startSession : Invalid Native Object");
	if (argc == 0) {
		cobj->startSession();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolAnalytics_startSession : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autoanysdkbindings_ProtocolAnalytics_stopSession(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolAnalytics* cobj = (anysdk::framework::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolAnalytics_stopSession : Invalid Native Object");
	if (argc == 0) {
		cobj->stopSession();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolAnalytics_stopSession : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool js_autoanysdkbindings_ProtocolAnalytics_logTimedEventEnd(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolAnalytics* cobj = (anysdk::framework::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolAnalytics_logTimedEventEnd : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_ProtocolAnalytics_logTimedEventEnd : Error processing arguments");
		cobj->logTimedEventEnd(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolAnalytics_logTimedEventEnd : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}

extern JSObject *jsb_anysdk_framework_PluginProtocol_prototype;

void js_anysdk_framework_ProtocolAnalytics_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolAnalytics)", obj);
}

void js_register_autoanysdkbindings_ProtocolAnalytics(JSContext *cx, JSObject *global) {
	jsb_anysdk_framework_ProtocolAnalytics_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_anysdk_framework_ProtocolAnalytics_class->name = "ProtocolAnalytics";
	jsb_anysdk_framework_ProtocolAnalytics_class->addProperty = JS_PropertyStub;
	jsb_anysdk_framework_ProtocolAnalytics_class->delProperty = JS_DeletePropertyStub;
	jsb_anysdk_framework_ProtocolAnalytics_class->getProperty = JS_PropertyStub;
	jsb_anysdk_framework_ProtocolAnalytics_class->setProperty = JS_StrictPropertyStub;
	jsb_anysdk_framework_ProtocolAnalytics_class->enumerate = JS_EnumerateStub;
	jsb_anysdk_framework_ProtocolAnalytics_class->resolve = JS_ResolveStub;
	jsb_anysdk_framework_ProtocolAnalytics_class->convert = JS_ConvertStub;
	jsb_anysdk_framework_ProtocolAnalytics_class->finalize = js_anysdk_framework_ProtocolAnalytics_finalize;
	jsb_anysdk_framework_ProtocolAnalytics_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("logTimedEventBegin", js_autoanysdkbindings_ProtocolAnalytics_logTimedEventBegin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("logError", js_autoanysdkbindings_ProtocolAnalytics_logError, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setCaptureUncaughtException", js_autoanysdkbindings_ProtocolAnalytics_setCaptureUncaughtException, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setSessionContinueMillis", js_autoanysdkbindings_ProtocolAnalytics_setSessionContinueMillis, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("startSession", js_autoanysdkbindings_ProtocolAnalytics_startSession, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("stopSession", js_autoanysdkbindings_ProtocolAnalytics_stopSession, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("logTimedEventEnd", js_autoanysdkbindings_ProtocolAnalytics_logTimedEventEnd, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_anysdk_framework_ProtocolAnalytics_prototype = JS_InitClass(
		cx, global,
		jsb_anysdk_framework_PluginProtocol_prototype,
		jsb_anysdk_framework_ProtocolAnalytics_class,
		dummy_constructor<anysdk::framework::ProtocolAnalytics>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "ProtocolAnalytics", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<anysdk::framework::ProtocolAnalytics> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_anysdk_framework_ProtocolAnalytics_class;
		p->proto = jsb_anysdk_framework_ProtocolAnalytics_prototype;
		p->parentProto = jsb_anysdk_framework_PluginProtocol_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_anysdk_framework_ProtocolAds_class;
JSObject *jsb_anysdk_framework_ProtocolAds_prototype;

bool js_autoanysdkbindings_ProtocolAds_showAds(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolAds* cobj = (anysdk::framework::ProtocolAds *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolAds_showAds : Invalid Native Object");
	if (argc == 1) {
		anysdk::framework::AdsType arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_ProtocolAds_showAds : Error processing arguments");
		cobj->showAds(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	else if (argc == 2) {
		anysdk::framework::AdsType arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_ProtocolAds_showAds : Error processing arguments");
		int arg1;
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_ProtocolAds_showAds : Error processing arguments");
		cobj->showAds(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolAds_showAds : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_autoanysdkbindings_ProtocolAds_hideAds(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolAds* cobj = (anysdk::framework::ProtocolAds *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolAds_hideAds : Invalid Native Object");
	if (argc == 1) {
		anysdk::framework::AdsType arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_ProtocolAds_hideAds : Error processing arguments");
		cobj->hideAds(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	else if (argc == 2) {
		anysdk::framework::AdsType arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_ProtocolAds_hideAds : Error processing arguments");
		int arg1;
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_ProtocolAds_hideAds : Error processing arguments");
		cobj->hideAds(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolAds_hideAds : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_autoanysdkbindings_ProtocolAds_preloadAds(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolAds* cobj = (anysdk::framework::ProtocolAds *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolAds_preloadAds : Invalid Native Object");
	if (argc == 1) {
		anysdk::framework::AdsType arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_ProtocolAds_preloadAds : Error processing arguments");
		cobj->preloadAds(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	else if (argc == 2) {
		anysdk::framework::AdsType arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_ProtocolAds_preloadAds : Error processing arguments");
		int arg1;
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_ProtocolAds_preloadAds : Error processing arguments");
		cobj->preloadAds(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolAds_preloadAds : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_autoanysdkbindings_ProtocolAds_queryPoints(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolAds* cobj = (anysdk::framework::ProtocolAds *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolAds_queryPoints : Invalid Native Object");
	if (argc == 0) {
		double ret = cobj->queryPoints();
		jsval jsret = JSVAL_NULL;
		jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolAds_queryPoints : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autoanysdkbindings_ProtocolAds_spendPoints(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolAds* cobj = (anysdk::framework::ProtocolAds *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolAds_spendPoints : Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_ProtocolAds_spendPoints : Error processing arguments");
		cobj->spendPoints(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolAds_spendPoints : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_autoanysdkbindings_ProtocolAds_isAdTypeSupported(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolAds* cobj = (anysdk::framework::ProtocolAds *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolAds_isAdTypeSupported : Invalid Native Object");
	if (argc == 1) {
		anysdk::framework::AdsType arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_ProtocolAds_isAdTypeSupported : Error processing arguments");
		bool ret = cobj->isAdTypeSupported(arg0);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolAds_isAdTypeSupported : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}

extern JSObject *jsb_anysdk_framework_PluginProtocol_prototype;

void js_anysdk_framework_ProtocolAds_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolAds)", obj);
}

void js_register_autoanysdkbindings_ProtocolAds(JSContext *cx, JSObject *global) {
	jsb_anysdk_framework_ProtocolAds_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_anysdk_framework_ProtocolAds_class->name = "ProtocolAds";
	jsb_anysdk_framework_ProtocolAds_class->addProperty = JS_PropertyStub;
	jsb_anysdk_framework_ProtocolAds_class->delProperty = JS_DeletePropertyStub;
	jsb_anysdk_framework_ProtocolAds_class->getProperty = JS_PropertyStub;
	jsb_anysdk_framework_ProtocolAds_class->setProperty = JS_StrictPropertyStub;
	jsb_anysdk_framework_ProtocolAds_class->enumerate = JS_EnumerateStub;
	jsb_anysdk_framework_ProtocolAds_class->resolve = JS_ResolveStub;
	jsb_anysdk_framework_ProtocolAds_class->convert = JS_ConvertStub;
	jsb_anysdk_framework_ProtocolAds_class->finalize = js_anysdk_framework_ProtocolAds_finalize;
	jsb_anysdk_framework_ProtocolAds_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("showAds", js_autoanysdkbindings_ProtocolAds_showAds, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("hideAds", js_autoanysdkbindings_ProtocolAds_hideAds, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("preloadAds", js_autoanysdkbindings_ProtocolAds_preloadAds, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("queryPoints", js_autoanysdkbindings_ProtocolAds_queryPoints, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("spendPoints", js_autoanysdkbindings_ProtocolAds_spendPoints, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isAdTypeSupported", js_autoanysdkbindings_ProtocolAds_isAdTypeSupported, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_anysdk_framework_ProtocolAds_prototype = JS_InitClass(
		cx, global,
		jsb_anysdk_framework_PluginProtocol_prototype,
		jsb_anysdk_framework_ProtocolAds_class,
		dummy_constructor<anysdk::framework::ProtocolAds>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "ProtocolAds", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<anysdk::framework::ProtocolAds> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_anysdk_framework_ProtocolAds_class;
		p->proto = jsb_anysdk_framework_ProtocolAds_prototype;
		p->parentProto = jsb_anysdk_framework_PluginProtocol_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_anysdk_framework_ProtocolSocial_class;
JSObject *jsb_anysdk_framework_ProtocolSocial_prototype;

bool js_autoanysdkbindings_ProtocolSocial_showLeaderboard(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolSocial* cobj = (anysdk::framework::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolSocial_showLeaderboard : Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_ProtocolSocial_showLeaderboard : Error processing arguments");
		cobj->showLeaderboard(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolSocial_showLeaderboard : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_autoanysdkbindings_ProtocolSocial_signOut(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolSocial* cobj = (anysdk::framework::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolSocial_signOut : Invalid Native Object");
	if (argc == 0) {
		cobj->signOut();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolSocial_signOut : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autoanysdkbindings_ProtocolSocial_showAchievements(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolSocial* cobj = (anysdk::framework::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolSocial_showAchievements : Invalid Native Object");
	if (argc == 0) {
		cobj->showAchievements();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolSocial_showAchievements : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autoanysdkbindings_ProtocolSocial_signIn(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolSocial* cobj = (anysdk::framework::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolSocial_signIn : Invalid Native Object");
	if (argc == 0) {
		cobj->signIn();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolSocial_signIn : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autoanysdkbindings_ProtocolSocial_submitScore(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolSocial* cobj = (anysdk::framework::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolSocial_submitScore : Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		long arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_long(cx, argv[1], &arg1);
		JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_ProtocolSocial_submitScore : Error processing arguments");
		cobj->submitScore(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolSocial_submitScore : wrong number of arguments: %d, was expecting %d", argc, 2);
	return false;
}

extern JSObject *jsb_anysdk_framework_PluginProtocol_prototype;

void js_anysdk_framework_ProtocolSocial_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolSocial)", obj);
}

void js_register_autoanysdkbindings_ProtocolSocial(JSContext *cx, JSObject *global) {
	jsb_anysdk_framework_ProtocolSocial_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_anysdk_framework_ProtocolSocial_class->name = "ProtocolSocial";
	jsb_anysdk_framework_ProtocolSocial_class->addProperty = JS_PropertyStub;
	jsb_anysdk_framework_ProtocolSocial_class->delProperty = JS_DeletePropertyStub;
	jsb_anysdk_framework_ProtocolSocial_class->getProperty = JS_PropertyStub;
	jsb_anysdk_framework_ProtocolSocial_class->setProperty = JS_StrictPropertyStub;
	jsb_anysdk_framework_ProtocolSocial_class->enumerate = JS_EnumerateStub;
	jsb_anysdk_framework_ProtocolSocial_class->resolve = JS_ResolveStub;
	jsb_anysdk_framework_ProtocolSocial_class->convert = JS_ConvertStub;
	jsb_anysdk_framework_ProtocolSocial_class->finalize = js_anysdk_framework_ProtocolSocial_finalize;
	jsb_anysdk_framework_ProtocolSocial_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("showLeaderboard", js_autoanysdkbindings_ProtocolSocial_showLeaderboard, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("signOut", js_autoanysdkbindings_ProtocolSocial_signOut, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("showAchievements", js_autoanysdkbindings_ProtocolSocial_showAchievements, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("signIn", js_autoanysdkbindings_ProtocolSocial_signIn, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("submitScore", js_autoanysdkbindings_ProtocolSocial_submitScore, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_anysdk_framework_ProtocolSocial_prototype = JS_InitClass(
		cx, global,
		jsb_anysdk_framework_PluginProtocol_prototype,
		jsb_anysdk_framework_ProtocolSocial_class,
		dummy_constructor<anysdk::framework::ProtocolSocial>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "ProtocolSocial", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<anysdk::framework::ProtocolSocial> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_anysdk_framework_ProtocolSocial_class;
		p->proto = jsb_anysdk_framework_ProtocolSocial_prototype;
		p->parentProto = jsb_anysdk_framework_PluginProtocol_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_anysdk_framework_ProtocolUser_class;
JSObject *jsb_anysdk_framework_ProtocolUser_prototype;

bool js_autoanysdkbindings_ProtocolUser_isLogined(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolUser* cobj = (anysdk::framework::ProtocolUser *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolUser_isLogined : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->isLogined();
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolUser_isLogined : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autoanysdkbindings_ProtocolUser_getUserID(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolUser* cobj = (anysdk::framework::ProtocolUser *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolUser_getUserID : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getUserID();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolUser_getUserID : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool js_autoanysdkbindings_ProtocolUser_login(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;

	JSObject *obj = NULL;
	anysdk::framework::ProtocolUser* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (anysdk::framework::ProtocolUser *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolUser_login : Invalid Native Object");
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = true; break; }
			cobj->login(arg0);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return true;
		}
		else if(argc == 2){
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			std::string arg1;
			ok &= jsval_to_std_string(cx, argv[1], &arg1);
			if (!ok) { ok = true; break; }
			cobj->login(arg0, arg1);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return true;
		}
	} while(0);

	do {
		if (argc == 0) {
			cobj->login();
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return true;
		}
	} while(0);

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolUser_login : wrong number of arguments");
	return false;
}
bool js_autoanysdkbindings_ProtocolUser_getPluginId(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolUser* cobj = (anysdk::framework::ProtocolUser *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolUser_getPluginId : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getPluginId();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolUser_getPluginId : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

extern JSObject *jsb_anysdk_framework_PluginProtocol_prototype;

void js_anysdk_framework_ProtocolUser_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolUser)", obj);
}

void js_register_autoanysdkbindings_ProtocolUser(JSContext *cx, JSObject *global) {
	jsb_anysdk_framework_ProtocolUser_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_anysdk_framework_ProtocolUser_class->name = "ProtocolUser";
	jsb_anysdk_framework_ProtocolUser_class->addProperty = JS_PropertyStub;
	jsb_anysdk_framework_ProtocolUser_class->delProperty = JS_DeletePropertyStub;
	jsb_anysdk_framework_ProtocolUser_class->getProperty = JS_PropertyStub;
	jsb_anysdk_framework_ProtocolUser_class->setProperty = JS_StrictPropertyStub;
	jsb_anysdk_framework_ProtocolUser_class->enumerate = JS_EnumerateStub;
	jsb_anysdk_framework_ProtocolUser_class->resolve = JS_ResolveStub;
	jsb_anysdk_framework_ProtocolUser_class->convert = JS_ConvertStub;
	jsb_anysdk_framework_ProtocolUser_class->finalize = js_anysdk_framework_ProtocolUser_finalize;
	jsb_anysdk_framework_ProtocolUser_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("isLogined", js_autoanysdkbindings_ProtocolUser_isLogined, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getUserID", js_autoanysdkbindings_ProtocolUser_getUserID, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("login", js_autoanysdkbindings_ProtocolUser_login, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPluginId", js_autoanysdkbindings_ProtocolUser_getPluginId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_anysdk_framework_ProtocolUser_prototype = JS_InitClass(
		cx, global,
		jsb_anysdk_framework_PluginProtocol_prototype,
		jsb_anysdk_framework_ProtocolUser_class,
		dummy_constructor<anysdk::framework::ProtocolUser>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "ProtocolUser", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<anysdk::framework::ProtocolUser> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_anysdk_framework_ProtocolUser_class;
		p->proto = jsb_anysdk_framework_ProtocolUser_prototype;
		p->parentProto = jsb_anysdk_framework_PluginProtocol_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_anysdk_framework_ProtocolPush_class;
JSObject *jsb_anysdk_framework_ProtocolPush_prototype;

bool js_autoanysdkbindings_ProtocolPush_startPush(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolPush* cobj = (anysdk::framework::ProtocolPush *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolPush_startPush : Invalid Native Object");
	if (argc == 0) {
		cobj->startPush();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolPush_startPush : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autoanysdkbindings_ProtocolPush_closePush(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolPush* cobj = (anysdk::framework::ProtocolPush *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolPush_closePush : Invalid Native Object");
	if (argc == 0) {
		cobj->closePush();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolPush_closePush : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autoanysdkbindings_ProtocolPush_delAlias(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolPush* cobj = (anysdk::framework::ProtocolPush *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolPush_delAlias : Invalid Native Object");
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_ProtocolPush_delAlias : Error processing arguments");
		cobj->delAlias(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolPush_delAlias : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_autoanysdkbindings_ProtocolPush_setAlias(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolPush* cobj = (anysdk::framework::ProtocolPush *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolPush_setAlias : Invalid Native Object");
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_ProtocolPush_setAlias : Error processing arguments");
		cobj->setAlias(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_ProtocolPush_setAlias : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}

extern JSObject *jsb_anysdk_framework_PluginProtocol_prototype;

void js_anysdk_framework_ProtocolPush_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolPush)", obj);
}

void js_register_autoanysdkbindings_ProtocolPush(JSContext *cx, JSObject *global) {
	jsb_anysdk_framework_ProtocolPush_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_anysdk_framework_ProtocolPush_class->name = "ProtocolPush";
	jsb_anysdk_framework_ProtocolPush_class->addProperty = JS_PropertyStub;
	jsb_anysdk_framework_ProtocolPush_class->delProperty = JS_DeletePropertyStub;
	jsb_anysdk_framework_ProtocolPush_class->getProperty = JS_PropertyStub;
	jsb_anysdk_framework_ProtocolPush_class->setProperty = JS_StrictPropertyStub;
	jsb_anysdk_framework_ProtocolPush_class->enumerate = JS_EnumerateStub;
	jsb_anysdk_framework_ProtocolPush_class->resolve = JS_ResolveStub;
	jsb_anysdk_framework_ProtocolPush_class->convert = JS_ConvertStub;
	jsb_anysdk_framework_ProtocolPush_class->finalize = js_anysdk_framework_ProtocolPush_finalize;
	jsb_anysdk_framework_ProtocolPush_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("startPush", js_autoanysdkbindings_ProtocolPush_startPush, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("closePush", js_autoanysdkbindings_ProtocolPush_closePush, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("delAlias", js_autoanysdkbindings_ProtocolPush_delAlias, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setAlias", js_autoanysdkbindings_ProtocolPush_setAlias, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_anysdk_framework_ProtocolPush_prototype = JS_InitClass(
		cx, global,
		jsb_anysdk_framework_PluginProtocol_prototype,
		jsb_anysdk_framework_ProtocolPush_class,
		dummy_constructor<anysdk::framework::ProtocolPush>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "ProtocolPush", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<anysdk::framework::ProtocolPush> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_anysdk_framework_ProtocolPush_class;
		p->proto = jsb_anysdk_framework_ProtocolPush_prototype;
		p->parentProto = jsb_anysdk_framework_PluginProtocol_prototype;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

JSClass  *jsb_anysdk_framework_ProtocolCrash_class;
JSObject *jsb_anysdk_framework_ProtocolCrash_prototype;

bool js_autoanysdkbindings_ProtocolCrash_setUserIdentifier(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolCrash* cobj = (anysdk::framework::ProtocolCrash *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolCrash_setUserIdentifier : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_ProtocolCrash_setUserIdentifier : Error processing arguments");
        cobj->setUserIdentifier(arg0.c_str());
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }
    
    JS_ReportError(cx, "js_autoanysdkbindings_ProtocolCrash_setUserIdentifier : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_autoanysdkbindings_ProtocolCrash_reportException(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolCrash* cobj = (anysdk::framework::ProtocolCrash *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolCrash_reportException : Invalid Native Object");
    if (argc == 2) {
        const char* arg0;
        const char* arg1;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_ProtocolCrash_reportException : Error processing arguments");
        cobj->reportException(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }
    
    JS_ReportError(cx, "js_autoanysdkbindings_ProtocolCrash_reportException : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_autoanysdkbindings_ProtocolCrash_leaveBreadcrumb(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolCrash* cobj = (anysdk::framework::ProtocolCrash *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolCrash_leaveBreadcrumb : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_ProtocolCrash_leaveBreadcrumb : Error processing arguments");
        cobj->leaveBreadcrumb (arg0.c_str());
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }
    
    JS_ReportError(cx, "js_autoanysdkbindings_ProtocolCrash_leaveBreadcrumb : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
extern JSObject *jsb_anysdk_framework_PluginProtocol_prototype;

void js_anysdk_framework_ProtocolCrash_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolCrash)", obj);
}

void js_register_autoanysdkbindings_ProtocolCrash(JSContext *cx, JSObject *global) {
    jsb_anysdk_framework_ProtocolCrash_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_anysdk_framework_ProtocolCrash_class->name = "ProtocolCrash";
    jsb_anysdk_framework_ProtocolCrash_class->addProperty = JS_PropertyStub;
    jsb_anysdk_framework_ProtocolCrash_class->delProperty = JS_DeletePropertyStub;
    jsb_anysdk_framework_ProtocolCrash_class->getProperty = JS_PropertyStub;
    jsb_anysdk_framework_ProtocolCrash_class->setProperty = JS_StrictPropertyStub;
    jsb_anysdk_framework_ProtocolCrash_class->enumerate = JS_EnumerateStub;
    jsb_anysdk_framework_ProtocolCrash_class->resolve = JS_ResolveStub;
    jsb_anysdk_framework_ProtocolCrash_class->convert = JS_ConvertStub;
    jsb_anysdk_framework_ProtocolCrash_class->finalize = js_anysdk_framework_ProtocolCrash_finalize;
    jsb_anysdk_framework_ProtocolCrash_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };
    
    static JSFunctionSpec funcs[] = {
        JS_FN("setUserIdentifier", js_autoanysdkbindings_ProtocolCrash_setUserIdentifier, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("leaveBreadcrumb", js_autoanysdkbindings_ProtocolCrash_leaveBreadcrumb, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("reportException", js_autoanysdkbindings_ProtocolCrash_reportException, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    
    JSFunctionSpec *st_funcs = NULL;
    
    jsb_anysdk_framework_ProtocolCrash_prototype = JS_InitClass(
                                                               cx, global,
                                                               jsb_anysdk_framework_PluginProtocol_prototype,
                                                               jsb_anysdk_framework_ProtocolCrash_class,
                                                               dummy_constructor<anysdk::framework::ProtocolCrash>, 0, // no constructor
                                                               properties,
                                                               funcs,
                                                               NULL, // no static properties
                                                               st_funcs);
    // make the class enumerable in the registered namespace
    //	bool found;
    //FIXME: Removed in Firefox v27	
    //	JS_SetPropertyAttributes(cx, global, "ProtocolCrash", JSPROP_ENUMERATE | JSPROP_READONLY, &found);
    
    // add the proto and JSClass to the type->js info hash table
    TypeTest<anysdk::framework::ProtocolCrash> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_anysdk_framework_ProtocolCrash_class;
        p->proto = jsb_anysdk_framework_ProtocolCrash_prototype;
        p->parentProto = jsb_anysdk_framework_PluginProtocol_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_anysdk_framework_ProtocolREC_class;
JSObject *jsb_anysdk_framework_ProtocolREC_prototype;

bool js_autoanysdkbindings_ProtocolREC_startRecording(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolREC* cobj = (anysdk::framework::ProtocolREC *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolREC_startRecording : Invalid Native Object");
    if (argc == 0) {
        cobj->startRecording();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }
    
    JS_ReportError(cx, "js_autoanysdkbindings_ProtocolREC_startRecording : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_autoanysdkbindings_ProtocolREC_stopRecording(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolREC* cobj = (anysdk::framework::ProtocolREC *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_ProtocolREC_stopRecording : Invalid Native Object");
    if (argc == 0) {
        cobj->stopRecording();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }
    
    JS_ReportError(cx, "js_autoanysdkbindings_ProtocolREC_stopRecording : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
extern JSObject *jsb_anysdk_framework_PluginProtocol_prototype;

void js_anysdk_framework_ProtocolREC_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolREC)", obj);
}

void js_register_autoanysdkbindings_ProtocolREC(JSContext *cx, JSObject *global) {
    jsb_anysdk_framework_ProtocolREC_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_anysdk_framework_ProtocolREC_class->name = "ProtocolREC";
    jsb_anysdk_framework_ProtocolREC_class->addProperty = JS_PropertyStub;
    jsb_anysdk_framework_ProtocolREC_class->delProperty = JS_DeletePropertyStub;
    jsb_anysdk_framework_ProtocolREC_class->getProperty = JS_PropertyStub;
    jsb_anysdk_framework_ProtocolREC_class->setProperty = JS_StrictPropertyStub;
    jsb_anysdk_framework_ProtocolREC_class->enumerate = JS_EnumerateStub;
    jsb_anysdk_framework_ProtocolREC_class->resolve = JS_ResolveStub;
    jsb_anysdk_framework_ProtocolREC_class->convert = JS_ConvertStub;
    jsb_anysdk_framework_ProtocolREC_class->finalize = js_anysdk_framework_ProtocolREC_finalize;
    jsb_anysdk_framework_ProtocolREC_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };
    
    static JSFunctionSpec funcs[] = {
        JS_FN("startRecording", js_autoanysdkbindings_ProtocolREC_startRecording, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stopRecording", js_autoanysdkbindings_ProtocolREC_stopRecording, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    
    JSFunctionSpec *st_funcs = NULL;
    
    jsb_anysdk_framework_ProtocolREC_prototype = JS_InitClass(
                                                               cx, global,
                                                               jsb_anysdk_framework_PluginProtocol_prototype,
                                                               jsb_anysdk_framework_ProtocolREC_class,
                                                               dummy_constructor<anysdk::framework::ProtocolREC>, 0, // no constructor
                                                               properties,
                                                               funcs,
                                                               NULL, // no static properties
                                                               st_funcs);
    // make the class enumerable in the registered namespace
    //	bool found;
    //FIXME: Removed in Firefox v27
    //	JS_SetPropertyAttributes(cx, global, "ProtocolREC", JSPROP_ENUMERATE | JSPROP_READONLY, &found);
    
    // add the proto and JSClass to the type->js info hash table
    TypeTest<anysdk::framework::ProtocolREC> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_anysdk_framework_ProtocolREC_class;
        p->proto = jsb_anysdk_framework_ProtocolREC_prototype;
        p->parentProto = jsb_anysdk_framework_PluginProtocol_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_anysdk_framework_ProtocolCustom_class;
JSObject *jsb_anysdk_framework_ProtocolCustom_prototype;

extern JSObject *jsb_anysdk_framework_PluginProtocol_prototype;

void js_anysdk_framework_ProtocolCustom_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolCustom)", obj);
}

void js_register_autoanysdkbindings_ProtocolCustom(JSContext *cx, JSObject *global) {
    jsb_anysdk_framework_ProtocolCustom_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_anysdk_framework_ProtocolCustom_class->name = "ProtocolCustom";
    jsb_anysdk_framework_ProtocolCustom_class->addProperty = JS_PropertyStub;
    jsb_anysdk_framework_ProtocolCustom_class->delProperty = JS_DeletePropertyStub;
    jsb_anysdk_framework_ProtocolCustom_class->getProperty = JS_PropertyStub;
    jsb_anysdk_framework_ProtocolCustom_class->setProperty = JS_StrictPropertyStub;
    jsb_anysdk_framework_ProtocolCustom_class->enumerate = JS_EnumerateStub;
    jsb_anysdk_framework_ProtocolCustom_class->resolve = JS_ResolveStub;
    jsb_anysdk_framework_ProtocolCustom_class->convert = JS_ConvertStub;
    jsb_anysdk_framework_ProtocolCustom_class->finalize = js_anysdk_framework_ProtocolCustom_finalize;
    jsb_anysdk_framework_ProtocolCustom_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };
    
    static JSFunctionSpec funcs[] = {
        JS_FN("startCustomording", js_autoanysdkbindings_ProtocolCrash_setUserIdentifier, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stopCustomording", js_autoanysdkbindings_ProtocolCrash_leaveBreadcrumb, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    
    JSFunctionSpec *st_funcs = NULL;
    
    jsb_anysdk_framework_ProtocolCustom_prototype = JS_InitClass(
                                                              cx, global,
                                                              jsb_anysdk_framework_PluginProtocol_prototype,
                                                              jsb_anysdk_framework_ProtocolCustom_class,
                                                              dummy_constructor<anysdk::framework::ProtocolCustom>, 0, // no constructor
                                                              properties,
                                                              funcs,
                                                              NULL, // no static properties
                                                              st_funcs);
    // make the class enumerable in the registered namespace
    //	bool found;
    //FIXME: Removed in Firefox v27
    //	JS_SetPropertyAttributes(cx, global, "ProtocolCustom", JSPROP_ENUMERATE | JSPROP_READONLY, &found);
    
    // add the proto and JSClass to the type->js info hash table
    TypeTest<anysdk::framework::ProtocolCustom> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_anysdk_framework_ProtocolCustom_class;
        p->proto = jsb_anysdk_framework_ProtocolCustom_prototype;
        p->parentProto = jsb_anysdk_framework_PluginProtocol_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}


JSClass  *jsb_anysdk_framework_AgentManager_class;
JSObject *jsb_anysdk_framework_AgentManager_prototype;

bool js_autoanysdkbindings_AgentManager_getSocialPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_AgentManager_getSocialPlugin : Invalid Native Object");
	if (argc == 0) {
		anysdk::framework::ProtocolSocial* ret = cobj->getSocialPlugin();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<anysdk::framework::ProtocolSocial>(cx, (anysdk::framework::ProtocolSocial*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_AgentManager_getSocialPlugin : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autoanysdkbindings_AgentManager_unloadALLPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("\n********** \nunloadALLPlugin was deprecated, please use unloadAllPlugins instead.\n**********");
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_AgentManager_unloadALLPlugin : Invalid Native Object");
	if (argc == 0) {
		cobj->unloadALLPlugin();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_AgentManager_unloadALLPlugin : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autoanysdkbindings_AgentManager_loadALLPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("\n********** \nloadALLPlugin was deprecated, please use loadAllPlugins instead.\n**********");
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_AgentManager_loadALLPlugin : Invalid Native Object");
	if (argc == 0) {
		cobj->loadALLPlugin();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_AgentManager_loadALLPlugin : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool js_autoanysdkbindings_AgentManager_unloadAllPlugins(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_AgentManager_unloadAllPlugins : Invalid Native Object");
    if (argc == 0) {
        cobj->unloadAllPlugins();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }
    
    JS_ReportError(cx, "js_autoanysdkbindings_AgentManager_unloadAllPlugins : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_autoanysdkbindings_AgentManager_loadAllPlugins(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_AgentManager_loadAllPlugins : Invalid Native Object");
    if (argc == 0) {
        cobj->loadAllPlugins();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }
    
    JS_ReportError(cx, "js_autoanysdkbindings_AgentManager_loadAllPlugins : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

bool js_autoanysdkbindings_AgentManager_getCustomParam(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_AgentManager_getCustomParam : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getCustomParam();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_AgentManager_getCustomParam : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autoanysdkbindings_AgentManager_getUserPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_AgentManager_getUserPlugin : Invalid Native Object");
	if (argc == 0) {
		anysdk::framework::ProtocolUser* ret = cobj->getUserPlugin();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<anysdk::framework::ProtocolUser>(cx, (anysdk::framework::ProtocolUser*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_AgentManager_getUserPlugin : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool js_autoanysdkbindings_AgentManager_getCrashPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_AgentManager_getCrashPlugin : Invalid Native Object");
    if (argc == 0) {
        anysdk::framework::ProtocolCrash* ret = cobj->getCrashPlugin();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<anysdk::framework::ProtocolCrash>(cx, (anysdk::framework::ProtocolCrash*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }
    
    JS_ReportError(cx, "js_autoanysdkbindings_AgentManager_getCrashPlugin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

bool js_autoanysdkbindings_AgentManager_getRECPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_AgentManager_getRECPlugin : Invalid Native Object");
    if (argc == 0) {
        anysdk::framework::ProtocolREC* ret = cobj->getRECPlugin();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<anysdk::framework::ProtocolREC>(cx, (anysdk::framework::ProtocolREC*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }
    
    JS_ReportError(cx, "js_autoanysdkbindings_AgentManager_getRECPlugin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

bool js_autoanysdkbindings_AgentManager_getCustomPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_AgentManager_getCustomPlugin : Invalid Native Object");
    if (argc == 0) {
        anysdk::framework::ProtocolCustom* ret = cobj->getCustomPlugin();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<anysdk::framework::ProtocolCustom>(cx, (anysdk::framework::ProtocolCustom*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }
    
    JS_ReportError(cx, "js_autoanysdkbindings_AgentManager_getCustomPlugin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}


bool js_autoanysdkbindings_AgentManager_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_AgentManager_init : Invalid Native Object");
	if (argc == 4) {
		std::string arg0;
		std::string arg1;
		std::string arg2;
		std::string arg3;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		ok &= jsval_to_std_string(cx, argv[1], &arg1);
		ok &= jsval_to_std_string(cx, argv[2], &arg2);
		ok &= jsval_to_std_string(cx, argv[3], &arg3);
		JSB_PRECONDITION2(ok, cx, false, "js_autoanysdkbindings_AgentManager_init : Error processing arguments");
		cobj->init(arg0, arg1, arg2, arg3);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_AgentManager_init : wrong number of arguments: %d, was expecting %d", argc, 4);
	return false;
}
bool js_autoanysdkbindings_AgentManager_getAdsPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_AgentManager_getAdsPlugin : Invalid Native Object");
	if (argc == 0) {
		anysdk::framework::ProtocolAds* ret = cobj->getAdsPlugin();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<anysdk::framework::ProtocolAds>(cx, (anysdk::framework::ProtocolAds*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_AgentManager_getAdsPlugin : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autoanysdkbindings_AgentManager_getPushPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_AgentManager_getPushPlugin : Invalid Native Object");
	if (argc == 0) {
		anysdk::framework::ProtocolPush* ret = cobj->getPushPlugin();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<anysdk::framework::ProtocolPush>(cx, (anysdk::framework::ProtocolPush*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_AgentManager_getPushPlugin : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autoanysdkbindings_AgentManager_getSharePlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_AgentManager_getSharePlugin : Invalid Native Object");
	if (argc == 0) {
		anysdk::framework::ProtocolShare* ret = cobj->getSharePlugin();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<anysdk::framework::ProtocolShare>(cx, (anysdk::framework::ProtocolShare*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_AgentManager_getSharePlugin : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autoanysdkbindings_AgentManager_getAnalyticsPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_AgentManager_getAnalyticsPlugin : Invalid Native Object");
	if (argc == 0) {
		anysdk::framework::ProtocolAnalytics* ret = cobj->getAnalyticsPlugin();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				js_proxy_t *jsProxy = js_get_or_create_proxy<anysdk::framework::ProtocolAnalytics>(cx, (anysdk::framework::ProtocolAnalytics*)ret);
				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_AgentManager_getAnalyticsPlugin : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autoanysdkbindings_AgentManager_getChannelId(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_autoanysdkbindings_AgentManager_getChannelId : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getChannelId();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "js_autoanysdkbindings_AgentManager_getChannelId : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autoanysdkbindings_AgentManager_setIsAnaylticsEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 1) {
		jsval *argv = JS_ARGV(cx, vp);
		bool arg = JSVAL_TO_BOOLEAN( argv[0] );
		cobj->setIsAnaylticsEnabled(arg);
		return true;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autoanysdkbindings_AgentManager_isAnaylticsEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->isAnaylticsEnabled();
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
bool js_autoanysdkbindings_AgentManager_end(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		anysdk::framework::AgentManager::end();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return true;
	}
	JS_ReportError(cx, "js_autoanysdkbindings_AgentManager_end : wrong number of arguments");
	return false;
}

bool js_autoanysdkbindings_AgentManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		anysdk::framework::AgentManager* ret = anysdk::framework::AgentManager::getInstance();
		jsval jsret = JSVAL_NULL;
		do {
		if (ret) {
			js_proxy_t *jsProxy = js_get_or_create_proxy<anysdk::framework::AgentManager>(cx, (anysdk::framework::AgentManager*)ret);
			jsret = OBJECT_TO_JSVAL(jsProxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}
	JS_ReportError(cx, "js_autoanysdkbindings_AgentManager_getInstance : wrong number of arguments");
	return false;
}



void js_anysdk_framework_AgentManager_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (AgentManager)", obj);
}

void js_register_autoanysdkbindings_AgentManager(JSContext *cx, JSObject *global) {
	jsb_anysdk_framework_AgentManager_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_anysdk_framework_AgentManager_class->name = "AgentManager";
	jsb_anysdk_framework_AgentManager_class->addProperty = JS_PropertyStub;
	jsb_anysdk_framework_AgentManager_class->delProperty = JS_DeletePropertyStub;
	jsb_anysdk_framework_AgentManager_class->getProperty = JS_PropertyStub;
	jsb_anysdk_framework_AgentManager_class->setProperty = JS_StrictPropertyStub;
	jsb_anysdk_framework_AgentManager_class->enumerate = JS_EnumerateStub;
	jsb_anysdk_framework_AgentManager_class->resolve = JS_ResolveStub;
	jsb_anysdk_framework_AgentManager_class->convert = JS_ConvertStub;
	jsb_anysdk_framework_AgentManager_class->finalize = js_anysdk_framework_AgentManager_finalize;
	jsb_anysdk_framework_AgentManager_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getSocialPlugin", js_autoanysdkbindings_AgentManager_getSocialPlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCustomPlugin", js_autoanysdkbindings_AgentManager_getCustomPlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCrashPlugin", js_autoanysdkbindings_AgentManager_getCrashPlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRECPlugin", js_autoanysdkbindings_AgentManager_getRECPlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("unloadALLPlugin", js_autoanysdkbindings_AgentManager_unloadALLPlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("loadALLPlugin", js_autoanysdkbindings_AgentManager_loadALLPlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("unloadAllPlugins", js_autoanysdkbindings_AgentManager_unloadAllPlugins, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadAllPlugins", js_autoanysdkbindings_AgentManager_loadAllPlugins, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getCustomParam", js_autoanysdkbindings_AgentManager_getCustomParam, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getUserPlugin", js_autoanysdkbindings_AgentManager_getUserPlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_autoanysdkbindings_AgentManager_init, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getAdsPlugin", js_autoanysdkbindings_AgentManager_getAdsPlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPushPlugin", js_autoanysdkbindings_AgentManager_getPushPlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getSharePlugin", js_autoanysdkbindings_AgentManager_getSharePlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getAnalyticsPlugin", js_autoanysdkbindings_AgentManager_getAnalyticsPlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getChannelId", js_autoanysdkbindings_AgentManager_getChannelId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setIsAnaylticsEnabled", js_autoanysdkbindings_AgentManager_setIsAnaylticsEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isAnaylticsEnabled", js_autoanysdkbindings_AgentManager_isAnaylticsEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("end", js_autoanysdkbindings_AgentManager_end, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getInstance", js_autoanysdkbindings_AgentManager_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_anysdk_framework_AgentManager_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_anysdk_framework_AgentManager_class,
		dummy_constructor<anysdk::framework::AgentManager>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "AgentManager", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<anysdk::framework::AgentManager> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_anysdk_framework_AgentManager_class;
		p->proto = jsb_anysdk_framework_AgentManager_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

void register_all_autoanysdkbindings(JSContext* cx, JSObject* obj) {
	// first, try to get the ns
	JS::RootedValue nsval(cx);
	JS::RootedObject ns(cx);
	JS_GetProperty(cx, obj, "anysdk", &nsval);
	if (nsval == JSVAL_VOID) {
		ns = JS_NewObject(cx, NULL, NULL, NULL);
		nsval = OBJECT_TO_JSVAL(ns);
		JS_SetProperty(cx, obj, "anysdk", nsval);
	} else {
		JS_ValueToObject(cx, nsval, &ns);
	}
	obj = ns;

	js_register_autoanysdkbindings_PluginProtocol(cx, obj);
	js_register_autoanysdkbindings_ProtocolUser(cx, obj);
	js_register_autoanysdkbindings_PluginFactory(cx, obj);
	js_register_autoanysdkbindings_ProtocolIAP(cx, obj);
	js_register_autoanysdkbindings_AgentManager(cx, obj);
	js_register_autoanysdkbindings_ProtocolSocial(cx, obj);
	js_register_autoanysdkbindings_ProtocolAnalytics(cx, obj);
	js_register_autoanysdkbindings_ProtocolAds(cx, obj);
	js_register_autoanysdkbindings_PluginManager(cx, obj);
	js_register_autoanysdkbindings_ProtocolPush(cx, obj);
    js_register_autoanysdkbindings_ProtocolREC(cx, obj);
    js_register_autoanysdkbindings_ProtocolCrash(cx, obj);
    js_register_autoanysdkbindings_ProtocolCustom(cx, obj);
}

