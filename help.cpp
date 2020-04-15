#include "help.h"
#include "ui_help.h"
#include "windows.h"
#include <QCryptographicHash>
help::help(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::help)
{
    ui->setupUi(this);
    QString lpRootPathName = "C:\\";
    LPTSTR lpVolumeNameBuffer=new TCHAR[12];//磁盘卷标
    DWORD nVolumeNameSize=12;// 卷标的字符串长度
    DWORD VolumeSerialNumber;//硬盘序列号
    DWORD MaximumComponentLength;// 最大的文件长度
    LPTSTR lpFileSystemNameBuffer=new TCHAR[10];// 存储所在盘符的分区类型的长指针变量
    DWORD nFileSystemNameSize=10;// 分区类型的长指针变量所指向的字符串长度
    DWORD FileSystemFlags;// 文件系统的一此标志

    GetVolumeInformation((LPTSTR)lpRootPathName.utf16(),
      lpVolumeNameBuffer, nVolumeNameSize,
      &VolumeSerialNumber, &MaximumComponentLength,
      &FileSystemFlags,
      lpFileSystemNameBuffer, nFileSystemNameSize);
    ui->ID->setText(QCryptographicHash::hash (QString::number(VolumeSerialNumber).toLocal8Bit(), QCryptographicHash::Md5 ).toHex());

}

help::~help()
{
    delete ui;
}
