
var social_plugin = null;

var Social = cc.Class.extend({
	ctor:function(){
		social_plugin = anysdk.AgentManager.getInstance().getSocialPlugin();
		if (social_plugin) {
			social_plugin.setListener(this.onSocialAction, this)
		};
	},
	submitScore:function(){
        var score = 131;
        social_plugin.submitScore("friend", score);
        social_plugin.signIn();
        social_plugin.signOut();
	},
	showLeaderboard:function(){
		social_plugin.showLeaderboard("friend");
	},
	unlockAchievement:function(){
        var achInfo = {"rank":"friends"};
        social_plugin.unlockAchievement(achInfo);
	},
	showAchievement:function(){
		social_plugin.showAchievements();
	},
	onSocialAction:function(code ,msg){
		cc.log("code:"+code+", msg:"+msg)
	}
});