![Icon](../resource/icon/menshen.png)


# 门神（MenShen）
拦截所有将要打开的 URL 链接，手动编辑并选择打开方式。



## 警告
**本项目目前仍处于极早期开发阶段，只有测试版本，请谨慎使用，避免不必要的损失。**



## 特性
- 拦截所有将要打开的 URL 链接并弹窗（需要设置为默认浏览器）
- 自动解析 URL 为不同部分，方便编辑清理 URL
- 支持选择 URL 打开方式，例如不同的浏览器
- 支持多标签页，可同时解析多个 URL



## 安装
### 基于 Debian 的发行版


### 从源码编译
```shell
just build
```


## 致谢
- [GTK](https://gitlab.gnome.org/GNOME/gtk)
：本项目基于 GTK 开发。

- [Adwaita](https://gitlab.gnome.org/GNOME/libadwaita)
：本项目界面样式基于 Adwaita。

- [URLCheck](https://github.com/TrianguloY/URLCheck)
：本项目的灵感来源。

- [GTK 4 Tutorial for beginners](https://github.com/ToshioCP/Gtk4-tutorial)
：本项目起步阶段参考的文档。


## 图标
本项目图标采用 [CC-BY-4.0](resource/icon/LICENSE) 协议分发：
- `resource/icon/menshen.kra`
- `resource/icon/menshen.png`

本项目图标基于以下项目修改而来：
- [Fluent UI Web](https://github.com/microsoft/fluentui)
： `resource/icon/door_fluentui.svg`

- [Noto Emoji](https://github.com/googlefonts/noto-emoji)
： `resource/icon/lotus_noto-emoji.svg`

- [FxEmojis](https://github.com/mozilla/fxemoji)
：`resource/icon/light_fxemoji.svg`



## 许可
本项目所有源码均采用 [GPL-3.0-or-later](../LICENSE) 协议开源。
