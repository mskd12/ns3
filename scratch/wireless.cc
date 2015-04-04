#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/mobility-module.h"
#include "ns3/config-store-module.h"
#include "ns3/wifi-module.h"
#include "ns3/athstats-helper.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/netanim-module.h"
#include "ns3/minstrel-wifi-manager.h"

#include <iostream>


using namespace ns3;
using namespace std;
/*
static void
SetVelocity (Ptr<Node> node, Vector vel)
{
  Ptr<ConstantVelocityMobilityModel> mobility =
    node->GetObject<ConstantVelocityMobilityModel> ();
  mobility->SetVelocity (vel);
}
#$ns_ at 3.0 "$node_(1) setdest 0 0 10" 
#$ns_ at 4.0 "$node_(1) setdest 0 0 0" 
#$ns_ at 5.0 "$node_(1) setdest 0 0 10" 
#$ns_ at 6.0 "$node_(1) setdest 0 0 0"

*/


Vector 
GetPosition (Ptr<Node> node) 
{ 
  Ptr<MobilityModel> mobility = node->GetObject<MobilityModel> (); 
  return mobility->GetPosition (); 
} 

static void 
AdvancePosition (NodeContainer stas) 
{ 
  Ptr<Node> node = stas.Get (0); 
  cout << Simulator::Now () <<" "<<  GetPosition (node) << std::endl; 
  Simulator::Schedule (Seconds (1), &AdvancePosition, stas); 
} 

void
PhyTxTrace (std::string context, Ptr<const Packet> packet, WifiMode mode, WifiPreamble preamble, uint8_t txPower)
{
      std::cout << "PHYTX mode=" << mode << " " << *packet << std::endl;   
}


int main() {
	NodeContainer stas, ap;
	LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
	LogComponentEnable("MinstrelWifiManager", LOG_LEVEL_INFO); 
  	Packet::EnablePrinting ();
  	LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
    // Enable logging from the ns2 helper
    LogComponentEnable ("Ns2MobilityHelper",LOG_LEVEL_DEBUG);

	std::string traceFile = "/home/mskd96/Downloads/ns-allinone-3.20/ns-3.20/scratch/wireless.ns_movements";
	ap.Create(1);
	stas.Create(1);
	
	//int distance = 50;
	double SimTime = 20.00;
	
	YansWifiChannelHelper wifiChannelHelper = YansWifiChannelHelper::Default ();
	Ptr<YansWifiChannel> wifiChannel = wifiChannelHelper.Create ();

	YansWifiPhyHelper wifiPhyHelper = YansWifiPhyHelper::Default ();
	wifiPhyHelper.SetChannel(wifiChannel);
	
	NqosWifiMacHelper wifiMacHelper = NqosWifiMacHelper::Default ();
	Ssid ssid = Ssid ("ns-3-ssid");
	wifiMacHelper.SetType ("ns3::StaWifiMac",
	                      "Ssid", SsidValue (ssid),
	                      "ActiveProbing", BooleanValue (false));

	WifiHelper wifiHelper = WifiHelper::Default ();

	wifiMacHelper.SetType ("ns3::ApWifiMac",
                       "Ssid", SsidValue (ssid));
	NetDeviceContainer apContainer = wifiHelper.Install(wifiPhyHelper, wifiMacHelper, ap);

	NetDeviceContainer wifiContainer = wifiHelper.Install(wifiPhyHelper, wifiMacHelper, stas);
	wifiHelper.SetStandard(WIFI_PHY_STANDARD_80211a);
	wifiHelper.SetRemoteStationManager("ns3::MinstrelWifiManager");
	/*wifiHelper.SetRemoteStationManager("ns3::ConstantRateWifiManager",
		"DataMode", StringValue ("OfdmRate54Mbps"),
		"ControlMode", StringValue ("OfdmRate54Mbps"));
	*/
	// Configure mobility
	/*MobilityHelper mobility;
	Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
	positionAlloc->Add (Vector (0.0, 0.0, 0.0));
	positionAlloc->Add (Vector (distance, 0.0, 0.0));
	//positionAlloc->Add (Vector (0.0, 5.0, 0.0));
	mobility.SetPositionAllocator (positionAlloc);
	mobility.SetMobilityModel ("ns3::ConstantVelocityMobilityModel");
	mobility.Install (stas);
	mobility.Install (ap);
	*/
	Ns2MobilityHelper mobility(traceFile);
    mobility.Install();
	//Simulator::Schedule (Seconds (0), &AdvancePosition, stas);
	//AnimationInterface::SetConstantPosition (stas.Get (0), 10, 30); 
	//AnimationInterface::SetConstantPosition (ap.Get (0), 10, 33); 

	InternetStackHelper stack;
  	stack.Install (ap);
  	stack.Install (stas);
  	
  	
  	Ipv4AddressHelper address;
  	address.SetBase ("10.1.1.0", "255.255.255.0");
	
	Ipv4InterfaceContainer apInterface, wifiInterface;
  	wifiInterface = address.Assign (wifiContainer);
  	apInterface = address.Assign (apContainer);

  	//Simulator::Schedule (Seconds (0.0), &SetVelocity, stas.Get (0),Vector (1.0,0.0,0.0));
 
  	UdpEchoServerHelper bulkServer (9);
  	//BulkSendHelper bulkServer ("ns3::TcpSocketFactory",
  	//	InetSocketAddress (apInterface.GetAddress (0), 9));
  	//bulkServer.SetAttribute ("MaxBytes", UintegerValue (100));
    ApplicationContainer serverApps = bulkServer.Install (ap);
    serverApps.Start (Seconds (0.0));
    serverApps.Stop (Seconds (SimTime - 0.01));

    UdpEchoClientHelper sinkClient (apInterface.GetAddress (0), 9);
	sinkClient.SetAttribute ("MaxPackets", UintegerValue (10));
    sinkClient.SetAttribute ("Interval", TimeValue (Seconds (1.)));
    sinkClient.SetAttribute ("PacketSize", UintegerValue (1024));
	
	//PacketSinkHelper sinkClient ("ns3::TcpSocketFactory",
	// 	InetSocketAddress (wifiInterface.GetAddress(0), 9));
	ApplicationContainer clientApps = sinkClient.Install (stas.Get (0));
    clientApps.Start (Seconds (0.0));
    clientApps.Stop (Seconds (SimTime - 0.01));

    Simulator::Stop (Seconds (SimTime));

    /*// Setting up Animation Interface nicely
    AnimationInterface::SetNodeDescription (ap, "AP"); // Optional
    AnimationInterface::SetNodeDescription (stas, "STA"); //b Optional
    AnimationInterface::SetNodeColor (ap, 0, 255, 0); // Optional
    AnimationInterface::SetNodeColor (stas, 255, 0, 0); // Optional

    AnimationInterface anim ("MyFirstAnimation.xml"); 
    //anim.SetMobilityPollInterval (Seconds (1));
    */
    //Config::Connect ("/NodeList/1/DeviceList/0/Phy/State/Tx", MakeCallback (&PhyTxTrace));
    //Config::Connect ("/NodeList/0/DeviceList/0/
    //	$ns3::WifiNetDevice/RemoteStationManager/$ns3::ConstantRateWifiManager", MakeCallback (&PhyTxTrace));

    Simulator::Run ();
    Simulator::Destroy ();


    //Ptr<UdpEchoClient> sink1 = DynamicCast<UdpEchoClient> (clientApps.Get (0));
  	//cout << "Total Bytes Received: " << sink1->GetTotalRx () << std::endl;

}