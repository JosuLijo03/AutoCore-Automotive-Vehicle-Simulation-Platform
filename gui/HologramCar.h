#ifndef HOLOGRAMCAR_H
#define HOLOGRAMCAR_H

#include <QWidget>
#include <QPixmap>
#include <QTimer>

class HologramCar : public QWidget
{
    Q_OBJECT

public:
    explicit HologramCar(QWidget *parent = nullptr);

    void setPixmap(const QPixmap &pix);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void updateScan();

private:
    QPixmap car;

    QTimer timer;

    int scanY;

    // Hologram pulse
    double opacity;

    bool increasing;
};

#endif