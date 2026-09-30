/* Address: 00048890; name: FUN_00048890; body bytes: 8 */

void FUN_00048890(int param_1,undefined4 param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 4) = param_2;
  }
  return;
}

