/* Address: CODE:a83e; name: FUN_CODE_a83e; body bytes: 8 */

undefined1 FUN_CODE_a83e(undefined1 *param_1,undefined1 *param_2,undefined1 param_3,char param_4)

{
  undefined1 uVar1;
  
  do {
    uVar1 = *param_2;
    param_2 = param_2 + '\x01';
    *param_1 = uVar1;
    param_1 = param_1 + '\x01';
    param_4 = param_4 + -1;
  } while (param_4 != '\0');
  return param_3;
}

