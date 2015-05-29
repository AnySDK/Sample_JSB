

//注意：这里appKey, appSecret, privateKey，要替换成自己打包工具里面的值(登录打包工具，游戏管理界面上显示的那三个参数)
//android
//var appKey = "BA5B660B-6DD5-0F67-8CC7-8FE0BA7545D6";
//var appSecret = "e23ae7d6da34334d4cc11df0dc7f3de0";
//var privateKey = "76E1D975EA4B9A4ECD0E85AF2D782E99";
//ios
var appKey = "0914CB16-BAEE-790E-808E-3A37B8FFBE3F";
var appSecret = "62bee0ddb86bdeccb8acd959765041cc";
var privateKey = "96C273AB03E1A798BA1AD0C38004871F";
var oauthLoginServer = "http://oauth.anysdk.com/api/OauthLoginDemo/Login.php";

var agent = null;
var user_plugin = null;
var iap_pluginMap = null;

var PluginChannel = cc.Class.extend({
	loadPlugins:function(){
        agent = anysdk.AgentManager.getInstance();
        // init
        agent.init(appKey,appSecret,privateKey,oauthLoginServer);
        // load
        agent.loadALLPlugin();
        // get plugins
        user_plugin   = agent.getUserPlugin();
        iap_pluginMap = agent.getIAPPlugin();

        if (user_plugin) {
        	user_plugin.setActionListener(this.onUserLogin, this);
        }

        for(var key in iap_pluginMap){
            var iap_plugin = iap_pluginMap[key];
            iap_plugin.setResultListener(this.onPayResult, this);
        }

        this.funcOfAgent();
	},
    onUserLogin:function(plugin, code, msg){
        cc.log("on user result action.");
        cc.log("msg:"+msg);
        cc.log("code:"+code);
        cc.log("plugin:"+plugin);
        // cc.log(plugin+", "+code+", "+msg);
    },
    funcOfAgent:function(){
        var customParam = agent.getCustomParam();
        cc.log("customParam:"+customParam);
//        var channelId = agent.getChannelId();
//        cc.log("channelId:"+channelId);
    },
    login:function(){
    	user_plugin.login();
    },
    logout:function(){
    	if ( user_plugin.isFunctionSupported("logout") )
    		user_plugin.callFuncWithParam("logout");
    },
    enterPlatform:function(){
    	if ( user_plugin.isFunctionSupported("enterPlatform") )
    		user_plugin.callFuncWithParam("enterPlatform");
    },
    showToolbar:function(pos){
        if ( user_plugin.isFunctionSupported("showToolBar") ){
            var param1 = anysdk.PluginParam.create(pos);
            user_plugin.callFuncWithParam("showToolBar", param1);
        }
    },
    hideToolbar:function(){
        if ( user_plugin.isFunctionSupported("hideToolBar") )
            user_plugin.callFuncWithParam("hideToolBar");
    },
    accountSwitch:function(){
        if ( user_plugin.isFunctionSupported("accountSwitch") )
            user_plugin.callFuncWithParam("accountSwitch");
    },
    realNameRegister:function(){
        if ( user_plugin.isFunctionSupported("realNameRegister") )
            user_plugin.callFuncWithParam("realNameRegister");
    },
    antiAddictionQuery:function(){
        if ( user_plugin.isFunctionSupported("antiAddictionQuery") )
            user_plugin.callFuncWithParam("antiAddictionQuery");
    },
    antiAddictionQuery:function(){
        if( user_plugin.isFunctionSupported("submitLoginGameRole") ){
            var data = anysdk.PluginParam.create({roleId:"123456",roleName:"test",roleLevel:"10",zoneId:"123",zoneName:"test",dataType:"1",ext:"login"});
            user_plugin.callFuncWithParam("submitLoginGameRole", data);
        }
    },
    pay:function(){
        var info = {
            Product_Price:"1", 
            Product_Id:"monthly",  
            Product_Name:"gold",  
            Server_Id:"13",  
            Product_Count:"1",  
            Role_Id:"1001",  
            Role_Name:"asd"
        };
        for(var p in iap_pluginMap){
            var iap_plugin = iap_pluginMap[p];
            cc.log("will pay for product");
            iap_plugin.payForProduct(info);
        }
    },
    onPayResult:function(ret, msg, info){
        cc.log("pay result, resultcode:"+ret+", msg: "+msg+", info:"+info);
    }

});