/* Address: CODE:9490; name: FUN_CODE_9490; body bytes: 30 */

void FUN_CODE_9490(char param_1,char param_2)

{
  byte bVar1;
  
  if (param_2 == '\x05') {
    FUN_CODE_33d6();
    bVar1 = FUN_CODE_33df();
    FUN_CODE_33d3(bVar1 | 0x10);
    bVar1 = FUN_CODE_33e2(param_1 + '\\');
    FUN_CODE_a99c(bVar1 & 0xfc);
    FUN_CODE_a377();
  }
  return;
}

