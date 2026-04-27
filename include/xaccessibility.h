/*
 * Copyright (C) the Wine project
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef __WINE_XACCESSIBILITY_H
#define __WINE_XACCESSIBILITY_H

#include <xgameruntimetypes.h>

typedef enum XClosedCaptionFontEdgeAttribute XClosedCaptionFontEdgeAttribute;
typedef enum XClosedCaptionFontStyle XClosedCaptionFontStyle;
typedef enum XHighContrastMode XHighContrastMode;
typedef enum XSpeechToTextPositionHint XSpeechToTextPositionHint;
typedef enum XSpeechToTextType XSpeechToTextType;

typedef struct XClosedCaptionProperties XClosedCaptionProperties;

enum XClosedCaptionFontEdgeAttribute
{
    XClosedCaptionFontEdgeAttribute_Default,
    XClosedCaptionFontEdgeAttribute_NoEdgeAttribute,
    XClosedCaptionFontEdgeAttribute_RaisedEdges,
    XClosedCaptionFontEdgeAttribute_DepressedEdges,
    XClosedCaptionFontEdgeAttribute_UniformedEdges,
    XClosedCaptionFontEdgeAttribute_DropShadowedEdges,
};

enum XClosedCaptionFontStyle
{
    XClosedCaptionFontStyle_Default,
    XClosedCaptionFontStyle_MonospacedWithSerifs,
    XClosedCaptionFontStyle_ProportionalWithSerifs,
    XClosedCaptionFontStyle_MonospacedWithoutSerifs,
    XClosedCaptionFontStyle_ProportionalWithoutSerifs,
    XClosedCaptionFontStyle_Casual,
    XClosedCaptionFontStyle_Cursive,
    XClosedCaptionFontStyle_SmallCapitals,
};

enum XHighContrastMode
{
    XHighContrastMode_Off,
    XHighContrastMode_Dark,
    XHighContrastMode_Light,
    XHighContrastMode_Other,
};

enum XSpeechToTextPositionHint
{
    XSpeechToTextPositionHint_BottomCenter,
    XSpeechToTextPositionHint_BottomLeft,
    XSpeechToTextPositionHint_BottomRight,
    XSpeechToTextPositionHint_MiddleRight,
    XSpeechToTextPositionHint_MiddleLeft,
    XSpeechToTextPositionHint_TopCenter,
    XSpeechToTextPositionHint_TopLeft,
    XSpeechToTextPositionHint_TopRight,
};

enum XSpeechToTextType
{
    XSpeechToTextType_Voice,
    XSpeechToTextType_Text,
};

struct XClosedCaptionProperties
{
    XColor BackgroundColor;
    XColor FontColor;
    XColor WindowColor;
    XClosedCaptionFontEdgeAttribute FontEdgeAttribute;
    XClosedCaptionFontStyle FontStyle;
    float FontScale;
    BOOLEAN Enabled;
};

#endif
