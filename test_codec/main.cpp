#include <stdio.h>
#include <QCoreApplication>
#include <QTextCodec>
#include <QDebug>
void utf8(const QString& string, const QString& codec) {
    printf("%s:%s:>>>>\n", __FUNCTION__, codec.toAscii().data());
    char *data = string.toAscii().data();
    for (int i = 0; i < strlen(data); i++) {
        printf("<0x%2x>", *(data+i) & 0x000000ff);
    }

    printf("\n%s:%s<<<<\n\n\n", __FUNCTION__,codec.toAscii().data());
}


void utf16(const QString& string, const QString& codec) {
    printf("%s:%s:>>>>\n", __FUNCTION__, codec.toAscii().data());
    const ushort *data = string.utf16();
    for (int i = 0; i < wcslen((const wchar_t*)data); i++) {
        printf("<0x%2x>", *(data+i) & 0x0000ffff);
    }

    printf("\n%s:%s<<<<\n\n\n", __FUNCTION__,codec.toAscii().data());
}


void test(const QString& string, const QString& codec) {
    QTextCodec* gbk_codec = QTextCodec::codecForName(codec.toAscii());
    QString gbk_string = gbk_codec->fromUnicode(string);
    printf("%s:%s:%d:%d>>>>\n", __FUNCTION__, codec.toAscii().data(),string.size(), gbk_string.size());
    char *data = gbk_string.toAscii().data();
    for (int i = 0; i < strlen(data); i++) {
        printf("<0x%2x>", *(data+i) & 0x000000ff);
    }
    printf("\n%s:%s<<<<\n\n\n", __FUNCTION__,codec.toAscii().data());
}

void test2(const QString& string, const QString& codec) {
    QTextCodec* gbk_codec = QTextCodec::codecForName(codec.toAscii());
    QString gbk_string = gbk_codec->toUnicode(string.toAscii());
    printf("%s:%s:>>>>\n", __FUNCTION__, codec.toAscii().data());
    char *data = gbk_string.toAscii().data();
    for (int i = 0; i < strlen(data); i++) {
        printf("<0x%2x>", *(data+i) & 0x000000ff);
    }
    printf("\n%s:%s<<<<\n\n\n", __FUNCTION__,codec.toAscii().data());
}


int main(int argc, char **argv) {
    QCoreApplication a(argc, argv);
    QList<QByteArray> array = QTextCodec::availableCodecs();
//    qDebug() << array;
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
//    qDebug() << QTextCodec::codecForCStrings();

//    test_UTF8("大家好");
//    printf("\n\n");

//    utf8("大家好", "Default");
//    utf16("大家好", "Default");
//
    test(QString::fromUtf8("大家好"), "System");
    test(QString::fromUtf8("大家好"), "UTF-8");
    test(QString::fromUtf8("大家好"), "GB2312");
    test(QString::fromUtf8("大家好"), "GBK");
    test(QString::fromUtf8("hello"), "GBK");

//    qDebug() << QString("大家好");
//    test("大家好", "System");
//    test("大家好", "latin1");
//    test("大家好", "ISO-8859-1");
//    test("大家好", "UTF-16");
//    test("大家好", "UTF-16LE");
//    test2("大家好", "ISO-8859-1");
    return a.exec();
}
