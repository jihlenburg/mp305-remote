/* Address: 0003f220; name: FUN_0003f220; body bytes: 272 */

void FUN_0003f220(undefined4 param_1,int param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined *puVar6;
  int iVar7;
  
  *(undefined2 *)(param_2 + 0x30) = 0x7e8;
  *(undefined1 *)(param_2 + 0x32) = 1;
  *(undefined1 *)(param_2 + 0x33) = 1;
  *(undefined2 *)(param_2 + 0x34) = 0x7e8;
  *(undefined1 *)(param_2 + 0x36) = 1;
  *(undefined1 *)(param_2 + 0x37) = 1;
  *(undefined4 *)(param_2 + 0x38) = 0;
  *(undefined4 *)(param_2 + 0x3c) = 0;
  FUN_0004a57a(param_2 + 0x121,0,0x348);
  uVar5 = 0;
  uVar2 = 0;
LAB_0003f26e:
  puVar6 = (undefined *)(&DAT_1ffe007c)[uVar2];
  do {
    *(undefined **)(param_2 + uVar2 * 4 + 0x40) = puVar6;
    while( true ) {
      uVar3 = uVar2 + 1;
      uVar2 = uVar3 & 0xff;
      if (0x37 < uVar2) {
        *(undefined **)(param_2 + 0x11c) = &DAT_0003f32c;
        uVar4 = FUN_0003e88c(param_2);
        *(undefined4 *)(param_2 + 0x2c) = uVar4;
        FUN_0003ee60(uVar4,param_2 + 0x40);
        puVar1 = (undefined4 *)(param_2 + 0x2c);
        FUN_0003ee28(*puVar1,0x220);
        FUN_0004aa4c(*puVar1,0x34869,0x1f,0);
        uVar4 = FUN_0004f078(100);
        FUN_0004eae2(*puVar1,uVar4);
        FUN_0004aa6e(*puVar1,&DAT_00084000);
        FUN_0004e624(param_2,1);
        FUN_0004e63c(*puVar1,1);
        FUN_0004ea86(param_2,2,0);
        FUN_0003f338(param_2,*(undefined2 *)(param_2 + 0x34),(int)*(char *)(param_2 + 0x36));
        *(undefined2 *)(param_2 + 0x30) = *(undefined2 *)(param_2 + 0x30);
        *(undefined1 *)(param_2 + 0x32) = *(undefined1 *)(param_2 + 0x32);
        *(undefined1 *)(param_2 + 0x33) = *(undefined1 *)(param_2 + 0x33);
        FUN_0003816c();
        return;
      }
      if (uVar2 == 0) goto LAB_0003f26e;
      if ((uVar3 & 7) == 7) break;
      if (uVar2 < 7) goto LAB_0003f26e;
      iVar7 = param_2 + uVar5 * 0x14;
      *(undefined1 *)(iVar7 + 0x121) = 0x78;
      uVar5 = uVar5 + 1 & 0xff;
      *(int *)(param_2 + uVar2 * 4 + 0x40) = iVar7 + 0x121;
    }
    puVar6 = &DAT_0003f328;
  } while( true );
}

