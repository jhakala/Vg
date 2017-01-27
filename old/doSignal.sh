combine datacard_qqg_750_combined_alt.txt -M GenerateOnly -m 750 -t 1000  --saveToys -s 334455 --expectSignal=0 --freezeNuisances alt_bg_btag,alt_bg_antibtag,env_pdf_0_13TeV_exp1 -n biasTest

combine datacard_qqg_750_combined.txt -M MaxLikelihoodFit -m 750 --expectSignal=0 --noErrors --minos none --rMin=-40 --rMax=40 -t 1000 --toysFile=higgsCombinebiasTest.GenerateOnly.mH750.334455.root -s 334455 -n output750

combine datacard_qqg_1000_combined_alt.txt -M GenerateOnly -m 1000 -t 1000  --saveToys -s 334455 --expectSignal=0 --freezeNuisances alt_bg_btag,alt_bg_antibtag,env_pdf_0_13TeV_exp1 -n biasTest_5

combine datacard_qqg_1000_combined.txt -M MaxLikelihoodFit -m 1000 --expectSignal=0 --noErrors --minos none --rMin=-4 --rMax=4 -t 1000 --toysFile=higgsCombinebiasTest1000.GenerateOnly.mH1000.334455.root -s 334455 -n output1000

combine datacard_qqg_2000_combined_alt.txt -M GenerateOnly -m 2000 -t 1000  --saveToys -s 334455 --expectSignal=0 --freezeNuisances alt_bg_btag,alt_bg_antibtag,env_pdf_0_13TeV_exp1 -n biasTest2000

combine datacard_qqg_2000_combined.txt -M MaxLikelihoodFit -m 2000 --expectSignal=0 --noErrors --minos none --rMin=-4 --rMax=4 -t 1000 --toysFile=higgsCombinebiasTest2000.GenerateOnly.mH2000.334455.root -s 334455 -n output2000

combine datacard_qqg_3000_combined_alt.txt -M GenerateOnly -m 3000 -t 1000  --saveToys -s 334455 --expectSignal=0 --freezeNuisances alt_bg_btag,alt_bg_antibtag,env_pdf_0_13TeV_exp1 -n biasTest3000

combine datacard_qqg_3000_combined.txt -M MaxLikelihoodFit -m 3000 --expectSignal=0 --noErrors --minos none --rMin=-4 --rMax=4 -t 1000 --toysFile=higgsCombinebiasTest3000.GenerateOnly.mH3000.334455.root -s 334455 -n output3000
