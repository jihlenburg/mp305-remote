/* Address: 0004f010; name: FUN_0004f010; body bytes: 56 */

uint FUN_0004f010(uint param_1,uint param_2)

{
  undefined4 uVar1;
  undefined2 local_8;
  undefined1 uStack_6;
  
  if (((param_1 < 0x13) && (param_2 != 0)) && (param_2 < 6)) {
    local_8 = *(undefined2 *)(&UNK_0007a2ee + (param_2 - 1 & 0xff) * 3 + param_1 * 0xf);
    uStack_6 = *(undefined1 *)((int)(&UNK_0007a2ee + (param_2 - 1 & 0xff) * 3 + param_1 * 0xf) + 2);
  }
  else {
    uVar1 = FUN_0004029c();
    local_8 = (undefined2)uVar1;
    uStack_6 = (undefined1)((uint)uVar1 >> 0x10);
  }
  return (uint)CONCAT12(uStack_6,local_8);
}

