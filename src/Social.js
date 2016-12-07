
var social_plugin = null;

var Social = cc.Class.extend({
	ctor:function(){
		social_plugin = anysdk.agentManager.getSocialPlugin();
        // set share result listener
        if (social_plugin)
            social_plugin.setListener(this.onSocialResult, this);
	},
	submitScore:function(){
        var score = 131;
        social_plugin.submitScore("friend", score);
	},
	showLeaderboard:function(){
		social_plugin.showLeaderboard("friend");
	},
	unlockAchievement:function(){
        var achInfo = {"rank":"friends"}
        social_plugin.unlockAchievement(achInfo);
	},
	showAchievements:function(){
		social_plugin.showAchievements();
	},
	signIn:function(){
		social_plugin.signIn();
	},
	signOut:function(){
		social_plugin.signOut();
	},
	onSocialResult:function(code, msg){
		cc.log("on social result listener.")
		cc.log("code:"+code+",msg:"+msg)
		switch(code)
		{
			case anysdk.SocialRetCode.kScoreSubmitSucceed:
				//do
				break;
			case anysdk.SocialRetCode.kScoreSubmitfail:
				//do
				break;
			case anysdk.SocialRetCode.kAchUnlockSucceed:
				//do
				break;
			case anysdk.SocialRetCode.kAchUnlockFail:
				//do
				break;
			case anysdk.SocialRetCode.kSocialSignInSucceed:
				//do
				break;
			case anysdk.SocialRetCode.kSocialSignOutSucceed:
				//do
				break;
			case anysdk.SocialRetCode.kSocialSignOutFail:
				//do
				break;
			case anysdk.SocialRetCode.kSocialSignOutFail:
				//do
				break;
			case anysdk.SocialRetCode.kSocialGetGameFriends:
				//do
				break;
		}
	}
});