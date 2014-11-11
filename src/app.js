
var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        /////////////////////////////
        // 2. add a menu item with "X" image, which is clicked to quit the program
        //    you may modify it.
        // ask director the window size
        var size = cc.director.getWinSize();

        // add a "close" icon to exit the progress. it's an autorelease object
        var closeItem = cc.MenuItemImage.create(
            res.CloseNormal_png,
            res.CloseSelected_png,
            function () {
                cc.log("Menu is clicked!");
            }, this);
        closeItem.attr({
            x: size.width - 20,
            y: 20,
            anchorX: 0.5,
            anchorY: 0.5
        });

        var menu = cc.Menu.create(closeItem);
        menu.x = 0;
        menu.y = 0;
        this.addChild(menu, 1);

        /////////////////////////////
        // 3. add your codes below...
        // add a label shows "Hello World"
        // create and initialize a label
        // var helloLabel = cc.LabelTTF.create("Hello World", "Arial", 38);
        // // position the label on the center of the screen
        // helloLabel.x = size.width / 2;
        // helloLabel.y = size.height * 0.9;
        // // add the label as a child to this layer
        // this.addChild(helloLabel, 5);

        // add "HelloWorld" splash screen"
        this.sprite = cc.Sprite.create(res.HelloWorld_png);
        this.sprite.setPosition(size.width/2, size.height/2);
        this.addChild(this.sprite, 0);

        var aLy = new AgentLayer();
        cc.log("aLy: "+aLy);
        this.addChild(aLy);

        return true;
    }
});


var appKey = "BA5B660B-6DD5-0F67-8CC7-8FE0BA7545D6";
var appSecret = "e23ae7d6da34334d4cc11df0dc7f3de0";
var privateKey = "76E1D975EA4B9A4ECD0E85AF2D782E99";
var oauthLoginServer = "http://oauth.anysdk.com/api/OauthLoginDemo/Login.php";

var agent = null;
var user_plugin = null;
var iap_plugin = null;
var share_plugin = null;
var ads_plugin = null;
var social_plugin = null;
var push_plugin = null;
var analytics_plugin = null;

var menu_lv = {
    base:100,
    user:200,
    iap:300,
    share:400,
    ads:500,
    social:600,
    push:700
};
var user_operation = {
    login:0,
    logout:1,
    enterPlatform:2,
    showToolbar:3,
    hideToolbar:4,
    accountSwitch:5,
    realNameRegister:6,
    antiAddictionQuery:7,
    submitLoginGameRole:8
};
var iap_operation = {
    pay:0
};
var share_operation = {
    share:0
};
var ads_operation = {
    showAds:0,
    hideAds:1
};
var social_operation = {
    submitScore:0,
    showLeaderboard:1,
    unlockAchievement:2,
    showAchievement:3
};
var push_operation = {
    closePush:0,
    setAlias:1,
    delAlias:2,
    setTags:3,
    delTags:4
};

