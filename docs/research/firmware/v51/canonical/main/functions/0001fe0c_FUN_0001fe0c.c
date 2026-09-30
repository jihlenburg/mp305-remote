/* Address: 0001fe0c; name: FUN_0001fe0c; body bytes: 158 */

undefined4 FUN_0001fe0c(int param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 local_18;
  undefined4 local_14;
  
  uVar4 = 0;
  if (*(char *)(param_1 + 1) != '5') {
    return 0;
  }
  uVar1 = *(uint *)(param_1 + 3);
  uVar2 = *(uint *)(param_1 + 7);
  iVar3 = *(int *)(param_1 + 0xb);
  if ((((0xffff < uVar1) && (uVar1 < 0xfc001)) && ((uVar1 & 3) == 0)) &&
     ((uVar2 < 0xec001 && (uVar1 + uVar2 < 0xfc001)))) {
    if (DAT_1fffa01c == iVar3) {
      DAT_1fffa01c = 0;
      local_18 = 0;
      local_14 = 0xaa55cc33;
      FUN_0001bef8(&PTR_DAT_0001001c,&local_18,4);
      FUN_0001bf3a(local_18,&local_14,4);
      uVar4 = 1;
      DAT_1fffa010 = uVar2;
      DAT_1fffa014 = iVar3;
    }
    else {
      DAT_1fffa010 = 0;
      DAT_1fffa014 = 0;
    }
  }
  return uVar4;
}

