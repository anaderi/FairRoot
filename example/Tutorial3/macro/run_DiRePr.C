void run_DiRePr(Int_t nofFiles, TString mcEngine="TGeant3" )
{
  FairLogger *logger = FairLogger::GetLogger();
 // logger->SetLogFileName("MyLog.log");
 // logger->SetLogToScreen(kTRUE);
//  logger->SetLogToFile(kTRUE);
  logger->SetLogVerbosityLevel("LOW");
//  logger->SetLogFileLevel("DEBUG4");
//  logger->SetLogScreenLevel("DEBUG");
  
  TString workDir = gSystem->WorkingDirectory();

  // Verbosity level (0=quiet, 1=event level, 2=track level, 3=debug)
  Int_t iVerbose = 0; // just forget about it, for the moment
  
  // Input file (MC events)
  //  TString inFile = "data/testrun_";
  //  inFile = inFile + mcEngine + ".root";
  
  // Parameter file
  //  TString parFile = "data/testparams_"; 
  //  parFile = parFile + mcEngine + ".root";

  // Output file
  TString outFile = Form("data/testDiRePr_%df_",nofFiles);
  outFile = outFile + mcEngine + ".root";
  
  // -----   Timer   --------------------------------------------------------
  TStopwatch timer;
  
  // -----   Reconstruction run   -------------------------------------------
  FairRunAnaProof *fRun= new FairRunAnaProof("");
  fRun->SetInputFile(Form("file://%s/data/testrun_%s_f%d.root",workDir.Data(),mcEngine.Data(),0));
  for ( Int_t ifile = 1 ; ifile < nofFiles ; ifile++ )
    fRun->AddFile   (Form("file://%s/data/testrun_%s_f%d.root",workDir.Data(),mcEngine.Data(),ifile));

  fRun->SetOutputFile(outFile);
  
  FairRuntimeDb* rtdb = fRun->GetRuntimeDb();
  FairParRootFileIo* parInput1 = new FairParRootFileIo();

  TList* fnamelist = new TList();

  for ( Int_t ifile = 0 ; ifile < nofFiles ; ifile++ )
    fnamelist->Add(new TObjString(Form("%s/data/testpar_%s_f%d.root",workDir.Data(),mcEngine.Data(),ifile)));

  cout << "PAR LIST CREATED" << endl;
  parInput1->open(fnamelist);       
  //  parInput1->open(parFile.Data());

  rtdb->setFirstInput(parInput1);
  
  FairTestDetectorDigiTask* digiTask = new FairTestDetectorDigiTask();
  fRun->AddTask(digiTask);
  
  FairTestDetectorRecoTask* hitProducer = new FairTestDetectorRecoTask();
  fRun->AddTask(hitProducer);

  fRun->Init();

  cout << "... Init done" << endl;
  timer.Start();
  fRun->Run();

  // -----   Finish   -------------------------------------------------------
  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();
  cout << endl << endl;
  cout << "Macro finished successfully." << endl;
  cout << "Output file is "    << outFile << endl;
  //  cout << "Parameter file is " << parFile << endl;
  cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << endl;
  cout << endl;
  // ------------------------------------------------------------------------
  cout << " Test passed" << endl;
  cout << " All ok " << endl;

  exit(0);
}
