//
// Created by xyx on 25-5-31.
//

#ifndef PHOTOS_H
#define PHOTOS_H

#include <string>
#include <vector>
#include <QPixmap>
#include <QIcon>

using namespace std;

class Photo {
    static string filePath;
    static vector<QPixmap> photos;
    static vector<QPixmap> backgrounds;
    static vector<QPixmap> dialogBackgrounds;
    static vector<QIcon> windowIcons;

    template<typename T>
    static void loadPhotos(vector<T> &container, stringstream &in);

public:
    static void loadPhotos();

    static int getPhotoNumber();
    static QPixmap getRandomPhoto();
    static bool hasPhoto();

    static QPixmap getBackground();
    static int getBackgroundNumber();
    static bool hasBackground();

    static QPixmap getDialogBackground();
    static int getDialogBackgroundNumber();
    static bool hasDialogBackground();

    static QIcon getWindowIcon();
    static int getWindowIconNumber();
    static bool hasWindowIcon();
};

#endif //PHOTOS_H
