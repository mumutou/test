#include <stdio.h>
#include <QCoreApplication>
#include <QTextCodec>
#include <QDebug>
void utf8(const QString& string, const QString& codec) {
   printf("%s:%s:>>>>\n", __FUNCTION__, codec.toAscii().data());
   char *data = string.toAscii().data();
   for (int i = 0;i < strlen(data); i++) {
       printf("<0x%2x>", *(data+i) & 0x000000ff);
   }

   printf("\n%s:%s<<<<\n\n\n", __FUNCTION__,codec.toAscii().data());
}


void utf16(const QString& string, const QString& codec) {
    printf("%s:%s:>>>>\n", __FUNCTION__, codec.toAscii().data());
    const ushort *data = string.utf16();
    for (int i = 0;i < wcslen((const wchar_t*)data); i++) {
        printf("<0x%2x>", *(data+i) & 0x0000ffff);
    }

    printf("\n%s:%s<<<<\n\n\n", __FUNCTION__,codec.toAscii().data());
}


void test(const QString& string, const QString& codec) {
    QTextCodec* gbk_codec = QTextCodec::codecForName(codec.toAscii());
    QString gbk_string = gbk_codec->fromUnicode(string);
    printf("%s:%s:%d:%d>>>>\n", __FUNCTION__, codec.toAscii().data(),string.size(), gbk_string.size());
    char *data = gbk_string.toAscii().data();
    for (int i = 0;i < strlen(data); i++) {
        printf("<0x%2x>", *(data+i) & 0x000000ff);
    }
    printf("\n%s:%s<<<<\n\n\n", __FUNCTION__,codec.toAscii().data());
}

void test2(const QString& string, const QString& codec) {
    QTextCodec* gbk_codec = QTextCodec::codecForName(codec.toAscii());
    QString gbk_string = gbk_codec->toUnicode(string.toAscii());
    printf("%s:%s:>>>>\n", __FUNCTION__, codec.toAscii().data());
    char *data = gbk_string.toAscii().data();
    for (int i = 0;i < strlen(data); i++) {
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

//    test_UTF8("��Һ�");
//    printf("\n\n");

//    utf8("��Һ�", "Default");
//    utf16("��Һ�", "Default");
//
    test(QString::fromUtf8("��Һ�"), "System");
    test(QString::fromUtf8("��Һ�"), "UTF-8");
    test(QString::fromUtf8("��Һ�"), "GB2312");
    test(QString::fromUtf8("��Һ�"), "GBK");
    test(QString::fromUtf8("hello"), "GBK");

//    qDebug() << QString("��Һ�");
//    test("��Һ�", "System");
//    test("��Һ�", "latin1");
//    test("��Һ�", "ISO-8859-1");
//    test("��Һ�", "UTF-16");
//    test("��Һ�", "UTF-16LE");
//    test2("��Һ�", "ISO-8859-1");
    return a.exec();
}
