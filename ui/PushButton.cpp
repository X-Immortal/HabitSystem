//
// Created by xyx on 25-5-29.
//

#include "PushButton.h"

PushButton::PushButton(QWidget *parent) : QPushButton(parent) {
    initButton();
}

PushButton::PushButton(const QString& text, QWidget *parent) : QPushButton(text, parent) {
    initButton();
}

void PushButton::initButton() {
    styleSheet =
        "QPushButton {"
        "   border: 1px solid #8f8f91;"   // 基础边框
        "   border-top-color: white;"     // 模拟凸起的上边缘
        "   border-left-color: white;"    // 模拟凸起的左边缘
        "   border-radius: 5px;"
        "   color: black;"
        "   font-size: 10px;"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f6f7fa, stop:1 #dadbde);"  // 渐变背景
        "}"
        "QPushButton:pressed {"          // 按下状态
        "   border-top-color: #8f8f91;"  // 反转高亮边
        "   border-left-color: #8f8f91;" // 创建凹陷效果
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #dadbde, stop:1 #f6f7fa);"  // 反转渐变方向
        "   padding: 2px 0 0 2px;"       // 微移文字位置增强按压感
        "}"
        "QPushButton:hover {"
        "   background-color: #e0e0e0;"  // 保持原有悬停效果
        "}";
    setStyleSheet(styleSheet);
}

void PushButton::addStyle(const QString &styleSheet) {
    this->styleSheet += styleSheet;
    setStyleSheet(this->styleSheet);
}
