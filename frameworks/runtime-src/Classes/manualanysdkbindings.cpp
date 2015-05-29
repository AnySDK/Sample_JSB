#include "manualanysdkbindings.hpp"
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

using namespace anysdk::framework;

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

JSClass  *jsb_anysdk_framework_PluginParam_class;
JSObject *jsb_anysdk_framework_PluginParam_prototype;

bool js_cocos2dx_PluginParam_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	PluginParam* ret = NULL;
	if(argc == 0){
		ret = new PluginParam();
	}
	else if (argc == 1){
		bool ok = true;
		jsval *argv = JS_ARGV(cx, vp);
		jsval arg0 = argv[0];
		if ( arg0.isObject() ){
			JSObject* tmp = JSVAL_TO_OBJECT(arg0);
		    if (!tmp) {
		        CCLOG("%s", "jsval_to_ccvaluemap: the jsval is not an object.");
		        return false;
		    }
		    
		    JSObject* it = JS_NewPropertyIterator(cx, tmp);

		    StringMap arg;
		    
		    while (true)
		    {
		        jsid idp;
		        jsval key;
		        if (! JS_NextProperty(cx, it, &idp) || ! JS_IdToValue(cx, idp, &key)) {
		            return false; // error
		        }
		        
		        if (key == JSVAL_VOID) {
		            break; // end of iteration
		        }
		        
		        if (!JSVAL_IS_STRING(key)) {
		            continue; // ignore integer properties
		        }
		        
		        JSStringWrapper keyWrapper(JSVAL_TO_STRING(key), cx);

				std::string v1;
				std::string v2;

		        v1 = keyWrapper.get();
		        JS::RootedValue value(cx);
		        JS_GetPropertyById(cx, tmp, idp, &value);
		        if (value.isString())
		        {
		            bool ok = jsval_to_std_string(cx, value, &v2);
		            if (ok){
		        		arg.insert( std::map<std::string,std::string>::value_type(v1, v2) );
		            }
		            else{
		            	CCLOG("wrong param in stringmap.\n");
		            }
		        }
		    }
		    ret = new PluginParam( arg );
		}
		else if(arg0.isBoolean()){
			bool arg = JSVAL_TO_BOOLEAN( arg0 );
			ret = new PluginParam( arg );
		}
		else if(arg0.isInt32()){
			int arg;
			ok = jsval_to_int(cx, arg0, &arg);
			if (ok)
				ret = new PluginParam( arg );
			else
				CCLOG("PluginParam int is wrong.");
		}
		else if(arg0.isNumber()){
			float arg;
			arg = arg0.toNumber();
			ret = new PluginParam( arg );
		}
		else if(arg0.isString()){
			std::string arg;
			ok = jsval_to_std_string(cx, arg0, &arg);
			if (ok)
				ret = new PluginParam( arg.c_str() );
			else
				CCLOG("PluginParam string is wrong.");
		}
	}
	else{
		JS_ReportError(cx, "js_cocos2dx_PluginParam_create : wrong number of arguments: %d, was expecting %d", argc, 0);
		return false;
	}

	jsval jsret = JSVAL_NULL;
	js_proxy_t *jsProxy = js_get_or_create_proxy<PluginParam>(cx, (PluginParam*)ret);
	jsret = OBJECT_TO_JSVAL(jsProxy->obj);
	JS_SET_RVAL(cx, vp, jsret);
	return true;
}

