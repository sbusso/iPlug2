#pragma once

#define STB_TEXTEDIT_CHARTYPE char
#define STB_TEXTEDIT_POSITIONTYPE int
#define STB_TEXTEDIT_STRING ITextEntryControl
#define STB_TEXTEDIT_KEYTYPE uint32_t

#include "stb_textedit.h"

#include "IControl.h"

/** A control for drawing a text entry in the graphics context */
class ITextEntryControl : public IControl
{
public:
  ITextEntryControl(IGEditorDelegate& dlg);
  ~ITextEntryControl() {}

  //IControl
  void Draw(IGraphics& g) override;

  void OnMouseDown(float x, float y, const IMouseMod& mod) override;
  bool OnKeyDown(float x, float y, const IKeyPress& key) override;
//  void OnMouseDrag(float x, float y, float dX, float dY, const IMouseMod& mod) override;
//  void OnMouseOver(float x, float y, const IMouseMod& mod) override;
//  void OnMouseOut() override;
//  void OnMouseWheel(float x, float y, const IMouseMod& mod, float d) override;
  void OnEndAnimation() override;

  void CreateTextEntry(const IRECT& bounds, const IText& text, const char* str);
  
  static int DeleteChars(ITextEntryControl* _this, size_t pos, size_t num);
  static int InsertChars(ITextEntryControl* _this, size_t pos, const char* text, size_t num);
  static void Layout(StbTexteditRow* row, ITextEntryControl* _this, int start_i);
  static float GetCharWidth(ITextEntryControl* _this, int n, int i);
  static char GetChar(ITextEntryControl* _this, int pos);
  static int GetLength(ITextEntryControl* _this);
  
  bool EditInProgress() { return mEditing; }
  void DismissEdit() { mEditing = false; SetTargetAndDrawRECTs(IRECT()); GetUI()->SetAllControlsDirty(); }
  
private:
  template<typename Proc>
  bool CallSTB(Proc proc);
  void OnStateChanged();
  void OnTextChange();
  void FillCharWidthCache();
  void CalcCursorSizes();
  float GetCharWidth (char c, char pc);
  
  bool mDrawCursor = false;
  
  bool mEditing = false;
  bool mRecursiveKeyGuard = false;
  bool mCursorIsSet = false;
  bool mCursorSizesValid = false;
  bool mNotifyTextChange = false;

  STB_TexteditState mEditState;
  WDL_String mEditString;
  WDL_TypedBuf<float> mCharWidths;
};