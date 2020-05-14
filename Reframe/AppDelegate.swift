//
//  AppDelegate.swift
//  Reframe
//
//  Created by Vincent Bernardi on 05/05/2020.
//  Copyright © 2020 Vincent Bernardi. All rights reserved.
//

import Cocoa

@NSApplicationMain
class AppDelegate: NSObject, NSApplicationDelegate {

    func application(_ sender: NSApplication, openFile filename: String) -> Bool {
        let bundleInfoDict: NSDictionary = Bundle.main.infoDictionary! as NSDictionary
        let appName = bundleInfoDict["CFBundleName"] as! String
        let slower = appName.contains("slower")
        print("1")
        print(filename)
        reframeFile(filename, slower)
        exit(1)
    }

    func application(_ sender: NSApplication, openFiles filenames: [String]) {
        let bundleInfoDict: NSDictionary = Bundle.main.infoDictionary! as NSDictionary
        let appName = bundleInfoDict["CFBundleName"] as! String
        let slower = appName.contains("slower")
        print("many")
        filenames.forEach { print($0) }
        filenames.forEach { reframeFile($0, slower) }
        exit(1)
    }

    private func reframeFile(_ filename: String, _ slower: Bool)
    {
        let path = Bundle.main.path(forResource: "reframe", ofType: "o")!
        let arguments = [filename, slower ? "slower" : "faster"]
        let task = Process.launchedProcess(launchPath: path, arguments: arguments)
        task.waitUntilExit()
    }

    func applicationDidFinishLaunching(_ aNotification: Notification) {
        // Insert code here to initialize your application
        let bundleInfoDict: NSDictionary = Bundle.main.infoDictionary! as NSDictionary
        let appName = bundleInfoDict["CFBundleName"] as! String
        print(appName)
    }

    func applicationWillTerminate(_ aNotification: Notification) {
        // Insert code here to tear down your application
    }


}