bool jsb_anysdk_PluginParam_getStringValue(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginParam* cobj = (anysdk::framework::PluginParam *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "jsb_anysdk_PluginParam_getStringValue : Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getStringValue();
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "jsb_anysdk_PluginParam_getStringValue : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool jsb_anysdk_PluginParam_getCurrentType(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginParam* cobj = (anysdk::framework::PluginParam *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "jsb_anysdk_PluginParam_getCurrentType : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getCurrentType();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "jsb_anysdk_PluginParam_getCurrentType : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool jsb_anysdk_PluginParam_getIntValue(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginParam* cobj = (anysdk::framework::PluginParam *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "jsb_anysdk_PluginParam_getIntValue : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getIntValue();
		jsval jsret = JSVAL_NULL;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "jsb_anysdk_PluginParam_getIntValue : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool jsb_anysdk_PluginParam_getFloatValue(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginParam* cobj = (anysdk::framework::PluginParam *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "jsb_anysdk_PluginParam_getFloatValue : Invalid Native Object");
	if (argc == 0) {
		float ret = cobj->getFloatValue();
		jsval jsret = JSVAL_NULL;
		jsret.setNumber(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "jsb_anysdk_PluginParam_getFloatValue : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool jsb_anysdk_PluginParam_getBoolValue(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginParam* cobj = (anysdk::framework::PluginParam *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "jsb_anysdk_PluginParam_getBoolValue : Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->getBoolValue();
		jsval jsret = JSVAL_NULL;
		jsret.setBoolean(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "jsb_anysdk_PluginParam_getBoolValue : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool jsb_anysdk_PluginParam_getMapValue(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginParam* cobj = (anysdk::framework::PluginParam *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "jsb_anysdk_PluginParam_getMapValue : Invalid Native Object");
	if (argc == 0) {
		typedef std::map<std::string, PluginParam*> MAP_PLUGINPARAM;
		MAP_PLUGINPARAM values = cobj->getMapValue();
		JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    	if (!tmp) return false;

    	MAP_PLUGINPARAM::iterator iter;
    	bool ok = true;
    	for (iter = values.begin(); iter != values.end(); iter++)
    	{
    		std::string str_key = ((std::string)(iter->first));
    		js_proxy_t *jsProxy = js_get_or_create_proxy<PluginParam>(cx, (PluginParam*)iter->second);
			ok &= JS_DefineProperty(cx, tmp, str_key.c_str(), OBJECT_TO_JSVAL(jsProxy->obj), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    	}

		jsval jsret = JSVAL_NULL;
		jsret = OBJECT_TO_JSVAL(tmp);
		JS_SET_RVAL(cx, vp, jsret);
	}

	JS_ReportError(cx, "jsb_anysdk_PluginParam_getMapValue : wrong number of arguments: %d, was expecting %d", argc, 0);
	return true;
}

bool jsb_anysdk_PluginParam_getStrMapValue(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginParam* cobj = (anysdk::framework::PluginParam *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "jsb_anysdk_PluginParam_getStrMapValue : Invalid Native Object");
	if (argc == 0) {
		StringMap values = cobj->getStrMapValue();
		JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    	if (!tmp) return false;

    	StringMap::iterator iter;
    	bool ok = true;
    	for (iter = values.begin(); iter != values.end(); iter++)
    	{
    		std::string str_key = ((std::string)(iter->first));
    		std::string str_tmp = ((std::string)(iter->second));
			ok &= JS_DefineProperty(cx, tmp, str_key.c_str(), std_string_to_jsval(cx, str_tmp), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    	}

		jsval jsret = JSVAL_NULL;
		jsret = OBJECT_TO_JSVAL(tmp);
		JS_SET_RVAL(cx, vp, jsret);
		return true;
	}

	JS_ReportError(cx, "jsb_anysdk_PluginParam_getStrMapValue : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

extern JSObject *jsb_anysdk_framework_PluginProtocol_prototype;

void js_anysdk_framework_PluginParam_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PluginParam)", obj);
}

void js_register_anysdkbindings_PluginParam(JSContext *cx, JSObject *global) {
	jsb_anysdk_framework_PluginParam_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_anysdk_framework_PluginParam_class->name = "PluginParam";
	jsb_anysdk_framework_PluginParam_class->addProperty = JS_PropertyStub;
	jsb_anysdk_framework_PluginParam_class->delProperty = JS_DeletePropertyStub;
	jsb_anysdk_framework_PluginParam_class->getProperty = JS_PropertyStub;
	jsb_anysdk_framework_PluginParam_class->setProperty = JS_StrictPropertyStub;
	jsb_anysdk_framework_PluginParam_class->enumerate = JS_EnumerateStub;
	jsb_anysdk_framework_PluginParam_class->resolve = JS_ResolveStub;
	jsb_anysdk_framework_PluginParam_class->convert = JS_ConvertStub;
	jsb_anysdk_framework_PluginParam_class->finalize = js_anysdk_framework_PluginParam_finalize;
	jsb_anysdk_framework_PluginParam_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getCurrentType", jsb_anysdk_PluginParam_getCurrentType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getIntValue", jsb_anysdk_PluginParam_getIntValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getFloatValue", jsb_anysdk_PluginParam_getFloatValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getBoolValue", jsb_anysdk_PluginParam_getBoolValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getStringValue", jsb_anysdk_PluginParam_getStringValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getMapValue", jsb_anysdk_PluginParam_getMapValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getStrMapValue", jsb_anysdk_PluginParam_getStrMapValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_cocos2dx_PluginParam_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_anysdk_framework_PluginParam_prototype = JS_InitClass(
		cx, global,
		jsb_anysdk_framework_PluginProtocol_prototype, // parent proto
		jsb_anysdk_framework_PluginParam_class,
		dummy_constructor<anysdk::framework::PluginParam>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "PluginParam", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<anysdk::framework::PluginParam> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_anysdk_framework_PluginParam_class;
		p->proto = jsb_anysdk_framework_PluginParam_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

class ProtocolShareResultListener : public ShareResultListener
{
public:
    ProtocolShareResultListener():m_bNeedUnroot(false), _jsCallback(JSVAL_VOID), _jsThisObj(JSVAL_VOID)
    {
    }
    ~ProtocolShareResultListener()
    {
    	CCLOG("on share result ~listener");
    }

    virtual void onShareResult(ShareResultCode code, const char* msg) 
    {
        CCLOG("on action result: %d, msg: %s.", code, msg);
    	JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    	JSObject *thisObj = JSVAL_IS_VOID(_jsThisObj) ? NULL : JSVAL_TO_OBJECT(_jsThisObj);

	    jsval retval;
	    if (_jsCallback != JSVAL_VOID)
	    {
	        jsval resultCode = INT_TO_JSVAL(code);
	        // JSString* jsstr = JS_NewStringCopyZ(cx, msg);

	        jsval valArr[2];
	        valArr[0] = resultCode;
	        valArr[1] = std_string_to_jsval(cx, msg);

	        JS_AddValueRoot(cx, valArr);

	        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

	        JS_CallFunctionValue(cx, thisObj, _jsCallback, 2, valArr, &retval);
	        JS_RemoveValueRoot(cx, valArr);
	    }
    }

    void setJSCallbackThis(jsval jsThisObj)
    {
        _jsThisObj = jsThisObj;
        
        JSObject *thisObj = JSVAL_TO_OBJECT(jsThisObj);
	    js_proxy *p = jsb_get_js_proxy(thisObj);
	    if (!p)
	    {
	        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
	        m_bNeedUnroot = true;
	        m_bNeedUnroot &= JS_AddValueRoot(cx, &jsThisObj);
	    }
    }
    void setJSCallbackFunc(jsval func) {
    	_jsCallback = func;
    	JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
		// Root the callback function.
    	JS_AddNamedValueRoot(cx, &_jsCallback, "JSCallbackWrapper_callback_func");
	}
private:
    jsval _jsCallback;
    jsval _jsThisObj;
    bool m_bNeedUnroot;
};

bool jsb_anysdk_ProtocolShare_setResultListener(JSContext *cx, uint32_t argc, jsval *vp){
	CCLOG("in ProtocolShare_setResultListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolShare* cobj = (ProtocolShare *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc != 2)
    {
		JS_ReportError(cx, "jsb_anysdk_ProtocolShare_setResultListener : wrong number of arguments: %d, was expecting %d", argc, 0);
    	return false;
    }
	jsval *argv = JS_ARGV(cx, vp);
    ProtocolShareResultListener* listener = new ProtocolShareResultListener();
    listener->setJSCallbackFunc( argv[0] );
    listener->setJSCallbackThis( argv[1] );
    cobj->setResultListener(listener);
	return true;
}

 bool jsb_anysdk_ProtocolShare_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("\n********** setDebugMode was deprecated.\n**********");
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ProtocolShare* cobj = (ProtocolShare *)(proxy ? proxy->ptr : NULL);
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

bool jsb_anysdk_ProtocolShare_share(JSContext *cx, uint32_t argc, jsval *vp){
	CCLOG("in ProtocolShare_share, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolShare* cobj = (ProtocolShare *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc != 1)
    {
		JS_ReportError(cx, "jsb_anysdk_ProtocolShare_share : wrong number of arguments: %d, was expecting %d", argc, 0);
    	return true;
    }
    jsval *argv = JS_ARGV(cx, vp);
    jsval arg0 = argv[0];
	if ( arg0.isObject() ){
		JSObject* tmp = JSVAL_TO_OBJECT(arg0);
	    if (!tmp) {
	        CCLOG("%s", "jsval_to_ccvaluemap: the jsval is not an object.");
	        return false;
	    }
	    
	    JSObject* it = JS_NewPropertyIterator(cx, tmp);

	    TShareInfo arg;
	    
	    while (true)
	    {
	        jsid idp;
	        jsval key;
	        if (! JS_NextProperty(cx, it, &idp) || ! JS_IdToValue(cx, idp, &key)) {
	            return false; // error
	        }
	        
	        if (key == JSVAL_VOID) {
	            break; // end of iteration
	        }
	        
	        if (!JSVAL_IS_STRING(key)) {
	            continue; // ignore integer properties
	        }
	        
	        JSStringWrapper keyWrapper(JSVAL_TO_STRING(key), cx);

			std::string v1;
			std::string v2;

	        v1 = keyWrapper.get();
	        JS::RootedValue value(cx);
	        JS_GetPropertyById(cx, tmp, idp, &value);
	        if (value.isString())
	        {
	            bool ok = jsval_to_std_string(cx, value, &v2);
	            if (ok){
	        		arg.insert( std::map<std::string,std::string>::value_type(v1, v2) );
	            }
	            else{
	            	CCLOG("wrong param in stringmap.\n");
	            }
	        }
	    }
	    cobj->share( arg );
	}
	return true;
}

JSClass  *jsb_anysdk_framework_ProtocolShare_class;
JSObject *jsb_anysdk_framework_ProtocolShare_prototype;

void js_anysdk_framework_ProtocolShare_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolShare)", obj);
}

void js_register_anysdkbindings_ProtocolShare(JSContext *cx, JSObject *global) {
	jsb_anysdk_framework_ProtocolShare_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_anysdk_framework_ProtocolShare_class->name = "ProtocolShare";
	jsb_anysdk_framework_ProtocolShare_class->addProperty = JS_PropertyStub;
	jsb_anysdk_framework_ProtocolShare_class->delProperty = JS_DeletePropertyStub;
	jsb_anysdk_framework_ProtocolShare_class->getProperty = JS_PropertyStub;
	jsb_anysdk_framework_ProtocolShare_class->setProperty = JS_StrictPropertyStub;
	jsb_anysdk_framework_ProtocolShare_class->enumerate = JS_EnumerateStub;
	jsb_anysdk_framework_ProtocolShare_class->resolve = JS_ResolveStub;
	jsb_anysdk_framework_ProtocolShare_class->convert = JS_ConvertStub;
	jsb_anysdk_framework_ProtocolShare_class->finalize = js_anysdk_framework_PluginParam_finalize;
	jsb_anysdk_framework_ProtocolShare_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("share", jsb_anysdk_ProtocolShare_share, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setDebugMode", jsb_anysdk_ProtocolShare_setDebugMode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setResultListener", jsb_anysdk_ProtocolShare_setResultListener, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FS_END
	};

	jsb_anysdk_framework_ProtocolShare_prototype = JS_InitClass(
		cx, global,
		jsb_anysdk_framework_PluginProtocol_prototype, // parent proto
		jsb_anysdk_framework_ProtocolShare_class,
		dummy_constructor<anysdk::framework::ProtocolShare>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
//	bool found;
//FIXME: Removed in Firefox v27	
//	JS_SetPropertyAttributes(cx, global, "PluginParam", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<anysdk::framework::ProtocolShare> t;
	js_type_class_t *p;
	std::string typeName = t.s_name();
	if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
	{
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->jsclass = jsb_anysdk_framework_ProtocolShare_class;
		p->proto = jsb_anysdk_framework_ProtocolShare_prototype;
		p->parentProto = NULL;
		_js_global_type_map.insert(std::make_pair(typeName, p));
	}
}

static bool jsb_anysdk_framework_PluginProtocol_callFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    PluginProtocol* cobj = (PluginProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    CCLOG("callFuncWithParam, param count:%d.\n", argc);
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    if(argc == 1){
    	std::string arg0;
    	ok &= jsval_to_std_string(cx, argv[0], &arg0);
    	CCLOG("arg0: %s\n", arg0.c_str());
    	cobj->callFuncWithParam(arg0.c_str(), NULL);
        return true;
    }
    else if (argc == 0) {
    	JS_ReportError(cx, "Invalid number of arguments");
        return false;
    }
    else{
    	std::string arg0;
    	ok &= jsval_to_std_string(cx, argv[0], &arg0);
    	CCLOG("arg0: %s\n", arg0.c_str());

		std::vector<PluginParam*> params;
    	
    	JSObject *obj_1 = JSVAL_TO_OBJECT(argv[1]);
		if ( JS_IsArrayObject(cx, obj_1) )
		{
			JS::RootedObject jsArr(cx);
			bool ok = argv[1].isObject() && JS_ValueToObject( cx, JS::RootedValue(cx, argv[1]), &jsArr );
			
			uint32_t len = 0;
    		JS_GetArrayLength(cx, jsArr, &len);
    		CCLOG("param len: %d", len);
    		for (uint32_t i=0; i < len; i++)
		    {
		        JS::RootedValue value(cx);
		        if (JS_GetElement(cx, jsArr, i, &value))
		        {
		            if (value.isObject())
		            {
				        JSObject* jsobj = JSVAL_TO_OBJECT(value);
						js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
						PluginParam* pobj_2 = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
						params.push_back(pobj_2);
		            }
		        }
		    }
		}
		else{
            for (int i = 1; i < argc; i++)
            {
			    JSObject* jsobj = JSVAL_TO_OBJECT(argv[i]);
			    js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
				PluginParam* param = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
                params.push_back(param);
            }
		}
		cobj->callFuncWithParam(arg0.c_str(), params);
    	return true;
    }
}

static bool jsb_anysdk_framework_PluginProtocol_callStringFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    PluginProtocol* cobj = (PluginProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	CCLOG("callStringFuncWithParam, param count:%d.\n", argc);
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    if(argc == 1){
    	std::string arg0;
    	ok &= jsval_to_std_string(cx, argv[0], &arg0);
    	CCLOG("arg0: %s\n", arg0.c_str());
    	std::string ret = cobj->callStringFuncWithParam(arg0.c_str(), NULL);
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
        return true;
    }
    else if (argc == 0) {
    	JS_ReportError(cx, "Invalid number of arguments");
        return false;
    }
    else{
    	std::string arg0;
    	ok &= jsval_to_std_string(cx, argv[0], &arg0);
    	CCLOG("arg0: %s\n", arg0.c_str());

		std::vector<PluginParam*> params;
    	
    	JSObject *obj_1 = JSVAL_TO_OBJECT(argv[1]);
		if ( JS_IsArrayObject(cx, obj_1) )
		{
			JS::RootedObject jsArr(cx);
			bool ok = argv[1].isObject() && JS_ValueToObject( cx, JS::RootedValue(cx, argv[1]), &jsArr );
			
			uint32_t len = 0;
    		JS_GetArrayLength(cx, jsArr, &len);
    		CCLOG("param len: %d", len);
    		for (uint32_t i=0; i < len; i++)
		    {
		        JS::RootedValue value(cx);
		        if (JS_GetElement(cx, jsArr, i, &value))
		        {
		            if (value.isObject())
		            {
				        JSObject* jsobj = JSVAL_TO_OBJECT(value);
						js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
						PluginParam* pobj_2 = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
						params.push_back(pobj_2);
		            }
		        }
		    }
		}
		else{
            for (int i = 1; i < argc; i++)
            {
			    JSObject* jsobj = JSVAL_TO_OBJECT(argv[i]);
			    js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
				PluginParam* param = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
                params.push_back(param);
            }
		}
		std::string ret = cobj->callStringFuncWithParam(arg0.c_str(), params);
		jsval jsret = JSVAL_NULL;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
    	return true;
    }
}

static bool jsb_anysdk_framework_PluginProtocol_callIntFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    PluginProtocol* cobj = (PluginProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	CCLOG("callIntFuncWithParam, param count:%d.\n", argc);
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    if(argc == 1){
    	std::string arg0;
    	ok &= jsval_to_std_string(cx, argv[0], &arg0);
    	CCLOG("arg0: %s\n", arg0.c_str());
    	int ret =cobj->callIntFuncWithParam(arg0.c_str(), NULL);
		jsval jsret = JSVAL_NULL;
		jsret = INT_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
        return true;
    }
    else if (argc == 0) {
    	JS_ReportError(cx, "Invalid number of arguments");
        return false;
    }
    else{
    	std::string arg0;
    	ok &= jsval_to_std_string(cx, argv[0], &arg0);
    	CCLOG("arg0: %s\n", arg0.c_str());

		std::vector<PluginParam*> params;
    	
    	JSObject *obj_1 = JSVAL_TO_OBJECT(argv[1]);
		if ( JS_IsArrayObject(cx, obj_1) )
		{
			JS::RootedObject jsArr(cx);
			bool ok = argv[1].isObject() && JS_ValueToObject( cx, JS::RootedValue(cx, argv[1]), &jsArr );
			
			uint32_t len = 0;
    		JS_GetArrayLength(cx, jsArr, &len);
    		CCLOG("param len: %d", len);
    		for (uint32_t i=0; i < len; i++)
		    {
		        JS::RootedValue value(cx);
		        if (JS_GetElement(cx, jsArr, i, &value))
		        {
		            if (value.isObject())
		            {
				        JSObject* jsobj = JSVAL_TO_OBJECT(value);
						js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
						PluginParam* pobj_2 = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
						params.push_back(pobj_2);
		            }
		        }
		    }
		}
		else{
            for (int i = 1; i < argc; i++)
            {
			    JSObject* jsobj = JSVAL_TO_OBJECT(argv[i]);
			    js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
				PluginParam* param = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
                params.push_back(param);
            }
		}
		int ret = cobj->callIntFuncWithParam(arg0.c_str(), params);
		jsval jsret = JSVAL_NULL;
		jsret = INT_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
    	return true;
    }
}

static bool jsb_anysdk_framework_PluginProtocol_callBoolFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    PluginProtocol* cobj = (PluginProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	CCLOG("callBoolFuncWithParam, param count:%d.\n", argc);
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    if(argc == 1){
    	std::string arg0;
    	ok &= jsval_to_std_string(cx, argv[0], &arg0);
    	CCLOG("arg0: %s\n", arg0.c_str());
    	bool ret = cobj->callBoolFuncWithParam(arg0.c_str(), NULL);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
        return true;
    }
    else if (argc == 0) {
    	JS_ReportError(cx, "Invalid number of arguments");
        return false;
    }
    else{
    	std::string arg0;
    	ok &= jsval_to_std_string(cx, argv[0], &arg0);
    	CCLOG("arg0: %s\n", arg0.c_str());

		std::vector<PluginParam*> params;
    	
    	JSObject *obj_1 = JSVAL_TO_OBJECT(argv[1]);
		if ( JS_IsArrayObject(cx, obj_1) )
		{
			JS::RootedObject jsArr(cx);
			bool ok = argv[1].isObject() && JS_ValueToObject( cx, JS::RootedValue(cx, argv[1]), &jsArr );
			
			uint32_t len = 0;
    		JS_GetArrayLength(cx, jsArr, &len);
    		CCLOG("param len: %d", len);
    		for (uint32_t i=0; i < len; i++)
		    {
		        JS::RootedValue value(cx);
		        if (JS_GetElement(cx, jsArr, i, &value))
		        {
		            if (value.isObject())
		            {
				        JSObject* jsobj = JSVAL_TO_OBJECT(value);
						js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
						PluginParam* pobj_2 = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
						params.push_back(pobj_2);
		            }
		        }
		    }
		}
		else{
            for (int i = 1; i < argc; i++)
            {
			    JSObject* jsobj = JSVAL_TO_OBJECT(argv[i]);
			    js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
				PluginParam* param = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
                params.push_back(param);
            }
		}
		bool ret = cobj->callBoolFuncWithParam(arg0.c_str(), params);
		jsval jsret = JSVAL_NULL;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
    	return true;
    }
}

static bool jsb_anysdk_framework_PluginProtocol_callFloatFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    PluginProtocol* cobj = (PluginProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
	CCLOG("callFloatFuncWithParam, param count:%d.\n", argc);
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    if(argc == 1){
    	std::string arg0;
    	ok &= jsval_to_std_string(cx, argv[0], &arg0);
    	CCLOG("arg0: %s\n", arg0.c_str());
    	double ret = cobj->callFloatFuncWithParam(arg0.c_str(), NULL);
		jsval jsret = JSVAL_NULL;
		jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
        return true;
    }
    else if (argc == 0) {
    	JS_ReportError(cx, "Invalid number of arguments");
        return false;
    }
    else{
    	std::string arg0;
    	ok &= jsval_to_std_string(cx, argv[0], &arg0);
    	CCLOG("arg0: %s\n", arg0.c_str());

		std::vector<PluginParam*> params;
    	
    	JSObject *obj_1 = JSVAL_TO_OBJECT(argv[1]);
		if ( JS_IsArrayObject(cx, obj_1) )
		{
			JS::RootedObject jsArr(cx);
			bool ok = argv[1].isObject() && JS_ValueToObject( cx, JS::RootedValue(cx, argv[1]), &jsArr );
			
			uint32_t len = 0;
    		JS_GetArrayLength(cx, jsArr, &len);
    		CCLOG("param len: %d", len);
    		for (uint32_t i=0; i < len; i++)
		    {
		        JS::RootedValue value(cx);
		        if (JS_GetElement(cx, jsArr, i, &value))
		        {
		            if (value.isObject())
		            {
				        JSObject* jsobj = JSVAL_TO_OBJECT(value);
						js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
						PluginParam* pobj_2 = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
						params.push_back(pobj_2);
		            }
		        }
		    }
		}
		else{
            for (int i = 1; i < argc; i++)
            {
			    JSObject* jsobj = JSVAL_TO_OBJECT(argv[i]);
			    js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
				PluginParam* param = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
                params.push_back(param);
            }
		}
		double ret = cobj->callFloatFuncWithParam(arg0.c_str(), params);
		jsval jsret = JSVAL_NULL;
		jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
    	return true;
    }
}

static bool jsb_anysdk_framework_AgentManager_getIAPPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    AgentManager* cobj = (AgentManager *)(proxy ? proxy->ptr : NULL);

    if (argc != 0)
    {
		CCLOG("AgentManager_getIAPPlugin param number is wrong.");
		return false;
    }
    std::map<std::string , ProtocolIAP*>* plugins = cobj->getIAPPlugin();
    JSObject *jsretArr = JS_NewArrayObject(cx, 0, NULL);

    for (auto iter = plugins->begin(); iter != plugins->end(); ++iter)
    {
    	JS::RootedValue dictElement(cx);

        std::string key = std::string(iter->first);
        CCLOG("iap key: %s.", key.c_str());
        ProtocolIAP* iap_plugin = (ProtocolIAP*)(iter->second);

        js_proxy_t *jsProxy = js_get_or_create_proxy<ProtocolIAP>(cx, (ProtocolIAP*)iap_plugin);
		dictElement = OBJECT_TO_JSVAL(jsProxy->obj);

		JS_SetProperty(cx, jsretArr, key.c_str(), dictElement);
    }
    jsval jsret = OBJECT_TO_JSVAL(jsretArr);
    JS_SET_RVAL(cx, vp, jsret);

	return true;
}
static bool jsb_anysdk_framework_AgentManager_getFrameworkVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    AgentManager* cobj = (AgentManager *)(proxy ? proxy->ptr : NULL);

    if (argc != 0)
    {
		CCLOG("AgentManager_getFrameworkVersion param number is wrong.");
		return false;
    }
    std::string version;
    version = cobj->getFrameworkVersion();
    
    jsval jsret;
    jsret = c_string_to_jsval(cx, version.c_str());
    JS_SET_RVAL(cx, vp, jsret);
	return true;
}

class ProtocolAdsResultListener : public AdsListener
{
public:
    ProtocolAdsResultListener():m_bNeedUnroot(false), _jsCallback(JSVAL_VOID), _jsThisObj(JSVAL_VOID)
    {
    }
    ~ProtocolAdsResultListener()
    {
    	CCLOG("on ads result ~listener");
    }

    virtual void onAdsResult(AdsResultCode code, const char* msg)
    {
        CCLOG("on ads result: %d, msg: %s.", code, msg);
    	JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    	JSObject *thisObj = JSVAL_IS_VOID(_jsThisObj) ? NULL : JSVAL_TO_OBJECT(_jsThisObj);

	    jsval retval;
	    if (_jsCallback != JSVAL_VOID)
	    {
	        jsval resultCode = INT_TO_JSVAL(code);
	        // JSString* jsstr = JS_NewStringCopyZ(cx, msg);

	        jsval valArr[2];
	        valArr[0] = resultCode;
	        valArr[1] = std_string_to_jsval(cx, msg);

	        JS_AddValueRoot(cx, valArr);

	        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

	        JS_CallFunctionValue(cx, thisObj, _jsCallback, 2, valArr, &retval);
	        JS_RemoveValueRoot(cx, valArr);
	    }
    }
    virtual void onPlayerGetPoints(ProtocolAds* pAdsPlugin, int points) 
    {
        CCLOG("on player get points: %d.", points);
    	JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    	JSObject *thisObj = JSVAL_IS_VOID(_jsThisObj) ? NULL : JSVAL_TO_OBJECT(_jsThisObj);

	    jsval retval;
	    if (_jsCallback != JSVAL_VOID)
	    {
	        jsval resultCode = INT_TO_JSVAL(points);

	        jsval valArr[2];
			js_proxy_t *proxy = js_get_or_create_proxy(cx, pAdsPlugin);
	        valArr[0] = OBJECT_TO_JSVAL(proxy->obj);
	        valArr[1] = resultCode;

	        JS_AddValueRoot(cx, valArr);

	        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

	        JS_CallFunctionValue(cx, thisObj, _jsCallback, 2, valArr, &retval);
	        JS_RemoveValueRoot(cx, valArr);
	    }
    }

    void setJSCallbackThis(jsval jsThisObj)
    {
        _jsThisObj = jsThisObj;
        
        JSObject *thisObj = JSVAL_TO_OBJECT(jsThisObj);
	    js_proxy *p = jsb_get_js_proxy(thisObj);
	    if (!p)
	    {
	        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
	        m_bNeedUnroot = true;
	        m_bNeedUnroot &= JS_AddValueRoot(cx, &jsThisObj);
	    }
    }
    void setJSCallbackFunc(jsval func) {
    	_jsCallback = func;
    	JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
		// Root the callback function.
    	JS_AddNamedValueRoot(cx, &_jsCallback, "JSCallbackWrapper_callback_func");
	}

    static ProtocolAdsResultListener* _instance;
    static ProtocolAdsResultListener* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new ProtocolAdsResultListener();
        }
        return _instance;
    }
    static void purge()
    {
        if (_instance != NULL)
        {
            delete _instance;
            _instance = NULL;
        }
    }
private:
    jsval _jsCallback;
    jsval _jsThisObj;
    bool m_bNeedUnroot;
};
ProtocolAdsResultListener* ProtocolAdsResultListener::_instance = NULL;

static bool jsb_anysdk_framework_ProtocolAds_setAdsListener(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolAds_setAdsListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolAds* cobj = (ProtocolAds *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc != 2)
    {
		JS_ReportError(cx, "jsb_anysdk_framework_ProtocolAds_setAdsListener : wrong number of arguments: %d, was expecting %d", argc, 0);
    	return false;
    }

	jsval *argv = JS_ARGV(cx, vp);
    ProtocolAdsResultListener* listener = ProtocolAdsResultListener::getInstance();
    listener->setJSCallbackFunc( argv[0] );
    listener->setJSCallbackThis( argv[1] );
    cobj->setAdsListener(listener);
	return true;
}

static bool jsb_anysdk_framework_ProtocolAds_removeListener(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolAds_removeListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolAds* cobj = (ProtocolAds *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (ProtocolAdsResultListener::_instance != NULL)
    {
        ProtocolAdsResultListener::purge();
    }
    if(argc != 0)
    	CCLOG("ProtocolAds_removeListener has wrong number of arguments.");
	return true;
}

static bool jsb_anysdk_framework_ProtocolAds_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("\n********** setDebugMode was deprecated.\n**********");
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ProtocolAds* cobj = (ProtocolAds *)(proxy ? proxy->ptr : NULL);
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

static bool jsb_anysdk_framework_ProtocolAnalytics_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("\n********** setDebugMode was deprecated.\n**********");
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ProtocolAnalytics* cobj = (ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
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

static bool jsb_anysdk_framework_ProtocolAnalytics_logEvent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolAnalytics* cobj = (ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);

	jsval *argv = JS_ARGV(cx, vp);
	jsval arg0 = argv[0];
	std::string arg;
	bool ok = jsval_to_std_string(cx, arg0, &arg);
	CCLOG("logevent, argc: %d, str: %s.", argc, arg.c_str());
	if (!ok)
	{
		CCLOG("ProtocolAnalytics_logEvent param type is wrong.");
		return false;
	}
    if (argc == 1)
    {
    	cobj->logEvent(arg.c_str());
    	return true;
    }
    else if(argc == 2)
    {
    	JSObject* tmp = JSVAL_TO_OBJECT(argv[1]);
	    if (!tmp) {
	        CCLOG("%s", "jsval_to_stdmap: the jsval is not an object.");
	        return false;
	    }
	    
	    JSObject* it = JS_NewPropertyIterator(cx, tmp);

    	LogEventParamMap params;
	    
	    while (true)
	    {
	        jsid idp;
	        jsval key;
	        if (! JS_NextProperty(cx, it, &idp) || ! JS_IdToValue(cx, idp, &key)) {
	            return false; // error
	        }
	        
	        if (key == JSVAL_VOID) {
	            break; // end of iteration
	        }
	        
	        if (!JSVAL_IS_STRING(key)) {
	            continue; // ignore integer properties
	        }
	        
	        JSStringWrapper keyWrapper(JSVAL_TO_STRING(key), cx);

			std::string v1;
			std::string v2;

	        v1 = keyWrapper.get();
	        JS::RootedValue value(cx);
	        JS_GetPropertyById(cx, tmp, idp, &value);
	        if (value.isString())
	        {
	            bool ok = jsval_to_std_string(cx, value, &v2);
	            if (ok){
	        		params.insert( std::map<std::string,std::string>::value_type(v1, v2) );
	            }
	            else{
	            	CCLOG("wrong param in stringmap.\n");
	            }
	        }
	    }
	    cobj->logEvent(arg.c_str(), &params);

    	return true;
    }
	JS_ReportError(cx, "jsb_anysdk_framework_ProtocolAnalytics_logEvent : wrong number of arguments: %d, was expecting %d", argc, 0);
	return true;
}

class ProtocolIAPResultListener : public PayResultListener
{
public:
    ProtocolIAPResultListener():m_bNeedUnroot(false), _jsCallback(JSVAL_VOID), _jsThisObj(JSVAL_VOID)
    {
    }
    ~ProtocolIAPResultListener()
    {
    	CCLOG("on IAP result ~listener");
    }

    virtual void onPayResult(PayResultCode code, const char* msg, TProductInfo info)
    {
        CCLOG("on pay result: %d, msg: %s.", code, msg);
    	JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    	JSObject *thisObj = JSVAL_IS_VOID(_jsThisObj) ? NULL : JSVAL_TO_OBJECT(_jsThisObj);
	    jsval retval;
	    if (_jsCallback != JSVAL_VOID)
	    {
		    std::string vec="{";
	        for (auto iter = info.begin(); iter != info.end(); ++iter)
		    {
		        std::string key = std::string(iter->first);
		        std::string value = (std::string)(iter->second);
		        // CCLOG("productInfo key: %s, value: %s.", key.c_str(), value.c_str());
		        vec += key + ":" +value+ ",";
		    }
		    vec.replace(vec.length() - 1, 1, "}");
	        jsval resultCode = INT_TO_JSVAL(code);
	        jsval valArr[3];
	        valArr[0] = resultCode;
	        valArr[1] = std_string_to_jsval(cx, msg);
	        valArr[2] = std_string_to_jsval(cx, vec);

	        JS_AddValueRoot(cx, valArr);

	        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

	        JS_CallFunctionValue(cx, thisObj, _jsCallback, 3, valArr, &retval);
	        JS_RemoveValueRoot(cx, valArr);
	    }
    }
    
    virtual void onRequestResult(RequestResultCode code, const char* msg, AllProductsInfo info)
    {
        CCLOG("on request result: %d, msg: %s.", code, msg);
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JSObject *thisObj = JSVAL_IS_VOID(_jsThisObj) ? NULL : JSVAL_TO_OBJECT(_jsThisObj);
        jsval retval;
        if (_jsCallback != JSVAL_VOID)
        {
            string value = "{";
            map<string, TProductInfo >::iterator iterParent;
            iterParent = info.begin();
            while(iterParent != info.end())
            {
                value.append(iterParent->first);
                value.append("={");
                map<string, string> infoChild = iterParent->second;
                map<string, string >::iterator iterChild;
                iterChild = infoChild.begin();
                while(iterChild != infoChild.end())
                {
                    value.append(iterChild->first);
                    value.append("=");
                    value.append(iterChild->second);
                    iterChild++;
                    if(iterChild != infoChild.end())
                        value.append(", ");
                }
                iterParent++;
                if(iterParent != info.end())
                    value.append("}, ");
            }
            value.append("}");
            jsval resultCode = INT_TO_JSVAL(code);
            jsval valArr[3];
            valArr[0] = resultCode;
            valArr[1] = std_string_to_jsval(cx, msg);
            valArr[2] = std_string_to_jsval(cx, value);
            
            JS_AddValueRoot(cx, valArr);
            
            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
            
            JS_CallFunctionValue(cx, thisObj, _jsCallback, 3, valArr, &retval);
            JS_RemoveValueRoot(cx, valArr);
        }
    }


    void setJSCallbackThis(jsval jsThisObj)
    {
        _jsThisObj = jsThisObj;
        
        JSObject *thisObj = JSVAL_TO_OBJECT(jsThisObj);
	    js_proxy *p = jsb_get_js_proxy(thisObj);
	    if (!p)
	    {
	        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
	        m_bNeedUnroot = true;
	        m_bNeedUnroot &= JS_AddValueRoot(cx, &jsThisObj);
	    }
    }
    void setJSCallbackFunc(jsval func) {
    	_jsCallback = func;
    	JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
		// Root the callback function.
    	JS_AddNamedValueRoot(cx, &_jsCallback, "JSCallbackWrapper_callback_func");
	}
	void setJsObject(JSObject* cx){
		_jsObj = cx;
	}

	typedef std::map<std::string, ProtocolIAPResultListener*> STD_MAP;
	typedef std::map<std::string, ProtocolIAPResultListener*>::iterator STD_MAP_ITERATOR;

    static STD_MAP std_map;
    static ProtocolIAPResultListener* getListenerByKey(std::string key)
    {
        auto listener = std_map[key];
        if (listener == NULL) {
            listener = new ProtocolIAPResultListener();
            std_map[key] = listener;
        }
        return listener;
    }
    static void purge(std::string key)
    {
        auto listener = std_map[key];
        delete listener;
        listener = NULL;
        std_map.erase(key);
    }
    static void purge()
    {
        for (STD_MAP_ITERATOR it = std_map.begin(); it != std_map.end(); ++it)
        {
            ProtocolIAPResultListener* listener = it->second;
            delete listener;
        }
        std_map.clear();
    }
private:
	JSObject* _jsObj;
    jsval _jsCallback;
    jsval _jsThisObj;
    bool m_bNeedUnroot;
};
ProtocolIAPResultListener::STD_MAP ProtocolIAPResultListener::std_map;

static bool jsb_anysdk_framework_ProtocolIAP_setResultListener(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolAds_setAdsListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolIAP* cobj = (ProtocolIAP *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc != 2)
    {
		JS_ReportError(cx, "jsb_anysdk_framework_ProtocolAds_setAdsListener : wrong number of arguments: %d, was expecting %d", argc, 0);
    	return true;
    }
	jsval *argv = JS_ARGV(cx, vp);
	std::string p_id = cobj->getPluginId();
    if (p_id.length() < 1)
    {
        p_id = "no_plugin";
    }
    if (ProtocolIAPResultListener::std_map[p_id] == NULL)
    {
        CCLOG("will set listener:");
        ProtocolIAPResultListener* listener = ProtocolIAPResultListener::getListenerByKey(p_id);
	    listener->setJSCallbackFunc( argv[0] );
	    listener->setJSCallbackThis( argv[1] );
	    cobj->setResultListener(listener);
    }

	return true;
}

static bool jsb_anysdk_framework_ProtocolIAP_removeListener(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolIAP_removeListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolIAP* cobj = (ProtocolIAP *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    std::string p_id = cobj->getPluginId();
    if (p_id.length() < 1)
    {
        p_id = "no_plugin";
    }
    if (ProtocolIAPResultListener::std_map[p_id] != NULL)
    {
        ProtocolIAPResultListener* listener = ProtocolIAPResultListener::std_map[p_id];
        listener->purge(p_id);
    }
    if(argc != 0)
    	CCLOG("ProtocolIAP_removeListener has wrong number of arguments.");
	return true;
}

static bool jsb_anysdk_framework_ProtocolIAP_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("\n********** setDebugMode was deprecated.\n**********");
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ProtocolIAP* cobj = (ProtocolIAP *)(proxy ? proxy->ptr : NULL);
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

static bool jsb_anysdk_framework_ProtocolIAP_payForProduct(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolIAP_payForProduct, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolIAP* cobj = (ProtocolIAP *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc != 1)
    {
		JS_ReportError(cx, "jsb_anysdk_framework_ProtocolIAP_payForProduct : wrong number of arguments: %d, was expecting %d", argc, 0);
    	return true;
    }
    jsval *argv = JS_ARGV(cx, vp);
    jsval arg0 = argv[0];
	if ( arg0.isObject() ){
		JSObject* tmp = JSVAL_TO_OBJECT(arg0);
	    if (!tmp) {
	        CCLOG("%s", "jsval_to_ccvaluemap: the jsval is not an object.");
	        return true;
	    }
	    
	    JSObject* it = JS_NewPropertyIterator(cx, tmp);

	    TProductInfo arg;
	    
	    while (true)
	    {
	        jsid idp;
	        jsval key;
	        if (! JS_NextProperty(cx, it, &idp) || ! JS_IdToValue(cx, idp, &key)) {
	            return false; // error
	        }
	        
	        if (key == JSVAL_VOID) {
	            break; // end of iteration
	        }
	        
	        if (!JSVAL_IS_STRING(key)) {
	            continue; // ignore integer properties
	        }
	        
	        JSStringWrapper keyWrapper(JSVAL_TO_STRING(key), cx);

			std::string v1;
			std::string v2;

	        v1 = keyWrapper.get();
	        JS::RootedValue value(cx);
	        JS_GetPropertyById(cx, tmp, idp, &value);
	        if (value.isString())
	        {
	            bool ok = jsval_to_std_string(cx, value, &v2);
	            if (ok){
	        		arg.insert( std::map<std::string,std::string>::value_type(v1, v2) );
	            }
	            else{
	            	CCLOG("wrong param in stringmap.\n");
	            }
	        }
	    }
	    cobj->payForProduct( arg );
	}
	return true;
}

class ProtocolPushActionListener : public PushActionListener
{
public:
    ProtocolPushActionListener():m_bNeedUnroot(false), _jsCallback(JSVAL_VOID), _jsThisObj(JSVAL_VOID)
    {
    }
    ~ProtocolPushActionListener()
    {
    	CCLOG("on Push result ~listener");
    }

    virtual void onActionResult(ProtocolPush* pPlugin, PushActionResultCode code, const char* msg)
    {
        CCLOG("on push result: %d, msg: %s.", code, msg);
    	JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    	JSObject *thisObj = JSVAL_IS_VOID(_jsThisObj) ? NULL : JSVAL_TO_OBJECT(_jsThisObj);

		js_proxy_t *proxy = js_get_or_create_proxy(cx, pPlugin);
	    jsval retval;
	    if (_jsCallback != JSVAL_VOID)
	    {
	        jsval resultCode = INT_TO_JSVAL(code);
	        // JSString* jsstr = JS_NewStringCopyZ(cx, msg);

	        jsval valArr[3];
	        valArr[0] = OBJECT_TO_JSVAL(proxy->obj);
	        valArr[1] = resultCode;
	        valArr[2] = std_string_to_jsval(cx, msg);

	        JS_AddValueRoot(cx, valArr);

	        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

	        JS_CallFunctionValue(cx, thisObj, _jsCallback, 3, valArr, &retval);
	        JS_RemoveValueRoot(cx, valArr);
	    }
    }

    void setJSCallbackThis(jsval jsThisObj)
    {
        _jsThisObj = jsThisObj;
        
        JSObject *thisObj = JSVAL_TO_OBJECT(jsThisObj);
	    js_proxy *p = jsb_get_js_proxy(thisObj);
	    if (!p)
	    {
	        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
	        m_bNeedUnroot = true;
	        m_bNeedUnroot &= JS_AddValueRoot(cx, &jsThisObj);
	    }
    }
    void setJSCallbackFunc(jsval func) {
    	_jsCallback = func;
    	JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
		// Root the callback function.
    	JS_AddNamedValueRoot(cx, &_jsCallback, "JSCallbackWrapper_callback_func");
	}

    static ProtocolPushActionListener* _instance;
    static ProtocolPushActionListener* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new ProtocolPushActionListener();
        }
        return _instance;
    }
    static void purge()
    {
        if (_instance != NULL)
        {
            delete _instance;
            _instance = NULL;
        }
    }
private:
    jsval _jsCallback;
    jsval _jsThisObj;
    bool m_bNeedUnroot;
};
ProtocolPushActionListener* ProtocolPushActionListener::_instance = NULL;

static bool jsb_anysdk_framework_ProtocolPush_setActionListener(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolPush_setActionListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolPush* cobj = (ProtocolPush *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc != 2)
    {
		JS_ReportError(cx, "jsb_anysdk_framework_ProtocolPush_setActionListener : wrong number of arguments: %d, was expecting %d", argc, 0);
    	return false;
    }
	jsval *argv = JS_ARGV(cx, vp);
    ProtocolPushActionListener* listener = ProtocolPushActionListener::getInstance();
    listener->setJSCallbackFunc( argv[0] );
    listener->setJSCallbackThis( argv[1] );
    cobj->setActionListener(listener);
	return true;
}

static bool jsb_anysdk_framework_ProtocolPush_removeListener(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolPush_removeListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolPush* cobj = (ProtocolPush *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (ProtocolPushActionListener::_instance != NULL)
    {
        ProtocolPushActionListener::purge();
    }
    if(argc != 0)
    	CCLOG("ProtocolPush_removeListener has wrong number of arguments.");
	return true;
}

static bool jsb_anysdk_framework_ProtocolPush_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("\n********** setDebugMode was deprecated.\n**********");
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ProtocolPush* cobj = (ProtocolPush *)(proxy ? proxy->ptr : NULL);
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

static bool jsb_anysdk_framework_ProtocolPush_setTags(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolPush_setActionListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolPush* cobj = (ProtocolPush *)(proxy ? proxy->ptr : NULL);
    if (argc != 1)
    {
		JS_ReportError(cx, "jsb_anysdk_framework_ProtocolPush_setTags : wrong number of arguments: %d, was expecting %d", argc, 0);
    	return true;
    }
    jsval *argv = JS_ARGV(cx, vp);
    jsval arg0 = argv[0];
	if ( arg0.isObject() ){
	    list<std::string> arg;
    	JS::RootedObject jsobj(cx);
	    bool ok = JS_ValueToObject( cx, JS::RootedValue(cx, arg0), &jsobj );
	    JSB_PRECONDITION3( ok, cx, false, "Error converting value to object");
	    JSB_PRECONDITION3( jsobj && JS_IsArrayObject( cx, jsobj), cx, false, "Object must be an array");

	    uint32_t len;
	    JS_GetArrayLength(cx, jsobj, &len);
	    
	    for( uint32_t i=0; i< len;i++ ) {
	        JS::RootedValue valarg(cx);
	        JS_GetElement(cx, jsobj, i, &valarg);

	        if( valarg.isString() )
	        {
	        	CCLOG("value is string;");
	        	std::string key;
	        	ok = jsval_to_std_string(cx, valarg, &key);
	        	if (ok)
	        	{
	        		CCLOG("key: %s.", key.c_str());
	        		arg.push_back( key );
	        	}
	        }
	    }
	    cobj->setTags(arg);
	}
	else {
		CCLOG("settags: is not object.");
	}
	return true;
}

static bool jsb_anysdk_framework_ProtocolPush_delTags(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolPush_setActionListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolPush* cobj = (ProtocolPush *)(proxy ? proxy->ptr : NULL);
    if (argc != 1)
    {
		JS_ReportError(cx, "jsb_anysdk_framework_ProtocolPush_delTags : wrong number of arguments: %d, was expecting %d", argc, 0);
    	return true;
    }
    jsval *argv = JS_ARGV(cx, vp);
    jsval arg0 = argv[0];
	if ( arg0.isObject() ){
	    list<std::string> arg;
    	JS::RootedObject jsobj(cx);
	    bool ok = JS_ValueToObject( cx, JS::RootedValue(cx, arg0), &jsobj );
	    JSB_PRECONDITION3( ok, cx, false, "Error converting value to object");
	    JSB_PRECONDITION3( jsobj && JS_IsArrayObject( cx, jsobj), cx, false, "Object must be an array");

	    uint32_t len;
	    JS_GetArrayLength(cx, jsobj, &len);
	    
	    for( uint32_t i=0; i< len;i++ ) {
	        JS::RootedValue valarg(cx);
	        JS_GetElement(cx, jsobj, i, &valarg);

	        if( valarg.isString() )
	        {
	        	CCLOG("value is string;");
	        	std::string key;
	        	ok = jsval_to_std_string(cx, valarg, &key);
	        	if (ok)
	        	{
	        		CCLOG("key: %s.", key.c_str());
	        		arg.push_back( key );
	        	}
	        }
	    }
	    cobj->delTags(arg);
	}
	return true;
}

class ProtocolUserActionListener : public UserActionListener
{
public:
    ProtocolUserActionListener():m_bNeedUnroot(false), _jsCallback(JSVAL_VOID), _jsThisObj(JSVAL_VOID)
    {
    }
    ~ProtocolUserActionListener()
    {
    	CCLOG("on user action result ~listener");
    }

    virtual void onActionResult(ProtocolUser* pPlugin, UserActionResultCode code, const char* msg)
    {
        CCLOG("on user action result: %d, msg: %s.", code, msg);
    	JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    	JSObject *thisObj = JSVAL_IS_VOID(_jsThisObj) ? NULL : JSVAL_TO_OBJECT(_jsThisObj);

		js_proxy_t *proxy = js_get_or_create_proxy(cx, pPlugin);
	    jsval retval;
	    if (_jsCallback != JSVAL_VOID)
	    {
	        jsval resultCode = INT_TO_JSVAL(code);
	        // JSString* jsstr = JS_NewStringCopyZ(cx, msg);

	        jsval valArr[3];
	        valArr[0] = OBJECT_TO_JSVAL(proxy->obj);
	        valArr[1] = resultCode;
	        valArr[2] = std_string_to_jsval(cx, msg);

	        JS_AddValueRoot(cx, valArr);

	        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

	        JS_CallFunctionValue(cx, thisObj, _jsCallback, 3, valArr, &retval);
	        JS_RemoveValueRoot(cx, valArr);
	    }
    }

    void setJSCallbackThis(jsval jsThisObj)
    {
        _jsThisObj = jsThisObj;
        
        JSObject *thisObj = JSVAL_TO_OBJECT(jsThisObj);
	    js_proxy *p = jsb_get_js_proxy(thisObj);
	    if (!p)
	    {
	        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
	        m_bNeedUnroot = true;
	        m_bNeedUnroot &= JS_AddValueRoot(cx, &jsThisObj);
	    }
    }
    void setJSCallbackFunc(jsval func) {
    	_jsCallback = func;
    	JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
		// Root the callback function.
    	JS_AddNamedValueRoot(cx, &_jsCallback, "JSCallbackWrapper_callback_func");
	}

    static ProtocolUserActionListener* _instance;
    static ProtocolUserActionListener* getInstance(){
        if (_instance == NULL){
            _instance = new ProtocolUserActionListener();
        }
        return _instance;
    }
    static void purge(){
        if (_instance)
        {
            delete _instance;
            _instance = NULL;
        }
    }
private:
    jsval _jsCallback;
    jsval _jsThisObj;
    bool m_bNeedUnroot;
};
ProtocolUserActionListener* ProtocolUserActionListener::_instance = NULL;

static bool jsb_anysdk_framework_ProtocolUser_setActionListener(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolUser_setActionListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolUser* cobj = (ProtocolUser *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc != 2)
    {
		JS_ReportError(cx, "jsb_anysdk_framework_ProtocolUser_setActionListener : wrong number of arguments: %d, was expecting %d", argc, 0);
    	return false;
    }
	jsval *argv = JS_ARGV(cx, vp);
    ProtocolUserActionListener* listener = ProtocolUserActionListener::getInstance();
    listener->setJSCallbackFunc( argv[0] );
    listener->setJSCallbackThis( argv[1] );
    cobj->setActionListener(listener);
	return true;
}
static bool jsb_anysdk_framework_ProtocolUser_removeListener(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolUser_removeListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolUser* cobj = (ProtocolUser *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (ProtocolUserActionListener::_instance != NULL)
    {
        ProtocolUserActionListener::purge();
    }
    if(argc != 0)
    	CCLOG("ProtocolUser_removeListener has wrong number of arguments.");
	return true;
}

static bool jsb_anysdk_framework_ProtocolUser_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("\n********** setDebugMode was deprecated.\n**********");
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ProtocolUser* cobj = (ProtocolUser *)(proxy ? proxy->ptr : NULL);
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

class ProtocolSocialListener : public SocialListener
{
public:
    ProtocolSocialListener():m_bNeedUnroot(false), _jsCallback(JSVAL_VOID), _jsThisObj(JSVAL_VOID)
    {
    }
    ~ProtocolSocialListener()
    {
    	CCLOG("on social result ~listener");
    }

    virtual void onSocialResult(SocialRetCode code, const char* msg)
    {
        CCLOG("on action result: %d, msg: %s.", code, msg);
    	JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    	JSObject *thisObj = JSVAL_IS_VOID(_jsThisObj) ? NULL : JSVAL_TO_OBJECT(_jsThisObj);

	    jsval retval;
	    if (_jsCallback != JSVAL_VOID)
	    {
	        jsval resultCode = INT_TO_JSVAL(code);
	        // JSString* jsstr = JS_NewStringCopyZ(cx, msg);

	        jsval valArr[2];
	        valArr[0] = resultCode;
	        valArr[1] = std_string_to_jsval(cx, msg);

	        JS_AddValueRoot(cx, valArr);

	        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

	        JS_CallFunctionValue(cx, thisObj, _jsCallback, 2, valArr, &retval);
	        JS_RemoveValueRoot(cx, valArr);
	    }
    }

    void setJSCallbackThis(jsval jsThisObj)
    {
        _jsThisObj = jsThisObj;
        
        JSObject *thisObj = JSVAL_TO_OBJECT(jsThisObj);
	    js_proxy *p = jsb_get_js_proxy(thisObj);
	    if (!p)
	    {
	        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
	        m_bNeedUnroot = true;
	        m_bNeedUnroot &= JS_AddValueRoot(cx, &jsThisObj);
	    }
    }
    void setJSCallbackFunc(jsval func) {
    	_jsCallback = func;
    	JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
		// Root the callback function.
    	JS_AddNamedValueRoot(cx, &_jsCallback, "JSCallbackWrapper_callback_func");
	}

    static ProtocolSocialListener* _instance;
    static ProtocolSocialListener* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new ProtocolSocialListener();
        }
        return _instance;
    }
    static void purge()
    {
        if (_instance != NULL)
        {
            delete _instance;
            _instance = NULL;
        }
    }
private:
    jsval _jsCallback;
    jsval _jsThisObj;
    bool m_bNeedUnroot;
};
ProtocolSocialListener* ProtocolSocialListener::_instance = NULL;

static bool jsb_anysdk_framework_ProtocolSocial_setListener(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolSocial_setListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolSocial* cobj = (ProtocolSocial *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc != 2)
    {
		JS_ReportError(cx, "jsb_anysdk_framework_ProtocolSocial_setListener : wrong number of arguments: %d, was expecting %d", argc, 0);
    	return false;
    }
	jsval *argv = JS_ARGV(cx, vp);
    ProtocolSocialListener* listener = ProtocolSocialListener::getInstance();
    listener->setJSCallbackFunc( argv[0] );
    listener->setJSCallbackThis( argv[1] );
    cobj->setListener(listener);
	return true;
}

static bool jsb_anysdk_framework_ProtocolSocial_removeListener(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolSocial_removeListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolSocial* cobj = (ProtocolSocial *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (ProtocolSocialListener::_instance != NULL)
    {
        ProtocolSocialListener::purge();
    }
    if(argc != 0)
    	CCLOG("ProtocolSocial_removeListener has wrong number of arguments.");
	return true;
}

static bool jsb_anysdk_framework_ProtocolSocial_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("\n********** setDebugMode was deprecated.\n**********");
	jsval *argv = JS_ARGV(cx, vp);
	bool ok = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ProtocolSocial* cobj = (ProtocolSocial *)(proxy ? proxy->ptr : NULL);
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

static bool jsb_anysdk_framework_ProtocolSocial_unlockAchievement(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolSocial_unlockAchievement, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolSocial* cobj = (ProtocolSocial *)(proxy ? proxy->ptr : NULL);
    if (argc != 1)
    {
		JS_ReportError(cx, "jsb_anysdk_framework_ProtocolSocial_unlockAchievement : wrong number of arguments: %d, was expecting %d", argc, 0);
    	return false;
    }
	jsval *argv = JS_ARGV(cx, vp);
	jsval arg0 = argv[0];
	if ( arg0.isObject() ){
		JSObject* tmp = JSVAL_TO_OBJECT(arg0);
	    if (!tmp) {
	        CCLOG("%s", "jsval_to_ccvaluemap: the jsval is not an object.");
	        return false;
	    }
	    
	    JSObject* it = JS_NewPropertyIterator(cx, tmp);

	    TAchievementInfo arg;
	    
	    while (true)
	    {
	        jsid idp;
	        jsval key;
	        if (! JS_NextProperty(cx, it, &idp) || ! JS_IdToValue(cx, idp, &key)) {
	            return false; // error
	        }
	        
	        if (key == JSVAL_VOID) {
	            break; // end of iteration
	        }
	        
	        if (!JSVAL_IS_STRING(key)) {
	            continue; // ignore integer properties
	        }
	        
	        JSStringWrapper keyWrapper(JSVAL_TO_STRING(key), cx);

			std::string v1;
			std::string v2;

	        v1 = keyWrapper.get();
	        JS::RootedValue value(cx);
	        JS_GetPropertyById(cx, tmp, idp, &value);
	        if (value.isString())
	        {
	            bool ok = jsval_to_std_string(cx, value, &v2);
	            if (ok){
	        		arg.insert( std::map<std::string,std::string>::value_type(v1, v2) );
	            }
	            else{
	            	CCLOG("wrong param in stringmap.\n");
	            }
	        }
	    }
	    cobj->unlockAchievement( arg );
	}
	return true;
}

extern JSObject* jsb_anysdk_framework_PluginProtocol_prototype;
extern JSObject* jsb_anysdk_framework_ProtocolIAP_prototype;
extern JSObject* jsb_anysdk_framework_ProtocolAnalytics_prototype;
extern JSObject* jsb_anysdk_framework_ProtocolAds_prototype;
extern JSObject* jsb_anysdk_framework_ProtocolSocial_prototype;
extern JSObject* jsb_anysdk_framework_ProtocolPush_prototype;
extern JSObject* jsb_anysdk_framework_ProtocolUser_prototype;
extern JSObject* jsb_anysdk_framework_AgentManager_prototype;

void register_all_anysdk_manual(JSContext* cx, JSObject* obj) {
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

	js_register_anysdkbindings_PluginParam(cx, obj);
	js_register_anysdkbindings_ProtocolShare(cx, obj);

	//PluginProtocol
	JS_DefineFunction(cx, jsb_anysdk_framework_PluginProtocol_prototype, "callFuncWithParam", jsb_anysdk_framework_PluginProtocol_callFuncWithParam, 6, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_anysdk_framework_PluginProtocol_prototype, "callStringFuncWithParam", jsb_anysdk_framework_PluginProtocol_callStringFuncWithParam, 6, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_anysdk_framework_PluginProtocol_prototype, "callIntFuncWithParam", jsb_anysdk_framework_PluginProtocol_callIntFuncWithParam, 6, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_anysdk_framework_PluginProtocol_prototype, "callBoolFuncWithParam", jsb_anysdk_framework_PluginProtocol_callBoolFuncWithParam, 6, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_anysdk_framework_PluginProtocol_prototype, "callFloatFuncWithParam", jsb_anysdk_framework_PluginProtocol_callFloatFuncWithParam, 6, JSPROP_ENUMERATE | JSPROP_PERMANENT);

	//AgentManager
	JS_DefineFunction(cx, jsb_anysdk_framework_AgentManager_prototype, "getIAPPlugin", jsb_anysdk_framework_AgentManager_getIAPPlugin, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_anysdk_framework_AgentManager_prototype, "getFrameworkVersion", jsb_anysdk_framework_AgentManager_getFrameworkVersion, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);

	//ProtocolAds
	JS_DefineFunction(cx, jsb_anysdk_framework_ProtocolAds_prototype, "setAdsListener", jsb_anysdk_framework_ProtocolAds_setAdsListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_anysdk_framework_ProtocolAds_prototype, "removeListener", jsb_anysdk_framework_ProtocolAds_removeListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_anysdk_framework_ProtocolAds_prototype, "setDebugMode", jsb_anysdk_framework_ProtocolAds_setDebugMode, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);

	//ProtocolAnalytics
	JS_DefineFunction(cx, jsb_anysdk_framework_ProtocolAnalytics_prototype, "logEvent", jsb_anysdk_framework_ProtocolAnalytics_logEvent, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_anysdk_framework_ProtocolAnalytics_prototype, "setDebugMode", jsb_anysdk_framework_ProtocolAnalytics_setDebugMode, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);

	//ProtocolIAP
	JS_DefineFunction(cx, jsb_anysdk_framework_ProtocolIAP_prototype, "setResultListener", jsb_anysdk_framework_ProtocolIAP_setResultListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_anysdk_framework_ProtocolIAP_prototype, "removeListener", jsb_anysdk_framework_ProtocolIAP_removeListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_anysdk_framework_ProtocolIAP_prototype, "setDebugMode", jsb_anysdk_framework_ProtocolIAP_setDebugMode, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_anysdk_framework_ProtocolIAP_prototype, "payForProduct", jsb_anysdk_framework_ProtocolIAP_payForProduct, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	
	//ProtocolSocial
	JS_DefineFunction(cx, jsb_anysdk_framework_ProtocolSocial_prototype, "setListener", jsb_anysdk_framework_ProtocolSocial_setListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_anysdk_framework_ProtocolSocial_prototype, "removeListener", jsb_anysdk_framework_ProtocolSocial_removeListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_anysdk_framework_ProtocolSocial_prototype, "setDebugMode", jsb_anysdk_framework_ProtocolSocial_setDebugMode, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_anysdk_framework_ProtocolSocial_prototype, "unlockAchievement", jsb_anysdk_framework_ProtocolSocial_unlockAchievement, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);

	//ProtocolPush
	JS_DefineFunction(cx, jsb_anysdk_framework_ProtocolPush_prototype, "setActionListener", jsb_anysdk_framework_ProtocolPush_setActionListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_anysdk_framework_ProtocolPush_prototype, "removeListener", jsb_anysdk_framework_ProtocolPush_removeListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_anysdk_framework_ProtocolPush_prototype, "setDebugMode", jsb_anysdk_framework_ProtocolPush_setDebugMode, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_anysdk_framework_ProtocolPush_prototype, "setTags", jsb_anysdk_framework_ProtocolPush_setTags, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_anysdk_framework_ProtocolPush_prototype, "delTags", jsb_anysdk_framework_ProtocolPush_delTags, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);

	//ProtocolUser
	JS_DefineFunction(cx, jsb_anysdk_framework_ProtocolUser_prototype, "setActionListener", jsb_anysdk_framework_ProtocolUser_setActionListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_anysdk_framework_ProtocolUser_prototype, "removeListener", jsb_anysdk_framework_ProtocolUser_removeListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_anysdk_framework_ProtocolUser_prototype, "setDebugMode", jsb_anysdk_framework_ProtocolUser_setDebugMode, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
}

void anysdk_jsb_cleanAllSingletons() {
	//FIXME: ??? memory leak, Oops...
//    ProtocolShareActionListener::purge();
    ProtocolPushActionListener::purge();
    ProtocolSocialListener::purge();
    ProtocolAdsResultListener::purge();
    ProtocolUserActionListener::purge();
    ProtocolIAPResultListener::purge();
}
