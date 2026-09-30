/* Address: CODE:88f5; name: FUN_CODE_88f5; body bytes: 8 */

undefined1 FUN_CODE_88f5(undefined1 param_1,char param_2)

{
  char in_PSW;
  
  return *(undefined1 *)CONCAT11(param_2 - (in_PSW >> 7),param_1);
}

