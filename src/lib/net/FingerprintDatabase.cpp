/*
 * Deskflow -- mouse and keyboard sharing utility
 * SPDX-FileCopyrightText: (C) 2025 Deskflow Developers
 * SPDX-FileCopyrightText: (C) 2021 Barrier Contributors
 * SPDX-License-Identifier: GPL-2.0-only WITH LicenseRef-OpenSSL-Exception
 */

#include "FingerprintDatabase.h"

#include <QFile>
#include <QTextStream>
#include <fstream>

void FingerprintDatabase::read(const QString &path)
{
  std::ifstream in(path.toStdString());
  readStream(in);
}

void FingerprintDatabase::readStream(std::istream &in)
{

  QString line;
  while (in) {
    std::string stdline;
    std::getline(in, stdline);
    line = QString::fromStdString(stdline);
    if (line.isEmpty())
      continue;
    auto fingerprint = Fingerprint::fromDbLine(line);
    if (!fingerprint.isValid()) {
      continue;
    }
    m_fingerprints.append(fingerprint);
  }
}

bool FingerprintDatabase::write(const QString &path)
{
  std::ofstream out(path.toStdString());
  return (writeStream(out));
}

bool FingerprintDatabase::writeStream(std::ostream &out)
{

  for (const auto &fingerprint : std::as_const(m_fingerprints)) {
    out << fingerprint.toDbLine().toStdString() << "\n";
  }
  return true;
}

void FingerprintDatabase::clear()
{
  m_fingerprints.clear();
}

void FingerprintDatabase::addTrusted(const Fingerprint &fingerprint)
{
  if (isTrusted(fingerprint)) {
    return;
  }
  m_fingerprints.append(fingerprint);
}

bool FingerprintDatabase::isTrusted(const Fingerprint &fingerprint) const
{
  return m_fingerprints.contains(fingerprint);
}
