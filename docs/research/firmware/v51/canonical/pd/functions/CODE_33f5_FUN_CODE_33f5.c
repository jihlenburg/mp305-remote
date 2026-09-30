/* Address: CODE:33f5; name: FUN_CODE_33f5; body bytes: 12 */

char FUN_CODE_33f5(undefined1 param_1,byte param_2)

{
  char in_PSW;
  
  *(undefined1 *)CONCAT11('\x03' - (in_PSW >> 7),param_1) = 0;
  return '\x03' - (((0xa9 < param_2) << 7) >> 7);
}

