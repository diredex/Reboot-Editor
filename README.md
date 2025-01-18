# Reboot Plugin for Unreal Engine

Reboot is a powerful Unreal Engine plugin designed to streamline your workflow by enabling seamless editor restarts, intelligent instance management, and customizable settings. With this plugin, developers can enhance their productivity and focus on building great projects without worrying about multiple editor instances or cumbersome restarts.

---

## Features

### 1. **Force Restart**
- Restart the Unreal Engine editor directly from the menu with a single click.
- Assign an icon to the menu button for easy recognition.

### 2. **Instance Management**
- Detect multiple instances of the same project running on startup.
- Display warnings when multiple instances are detected.
- Automatically close extra instances or allow multiple instances as per your settings.

### 3. **Customizable Settings**
- Configure behavior through plugin settings, including:
  - Force Restart Default
  - Check for Multiple Instances on Startup
  - Automatically Close Multiple Instances
  - Allow Multiple Instances
- Settings changes take effect immediately with a prompt to restart the editor.

### 4. **User-Friendly Design**
- Persistent warning messages for better visibility when issues are detected.
- Integrated seamlessly with Unreal Engine’s menu and settings system.

---

## Installation

1. Download the plugin from the [GitHub Releases](#) page.
2. Place the plugin folder in your Unreal Engine project's `Plugins` directory.
3. Open the Unreal Engine editor and enable the plugin in the `Plugins` menu.
4. Restart the editor to complete the installation.

---

## Usage

### Force Restart
- Navigate to the menu where the "Force Restart" option is located.
- Click the button to restart the editor instantly.

### Settings Configuration
1. Open `Edit > Project Settings > Plugins > Reboot Settings`.
2. Adjust the following options to fit your needs:
   - **Force Restart Default**: Enable/disable the default restart behavior.
   - **Check for Multiple Instances on Startup**: Enable/disable instance detection.
   - **Automatically Close Multiple Instances**: Enable/disable automatic instance termination.
   - **Allow Multiple Instances**: Enable/disable support for multiple instances.
3. Save your changes, and follow the prompt to restart the editor if necessary.

---

## Contribution

We welcome contributions! To contribute:

1. Fork the repository.
2. Create a feature branch: `git checkout -b feature-name`.
3. Commit your changes: `git commit -m "Add some feature"`.
4. Push to the branch: `git push origin feature-name`.
5. Open a pull request.

Please ensure your code adheres to Unreal Engine's coding standards.

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## Support

If you encounter any issues or have questions, feel free to open an issue on GitHub or contact us via Discord(#).

---

Happy developing with Reboot!

