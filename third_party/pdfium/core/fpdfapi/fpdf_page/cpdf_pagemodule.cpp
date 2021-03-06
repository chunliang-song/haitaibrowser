// Copyright 2016 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#include "core/fpdfapi/fpdf_page/cpdf_pagemodule.h"

CPDF_ColorSpace* CPDF_PageModule::GetStockCS(int family) {
  if (family == PDFCS_DEVICEGRAY)
    return &m_StockGrayCS;
  if (family == PDFCS_DEVICERGB)
    return &m_StockRGBCS;
  if (family == PDFCS_DEVICECMYK)
    return &m_StockCMYKCS;
  if (family == PDFCS_PATTERN)
    return &m_StockPatternCS;
  return nullptr;
}
