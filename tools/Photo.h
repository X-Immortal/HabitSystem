//
// Created by xyx on 25-5-31.
//

#ifndef PHOTOS_H
#define PHOTOS_H

#include <string>
#include <vector>
#include <QPixmap>

using namespace std;

class Photo {
    static string filePath;
    static vector<QPixmap> photos;
    static vector<QPixmap> backgrounds;
    static vector<QPixmap> dialogBackgrounds;

    static void loadPhotos(vector<QPixmap> &container, stringstream &in);

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
};

#endif //PHOTOS_H
