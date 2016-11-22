
var a8csdk = null;

var A8CSDK = cc.Class.extend({
	ctor:function(){
        a8csdk = anysdk.agentManager.getCustomPlugin();
        // set custom result listener
        if (a8csdk)
            a8csdk.setResultListener(this.onCustomResult, this);
	},

	onCreateRole:function(){
        if (!a8csdk || !(a8csdk.isFunctionSupported("onCreateRole"))) return;
        var info = {
            "serverId" : "serverId",
            "serverName":"serverName",
            "roleId": "roleId",
            "roleName":"rolename",
            "roleLevel": "5",
            "ext": ""
        };
        a8csdk.onCreateRole(info);

	},
    onEnterGame:function(){
        if (!a8csdk || !(a8csdk.isFunctionSupported("onEnterGame"))) return;
        var info = {
            "serverId" : "serverId",
            "serverName":"serverName",
            "roleId": "roleId",
            "roleName":"rolename",
            "roleLevel": "5",
            "ext": ""
        };
        a8csdk.onEnterGame(info);
    },
    onLogin:function(){
        if (!a8csdk || !(a8csdk.isFunctionSupported("onLogin"))) return;
        var info = {
            "uid" : "123456",
            "uname":"",
            "ext": ""
        };
        a8csdk.onLogin(info);
    },
    onPay:function(){
        if (!a8csdk || !(a8csdk.isFunctionSupported("onPay"))) return;
        var info = {
            "orderId" : "123456",
            "price":"10",
            "count": "1",
            "goodsId":"goodsId",
            "goodsName": "10",
            "title": "10",
            "ext": ""
        };
        a8csdk.onPay(info);
    },
    onExit:function(){
        if (!a8csdk || !(a8csdk.isFunctionSupported("onExit"))) return;
        a8csdk.onExit();
    },
	onLevelUp:function(){
        if (!a8csdk || !(a8csdk.isFunctionSupported("onLevelUp"))) return;
        var info = {
            "serverId" : "serverId",
            "serverName":"serverName",
            "roleId": "roleId",
            "roleName":"rolename",
            "roleLevel": "5",
            "ext": ""
        };
        a8csdk.onLevelUp(info);
	},
	onRegister:function(){
        if (!a8csdk || !(a8csdk.isFunctionSupported("onRegister"))) return;
        var info = {
            "uid" : "123456",
            "uname":"",
            "ext": ""
        };
        a8csdk.onRegister(info);

	},
    onCustomEvent:function(){
        if (!a8csdk || !(a8csdk.isFunctionSupported("onCustomEvent"))) return;
        var info = {
            "dataType" : "123456",
            "info":"10",
            "ext": ""
        };
        a8csdk.onCustomEvent(info);
    },
    getLastGameServerInfo:function(){
        if (!a8csdk || !(a8csdk.isFunctionSupported("getLastGameServerInfo"))) return;
        a8csdk.getLastGameServerInfo();
    },
	isFunctionSupported:function(functionName){
		if (!a8csdk) return false;
		return a8csdk.isFunctionSupported(functionName);
	},
    onCustomResult:function(code, msg){
        switch(code)
        {
        case CustomResultCode.kCustomExtension + 1://初始化成功
            cc.log("InitSuccess\n");
            break;
        case CustomResultCode.kCustomExtension + 2://初始化失败
            cc.log("InitFail\n");
            break;
        case CustomResultCode.kCustomExtension + 2:///获取服务器信息
            cc.log("getLastGameServerInfo \n");
            break;
        default:
            break;
        }
    }
});
