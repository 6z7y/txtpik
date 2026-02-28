# txtpik

**txtpik** is a simple command-line text picker tool for Linux.  
This minimal example demonstrates a structure for a text picker project.

## Installation

### Prerequisites

**For X11**:
```bash
maim tesseract-ocr-eng
```

**For Wayland**:
```bash
grim slurp tesseract-ocr-eng
```

Clone the repository and run:

```bash
git clone https://github.com/6z7y/txtpik.git
cd txtpik
make install
```

To uninstall:

```bash
make uninstall
```

## Usage

```bash
txtpik
```
Then click and drag to select the text you want to extract.

### Optional — Copy to Clipboard

You can pipe the output to a clipboard tool:

**wayland**: `txtpik | wl-copy`

**x11**: `txtpik | xclip -selection clipboard`


## How it works

1. **Select area** → Click and drag to choose text on screen
2. **Take screenshot** → Captures selected region
3. **Run OCR** → Tesseract extracts text from image
4. **Print text** → Shows result in terminal
5. **Clean up** → Deletes temporary screenshot


-- uses
( Wayland
- **slurp** - Wayland screen region selector
- **grim** - Wayland screenshot tool  
)

( X11
- **maim** - X11 screenshot tool with built-in selection
)

- **tesseract-ocr** - Converts images to text
--
