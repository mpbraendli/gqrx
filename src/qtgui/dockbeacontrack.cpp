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
#include <QDebug>
#include <QVariant>
#include "dockbeacontrack.h"
#include "ui_dockbeacontrack.h"


DockBeaconTrack::DockBeaconTrack(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::DockBeaconTrack)
{
    ui->setupUi(this);

    ui->beaconSpectrum->setFreqUnits(1000);
    ui->beaconSpectrum->setSampleRate(48000);
    ui->beaconSpectrum->setSpanFreq(24000);
    ui->beaconSpectrum->setCenterFreq(0);
    ui->beaconSpectrum->setPercent2DScreen(100);
    ui->beaconSpectrum->setFftCenterFreq(0);
    ui->beaconSpectrum->setDemodCenterFreq(0);
    ui->beaconSpectrum->setFilterBoxEnabled(false);
    ui->beaconSpectrum->setCenterLineEnabled(false);
    ui->beaconSpectrum->setBookmarksEnabled(false);
    ui->beaconSpectrum->setFftRange(-80., 0.);
    ui->beaconSpectrum->setVdivDelta(40);
    ui->beaconSpectrum->setHdivDelta(40);
    ui->beaconSpectrum->setFreqDigits(1);
}

DockBeaconTrack::~DockBeaconTrack()
{
    delete ui;
}

void DockBeaconTrack::saveSettings(QSettings *settings)
{
}

void DockBeaconTrack::readSettings(QSettings *settings)
{
}

void DockBeaconTrack::setNewFftData(float *fftData, int size, unsigned int rate)
{
    if (rate != d_rate) {
        d_rate = rate;
        ui->beaconSpectrum->setSampleRate(d_rate);
        ui->beaconSpectrum->setSpanFreq(d_rate / 2);
    }
    ui->beaconSpectrum->setNewFftData(fftData, size);
}

void DockBeaconTrack::setBeaconTrackingFreq(float freq)
{
    QString f = QString::number(freq/1e3);
    ui->trackedFreq->setText(f + " kHz");
}

void DockBeaconTrack::on_trackBeaconBox_stateChanged(int checkstate)
{
    emit beaconTrackingChanged(checkstate != 0);
}

void DockBeaconTrack::on_expectedFreqBox_valueChanged(double freq_MHz)
{
    emit expectedBeaconFreqChanged(freq_MHz * 1e6);
}

void DockBeaconTrack::on_loopBWBox_valueChanged(double loop_bw)
{
    emit beaconTrackingLoopBWChanged(loop_bw);
}

void DockBeaconTrack::on_filterBWBox_valueChanged(double bw_kHz)
{
    emit beaconFilterBWChanged(bw_kHz * 1000.0);
}

void DockBeaconTrack::on_applyTrackingSettingsBtn_clicked()
{
    emit applyTrackingSettingsClicked();
}

