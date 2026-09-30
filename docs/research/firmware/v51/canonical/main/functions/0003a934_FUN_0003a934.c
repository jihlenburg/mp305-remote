/* Address: 0003a934; name: FUN_0003a934; body bytes: 54 */

undefined4 FUN_0003a934(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  DAT_1ffe0120 = (char *)0x0;
  FUN_0004e5a6(param_1,0x21,param_2);
  if (DAT_1ffe0120 == (char *)0x0) {
    return 1;
  }
  if (*DAT_1ffe0120 != '\0') {
    iVar1 = thunk_FUN_00050a1a(DAT_1ffe0120,param_2);
    if (iVar1 == 0) {
      return 1;
    }
    FUN_00051eb8(param_1,DAT_1ffe0120);
  }
  return 0;
}

