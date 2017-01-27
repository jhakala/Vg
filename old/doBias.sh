#combine datacard_qqg_750_combined.txt -M GenerateOnly -m 750 -t 1000  --saveToys -s 334455 --expectSignal=0 --freezeNuisances alt_bg_btag,alt_bg_antibtag,env_pdf_0_13TeV_exp1 -n biasTest

#combine datacard_qqg_750_combined.txt -M MaxLikelihoodFit -m 750 --expectSignal=0. --noErrors --minos none --rMin=-40 --rMax=40 -t 1000 --toysFile=higgsCombinebiasTest.GenerateOnly.mH750.334455.root -s 334455 -n output750_0

combine datacard_qqg_1000_combined.txt -M GenerateOnly -m 1000 -t 1000  --saveToys -s 334455 --expectSignal=0. --freezeNuisances alt_bg_btag,alt_bg_antibtag,env_pdf_0_13TeV_exp1 -n biasTest1000

combine datacard_qqg_1000_combined.txt -M MaxLikelihoodFit -m 1000 --expectSignal=0. --noErrors --minos none --rMin=-10 --rMax=10 -t 1000 --toysFile=higgsCombinebiasTest1000.GenerateOnly.mH1000.334455.root -s 334455 -n output1000_0

#combine datacard_qqg_10000_combined.txt -M GenerateOnly -m 10000 -t 1000  --saveToys -s 334455 --expectSignal=0. --freezeNuisances alt_bg_btag,alt_bg_antibtag,env_pdf_0_13TeV_exp1 -n biasTest10000

#combine datacard_qqg_10000_combined.txt -M MaxLikelihoodFit -m 10000 --expectSignal=0. --noErrors --minos none --rMin=-10 --rMax=10 -t 1000 --toysFile=higgsCombinebiasTest10000.GenerateOnly.mH10000.334455.root -s 334455 -n output10000_0


combine datacard_qqg_1000_combined.txt -M GenerateOnly -m 1000 -t 1000  --saveToys -s 334455 --expectSignal=0.05 --freezeNuisances alt_bg_btag,alt_bg_antibtag,env_pdf_0_13TeV_exp1 -n biasTest1000

combine datacard_qqg_1000_combined.txt -M MaxLikelihoodFit -m 1000 --expectSignal=0.05 --noErrors --minos none --rMin=-10 --rMax=10 -t 1000 --toysFile=higgsCombinebiasTest1000.GenerateOnly.mH1000.334455.root -s 334455 -n output1000_1


combine datacard_qqg_1000_combined.txt -M GenerateOnly -m 1000 -t 1000  --saveToys -s 334455 --expectSignal=0.15 --freezeNuisances alt_bg_btag,alt_bg_antibtag,env_pdf_0_13TeV_exp1 -n biasTest1000

combine datacard_qqg_1000_combined.txt -M MaxLikelihoodFit -m 1000 --expectSignal=0.15 --noErrors --minos none --rMin=-10 --rMax=10 -t 1000 --toysFile=higgsCombinebiasTest1000.GenerateOnly.mH1000.334455.root -s 334455 -n output1000_3


combine datacard_qqg_1000_combined.txt -M GenerateOnly -m 1000 -t 1000  --saveToys -s 334455 --expectSignal=0.25 --freezeNuisances alt_bg_btag,alt_bg_antibtag,env_pdf_0_13TeV_exp1 -n biasTest1000

combine datacard_qqg_1000_combined.txt -M MaxLikelihoodFit -m 1000 --expectSignal=0.25 --noErrors --minos none --rMin=-10 --rMax=10 -t 1000 --toysFile=higgsCombinebiasTest1000.GenerateOnly.mH1000.334455.root -s 334455 -n output1000_5

