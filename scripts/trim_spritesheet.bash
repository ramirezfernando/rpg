# Trims transparent padding from each cell of an equally-split sprite sheet so
# that each cell's dimensions match its visible pixel boundary (easier to work
# with). Cells are re-packed in row-major order using ImageMagick.
#
# Requires: ImageMagick 7+ (`magick` command)
#
# Usage:
#   bash trim_spritesheet.bash <input.png> <columns> <rows> [output.png] [spacing]
#
# Examples:
#   bash trim_spritesheet.bash sprite.png 4 3
#   bash trim_spritesheet.bash sprite.png 4 3 sprite_trimmed.png
#   bash trim_spritesheet.bash sprite.png 4 3 sprite_trimmed.png 0


# ── Arguments ────────────────────────────────────────────────────────────────

if [[ $# -lt 3 ]]; then
  echo "Usage: $0 <input.png> <columns> <rows> [output.png] [spacing]"
  exit 1
fi

INPUT="$1"
COLUMNS="$2"
ROWS="$3"
OUTPUT="${4:-${INPUT%.png}_trimmed.png}"
SPACING="${5:-4}"

if [[ ! -f "$INPUT" ]]; then
  echo "Error: input file '$INPUT' not found."
  exit 1
fi

if ! command -v magick &>/dev/null; then
  echo "Error: ImageMagick 'magick' command not found. Install ImageMagick 7+."
  exit 1
fi

# ── Sheet dimensions ──────────────────────────────────────────────────────────

read -r SHEET_W SHEET_H < <(magick identify -format "%w %h" "$INPUT")
CELL_W=$(( SHEET_W / COLUMNS ))
CELL_H=$(( SHEET_H / ROWS ))

echo "Input:     $INPUT"
echo "Output:    $OUTPUT"
echo "Grid:      ${COLUMNS}x${ROWS}  (cell: ${CELL_W}x${CELL_H})"
echo "Spacing:   $SPACING"

# ── Crop, trim, and smush row by row ─────────────────────────────────────────
# Each cell is cropped from the sheet by geometry, then `-trim` removes its
# transparent padding, then `+smush` combines each row horizontally.
# Finally all row strips are smushed vertically into the final sheet.

echo "Processing..."

TMPDIR_WORK=$(mktemp -d)
trap 'rm -rf "$TMPDIR_WORK"' EXIT

for (( row = 0; row < ROWS; row++ )); do
  ROW_FILE="$TMPDIR_WORK/row_${row}.miff"
  Y=$(( row * CELL_H ))

  (
    for (( col = 0; col < COLUMNS; col++ )); do
      X=$(( col * CELL_W ))
      # Crop the cell then trim its own transparent padding
      magick "$INPUT" \
        -crop "${CELL_W}x${CELL_H}+${X}+${Y}" +repage \
        -trim +repage \
        miff:-
    done
  ) | magick - -background none -gravity south +smush "$SPACING" "$ROW_FILE"

  echo "  Row $(( row + 1 ))/$ROWS done."
done

# ── Stack all rows vertically and restore outer border ───────────────────────
# `+smush` only adds spacing between cells, not around the outside edge.
# `-border` adds the same spacing around the entire sheet so the outer
# cells aren't flush against the image boundary.

magick "$TMPDIR_WORK"/row_*.miff \
  -background none -smush "$SPACING" \
  -bordercolor none -border "${SPACING}" \
  "$OUTPUT" || { echo "Error: failed to stack rows"; exit 1; }

echo "Done → $OUTPUT"