var AgentLayer = cc.Layer.extend({
    base_menu:null,
    sec_menu:null,
    sec_lys:null,
    is_dis_sec:false,
    i_cur_dis:-1,
    ctor:function () {
        this._super();

        agent = anysdk.AgentManager.getInstance();
        // init
        agent.init(appKey,appSecret,privateKey,oauthLoginServer);
        // load
        agent.loadALLPlugin();
        // get plugins
        user_plugin  = agent.getUserPlugin();
        iap_plugin   = agent.getIAPPlugin();
        share_plugin = agent.getSharePlugin();
        ads_plugin   = agent.getAdsPlugin();
        social_plugin = agent.getSocialPlugin();
        push_plugin  = agent.getPushPlugin();
        analytics_plugin = agent.getAnalyticsPlugin();
        cc.log("agent:"+agent);

        user_plugin.setActionListener(this.onUserLogin, this);
        cc.log("222---")
        iap_plugins = iap_plugin;
        for(var key in iap_plugins){
            var iap_plusgin = iap_plugins[key];
            iap_plusgin.setResultListener(this.onPayResult, this);
        }
        // set share result listener
        if (share_plugin)
            share_plugin.setResultListener(this.onShareResult, this);

        // 
        this.funcOfAgent();

        this.base_menu = ["User System", "IAP System", "Share System", "Ads System", "Social System", "Push System"];

        this.sec_menu = [
                    ["login", "logout", "enterPlatform", "showToolBar", "hideToolBar", "accountSwitch", "realNameRegister", "antiAddictionQuery", "submitLoginGameRole"],
                    ["pay"],
                    ["share"],
                    ["show Ads", "hide Ads"],
                    ["submit score", "show Leaderboard", "unloack Achievement", "show Achievement"],
                    ["close Push", "set Alias", "del Alias", "set Tags", "del Tags"],
                    ];

        this.sec_lys = [];
        var b_x = 130.0;
        var b_y = 400.0;
        var b_h = 60.0;
        var menu = cc.Menu.create();
        var arrBtns = [];
        for (var i = this.base_menu.length - 1; i >= 0; i--) {
            var btn = this.create_btn(this.base_menu[i], i);
            btn.setPosition(b_x, b_y - i*b_h);
            arrBtns.push(btn);
        };
        var menu = cc.Menu.create();
        menu.initWithArray(arrBtns);
        menu.x = 0;
        menu.y = 0;
        this.addChild(menu, 1);
    },
    funcOfAgent:function(){
        var customParam = agent.getCustomParam();
        cc.log("customParam:"+customParam);
        var channelId = agent.getChannelId();
        cc.log("channelId:"+channelId);
    },
    create_btn:function(str, tag){
        var lb = cc.LabelTTF.create(str, "Arial", 38);
        var menuItem = cc.MenuItemLabel.create(lb, this.onClick.bind(this));
        // var menuItem = cc.MenuItemImage.create(res.sp1_png, res.sp2_png, this.onClick.bind(this), this);
        menuItem.setTag(tag);
        // menuItem.addChild(lb);
        // var size = menuItem.getContentSize();
        // lb.setPosition(size.width/2, size.height/2);
        return menuItem;
    },
    onClick:function(item){
        var tag = item.getTag();
        cc.log("click item: "+tag);
        if (tag < menu_lv.base){
            this.setSecInvisible();
            this.displaySecLayer(tag);
            this.i_cur_dis = tag;
        }
        else if (tag < menu_lv.user){
            this.onUserAction(tag - menu_lv.base);
        }
        else if (tag < menu_lv.iap){
            this.onIAPAction(tag - menu_lv.user);
        }
        else if (tag < menu_lv.share){
            this.onShareAction(tag - menu_lv.iap);
        }
        else if (tag < menu_lv.ads){
            this.onAdsAction(tag - menu_lv.share);
        }
        else if (tag < menu_lv.social){
            this.onSocialAction(tag - menu_lv.ads);
        }
        else if (tag < menu_lv.push){
            this.onPushAction(tag - menu_lv.social);
        }
    },
    setSecInvisible:function(){
        for (var i = this.sec_lys.length - 1; i >= 0; i--) {
            if (this.sec_lys[i] != null)
                this.sec_lys[i].setVisible(false);
        };
    },
    displaySecLayer:function(idx){
        if( this.is_dis_sec && idx == this.i_cur_dis){
            this.is_dis_sec = false;
            return;
        }
        if(this.sec_lys[idx] != null)
            this.sec_lys[idx].setVisible(true);
        else{
            var b_x = 530.0;
            var b_y = 400.0;
            var b_h = 55.0;
            if (idx == 0){
                b_y = 440.0;
                b_h = 48.0;
            }
            var menu = cc.Menu.create();
            var arrBtns = [];
            for (var i = this.sec_menu[idx].length - 1; i >= 0; i--) {
                var btn = this.create_btn(this.sec_menu[idx][i], i + 100*(idx+1));
                btn.setPosition(b_x, b_y - i*b_h);
                arrBtns.push(btn);
            };
            var menu = cc.Menu.create();
            menu.initWithArray(arrBtns);
            menu.x = 0;
            menu.y = 0;
            this.addChild(menu, 1);

            this.sec_lys[idx] = menu;
        }

        this.is_dis_sec = true;
    },
    onUserAction:function(idx){
        if (user_plugin == null) {
            cc.log("user plugin was not loaded.");
            return;
        }
        switch(idx){
            case user_operation.login:{
                    user_plugin.login();
                    analytics_plugin.logEvent("login");
                }break;
            case user_operation.logout:
                    if ( user_plugin.isSupportFunction("logout") )
                        user_plugin.callFuncWithParam("logout");
                break;
            case user_operation.enterPlatform:
                    if ( user_plugin.isSupportFunction("enterPlatform") )
                        user_plugin.callFuncWithParam("enterPlatform");
                break;
            case user_operation.showToolbar:
                    if ( user_plugin.isSupportFunction("showToolBar") ){
                        var param1 = anysdk.PluginParam.create(ToolBarPlace.kToolBarTopLeft)
                        user_plugin.callFuncWithParam("showToolBar", param1);
                    }
                break;
            case user_operation.hideToolbar:
                    if ( user_plugin.isSupportFunction("hideToolBar") )
                        user_plugin.callFuncWithParam("hideToolBar");
                break;
            case user_operation.accountSwitch:
                    if ( user_plugin.isSupportFunction("accountSwitch") )
                        user_plugin.callFuncWithParam("accountSwitch");
                break;
            case user_operation.realNameRegister:
                    if ( user_plugin.isSupportFunction("realNameRegister") )
                        user_plugin.callFuncWithParam("realNameRegister");
                break;
            case user_operation.antiAddictionQuery:
                    if ( user_plugin.isSupportFunction("antiAddictionQuery") )
                        user_plugin.callFuncWithParam("antiAddictionQuery");
                break;
            case user_operation.submitLoginGameRole:
                    if( user_plugin.isSupportFunction("submitLoginGameRole") ){
                        var data = anysdk.PluginParam.create({roleId:"123456",roleName:"test",roleLevel:"10",zoneId:"123",zoneName:"test",dataType:"1",ext:"login"});
                        user_plugin.callFuncWithParam("submitLoginGameRole", data);
                    }
                break;
        }
    },
    onIAPAction:function(idx){
        if (iap_plugin == null) {
            cc.log("IAP plugin was not loaded.");
            return;
        }
        switch(idx){
            case iap_operation.pay:{
                    var info = {
                        Product_Price:"1", 
                        Product_Id:"monthly",  
                        Product_Name:"gold",  
                        Server_Id:"13",  
                        Product_Count:"1",  
                        Role_Id:"1001",  
                        Role_Name:"asd"
                    };
                    cc.log("will log pay event:");
                    analytics_plugin.logEvent("pay", info);
                    var obj = iap_plugin
                    for(var p in obj){
                        var iap_plusgin = obj[p];
                        cc.log("will pay for product");
                        iap_plusgin.payForProduct(info);
                    }
                }break;
        }
    },
    onShareAction:function(idx){
        if (share_plugin == null) {
            cc.log("share plugin was not loaded.");
            return;
        }
        switch(idx){
            case share_operation.share:{
                    var info = {
                        title : "ShareSDK是一个神奇的SDK",
                        titleUrl : "http://sharesdk.cn",
                        site : "ShareSDK",
                        siteUrl : "http://sharesdk.cn",
                        text : "ShareSDK集成了简单、支持如微信、新浪微博、腾讯微博等社交平台",
                        comment : "无",
                    }
                    cc.log("share info:"+info+", "+info["site"]);
                    share_plugin.share(info)
                    cc.log("will log event");
                    analytics_plugin.logEvent("share")
                }break;
        }
    },
    onAdsAction:function(idx){
        if (ads_plugin == null) {
            cc.log("ads plugin was not loaded.");
            return;
        }
        switch(idx){
            case ads_operation.showAds:
                if ( ads_plugin.isSupportFunction("AD_TYPE_FULLSCREEN") )
                    ads_plugin.showAds(AdsType.AD_TYPE_FULLSCREEN)
                    // ads_plugin.showAds(AdsType.FULLSCREEN)
                break;
            case ads_operation.hideAds:
                if ( ads_plugin.isSupportFunction("AD_TYPE_FULLSCREEN") )
                    ads_plugin.hideAds(AdsType.AD_TYPE_FULLSCREEN)
                break;
        }
    },
    onSocialAction:function(idx){
        if (social_plugin == null) {
            cc.log("social plugin was not loaded.");
            return;
        }
        switch(idx){
            case social_operation.submitScore:{
                var score = 131;
                    social_plugin.submitScore("friend", score);
                    social_plugin.signIn();
                    social_plugin.signOut();
                }break;
            case social_operation.showLeaderboard:
                    social_plugin.showLeaderboard("friend");
                break;
            case social_operation.unlockAchievement:
                    var achInfo = {"rank":"friends"}
                    social_plugin.unlockAchievement(achInfo);
                break;
            case social_operation.showAchievement:
                    social_plugin.showAchievements();
                    analytics_plugin.logEvent("showAchievements");
                break;
        }
    },
    onPushAction:function(idx){
        if (push_plugin == null) {
            cc.log("push plugin was not loaded.");
            return;
        }
        switch(idx){
            case push_operation.closePush:
                    push_plugin.closePush();
                break;
            case push_operation.setAlias:
                    push_plugin.setAlias("ivenKill");
                break;
            case push_operation.delAlias:
                    push_plugin.delAlias("ivenKill");
                break;
            case push_operation.setTags:
                    push_plugin.setTags(["easy","fast","qwe"]);
                break;
            case push_operation.delTags:
                    push_plugin.delTags(["easy","qwe"]);
                break;
        }
    },
    onPayResult:function(ret, msg, info){
        cc.log("pay result, resultcode:"+ret+", msg: "+msg+", info:"+info);
    },
    onUserLogin:function(plugin, code, msg){
        cc.log("on user result action.");
        cc.log("msg:"+msg);
        cc.log("code:"+code);
        cc.log("plugin:"+plugin);
        // cc.log(plugin+", "+code+", "+msg);
    },
    onShareResult:function(code, msg){
        cc.log("share result, resultcode:"+code+", msg: "+msg);
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

