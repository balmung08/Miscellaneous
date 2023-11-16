// index.js
// 获取应用实例
const app = getApp()
Page({
  data: {
    motto: 'Hello World',
    userInfo: {},
    hasUserInfo: false,
    canIUse: wx.canIUse('button.open-type.getUserInfo'),
    canIUseGetUserProfile: false,
    canIUseOpenData: wx.canIUse('open-data.type.userAvatarUrl') && wx.canIUse('open-data.type.userNickName') // 如需尝试获取用户信息可改为false
  },
  // 事件处理函数
  bindViewTap() {
    wx.navigateTo({
      url: '../logs/logs'
    })
  },
  onLoad() {
    if (wx.getUserProfile) {
      this.setData({
        canIUseGetUserProfile: true
      })
    }
  },
  sendSocket:function () {
    wx.request({
      url: 'http://balmung.online/lyya.html',
      method: 'GET',
      success: res=> {
        this.setData({
          value: res.data
      })
      if (res.data == 0){
      this.setData({text:"mild"})
      this.setData({image:"happy.png"})
      this.setData({tip:"祝您一路好心情"})}
      if (res.data == 1){
      this.setData({text:"angry"})
      this.setData({image:"angry.png"})
      this.setData({tip:"开车时可不能心烦气躁哦"})}
      if (res.data == 2){
      this.setData({text:"loading"})
      this.setData({image:"loading.png"})
      this.setData({tip:"系统正在初始化，请稍候"})}
      if (res.data == 3){
      this.setData({text:"caution"})
      this.setData({image:"caution.png"})
      this.setData({tip:"请正确持握方向盘"})}
    }
    })
  },
 autodo:function (){
  this.setData({show:"none"})
  setInterval(this.sendSocket,500)
 }
})
