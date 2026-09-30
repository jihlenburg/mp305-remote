/* Address: CODE:1d3e; name: FUN_CODE_1d3e; body bytes: 11 */

undefined1 FUN_CODE_1d3e(char param_1)

{
  return *(undefined1 *)
          (CONCAT11('\x03' - (((0xcU < (byte)(param_1 * '\x04')) << 7) >> 7),param_1 * '\x04' - 0xd)
          + 1);
}

