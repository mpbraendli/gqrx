/* -*- c++ -*- */
/*
 * Gqrx SDR: Software defined radio receiver powered by GNU Radio and Qt
 *           http://gqrx.dk/
 *
 * Copyright 2011-2013 Alexandru Csete OZ9AEC.
 *
 * Gqrx is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * Gqrx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Gqrx; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */
#ifndef DOCKBEACONTRACK_H
#define DOCKBEACONTRACK_H

#include <QDockWidget>
#include <QSettings>
#include "qtgui/agc_options.h"
#include "qtgui/demod_options.h"
#include "qtgui/nb_options.h"

namespace Ui {
    class DockBeaconTrack;
}


/**
 * @brief Dock window for beacon tracker
 * @ingroup UI
 *
 * Configures and shows spectrum of beacon tracker
 */
class DockBeaconTrack : public QDockWidget
{
    Q_OBJECT

public:
    explicit DockBeaconTrack(QWidget *parent = 0);
    ~DockBeaconTrack();

    void readSettings(QSettings *settings);
    void saveSettings(QSettings *settings);

    void setNewFftData(float *fftData, int size, unsigned int rate);

public slots:
    void setBeaconTrackingFreq(float freq);

signals:
    /** Signals emitted for changes to beacon tracking settings. */
    void beaconTrackingChanged(bool enable);
    void expectedBeaconFreqChanged(double freq_kHz);
    void beaconTrackingLoopBWChanged(double loop_bw);
    void beaconFilterBWChanged(double bw_kHz);
    void applyTrackingSettingsClicked();

private slots:
    void on_trackBeaconBox_stateChanged(int checkstate);
    void on_expectedFreqBox_valueChanged(double freq_MHz);
    void on_loopBWBox_valueChanged(double bw);
    void on_filterBWBox_valueChanged(double bw_kHz);
    void on_applyTrackingSettingsBtn_clicked();

private:
    Ui::DockBeaconTrack *ui;        /** The Qt designer UI file. */
    unsigned int d_rate = 0;
};

#endif // DOCKRXOPT_H
