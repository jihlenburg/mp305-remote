/* Address: 0003e588; name: FUN_0003e588; body bytes: 124 */

/* Recovered from stored Thumb pointer at 0003e638; callback identification is inferred until
   reviewed. */

undefined4 FUN_0003e588(undefined4 param_1,int param_2,uint *param_3,int param_4)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int local_10;
  
  cVar1 = *(char *)(param_2 + 0x10);
  local_10 = param_4;
  if (cVar1 == '\0') {
    FUN_0004a404(param_3,*(undefined4 *)(param_2 + 0xc),0xc);
LAB_0003e5f2:
    if ((*param_3 & 0xff) != 0x19) {
      *(short *)((int)param_3 + 2) = (short)((*param_3 >> 0x11) << 1);
    }
    return 1;
  }
  if (cVar1 == '\x01') {
    uVar2 = FUN_00046ca0(*(undefined4 *)(param_2 + 0xc));
    iVar3 = thunk_FUN_00050a1a(uVar2,&DAT_0003e604);
    if (((iVar3 == 0) && (iVar3 = FUN_00046d6e(param_2 + 0x14,param_3,0xc,&local_10), iVar3 == 0))
       && (local_10 == 0xc)) {
      if ((char)*param_3 != '\x19') {
        *(char *)((int)param_3 + 1) = (char)*param_3;
        *(char *)param_3 = '\x19';
      }
      *(ushort *)((int)param_3 + 2) = (ushort)(*param_3 >> 0x10) | 0x20;
      goto LAB_0003e5f2;
    }
  }
  else if (cVar1 == '\x02') {
    *(undefined2 *)(param_3 + 1) = 1;
    ((char *)((int)param_3 + 6))[0] = '\x01';
    ((char *)((int)param_3 + 6))[1] = '\0';
    *(char *)((int)param_3 + 1) = '\x0e';
    goto LAB_0003e5f2;
  }
  return 0;
}

