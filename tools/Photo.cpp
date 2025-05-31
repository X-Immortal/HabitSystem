//
// Created by xyx on 25-5-31.
//

#include "Photo.h"
#include <fstream>
#include <sstream>
#include <random>

int getRandom(int min, int max) {
    static mt19937 gen(random_device{}());
    uniform_int_distribution<size_t> dis(min, max);
    return dis(gen);
}

#ifdef _WIN32
string Photo::filePath = "..\\.file\\photos\\photopath.txt";
#else
string Photo::filePath = "../.file/photos/photopath.txt";
#endif

vector<QPixmap> Photo::photos;
vector<QPixmap> Photo::backgrounds;
vector<QPixmap> Photo::dialogBackgrounds;

void Photo::loadPhotos() {
    if (hasPhoto() && hasBackground()) {
        return;
    }
    ifstream in(filePath);
    if (!in) {
        return;
    }
    stringstream ss;
    ss << in.rdbuf();
    string line;

    while (getline(ss, line)) {
        if (line.empty()) {
            continue;
        }
        if (line == "[BACKGROUND]") {
            loadPhotos(backgrounds, ss);
        } else if (line == "[PHOTO]") {
            loadPhotos(photos, ss);
        } else if (line == "[DIALOG-BACKGROUND]") {
            loadPhotos(dialogBackgrounds, ss);
        }
    }
}

void Photo::loadPhotos(vector<QPixmap> &container, stringstream &in) {
    string line;
    while (getline(in, line)) {
        if (line.empty()) {
            continue;
        }
        if (line == "[END]") {
            return;
        }
        QPixmap pixmap = QPixmap(QString::fromStdString(line));
        if (pixmap.isNull()) {
            continue;
        }
        container.push_back(pixmap);
    }
}

bool Photo::hasPhoto() {
    return !photos.empty();
}

int Photo::getPhotoNumber() {
    return photos.size();
}

QPixmap Photo::getRandomPhoto() {
    if (!hasPhoto()) {
        throw runtime_error("Invalid photo");
    }
    return photos[getRandom(0, getPhotoNumber() - 1)];
}

QPixmap Photo::getBackground() {
    if (!hasBackground()) {
        throw runtime_error("Invalid background");
    }
    return backgrounds[getRandom(0, getBackgroundNumber() - 1)];
}

bool Photo::hasBackground() {
    return !backgrounds.empty();
}

int Photo::getBackgroundNumber() {
    return backgrounds.size();
}

bool Photo::hasDialogBackground() {
    return !dialogBackgrounds.empty();
}

int Photo::getDialogBackgroundNumber() {
    return dialogBackgrounds.size();
}

QPixmap Photo::getDialogBackground() {
    if (!hasDialogBackground()) {
        throw runtime_error("Invalid dialog background");
    }
    return dialogBackgrounds[getRandom(0, getDialogBackgroundNumber() - 1)];
}




